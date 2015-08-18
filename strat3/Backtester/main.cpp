//#include "DataManager/DataManager.h"
#include "DataManager/MatrixManager.h"
#include "Backtester/Backtester.h"
#include "DataManager/Buffer.h"

#include <iostream>

using namespace strat3;
using std::cout;

int main()
{
    Backtester bt;

    // Create New Strategy

    NodeTuple strat;

    cout << "DLL loading\n";

    strat.load_portfolio("./libStandardPortfolio.so");
    strat.load_strategy("./libStandardStrategy.so");

    bt.add_strategy(&strat);

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
