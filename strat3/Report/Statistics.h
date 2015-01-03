#ifndef STRAT3_REPORT_STATISTICS_HEADER
#define STRAT3_REPORT_STATISTICS_HEADER

#include "../smath.h"

template<typename Type>
Eigen::Matrix<Type, -1, -1> get_matrix(std::vector<Type> &vec)
{
    return Eigen::Map<Eigen::Matrix<Type, -1, -1> >(&vec[0], 1, vec.size());
}

Matrix sort(Matrix x);
Matrix frequency(Matrix x, int bucket, bool percentage = true);
Matrix frequency(Matrix x, bool p = true);

struct Mean
{
public:
    Mean();
    void operator() (double x);

    double mean_operator(double x);
    double getMean();

    double sum;
    int element;
//    int    window;
};


// build visitor
struct SecondMoment
{
public:
    SecondMoment(int sizE);

    ~SecondMoment();
    void init(const double& x, Index i, Index j);

    // we are going to use the following formula
    // E(X²) - E(X)²
    // e0 is mean to increase numeric stability when using large numbers
    void operator() (const double& x, Index i, Index j);
    Matrix getAllMean();

    Matrix getAllVariance();
    Matrix getAllSD();

    double getSD      (Index j);
    double getVariance(Index j);
    double getMean    (Index j);

    std::vector<double> sum_std;
    std::vector<double> sum_mean;
    std::vector<double> e0;
    std::vector<   int> element;
    int                 size;
};

struct StatisticPoint
{
    StatisticPoint(int size)
        :usual(size), negative(size), positive(size)
    {}

    void init(const double& x, Index i, Index j)
    {
        usual.init(x, i, j);

        if (x < 0)
            negative.init(x, i, j);
        else
            positive.init(x, i, j);
    }

    void operator() (const double& x, Index i, Index j)
    {
        usual(x, i, j);

        if (x < 0)
        {
            if (negative.size == 0)
                negative.init(x, i, j);
            else
                negative(x, i, j);
        }
        else
        {
            if (positive.size == 0)
                positive.init(x, i, j);
            else
                positive(x, i, j);
        }
    }

    SecondMoment usual;
    SecondMoment negative;
    SecondMoment positive;
};


struct Drawdown
{
public:

    Drawdown()
    {}

    void init(const double& x, Index i, Index j)
    {
        max = x;
        cumulative_returns = x;
        drawdown.push_back(max);
    }

    void operator() (const double& x, Index i, Index j)
    {
        cumulative_returns += x;
        drawdown.push_back(max - cumulative_returns);
        max = std::max(cumulative_returns, max);
    }

    Matrix getDrawdown()
    {
        return Eigen::Map<Matrix>(&drawdown[0], drawdown.size(), 1);
    }

    std::vector<double> drawdown;
    double cumulative_returns;
    double max;
};


struct MovingStandardDeviation
{
    MovingStandardDeviation(int window, int cols, Matrix* st):
        window(window), cols(cols), data(Matrix::Zero(window, cols)),
        moving_std(st)
    {}

    void init(const double& x, Index i, Index j)
    {
        data(i, j) = x;
    }

    void operator() (const double& x, Index i, Index j)
    {
        //pos[j]++;
        data(i % window, j) = x;
        (*moving_std)(i, j) = sqrt(data.col(j).cwiseProduct(data.col(j)).mean() - pow(data.col(j).mean(), 2));
    }

    int window;
    int cols;

    Matrix data;
    Matrix* moving_std;

    //std::vector<int> pos;
};

const char* get_month(int x);
const char* get_week(int x);



#endif
