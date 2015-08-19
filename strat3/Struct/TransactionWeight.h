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

struct BT_EXPORT TransactionWeight
{
    public:
        TransactionWeight::TransactionWeight():
            type(TotalPercentage)
        {}

        Matrix     weight;
        WeightType type;
};

#endif
