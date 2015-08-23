#ifndef STRAT3_REPORT_VISITOR_HEADER
#define STRAT3_REPORT_VISITOR_HEADER

#include <vector>
#include "../enum.h"

struct SimpleMeanVarianceVisitor
{
public:
    typedef Eigen::ArrayXd ARow;

    SimpleMeanVarianceVisitor(int sizE):
        size(sizE), sum_std(ARow::Zero(sizE)), sum_mean(ARow::Zero(sizE)),
        e0(ARow::Zero(sizE)), element (ARow::Zero(sizE))
    {}


    void init(const double& x, uint i, uint j)
    {
        if (i == 0)
        {
            e0(j) = x;
            sum_mean(j) =  x - e0(j);
            sum_std (j) = (x - e0(j)) * (x - e0(j));
            element (j) = 1;
        }
        else
        {
            return this->operator ()(x, i, j);
        }
    }


    // we are going to use the following formula
    // E(X²) - E(X)²
    // e0 is mean to increase numeric stability when using large numbers
    void operator() (const double& x, uint i, uint j)
    {
        sum_mean(j) +=  x - e0(j);
        sum_std (j) += (x - e0(j)) * (x - e0(j));
        element(j)++;
    }

    Matrix get_means()      {   return e0 + sum_mean / element;                          }
    Matrix get_variance()   {   return  (sum_std - sum_mean.pow(2.0) / element) / element;         }
    Matrix get_sd()         {   return ((sum_std - sum_mean.pow(2.0) / element) / element).sqrt(); }

    int  size;
    ARow sum_std;
    ARow sum_mean;
    ARow e0;
    ARow element;
};

struct SkewKurtosisVisitor
{
    SkewKurtosisVisitor(const Matrix& mean, const Matrix& std):
        mean(mean), std(std), skew(Matrix::Zero(1, mean.cols())), kurtosis(Matrix::Zero(1, mean.cols())), n(0)
    {}

    void init(const double& x, Index i, Index j)
    {
        return this->operator ()(x, i, j);
    }

    void operator() (const double& x, Index i, Index j)
    {
        skew    (0, j) += pow((x - mean(0, j) ) / std(0, j), 3.0);
        kurtosis(0, j) += pow((x - mean(0, j) ) / std(0, j), 4.0);
        n = i + 1 > n ? i + 1: n;
    }

    Matrix get_skew() { return skew / n; }
    Matrix get_kurtosis() { return kurtosis / n; }

    const Matrix& mean;
    const Matrix& std;
    Matrix skew;
    Matrix kurtosis;
    double n;

};


struct MeanVarianceVisitor
{
    MeanVarianceVisitor(int size)
        :usual(size), negative(size), positive(size)
    {}

    void init(const double& x, Index i, Index j)
    {
        usual.init(x, i, j);

        // do not need e0 to be possitive or neg
//        if (x < 0)
            negative.init(x, i, j);
//        else
            positive.init(x, i, j);
    }

    void operator() (const double& x, Index i, Index j)
    {
        usual(x, i, j);

        if (x < 0)
        {
            negative(x, i, j);
        }
        else
        {
            positive(x, i, j);
        }
    }

    SimpleMeanVarianceVisitor usual;
    SimpleMeanVarianceVisitor negative;
    SimpleMeanVarianceVisitor positive;
};


//struct MovingStandardDeviation
//{
//    MovingStandardDeviation(uint window, uint cols):
//        window(window), cols(cols), data(Matrix::Zero(window, cols))
//    {}

//    void init(const double& x, Index i, Index j)
//    {
//       data(i, j) = x;
//    }

//    void operator() (const double& x, Index i, Index j)
//    {
//        data(i % window, j) = x;
//        (*moving_std)(i, j) = sqrt(data.col(j).cwiseProduct(data.col(j)).mean() - pow(data.col(j).mean(), 2));
//    }

//    uint window;
//    uint cols;
//    Matrix data;

//};

#endif
