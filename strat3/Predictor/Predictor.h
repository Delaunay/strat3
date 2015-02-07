#ifndef STRAT3_PREDICTOR_PREDICTOR_HEADER
#define STRAT3_PREDICTOR_PREDICTOR_HEADER

#include <vector>

#include "../enum.h"

struct DataStruct;

/*!
 * \brief The Predictor class is used to compute useful statistics that may be reused
 * on multiple strategies to prevent them from computing multiple times the same things
 * example: expected Covariance Matrix, expected returns etc...
 */
class Predictor
{
public:
    enum Fields
    {
        Covariance,
        Returns,
        ExpectedCovariance,
        ExpectedReturns,
        MAX
    };

    Predictor()
    {}

    //! compute prediction
    virtual void predict(DataStruct*) = 0;

    //! returns computed prediction
    virtual const Matrix& prediction(int i) = 0;

protected:

    // Predictor Version
    Index             _Version;
    std::string       _Description;
    std::string       _Title;

};

#endif
