#ifndef STRAT3_STRATEGY_MAXDIVER_HEADER
#define STRAT3_STRATEGY_MAXDIVER_HEADER

#include "Strategy.h"

class MaximumDiversification: public Strategy
{
public:
    MaximumDiversification(Key managerKey, Key matrixkey, int securitySize,
                bool rebalanced = true, Index frequency = 1);

    ~MaximumDiversification();

    TransactionWeight* operator() (DataStruct* dq);

protected:

    Matrix data;
    Matrix ret;
    Matrix mean;
    Matrix cov;
    Matrix correl;
    Matrix A;
    Matrix B;
    Matrix std;

    int    _Window;
    int    _Sec;

};

#endif
