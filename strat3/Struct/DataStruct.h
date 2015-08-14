#ifndef STRAT3_SECURITY_DATASTRUCT_HEADER
#define STRAT3_SECURITY_DATASTRUCT_HEADER

#include <vector>
#include "../enum.h"
//#include "../Abstract/AbstractStrategy.h"

class DataQuery;
class SecurityDatabase;
class Predictor;

//struct MCBIRPStruct : public strat_init
//{
//    int simulation;
//    double min;
//    double max;
//    int seed;
//    bool fixed;
//};


// define what is available to each strategies
struct DataStruct
{
public:

    DataStruct(const Key& m, const Key& mat):
        managerKey(m), matrixKey(mat)
    {}

    DataQuery* dataManager;

    // TODO
    // make logs available as const

    std::vector<Predictor>* predictors;
    SecurityDatabase*       securities;

    unsigned int time;

    // return lastest price matrix from today to today - window period
    // latest price are at the bottom row
    Matrix price(int window);

    const Key& managerKey;
    const Key& matrixKey;
};

#endif
