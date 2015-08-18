#ifndef STRAT3_SECURITY_DATASTRUCT_HEADER
#define STRAT3_SECURITY_DATASTRUCT_HEADER

#include <vector>
#include "../enum.h"

class MatrixQuery;
class SecurityDatabase;
class Predictor;


// define what is available to each strategies
struct DataStruct
{
public:

    DataStruct(const Key& mat):
        matrix_key(mat)
    {}

    MatrixQuery* dataManager;

    // TODO
    // make logs available as const

    std::vector<Predictor>* predictors;
    SecurityDatabase*       securities;

    unsigned int time;

    // return lastest price matrix from today to today - window period
    // latest price are at the bottom row
    Matrix price(int window);

    const Key& matrix_key;
};

#endif
