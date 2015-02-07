#ifndef STRAT3_STRAT3_SMATH_HEADER
#define STRAT3_STRAT3_SMATH_HEADER
/*!
 * implement basics functions
 */

#include "enum.h"
#include <cmath>


// this function should be in the std library seriously
// even excel has it
/*!
 * \brief trunc trunc a floating point number at the nth decimal
 * \param x
 * \param n
 * \return truncated number
 */
template<typename T>
T trunc(T x, int decimal = 2)
{
    T xx = (int(x * pow(T(10), T(decimal))) / pow(T(10), T(decimal)));

    // if x is nan
    // TODO rethink it
    if ((xx >= 2.14748e+07) || (xx <= -2.14748e+07))
            return x;

    return xx;
}

// we force specialization because we had troubles with eigen's Matrix and unaryExpr
// (complex numbers were involved)
double log_double(double x);

// assume data are from older to newer
Matrix compute_returns      (const Matrix& data_price);
Matrix compute_covariance   (const Matrix& data_percentage);
Matrix compute_correlation  (const Matrix& data_covariance);

Key get_bool_as_string(bool a);

#endif
