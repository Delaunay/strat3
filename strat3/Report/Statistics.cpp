#include "Statistics.h"

Matrix sort(Matrix x)
{
    Matrix temp = x;
    double min = 0;
    double buf = 0;

    for (int j = 0, m = x.cols(); j < m; j++)
    {
        for (int i = 0, n = x.rows(); i < n; i++)
        {
            min = temp(i, j);

            for (int k = i; k < n; k++)
                if (min > temp(k, j))
                {
                    buf = temp(k, j);
                    temp(k, j) = min;
                    temp(i, j) = buf;
                    min = buf;
                }
        }
    }

    return temp;
}

// compute the frequency
// bucket have the same size
Matrix frequency(Matrix x, int bucket, bool percentage)
{
    double min = x.minCoeff();
    double max = x.maxCoeff();

    double step = (max - min) / double(bucket);
    Matrix freq = Matrix::Zero(bucket, x.cols() + 2);

    // first we sort the matrix

    Matrix temp = sort(x);

    // cols
    for (int k = 0, m = x.cols(); k < m; k++)
    {
        int j = 1;
        // rows
        for (int i = 0, n = x.rows(); i < n; i++)
        {
            if (temp(i, k) <= double(j) * step  + min)
            {
                freq(j - 1, k + 2) += 1;
            }
            else
            {
                // we want to go until max is reached
                if (j != bucket)
                    j++;
                else
                    break;
            }
        }
    }

    for (int i = 0; i < bucket; i ++)
    {
        freq(i, 0) = double(i) * step + min;          // lower bound
        freq(i, 1) = double(i + 1) * step + min;      // upper bound
    }

    if (percentage)
        freq.block(0, 2, freq.rows(), x.cols()) = freq.block(0, 2, freq.rows(), x.cols()) / x.rows();

    return freq;
}

Matrix frequency(Matrix x, bool p)
{
    return frequency(x, 4 * sqrt(x.rows()), p);
}


Mean::Mean():
    sum(0), element(0)//, window(0)
{}

void Mean::operator() (double x)
{
    element++;
    sum += x;
}

double Mean::mean_operator(double x)
{
    sum += x;
    element++;
    return sum / double(element);
}

double Mean::getMean() {  return sum / double(element); }

SecondMoment::SecondMoment(int sizE):
    size(sizE), sum_std (std::vector<double>(sizE)), sum_mean(std::vector<double>(sizE)),
    e0(std::vector<double>(sizE)), element (std::vector<int>(sizE))
{}

SecondMoment::~SecondMoment()
{}

void SecondMoment::init(const double& x, Index i, Index j)
{
    e0[j] = x;
    sum_mean[j] =  x - e0[j];
    sum_std [j] = (x - e0[j]) * (x - e0[j]);
    element [j] = 1;
}

void SecondMoment::operator() (const double& x, Index i, Index j)
{
    sum_mean[j] +=  x - e0[j];
    sum_std [j] += (x - e0[j]) * (x - e0[j]);
    element [j]++;
}

Matrix SecondMoment::getAllMean()
{
    Matrix mean = Matrix::Zero(1, size);

    for(int i = 0; i < size; i++)
    {
        mean(0, i) = getMean(i);
    }

    return mean;
}

Matrix SecondMoment::getAllVariance()
{
    Matrix mean = Matrix::Zero(1, size);

    for(int i = 0; i < size; i++)
    {
        mean(0, i) = getVariance(i);
    }

    return mean;
}

Matrix SecondMoment::getAllSD()
{
    Matrix mean = Matrix::Zero(1, size);

    for(int i = 0; i < size; i++)
    {
        mean(0, i) = getSD(i);
    }

    return mean;
}

double SecondMoment::getSD      (Index j) { return sqrt(getVariance(j)); }
double SecondMoment::getVariance(Index j) { return (sum_std[j] - sum_mean[j] * sum_mean[j] / double(element[j])) / double(element[j]); }
double SecondMoment::getMean    (Index j) { return e0[j] + sum_mean[j] / double(element[j]); }

const char* get_month(int x)
{
    switch(x)
    {
    case 0:
        return "Jan";
    case 1:
        return "Feb";
    case 2:
        return "Mar";
    case 3:
        return "Apr";
    case 4:
        return "May";
    case 5:
        return "Jun";
    case 6:
        return "Jul";
    case 7:
        return "Aug";
    case 8:
        return "Sep";
    case 9:
        return "Oct";
    case 10:
        return "Nov";
    case 11:
        return "Dec";
    default:
        return "Dec";
    }
}

const char* get_week(int x)
{
    switch(x)
    {
    case 0:
        return "Sun";
    case 1:
        return "Mon";
    case 2:
        return "Tue";
    case 3:
        return "Wed";
    case 4:
        return "Thu";
    case 5:
        return "Fri";
    case 6:
        return "Sat";

    default:
        return "Mon";
    }
}



