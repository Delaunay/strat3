#include "smath.h"

double log_double(double x)
{
    return log(x);
}

// assume data are from older to newer
Matrix compute_returns(const Matrix& data)
{
    int n = data.rows();
    Matrix ret = data.bottomRows(n - 1).cwiseQuotient(data.topRows(n - 1));
    return ret.unaryExpr(std::ptr_fun(log_double));
}

Matrix compute_covariance(const Matrix& data)
{
    Matrix mean = data.colwise().mean();
    mean = (data - Matrix::Ones(data.rows(), 1) * mean);
    return (mean.transpose() * mean) / double(data.rows());
}

Matrix compute_correlation(const Matrix& cov)
{
    //Matrix cov = compute_covariance(data);
    Matrix correl = Matrix::Zero(cov.rows(), cov.cols());

    for(int i = 1, n = cov.rows(); i < n; i++)
        for(int j = 0; j < i; j++)
            correl(i, j) = cov(i, j) / sqrt(cov(i, i) * cov(j, j));

    correl = correl + correl.transpose().eval();
    correl.diagonal() = Eigen::Diagonal<Matrix>::Ones(cov.rows(), 1);

    return correl;
}

Key get_bool_as_string(bool a)
{
    if (a)
        return "true";
    else
        return "false";
}
