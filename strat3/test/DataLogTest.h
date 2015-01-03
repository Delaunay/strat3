
#include <gtest/gtest.h>

#include "StrategyTest.h"
#include "../DataLog/DataLog.h"
#include "../Portfolio/Portfolio.h"

TEST(DataLog, PortfolioState)
{
    Portfolio   pf(2, 1000, "../gen/testlog", 0);
    EqualWeight strat("GTFO", "GTFO", 2);
    DataManager DM;
    DataQuery   DQ = DM.dataQuery(0, 0);

    TransactionWeight* w = strat(&DQ);
    Row price[2];
    price[0] = Row::Zero(1, 2);
    price[1] = Row::Zero(1, 2);

    price[0](0, 0) = 50;
    price[0](0, 1) = 100;

    price[1](0, 0) = 60;
    price[1](0, 1) = 70;

    // portfolio test
    for (int i = 0; i < 5; i ++)
        pf.processTransactionWeight(i, &price[i % 2], w);

//    DataLog* log = pf.log();

//    Matrix rs = log->readPortfolioState();
//    std::cout << "State" << std::endl << rs << std::endl << std::endl;

//    Matrix rw = log->readWeightMatrix();
//    std::cout << "Weight" << std::endl << rw << std::endl << std::endl;

//    Matrix ro = log->readTransactionOrder();
//    std::cout << "Order" << std::endl << ro << std::endl << std::endl;

//    Matrix rv = log->readPortfolioValues();
//    std::cout << "Values" << std::endl << rv << std::endl << std::endl;

//    // check size
//    EXPECT_EQ(m.cols(), state.rows() + 1);
//    EXPECT_EQ(m.rows(), time);
}

