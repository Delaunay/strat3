// This file containts helper function to translate C++ function into python
#ifndef STRAT3_PYTHON_MATRIX_HEADER
#define STRAT3_PYTHON_MATRIX_HEADER
#include <string>
#include <Python.h>
#include "../enum.h"

// Shortcut
typedef Eigen::PartialPivLU<Matrix>         PartialLU;
typedef Eigen::FullPivLU<Matrix>            FullLU;
typedef Eigen::HouseholderQR<Matrix>        QR;
typedef Eigen::ColPivHouseholderQR<Matrix>  ColQR;
typedef Eigen::FullPivHouseholderQR<Matrix> FullQR;
typedef Eigen::LLT<Matrix>                  LLT;
typedef Eigen::LDLT<Matrix>                 LDLT;

typedef Eigen::JacobiSVD<Matrix>            JacobiSVD;

typedef Eigen::SelfAdjointEigenSolver<Matrix>            SAEigenSolver;
typedef Eigen::ComplexEigenSolver<Matrix>                CEigenSolver;
typedef Eigen::EigenSolver<Matrix>                       EigenSolver;
typedef Eigen::GeneralizedSelfAdjointEigenSolver<Matrix> GSAEigenSolver;
typedef Eigen::Tridiagonalization<Matrix>                Tridiag;

namespace strat3{
namespace python{
namespace matrix{

    template<typename Mat = Matrix>
    double get_val_matrix(Mat const & self, int const & x, int const & y)
    {
        return self(x, y);
    }

    template<typename Mat = Matrix>
    void set_val_matrix(Mat & self, int const & x, int const & y, double val)
    {
        self(x, y) = val;
    }

    template<typename Mat = Matrix>
    std::string str_matrix(Mat const & self)
    {
        std::stringstream a;
        a << self;
        return a.str();
    }

    template<typename Mat = Matrix>
    Column get_col_matrix(Mat const & self, int const & x)
    {
        return self.col(x);
    }

    template<typename Mat = Matrix>
    void set_col_matrix(Mat & self, int const & x, Column const & col)
    {
        self.col(x) = col;
    }

    template<typename Mat = Matrix>
    Row get_row_matrix(Mat const & self, int const & x)
    {
        return self.row(x);
    }

    template<typename Mat = Matrix>
    void set_row_matrix(Mat & self, int const & x, Row const & row)
    {
        self.row(x) = row;
    }

    template<typename Mat = Matrix>
    Mat get_block_matrix(Mat const & self,
                     int const& x1,
                     int const& x2,
                     int const& y1,
                     int const & y2)
    {
        return self.block(x1, x2, y1, y2);
    }
    template<typename Mat = Matrix>
    void set_block_matrix(Mat & self,
                     int const& x1,
                     int const& x2,
                     int const& y1,
                     int const & y2, Matrix block)
    {
        self.block(x1, x2, y1, y2) = block;
    }

    template<typename Mat = Matrix>
    void set_item_int(Mat & self, PyObject *tuple, int a)
    {
        // read agguments
        PyObject* obj1 = PyTuple_GET_ITEM(tuple, 0);
        PyObject* obj2 = PyTuple_GET_ITEM(tuple, 1);

        PySliceObject* slice1 = 0;
        PySliceObject* slice2 = 0;

        if (PySlice_Check(obj1) == true)
        {
            slice1 = (PySliceObject*)(obj1);
        }

        if (PySlice_Check(obj2) == true)
        {
            slice2 = (PySliceObject*)(obj2);
        }

        /*long */int start_row, stop_row, step_row, length_row = 1;
        /*long */int start_col, stop_col, step_col, length_col = 1;

        if (slice1 != 0)
        {
            PySlice_GetIndicesEx(slice1, self.rows(),
                                 &start_row,
                                 &stop_row,
                                 &step_row,
                                 &length_row);
        }
        else if (PyInt_Check(obj1)) // if not a slice, it is a number
        {
            start_row = PyInt_AsLong(obj1);
        }

        if (slice2 != 0)
        {
            PySlice_GetIndicesEx(slice2, self.cols(),
                                 &start_col,
                                 &stop_col,
                                 &step_col,
                                 &length_col);
        }
        else if (PyInt_Check(obj2)) // if not a slice, it is a number
        {
            start_col = PyInt_AsLong(obj2);
        }

        self.block(start_row, start_col, length_row, length_col)
            = a * Mat::Ones(length_row, length_col);
    }

    template<typename Mat = Matrix>
    void set_item_mat(Mat & self, PyObject *tuple, Mat const& a)
    {
        // read agguments
        PyObject* obj1 = PyTuple_GET_ITEM(tuple, 0);
        PyObject* obj2 = PyTuple_GET_ITEM(tuple, 1);

        PySliceObject* slice1 = 0;
        PySliceObject* slice2 = 0;

        if (PySlice_Check(obj1) == true)
        {
            slice1 = (PySliceObject*)(obj1);
        }

        if (PySlice_Check(obj2) == true)
        {
            slice2 = (PySliceObject*)(obj2);
        }

        /*long */int start_row, stop_row, step_row, length_row = 1;
        /*long */int start_col, stop_col, step_col, length_col = 1;

        if (slice1 != 0)
        {
            PySlice_GetIndicesEx(slice1, self.rows(),
                                 &start_row,
                                 &stop_row,
                                 &step_row,
                                 &length_row);
        }
        else if (PyInt_Check(obj1)) // if not a slice, it is a number
        {
            start_row = PyInt_AsLong(obj1);
        }

        if (slice2 != 0)
        {
            PySlice_GetIndicesEx(slice2, self.cols(),
                                 &start_col,
                                 &stop_col,
                                 &step_col,
                                 &length_col);
        }
        else if (PyInt_Check(obj2)) // if not a slice, it is a number
        {
            start_col = PyInt_AsLong(obj2);
        }

        self.block(start_row, start_col, length_row, length_col) = a;
    }
    template<typename Mat = Matrix>
    Mat get_item(Mat const & self, PyObject *tuple)
    {
        // read agguments
        PyObject* obj1 = PyTuple_GET_ITEM(tuple, 0);
        PyObject* obj2 = PyTuple_GET_ITEM(tuple, 1);

        PySliceObject* slice1 = 0;
        PySliceObject* slice2 = 0;

        if (PySlice_Check(obj1) == true)
        {
            slice1 = (PySliceObject*)(obj1);
        }

        if (PySlice_Check(obj2) == true)
        {
            slice2 = (PySliceObject*)(obj2);
        }

        /*long */int start_row, stop_row, step_row, length_row = 1;
        /*long */int start_col, stop_col, step_col, length_col = 1;

        if (slice1 != 0)
        {
            PySlice_GetIndicesEx(slice1, self.rows(),
                                 &start_row,
                                 &stop_row,
                                 &step_row,
                                 &length_row);
        }
        else if (PyInt_Check(obj1)) // if not a slice, it is a number
        {
            start_row = PyInt_AsLong(obj1);
        }

        if (slice2 != 0)
        {
            PySlice_GetIndicesEx(slice2, self.cols(),
                                 &start_col,
                                 &stop_col,
                                 &step_col,
                                 &length_col);
        }
        else if (PyInt_Check(obj2)) // if not a slice, it is a number
        {
            start_col = PyInt_AsLong(obj2);
        }

        return self.block(start_row, start_col, length_row, length_col);
    }

    template<typename Mat = Matrix> Mat cwise_min_mat(Mat const & self, Mat const & a) {    return self.cwiseMin(a);   }
    template<typename Mat = Matrix> Mat cwise_max_mat(Mat const & self, Mat const & a) {    return self.cwiseMax(a);   }
    template<typename Mat = Matrix> Mat cwise_min_scalar(Mat const & self, double const & a) {    return self.cwiseMin(a);   }
    template<typename Mat = Matrix> Mat cwise_max_scalar(Mat const & self, double const & a) {    return self.cwiseMax(a);   }

    template<typename Mat = Matrix> Mat cwise_product_mat (Mat const & self, Mat const & a) {   return self.cwiseProduct(a); }
    template<typename Mat = Matrix> Mat cwise_quotient_mat(Mat const & self, Mat const & a) {   return self.cwiseQuotient(a); }


    template<typename Mat = Matrix> Mat cwise_inverse(Mat const & self) {   return self.cwiseInverse(); }
    template<typename Mat = Matrix> Mat cwise_abs    (Mat const & self) {   return self.cwiseAbs(); }
    template<typename Mat = Matrix> Mat cwise_abs2   (Mat const & self) {   return self.cwiseAbs2(); }
    template<typename Mat = Matrix> Mat cwise_sqrt   (Mat const & self) {   return self.cwiseSqrt(); }

    template<typename Mat = Matrix> double mean        (Mat const & self) { return self.mean(); }
    template<typename Mat = Matrix> double max_mat2    (Mat const & self) { return self.maxCoeff(); }
    template<typename Mat = Matrix> double max_mat     (Mat const & self, int* row, int* col) { return self.maxCoeff(row, col); }
    template<typename Mat = Matrix> double min_mat2    (Mat const & self) { return self.minCoeff(); }
    template<typename Mat = Matrix> double min_mat     (Mat const & self, int* row, int* col) { return self.minCoeff(row, col); }
    template<typename Mat = Matrix> double norm_mat2   (Mat const & self) { return self.norm(); }
    template<typename Mat = Matrix> double prod        (Mat const & self) { return self.prod(); }
    template<typename Mat = Matrix> double sum         (Mat const & self) { return self.sum(); }

    template<typename Mat = Matrix> Mat colwise_mean(Mat const & self) { return self.colwise().mean(); }
    template<typename Mat = Matrix> Mat rowwise_mean(Mat const & self) { return self.rowwise().mean(); }
    template<typename Mat = Matrix> Mat colwise_max (Mat const & self) { return self.colwise().maxCoeff(); }
    template<typename Mat = Matrix> Mat rowwise_max (Mat const & self) { return self.rowwise().maxCoeff(); }
    template<typename Mat = Matrix> Mat colwise_min (Mat const & self) { return self.colwise().minCoeff(); }
    template<typename Mat = Matrix> Mat rowwise_min (Mat const & self) { return self.rowwise().minCoeff(); }
    template<typename Mat = Matrix> Mat colwise_prod(Mat const & self) { return self.colwise().prod(); }
    template<typename Mat = Matrix> Mat rowwise_prod(Mat const & self) { return self.rowwise().prod(); }
    template<typename Mat = Matrix> Mat colwise_sum (Mat const & self) { return self.colwise().sum(); }
    template<typename Mat = Matrix> Mat rowwise_sum (Mat const & self) { return self.rowwise().sum(); }

    template<typename Mat = Matrix> double trace (Mat const & self) { return self.trace(); }
    template<typename Mat = Matrix> Mat transpose (Mat const & self) { return self.transpose(); }

    template<typename Mat = Matrix> Mat adjoint (Mat const & self) { return self.adjoint(); }
    template<typename Mat = Matrix> Mat inverse (Mat const & self) { return self.inverse(); }

    template<typename Mat = Matrix> bool all_finite (Mat const & self) { return self.allFinite(); }
    template<typename Mat = Matrix> bool has_nan (Mat const & self) { return self.hasNaN(); }
    template<typename Mat = Matrix> double value (Mat const & self) { return self.value(); }

    template<typename Mat = Matrix> Mat ones(int x, int y)  {   return Mat::Ones(x, y);   }
    template<typename Mat = Matrix> Mat zero(int x, int y)  {   return Mat::Zero(x, y);   }
    template<typename Mat = Matrix> Mat random(int x, int y)  {   return Mat::Random(x, y);   }
    template<typename Mat = Matrix> Mat identity(int x, int y)  {   return Mat::Identity(x, y);   }
    template<typename Mat = Matrix> Mat constant(int x, int y, double z)  {   return Mat::Constant(x, y, z);   }

    // template<typename Mat = Matrix> Mat __eq__  (Mat const & self, Mat const & b) { return self == b; }

    template<typename Mat = Matrix> Mat __add__ (Mat const & self, Mat const & b) { return self + b; }
    template<typename Mat = Matrix> Mat __sub__ (Mat const & self, Mat const & b) { return self - b; }
    template<typename Mat = Matrix> void __iadd__(Mat & self, Mat const & b) { self = self + b; }
    template<typename Mat = Matrix> void __isub__(Mat & self, Mat const & b) { self = self - b; }
    template<typename Mat = Matrix> Mat __div__ (Mat const & self, double const & b) { return self / b; }

    template<typename Mat = Matrix> Mat __mul__mat    (Mat const & self, Mat const & b) { return self * b; }
    template<typename Mat = Matrix> Mat __mul__scalar (Mat const & self, double const & b) { return self * b; }
    template<typename Mat = Matrix> int __len__ (Mat const & self) { return self.rows(); }

    template<typename Mat = Matrix> Mat __neg__(Mat const & self) { return -self;   }
    template<typename Mat = Matrix> Mat __pos__(Mat const & self) { return self;    }

}

template<typename Solver>
Matrix inverse(Solver const & self)
{
    return self.inverse();
}

template<typename Solver>
Matrix solve(Solver const & self, Matrix const & b)
{
    return self.solve(b);
}

namespace partiallu
{
    Matrix matrixlu(PartialLU const & self)
    {
           return self.matrixLU();
    }
}
}
}


    // typedef double(*UnaryExprType)(double);

    //namespace internal{
    //struct Pow
    //{
    //public:
    //    Pow(double p):
    //        p(p)
    //    {}

    //    double p;

    //    double operator() (double x) {   return pow(x, p);   }
    //};
    //}
    
    
//#include <boost/python.hpp>
//template<typename Mat = Matrix> Mat cwise_pow(Mat & self, double const & a)
//{
//    internal::Pow f(a);
//    return self.unaryExpr(f);
//}
//struct PythonCallBackBase
//{
//public:
//    virtual ~PythonCallBackBase()   {}
//    virtual double operator() (double const & x) {  return 0;   }
//};

//struct PythonCallBack : PythonCallBackBase, boost::python::wrapper<PythonCallBackBase>
//{
//public:
//    typedef boost::python::wrapper<PythonCallBackBase> wrap;

//    double default_op(double const & x)
//    {
//        return 0;
//    }

//    double operator() (double const & x)
//    {
//        if (boost::python::override f = wrap::get_override("__call__"))
//            return f(x);
//        return PythonCallBackBase::operator ()(x);
//    }
//};

//template<typename Mat = Matrix> void unary_expr_class(Mat const & self, PythonCallBack const & a)
//{
//    self.unaryExpr(a);
//}

//template<typename Mat = Matrix> void unary_expr (Mat const & self, UnaryExprType a)
//{
//    self.unaryExpr(a);
//}

// buggy

//template<typename Mat = Matrix> void resize (Mat const & self, int const & col, int const & row) { return self.resize(col, row); }

//template<typename Mat = Matrix> Mat cwise_equal_mat   (Mat const & self, const Mat& a)    {   return self.cwiseEqual(a); }
//template<typename Mat = Matrix> Mat cwise_equal_scalar(Mat const & self, const double& a) {   return self.cwiseEqual(a); }

//template<typename Mat = Matrix> void normalize  (Mat const & self) { return self.normalize(); }

//template<typename Mat = Matrix> double squared_norm(Mat const & self) { return self.squaredNorm(); }
//template<typename Mat = Matrix> double stable_norm (Mat const & self) { return self.stableNorm(); }
//template<typename Mat = Matrix> void conservative_resize(Mat const & self, int x, int y) {   self.conservativeResize(x, y);  }

//template<typename Mat = Matrix> void set_constant (Mat const & self, double const & a) { self.setConstant(a); }
//template<typename Mat = Matrix> void set_idendity (Mat const & self) { self.setIdentity(); }
//template<typename Mat = Matrix> void set_ones (Mat const & self) { self.setOnes(); }
//template<typename Mat = Matrix> void set_zero (Mat const & self) { self.setZero(); }

#endif
