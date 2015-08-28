//#include "DataManager/DataManager.h"
#include "DataManager/MatrixManager.h"
#include "Backtester/Backtester.h"
#include "DataManager/Buffer.h"
#include "Report/DataAnalyzer.h"
#include "Report/Latex.h"

#include <iostream>

// "./" make the prog seek the dll in the exe folder
std::string name_fix(const std::string& name, const std::string& path ="./")
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

int main()
{
    Backtester bt;

    // Create New Strategy
    cout << "DLL loading\n";

    NodeTuple strat;
    strat.load_portfolio(name_fix("StandardPortfolio"));
    strat.load_strategy(name_fix("StandardStrategy"));

//    strat.load_strategy(name_fix("MovingAverageStrategy"));

    bt.add_strategy(&strat);

    cout << "DLL loaded\n";
    cout << "File Reading\n";

    // load data
    CSVReader csv_dat("../../data/date_test.csv");

    std::vector<std::string> sec_name = csv_dat.get_header(1);
    Matrix m = csv_dat.get_eigen3<MatrixRowMajor>(false);

    Matrix date = m.leftCols(3);
    Matrix data = m.rightCols(m.cols() - 3);

    MatrixManager mm;
    mm.add_matrix("price", data);

    Eigen::IOFormat fmt;
    for(auto& el:sec_name)
        std::cout << el << "\t";

    cout << "\n" << data.topRows(5).format(fmt) << "\n";

    // set Data
    bt.set_data_manager(&mm, "price");
    bt.dates() = date;
    bt.set_security_name(sec_name);

    strat.portfolio()->initialize(1000, data.cols());
    strat.strategy()->initialize(data.cols());

    bt.set_strat_window(251);
    bt.initialize();

    // Run simulation
    for(int i = 0, n = bt.max_period(); i < n; ++i)
        bt.run_one_step();

    std::cout << "BT Finished" <<std::endl;

    uint n_sec = bt.strategy_log().security_number();

//    std::vector<std::string> security_names;
//    for(int i = 0; i < n_sec; ++i)
//        security_names.push_back("Sec" + std::to_string(i));

    bt.strategy_log().dump();

    DataAnalyzer da(bt.strategy_name(), sec_name, bt.strategy_log());

    da.compute_statistics();
    da.dump();

#if __linux__
    Latex ltx(da, bt);

//    ltx.body();

    ltx.generate();
#endif
    return 0;
}
