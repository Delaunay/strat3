

#include "MaximumDiversification.h"
#include "../DataManager/DataQuery.h"
#include "../smath.h"

MaximumDiversification::MaximumDiversification(Key managerKey, Key matrixkey, int securitySize,
            bool rebalanced, Index frequency):
    Strategy(managerKey, matrixkey, securitySize, rebalanced, frequency),
    _Sec(securitySize), _Window(20)
{

_Description ="Maximum Diversification Portfolio "
        "Compute the weights \\(x\\) which maximize the Diversification Ratio";

_Title = "MaxDiv";

A = Matrix::Zero(_Sec + 1, _Sec + 1);
B = Matrix::Zero(_Sec + 1, 1);

B(_Sec, 0) = 1;
}


MaximumDiversification::~MaximumDiversification()
{}


TransactionWeight* MaximumDiversification::operator() (DataStruct* dq, Predictor* m)
{
    data = dq->dataManager->reverseMiddleRows(this->_FeatureManagerKey, this->_FeatureMatrixKey, _Window + 1);

    // compute returns
    ret = data.bottomRows(_Window).cwiseQuotient(data.topRows(_Window));
    ret = ret.unaryExpr(std::ptr_fun(log_double));

    // compute covariance
    mean = ret.colwise().mean();
    mean = (ret - Matrix::Ones(ret.rows(), 1) * mean);

    cov = (mean.transpose() * mean) / double(ret.rows());

    // compute correlation
    correl = Matrix::Zero(cov.rows(), cov.cols());

    for(int i = 1, n = cov.rows(); i < n; i++)
        for(int j = 0; j < i; j++)
            correl(i, j) = cov(i, j) / sqrt(cov(i, i) * cov(j, j));

    correl = correl + correl.transpose().eval();
    correl.diagonal() = Eigen::Diagonal<Matrix>::Ones(cov.rows(), 1);

    A.block(0, 0, cov.rows(), cov.cols()) = correl;

    A.block(0, _Sec, _Sec, 1) = - Matrix::Ones(cov.rows(), 1);
    A.block(_Sec, 0, 1, _Sec) = Matrix::Ones(1, cov.cols());

    std = cov.diagonal().cwiseSqrt();

    //std::cout << std << std::endl<< std::endl;

    // compute weights
    this->_Weight.weight = A.lu().solve(B).topRows(_Sec);
    this->_Weight.weight.cwiseQuotient(std);

    for(int i = 0; i < _Sec; i++)
        _Weight.weight(i) = _Weight.weight(i) / std(i);

    this->_Weight.weight = this->_Weight.weight / this->_Weight.weight.sum();
    // std::cout << _Weight.weight  << std::endl;

    return &_Weight;
}
