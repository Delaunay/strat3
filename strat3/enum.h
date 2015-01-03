#ifndef STRAT3_ENUM_HEADER
#define STRAT3_ENUM_HEADER

#if __linux
#include <eigen3/Eigen/Dense>
#else
#include <Eigen/dense>
#endif


typedef std::string         Key;
typedef std::string         FileName;
typedef Eigen::MatrixXd     Matrix;
typedef Eigen::VectorXd     Column;
typedef Eigen::RowVectorXd  Row;
typedef unsigned int        Index;


#endif
