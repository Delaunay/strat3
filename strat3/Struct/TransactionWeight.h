#ifndef STRAT3_STRUCT_TRANSACTIONWEIGHT_HEADER
#define STRAT3_STRUCT_TRANSACTIONWEIGHT_HEADER

#include "../enum.h"

enum WeightType{
    TotalPercentage,
    DifferentialPercentage,
    TotalShare,
    DifferentialShare,
    NoTransaction
};

struct TransactionWeight
{
    public:
        TransactionWeight();
        Matrix     weight;
        WeightType type;
};

#endif
