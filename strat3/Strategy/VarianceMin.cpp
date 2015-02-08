
#include "../DataManager/DataQuery.h"
#include "VarianceMin.h"
#include "../smath.h"

VarianceMin::VarianceMin(Key managerKey, Key matrixkey, int securitySize,
            bool rebalanced, Index frequency):
    Strategy(managerKey, matrixkey, securitySize, rebalanced, frequency),
    _Sec(securitySize), _Window(20)
{
    // allocate memory
    _A = Matrix::Zero(securitySize + 1, securitySize + 1);
    _B = Matrix::Zero(securitySize + 1, 1);

    // weight constraint
    _A.block(0, securitySize, securitySize, 1) = - Matrix::Ones(securitySize, 1);
    _A.block(securitySize, 0, 1, securitySize) =   Matrix::Ones(1, securitySize);

    _B(securitySize, 0) = 1;

    _Description ="Minimal Variance Portfolio "
            "Compute the weights \\(x\\) which minimize the expected variance of the portfolio";

    _Title = "VarianceMin";
}

VarianceMin::~VarianceMin()
{}

void VarianceMin::setWindow(int x)
{
    _Window = x;
}

TransactionWeight* VarianceMin::operator() (DataStruct* dq, Predictor* m)
{
    // query data
    data = dq->dataManager->reverseMiddleRows(this->_FeatureManagerKey, this->_FeatureMatrixKey, _Window + 1);

    // compute returns
    ret = data.bottomRows(_Window).cwiseQuotient(data.topRows(_Window));
    ret = ret.unaryExpr(std::ptr_fun(log_double));

    // compute means
    mean = ret.colwise().mean();
    mean = (ret - Matrix::Ones(ret.rows(), 1) * mean);

    // compute covariance
    _A.block(0, 0, _Sec, _Sec) = (mean.transpose() * mean) / double(ret.rows());

    // compute weights
    this->_Weight.weight = _A.lu().solve(_B).topRows(_Sec);
    return &_Weight;
}
