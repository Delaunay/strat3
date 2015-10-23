#ifndef STRAT3_NETWORK_COMM_HEADER
#define STRAT3_NETWORK_COMM_HEADER

#include <string>
#include <vector>

enum 
{
    ENM_DATAREQUEST,
    ENM_MATRIXDATA,
    ENM_DATAANSWER,
    ENM_TRANSACTIONWEIGHT
};

struct NetworkDataRequest
{
    unsigned int type{ENM_DATAREQUEST};
    unsigned int strategy;
    const std::string& k;
    unsigned int nb;
    unsigned int startRow;
};

struct NetworkMatrixData
{
    unsigned int type{ENM_MATRIXDATA};
    unsigned int strategy;
    unsigned int rows;
    unsigned int cols;
    std::vector<double> matrix;
};

struct NetworkDataAnswer
{
    unsigned int type{ENM_DATAANSWER};
    std::string key;
    NetworkMatrixData data;
};

struct NetworkTransactionWeight
{
    unsigned int type{ENM_TRANSACTIONWEIGHT};
    unsigned int strategy;
};

//struct

#endif
