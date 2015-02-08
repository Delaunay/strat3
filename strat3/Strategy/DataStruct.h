#ifndef STRAT3_SECURITY_DATASTRUCT_HEADER
#define STRAT3_SECURITY_DATASTRUCT_HEADER

#include <vector>

class DataQuery;
class SecurityDatabase;
class Predictor;

// define what is available to each strategies
struct DataStruct
{
public:
    DataQuery* dataManager;

    // TODO
    // make logs available as const

    std::vector<Predictor>* predictors;
    SecurityDatabase*       securities;

    unsigned int time;
};

#endif
