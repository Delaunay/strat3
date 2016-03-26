#ifndef STRAT3_SECURITY_DATASTRUCT_HEADER
#define STRAT3_SECURITY_DATASTRUCT_HEADER

#include "../enum.h"
#include "DataManager/MatrixManager.h"

#include <vector>

// define what is available to each strategies
struct BT_EXPORT DataStruct
{
public:

    DataStruct(const Key& mat):
        matrix_key(mat), data_manager(0)
    {}

    // TODO
    // make logs available as const
    //std::vector<Predictor>* predictors;
    //SecurityDatabase*       securities;

    unsigned int time;

    // return lastest price matrix from today to today - window period
    // latest price are at the bottom row
    Matrix price(int window) const
    {
        return data_manager->bottom_rows(matrix_key, window);
    }

    const Key& matrix_key;

    MatrixQuery* data_manager;
};

#endif
