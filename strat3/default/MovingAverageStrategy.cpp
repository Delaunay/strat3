#define NEW_PLUGIN
#include "Abstract/Strategy.h"
#include "Struct/DataStruct.h"
#include "Struct/TransactionWeight.h"

#include <iostream>

typedef unsigned int uint;

struct TransactionWeight;

class PLUGIN_EXPORT MAStrategy : public Strategy
{

public:

    MAStrategy()
    {
        this->title = "MovingAverage";
        this->strategy_window = ltaverage_window;
//        this->weight_type() = NoTransaction;
    }

    void initialize(const uint& nsecurity, const uint& nstrat = 1, const void* user_data = 0)
    {
        _nsecurity = nsecurity;
        weight() = Matrix::Constant(_nsecurity, nstrat, 0);
        signal = Matrix::Constant(_nsecurity, nstrat, 0);
    }

    const TransactionWeight* operator() (const DataStruct& ds)
    {
        // request latest prices
        Matrix price = ds.price(ltaverage_window);

//        std::cout << "(" << price.rows() << "x" << price.cols() << ")" << std::endl;

        t1 = t2;
        pos_t1 = pos_t2;
        ltaverage_t1 = ltaverage_t2;
        staverage_t1 = ltaverage_t2;

        // compute averages
        t2 = ds.time;
        ltaverage_t2 = price.colwise().mean();
        staverage_t2 = price.bottomRows(staverage_window).colwise().mean();

        // new signal
        pos_t2 = (ltaverage_t2.array() > staverage_t2.array()).cast<double>();

        if (set){
            signal = signal + (pos_t2 - pos_t1).transpose();
            weight() = signal / signal.sum();
//            weight_type() = TotalPercentage;
        }

        set = true;
        return &tw();
    }

    uint   t1;
    Matrix ltaverage_t1;
    Matrix staverage_t1;
    Matrix pos_t1;

    uint   t2;
    Matrix ltaverage_t2;
    Matrix staverage_t2;
    Matrix pos_t2;

    Matrix signal;

    uint ltaverage_window{250};
    uint staverage_window{50};
private:
    bool set{false};
};

void* create_object()
{
    return new MAStrategy();
}
void destroy_object(void* o)
{
    delete (MAStrategy*) o;
}
