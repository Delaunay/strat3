#ifndef STRAT3_ENUM_HEADER
#define STRAT3_ENUM_HEADER

#if __linux
#include <eigen3/Eigen/Dense>
#else
#include <Eigen/dense>
#endif

#ifdef __linux__
#   define BT_EXPORT __attribute__ ((visibility ("default")))
#else
#   define BT_EXPORT __declspec(dllexport)
#endif

typedef unsigned int        uint;
typedef std::string         Key;
typedef std::string         FileName;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>     Matrix;
typedef Eigen::VectorXd     Column;
typedef Eigen::RowVectorXd  Row;
typedef unsigned int        Index;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixRowMajor;
typedef Eigen::Array <double, Eigen::Dynamic, Eigen::Dynamic> Array;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixRM;
typedef Eigen::Array <double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ArrayRM;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> MatrixCM;
typedef Eigen::Array <double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> ArrayCM;
typedef Eigen::Map<Matrix> MatrixMap;
typedef Eigen::Map<MatrixRM> MatrixRMMap;
typedef Eigen::Map<Array> ArrayMap;
typedef Eigen::Map<ArrayRM> ArrayRMMap;
typedef Eigen::Map<const Matrix> ConstMatrixMap;

#endif
