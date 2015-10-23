//#include "DataManager/DataManager.h"
#include "DataManager/MatrixManager.h"
#include "Backtester/Backtester.h"
#include "DataManager/Buffer.h"
#include "Report/DataAnalyzer.h"
#include "Report/Latex.h"
#include "Report/HTML.h"

#include <iostream>

// "./" make the prog seek the dll in the exe folder
std::string name_fix(const std::string& name, const std::string& path = "./")
{
#ifdef __linux__
    return path + "lib" + name + ".so";
#elif __MINGW32__
    return path + "lib" + name + ".dll";
#else
    return path + name + ".dll";
#endif
}


using namespace strat3;
using std::cout;

int main(int argc, char* argv[])
{
    Backtester bt;

    // Create New Strategy
    cout << "DLL loading\n";

    ADD_TRACE("Load Portfolio DLL");
    NodeTuple strat;
    strat.load_portfolio(name_fix("StandardPortfolio"));


    ADD_TRACE("Load Strategy DLL");
    strat.load_strategy(name_fix("StandardStrategy"));
    bt.add_strategy(&strat);


    ADD_TRACE("Load Data");
    CSVReader csv_dat("../../data/date_test.csv");

    std::vector<std::string> sec_name = csv_dat.get_header(1);
    Matrix m = csv_dat.get_eigen3<MatrixRowMajor>(false);

    Matrix date = m.leftCols(3);
    Matrix data = m.rightCols(m.cols() - 3);

    MatrixManager mm;
    mm.add_matrix("price", data);

    // little data preview
    Eigen::IOFormat fmt;
    for(auto& el:sec_name)
        std::cout << el << "\t";

    cout << "\n" << data.topRows(5).format(fmt) << "\n";

    // set data
    bt.set_data_manager(&mm, "price");
    bt.dates() = date;
    bt.set_security_name(sec_name);

    // initialize Simulation
    strat.portfolio()->initialize(1000, data.cols());
    strat.strategy()->initialize(data.cols());

    bt.set_strat_window(1);
    bt.initialize();

    // Run simulation

    ADD_TRACE("Simulation Starting");
    for(int i = 0, n = bt.max_period(); i < n; ++i)
        bt.run_one_step();

    ADD_TRACE("Analyse Data");
    DataAnalyzer da(bt.strategy_name(), sec_name, bt.strategy_log());
    da.compute_statistics();


    ADD_TRACE("Generate Report");
    HTML ltx(da, bt);
    ltx.generate();

    return 0;
}
