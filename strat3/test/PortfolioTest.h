#include <gtest/gtest.h>

#include "StrategyTest.h"
#include "../DataLog/DataLog.h"
#include "../Portfolio/Portfolio.h"

TEST(Portfolio, Operator)
{
    Portfolio   pf(2, 1000, "../gen/EqualWeight", 0);
    EqualWeight strat("GTFO", "GTFO", 2);
    DataManager DM;
    DataQuery   DQ = DM.dataQuery(0, 0);
    DataStruct  ds;
    ds.dataManager = &DQ;

    TransactionWeight* w = strat(&ds);
    Row price(1, 2);
    price(0, 0) = 50;
    price(0, 1) = 100;

    // portfolio test
    pf.processTransactionWeight(0, &price, w);

//    Matrix pstate = pf.log()->readPortfolioState();
//    std::cout << pstate << std::endl;
}
