#ifndef STRAT3_TEST_STRATEGY_HEADER
#define STRAT3_TEST_STRATEGY_HEADER

#include "../Strategy/Strategy.h"
#include <gtest/gtest.h>

class EqualWeight : public Strategy
{
    public:
        EqualWeight(Key managerKey, Key matrixkey, int securitySize):
            Strategy(managerKey, matrixkey, securitySize),
            _Set(false)
        {
            _Title = "EW";
            _Description = "Equal Weighted Portfolio";
            _Version = 1;
        }

        TransactionWeight* operator() (DataStruct* m, Predictor* p = 0)
        {
            if (!_Set)
            {
                _Weight.weight = Column::Constant(_Weight.weight.rows(), 1, 1.0/double(_Weight.weight.rows()));
                _Set = true;
            }

            return &(_Weight);
        }

    protected:

        bool _Set;
};

TEST(Strategy, Operator)
{
    EqualWeight A("GTFO", "GTFO", 2);
    DataManager B;
    DataQuery   C = B.dataQuery(0, 0);

    DataStruct ds;
    ds.dataManager = &C;

    TransactionWeight* w = A(&ds);

    EXPECT_EQ(w->weight(0, 0), 0.5);
    EXPECT_EQ(w->weight(1, 0), 0.5);
}

#endif
