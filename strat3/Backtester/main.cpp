//#include "DataManager/DataManager.h"
#include "DataManager/MatrixManager.h"
#include "Backtester/Backtester.h"
#include "DataManager/Buffer.h"
#include "Report/DataAnalyzer.h"

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
    CSVReader csv_dat("../../data/data.csv");

    Matrix m = csv_dat.get_eigen3<MatrixRowMajor>();

    MatrixManager mm;
    mm.add_matrix("price", std::move(m));

    Eigen::IOFormat fmt;
    cout << m.topRows(5).format(fmt) << "\n";

    // set Data
    bt.set_data_manager(&mm, "price");

    strat.portfolio()->initialize(1000, m.cols());
    strat.strategy()->initialize(m.cols());

    bt.set_strat_window(251);
    bt.initialize();

    // Run simulation
    for(int i = 0, n = bt.max_period(); i < n; ++i)
        bt.run_one_step();

    std::cout << "BT Finished" <<std::endl;

    uint n_sec = bt.strategy_log().security_number();

    std::vector<std::string> security_names;
    for(int i = 0; i < n_sec; ++i)
        security_names.push_back("Sec" + std::to_string(i));

    bt.strategy_log().dump();

    DataAnalyzer ltx(bt.strategy_name(), security_names, bt.strategy_log());

    ltx.compute_statistics();

    ltx.dump();

    return 0;
}
