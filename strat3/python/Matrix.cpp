#include <boost/python.hpp>
// #include "pyMatrix.h"

//  Currently missing:
//      - Linear Solver
//      - is Statement

#include "Matrix.h"
#include "DataManager.h"
#include "../python/Strategy.h"
#include "Portfolio.h"
#include "Transaction.h"
#include "MarketEngine.h"

using namespace strat3::python;



BOOST_PYTHON_MODULE(libpyStrat3)
{
    using namespace boost::python;

/*************************************************************************
*           Eigen3 Library
*************************************************************************/

    // Basic Initialization
    def("Ones", &matrix::ones<Matrix>);
    def("Zero", &matrix::zero<Matrix>);
    def("Random", &matrix::random<Matrix>);
    def("Identity", &matrix::identity<Matrix>);
    def("Constant", &matrix::constant<Matrix>);

    enum_<Eigen::ComputationInfo>("ComputationInfo")
        .value("Sucess", Eigen::Success)
        .value("NumericalIssue", Eigen::NumericalIssue)
        .value("NoConvergence", Eigen::NoConvergence)
        .value("InvalidInput", Eigen::InvalidInput)
    ;

    // Decomposition / Factorization
    class_<PartialLU>("PartialLU", init<Matrix>())
    // Not implemented
        //.def("__init__",        &partiallu::init_def)
        //.def("__init__",        &partiallu::init_size)
        //.def("__init__",        &partiallu::init_mat)

    // Passing
        .def("determinant",         &PartialLU::determinant)
        .def("inverse",             &PartialLU::inverse)
        .def("solve",               &strat3::python::solve<PartialLU>)
        //.def("solve",               &PartialLU::solve, return_internal_reference<1, Matrix>())
        .def("reconstructedMatrix", &PartialLU::reconstructedMatrix)
        .def("matrix_lu",           &strat3::python::partiallu::matrixlu)

    // Crashing
        //.def("permutation"          &PartialLU::permutationP)  // Need the implementation of perm matrix
    ;

    class_<FullLU>("FullLU")
    // Not Implemented
        //.def("__init__",        &fulllu::init_def)
        //.def("__init__",        &fulllu::init_size)
        //.def("__init__",        &fulllu::init_mat)

    // Passing
        .def("is_injective",    &FullLU::isInjective)
        .def("is_invertible",   &FullLU::isInvertible)
        .def("is_surjective",   &FullLU::isSurjective)
        .def("inverse",         &FullLU::inverse)
        .def("threshold",       &FullLU::threshold)
        .def("dimension_kernel",&FullLU::dimensionOfKernel)
        .def("image",           &FullLU::image)
        .def("kernel",          &FullLU::kernel)
        .def("max_pivot",       &FullLU::maxPivot)
        .def("non_zero_pivot",  &FullLU::nonzeroPivots)
        .def("rank",            &FullLU::rank)
        .def("determinant",     &FullLU::determinant)
        .def("reconstructedMatrix", &FullLU::reconstructedMatrix)
        .def("solve",           &strat3::python::solve<FullLU>)

    // Crashing => i.e require some glue code
        //.def("compute",         &FullLU::compute)
        //.def("permutation"      &FullLU::permutationP)
        //.def("set_threshold",   &FullLU::setThreshold)
        //.def("matrix_lu",       &FullLU::matrixLU)
        //.def("permutation_p",   &FullLU::permutationP)
        //.def("permutation_q",   &FullLU::permutationQ)
    ;

    class_<QR>("HouseholderQR")
    // Not Implemented
        //.def("__init__",        &qr::init_def)
        //.def("__init__",        &qr::init_size)
        //.def("__init__",        &qr::init_mat)

    // Passing
        .def("log_abs_determinant", &QR::logAbsDeterminant)
        .def("abs_determinant",     &QR::absDeterminant)
        .def("solve",               &strat3::python::solve<QR>)

    // Crashing
        //.def("h_coeffs",            &QR::hCoeffs)
        //.def("compute",             &QR::compute)
        //.def("matrix_qr",           &QR::matrixQR)
    ;

    class_<LLT>("LLT")
    // Not Implemented
        //.def("__init__",        &llt::init_def)
        //.def("__init__",        &llt::init_mat)

    // Passing
        .def("info",                &LLT::info)
        .def("solve",               &strat3::python::solve<LLT>)
        .def("reconstructedMatrix", &LLT::reconstructedMatrix)

    // Crashing
        //.def("compute",             &LLT::compute)
        //.def("rank_update",         &LLT::rankUpdate)
        //.def("matrix_l",            &LLT::matrixL)
        //.def("matrix_u",            &LLT::matrixU)
        //.def("matrix_llt",          &LLT::matrixLLT)
    ;

//    class_<LDLT>("LDLT")
//    ;

//    class_<ColQR >("ColHouseholderQR")
//    ;

//    class_<FullQR>("FullHouseholderQR")
//    ;

//    typedef Eigen::JacobiSVD<Matrix>            JacobiSVD;
//    typedef Eigen::SelfAdjointEigenSolver<Matrix>            SAEigenSolver;
//    typedef Eigen::ComplexEigenSolver<Matrix>                CEigenSolver;
//    typedef Eigen::EigenSolver<Matrix>                       EigenSolver;
//    typedef Eigen::GeneralizedSelfAdjointEigenSolver<Matrix> GSAEigenSolver;
//    typedef Eigen::Tridiagonalization<Matrix>                Tridiag;

    // Singular value stuff

    class_<Matrix>("Matrix", init<int, int>())
        .def("cols",    &Matrix::cols)
        .def("rows",    &Matrix::rows)

        .def("get_col", &matrix::get_col_matrix<Matrix>)
        .def("set_col", &matrix::set_col_matrix<Matrix>)

        .def("get_row", &matrix::get_row_matrix<Matrix>)
        .def("set_row", &matrix::set_row_matrix<Matrix>)

        .def("block",   &matrix::get_block_matrix<Matrix>)
        .def("block",   &matrix::set_block_matrix<Matrix>)

        .def("__str__", &matrix::str_matrix<Matrix>)

        .def("__getitem__", &matrix::get_item<Matrix>)
        .def("__setitem__", &matrix::set_item_int<Matrix>)
        .def("__setitem__", &matrix::set_item_mat<Matrix>)

        .def("cwise_min",       &matrix::cwise_min_mat<Matrix>)
        .def("cwise_max",       &matrix::cwise_max_mat<Matrix>)
        .def("cwise_min",       &matrix::cwise_min_scalar<Matrix>)
        .def("cwise_max",       &matrix::cwise_max_scalar<Matrix>)

        .def("cwise_product",   &matrix::cwise_product_mat<Matrix>)
        .def("cwise_quotient",  &matrix::cwise_quotient_mat<Matrix>)

        .def("cwise_inverse",   &matrix::cwise_inverse<Matrix>)
        .def("cwise_abs",       &matrix::cwise_abs<Matrix>)
        .def("cwise_asb2",      &matrix::cwise_abs2<Matrix>)
        .def("cwise_sqrt",      &matrix::cwise_sqrt<Matrix>)

        //
        .def("mean",            &matrix::mean<Matrix>)
        .def("max",             &matrix::max_mat<Matrix>)
        .def("min",             &matrix::min_mat<Matrix>)
        .def("max",             &matrix::max_mat2<Matrix>)
        .def("min",             &matrix::min_mat2<Matrix>)
        .def("norm",            &matrix::norm_mat2<Matrix>)
        .def("prod",            &matrix::prod<Matrix>)
        .def("sum",             &matrix::sum<Matrix>)

        .def("colwise_mean",    &matrix::colwise_mean<Matrix>)
        .def("rowwise_mean",    &matrix::rowwise_mean<Matrix>)
        .def("colwise_max",     &matrix::colwise_max<Matrix>)
        .def("rowwise_max",     &matrix::rowwise_max<Matrix>)
        .def("colwise_min",     &matrix::colwise_min<Matrix>)
        .def("rowwise_min",     &matrix::rowwise_min<Matrix>)
        .def("colwise_prod",    &matrix::colwise_prod<Matrix>)
        .def("rowwise_prod",    &matrix::rowwise_prod<Matrix>)
        .def("colwise_sum",     &matrix::colwise_sum<Matrix>)
        .def("rowwise_sum",     &matrix::rowwise_sum<Matrix>)

        .def("trace",           &matrix::trace<Matrix>)
        .def("transpose",       &matrix::transpose<Matrix>)

        .def("all_finite",      &matrix::all_finite<Matrix>)
        .def("has_nan",         &matrix::has_nan<Matrix>)
        .def("adjoint",         &matrix::adjoint<Matrix>)
        .def("inverse",         &matrix::inverse<Matrix>)
        .def("value",           &matrix::value<Matrix>)

        // solver reference
        .def("full_lu",         &Matrix::fullPivLu)
        .def("partial_lu",      &Matrix::lu)
        .def("lu",              &Matrix::lu)
        .def("qr",              &Matrix::householderQr)
        .def("llt",             &Matrix::llt)

        // Operator
        .def("__abs__",  &matrix::cwise_abs<Matrix>)
        .def("__add__",  &matrix::__add__<Matrix>)
        .def("__div__",  &matrix::__div__<Matrix>)
        .def("__mul__",  &matrix::__mul__mat<Matrix>)
        .def("__mul__",  &matrix::__mul__scalar<Matrix>)

        .def("__sub__",  &matrix::__sub__<Matrix>)
        .def("__iadd__", &matrix::__iadd__<Matrix>)
        .def("__isub__", &matrix::__isub__<Matrix>)

        .def("__neg__",  &matrix::__neg__<Matrix>)
        .def("__pos__",  &matrix::__pos__<Matrix>)

        // .def("__pow__",  &cwise_pow<Matrix>)
            // operator and is statement
            //            .def("unary_expr",      &unary_expr<Matrix>)
            //            .def("unary_expr",      &unary_expr_class<Matrix>)
            // buggy
            //.def("resize",          &resize<Matrix>)
            //.def("squared_norm",    &squared_norm<Matrix>)
            //.def("stable_norm",     &stable_norm<Matrix>)
            //.def("normalize",       &normalize<Matrix>)
            //.def("cwise_equal",     &cwise_equal_mat<Matrix>)
            //.def("cwise_equal",     &cwise_equal_scalar<Matrix>)
//            .def("conservative_resize", &conservative_resize<Matrix>)
//            .def("set_constant",    &set_constant<Matrix>)
//            .def("fill",            &set_constant<Matrix>)
//            .def("set_identity",    &set_idendity<Matrix>)
//            .def("set_ones",        &set_ones<Matrix>)
//            .def("set_zero",        &set_zero<Matrix>)

            //    class_<Column>("Column", init<int>())
            //        .def("cols", &Column::cols)
            //        .def("rows", &Column::rows)
            //    ;

                // add a Numpy looking cast
                // add Numpy casts

            //    class_<Row>("Column", init<int>())
            //        .def("cols", &Row::cols)
            //        .def("rows", &Row::rows)
            //    ;

            //    class_<PythonCallBack, boost::noncopyable>("PythonCallBack")
            //            .def("__call__", &PythonCallBack::operator (), &PythonCallBack::default_op);
    ;



/*************************************************************************
*           DataManager.h
*************************************************************************/

    enum_<SaveFileOptions>("SaveFileOptions")
        .value("OneFile", OneFile)
        .value("MultipleFile", MultipleFile)
    ;

    enum_<SaveOptions>("SaveOptions")
        .value("Erase", Erase)
        .value("Append", Append)
    ;

    enum_<FileType>("FileType")
        .value("Binary", Binary)
        .value("CSV", CSV)
    ;

    class_<MatrixManager>("MatrixManager")
        .def("append",      &datamanager::add_matrix)
        .def("add_matrix",  &datamanager::add_matrix)
        .def("__getitem__", &MatrixManager::matrix, &datamanager::get_matrix) // return_value_policy<return_by_value>()
        .def("__setitem__", &datamanager::set_matrix)
        .def("save",        &MatrixManager::save)
        .def("load",        &MatrixManager::load)
        .def("read_csv",    &MatrixManager::readCSV)
        .def("__len__",     &MatrixManager::size)
        .def("size",        &MatrixManager::size)
    ;

    class_<MatrixQuery>("MatrixQuery", init<MatrixManager*, int, int>())
            .def("middle_rows", &MatrixQuery::middleRows)
            .def("size", &MatrixQuery::size)
            .def("cols", &MatrixQuery::cols)
            .def("min", &MatrixQuery::min)
            .def("max", &MatrixQuery::max)
    ;

    class_<DataManager>("DataManager")
            .def("append",              &datamanager::add_matrix_manager)
            .def("add_matrix_manager",  &datamanager::add_matrix_manager)
            .def("__getitem__",         &datamanager::get_matrix_manager)
            .def("__setitem__",         &datamanager::set_matrix_manager)
            .def("size",                &DataManager::size)
            .def("__len__",             &DataManager::size)
    ;

    class_<DataQuery>("DataQuery", init<DataManager*, int, int>())
        .def("middle_rows", &DataQuery::middleRows)
        .def("size", &DataQuery::size)
        .def("cols", &DataQuery::cols)
        .def("min", &DataQuery::min)
        .def("max", &DataQuery::max)
    ;

/*************************************************************************
*           Strategy.h
*************************************************************************/

    enum_<WeightType>("WeightType")
        .value("TotalPercentage",        TotalPercentage)
        .value("DifferentialPercentage", DifferentialPercentage)
        .value("TotalShare",             TotalShare)
        .value("DifferentialShare",      DifferentialShare)
        .value("NoTransaction",          NoTransaction)
    ;

    class_<TransactionWeight>("TransactionWeight")
        .def_readwrite("weight", &TransactionWeight::weight)
        .def_readwrite("type",   &TransactionWeight::type)
    ;

//    class_<StrategyWrap, boost::noncopyable>("Strategy",
//                                             init<Key, Key, int, bool, Index>())
//        .def("version", &Strategy::version)
//        .def("frequency", &Strategy::frequency)
//        .def("rebalanced", &Strategy::rebalanced)
//        .def("set_frequency", &Strategy::setFrequency)
//        .def("set_rebalanced", &Strategy::setRebalanced)
////        .def("__call__", &Strategy::compute_weight, &StrategyWrap::def_call_cw_s)
//        //.def("__call__", &Strategy::operator (), &StrategyWrap::default_call_op_q)
//        // def __call__
////        .def("title", &Strategy::title, &StrategyWrap::def_title)
////        .def("description", &Strategy::description, &StrategyWrap::def_description)
//    ;

/*************************************************************************
*           Portfolio.h
*************************************************************************/

//    class_<Portfolio>("Portfolio", init<int, double, Key, MarketEngine*>())
//        // .def()
//    ;

/*************************************************************************
*           Transaction.h
*************************************************************************/

    enum_<Transaction::Field>("TransactionField")
        .value("TickerIndex"    ,Transaction::TickerIndex)
        .value("Size"           ,Transaction::Size)
        .value("ExecutionField" ,Transaction::ExecutionField)
        .value("ValidityField"  ,Transaction::ValidityField)
        .value("Price"          ,Transaction::Price)
        .value("Option1"        ,Transaction::Option1)
        .value("Option2"        ,Transaction::Option2)
        .value("Date"           ,Transaction::Date)
        .value("DisplayField"   ,Transaction::DisplayField)
        .value("CurrentDate"    ,Transaction::CurrentDate)
        .value("ID"             ,Transaction::ID)
    ;

    enum_<Transaction::Execution>("ExecutionField")
        .value("Market" ,Transaction::Market)
        .value("Limit"  ,Transaction::Limit)
        .value("Stop"   ,Transaction::Stop)
        .value("MKT"    ,Transaction::Market)
        .value("LMT"    ,Transaction::Limit)
        .value("STO"    ,Transaction::Stop)
    ;

    enum_<Transaction::Validity>("ValidityField")
        .value("GooDTillDate"     , Transaction::GooDTillDate)
        .value("GoodOnDay"        , Transaction::GoodOnDay)
        .value("GoodTillCancelled", Transaction::GoodTillCancelled)
        .value("ImmediateOrCancel", Transaction::ImmediateOrCancel)
        .value("GoodOnClose"      , Transaction::GoodOnClose)
        .value("GoodOnOpen"       , Transaction::GoodOnOpen)

        .value("FillOrKill"       , Transaction::ImmediateOrCancel)
        .value("MarketOnClose"    , Transaction::GoodOnClose)
        .value("MarketOnOpen"     , Transaction::GoodOnOpen)

        .value("GTD", Transaction::GooDTillDate)
        .value("GOD", Transaction::GoodOnDay)
        .value("GTC", Transaction::GoodTillCancelled)
        .value("FOK", Transaction::ImmediateOrCancel)
        .value("IOC", Transaction::ImmediateOrCancel)
        .value("GOC", Transaction::GoodOnClose)
        .value("COO", Transaction::GoodOnOpen)
        .value("MOC", Transaction::GoodOnClose)
        .value("MOO", Transaction::GoodOnOpen)
    ;

    enum_<Transaction::Option>("OptionField")
        .value("None"         , Transaction::None)
        .value("AllOrNothing" , Transaction::AllOrNothing)
        .value("Hidden"       , Transaction::Hidden)
        .value("Display"      , Transaction::Display)
        .value("AON"          , Transaction::AllOrNothing)
        .value("HID"          , Transaction::Hidden)
        .value("DIS"          , Transaction::Display)
    ;

    class_<Transaction>("Transaction", init<Portfolio*>())
        .def("execution", &Transaction::execution)
        .def("price", &Transaction::price)
        .def("size", &Transaction::size)
        .def("ticker_index", &Transaction::tickerIndex)
        .def("id", &Transaction::id)

        .def("set_field", &Transaction::setField)
        .def("get_field", &Transaction::getField)

//        .def_read("transactions", &transaction::get_transactions_mat)
//        .def_write("transactions", &transaction::set_transactions_mat)

        .def("__lt__", &Transaction::operator <)
        .def("__gt__", &Transaction::operator <)
    ;

    enum_<TransactionAnswer::Field>("AnswerField")
        .value("TickerIndex",TransactionAnswer::TickerIndex)
        .value("Size"       ,TransactionAnswer::Size)
        .value("Price"      ,TransactionAnswer::Price)
        .value("Time"       ,TransactionAnswer::Time)
        .value("Cost"       ,TransactionAnswer::Cost)
        .value("ID"         ,TransactionAnswer::ID)
    ;

    class_<TransactionAnswer>("TransactionAnswer", init<Index, double, double, Index, double, Index>())
        .def("index", &TransactionAnswer::index)
        .def("size",  &TransactionAnswer::size)
        .def("price", &TransactionAnswer::price)
        .def("cost",  &TransactionAnswer::cost)
        .def("value", &TransactionAnswer::value)
        .def("id",    &TransactionAnswer::id)

        .def("get_field", &TransactionAnswer::getField)
        .def("set_field", &TransactionAnswer::setField)

//        .def_read("answer", &answer::get_transactions_mat)
//        .def_write("answer", &answer::set_transactions_mat)
    ;

/*************************************************************************
*           MarketEngine.h
*************************************************************************/


/*************************************************************************
*           DataLog.h
*************************************************************************/
}




