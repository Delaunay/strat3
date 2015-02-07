#ifndef STRAT3_STRATEGY_VARMIN_HEADER
#define STRAT3_STRATEGY_VARMIN_HEADER

#include "Strategy.h"

class VarianceMin : public Strategy
{
public:
    VarianceMin(Key managerKey, Key matrixkey, int securitySize,
                bool rebalanced = true, Index frequency = 1);

    ~VarianceMin();

    void setWindow(int x);

    TransactionWeight* operator() (DataStruct* dq);
    //TransactionWeight* operator() (DataQuery* dq);

protected:


    int    _Window;
    int    _Sec;

    // pre allocate memory

    // return matrix
    Matrix data;
    Matrix ret;
    Matrix mean;

    // Equation system (Only the covariance mat change)
    Matrix _A;
    Matrix _B;
};

#endif
