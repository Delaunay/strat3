//#include "DataManager/DataManager.h"
#include "DataManager/MatrixManager.h"
#include "Backtester/Backtester.h"
#include "DataManager/Buffer.h"

#include <iostream>

//#ifdef __linux__
//#   define name_fix(path, name) "./" + string(path) + "lib" + string(name) + ".so"
//#else
//#   define name_fix(path, name) "./" + string(path) + string(name) + ".dll"
//#endif



std::string name_fix(const std::string& name, const std::string& path ="./")
{
#ifdef __linux__
    return path + "lib" + name + ".so";
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

    NodeTuple strat;

    cout << "DLL loading\n";

    strat.load_portfolio(name_fix("StandardPortfolio-debug"));
    strat.load_strategy(name_fix("StandardStrategy-debug"));

    bt.add_strategy(&strat);

    cout << "DLL loaded\n";
    cout << "File Reading\n";

    // load data
    CSVReader csv_dat("../../data/data.csv");

    Matrix m = csv_dat.get_eigen3<MatrixRowMajor>();

    MatrixManager mm;
    mm.add_matrix("price", &m, false);

    Eigen::IOFormat fmt;
    cout << m.topRows(5).format(fmt) << "\n";

    // set Data
    bt.set_data_manager(&mm, "price");

    strat.portfolio()->initialize(1000, m.cols());
    strat.strategy()->initialize(m.cols());

    bt.initialize();

    // Run simulation
    for(int i = 0, n = bt.max_period(); i < n; ++i)
        bt.run_one_step();

//    cout << "Data Dump\n";
    bt.strategy_log().dump();

    std::cout << bt.strategy_log().security_number() << "\n";

//    const std::vector<double>& v = bt.strategy_log().time_serie({"EqualWeighted", "st_weights"});

//    for(int i = 0; i < v.size(); ++i)
//    {
//        std::cout << v[i] << "\t";

//        if ((i + 1) % 7 == 0)
//            std::cout << "\n";
//    }

    return 0;
}
