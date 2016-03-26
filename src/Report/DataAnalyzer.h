#ifndef STRAT3_REPORT_DATAANLYZER_HEADER
#define STRAT3_REPORT_DATAANLYZER_HEADER

#include "Report.h"
#include "StrategyLog/StrategyLog.h"
#include "visitor.h"

#define CLASS_GLOBAL(fname, name, row, col) MatrixMap& fname() \
                     {  \
                        static MatrixMap _CLASS_name(&df[name][0], row, col);\
                        return _CLASS_name;\
                     }

namespace strat3{

template<typename T>
const T& _min(const T& x, const T& y)    {   return ((x > y) ? (x) : (y));   }

//  ColWise Sort (must be colwise) make a copy
// Complexity ((nm)(log(n))) with m number of col
Matrix sort(const Matrix& x);

// Compute frequency (Global Scale)
// ((nm)(log(n))) + m * n
Matrix frequency(const Matrix& x, uint bucket, bool percentage);

/*
 *  Add a new DataFrame "statistics"
 *      - Returns ==>>> matrix
 */
class DataAnalyzer
{
public:
    DataAnalyzer(const std::vector<std::string>& sn, const std::vector<std::string>& sec, StrategyLog& l):
        log(l), _strategy_names(sn), days(log.size()), n_strat(strategy_names().size()),
        df(log.add_data_frame("Statistics")), n_sec(sec.size()), _sec_names(sec)
    {}

    // somehow DataFrame is bugging and MatrixMap does not modify the underlying
    // DataFrame if we dont do that
    // of course if those functions are called before compute_statistics()
    // it will segfault
    CLASS_GLOBAL(assets,    "assets",    days,      n_strat)
    CLASS_GLOBAL(hpr,       "hpr",       days,      n_strat)
    CLASS_GLOBAL(drawdown,  "drawdown",  days,      n_strat)
    CLASS_GLOBAL(mov_stdev, "mov_stdev", days - 1,  n_strat)
    CLASS_GLOBAL(returns,   "returns",   days - 1,  n_strat)

    CLASS_GLOBAL(means,     "means",      1, n_strat)
    CLASS_GLOBAL(count,     "count",      1, n_strat)
    CLASS_GLOBAL(pos_means, "pos_means",  1, n_strat)
    CLASS_GLOBAL(neg_means, "neg_means",  1, n_strat)
    CLASS_GLOBAL(pos_count, "pos_count",  1, n_strat)
    CLASS_GLOBAL(neg_count, "neg_count",  1, n_strat)
    CLASS_GLOBAL(stdev,     "stdev",      1, n_strat)
    CLASS_GLOBAL(pos_stdev, "pos_stdev",  1, n_strat)
    CLASS_GLOBAL(neg_stdev, "neg_stdev",  1, n_strat)
    CLASS_GLOBAL(variance,  "variance",   1, n_strat)
    CLASS_GLOBAL(kurtosis,  "kurtosis",   1, n_strat)
    CLASS_GLOBAL(skewness,  "skewness",   1, n_strat)
    CLASS_GLOBAL(vol_mean,  "vol_mean",   1, n_strat)
    CLASS_GLOBAL(vol_stdev, "vol_stdev",  1, n_strat)

    CLASS_GLOBAL(return_distri, "return_distri", (uint) sqrt(returns().rows()), n_strat + 2)

    void dump(Eigen::IOFormat &date_fmt = format_date(), bool js = false);

    bool has_dates()        {   return log.has_dates();     }
    const Matrix& dates()   {   return log.dates();         }

    void compute_assets();
    void compute_returns(MatrixMap& assets);
    void compute_hpr(MatrixMap& daily_returns, uint window=20);
    void compute_point_statistics();
    void compute_return_distribution();
    void compute_volatility_stats();
    void compute_transaction_order_statistics();

    // Shortcuts
    MatrixMap to_mean(uint k)   {   return log.get_matrix<Matrix>(strategy_names()[k], "to_mean", 1, n_sec); }
    MatrixMap to_count(uint k)   {   return log.get_matrix<Matrix>(strategy_names()[k], "to_count", 1, n_sec); }
    MatrixMap to_stdev(uint k)   {   return log.get_matrix<Matrix>(strategy_names()[k], "to_stdev", 1, n_sec); }
    MatrixMap to_pos_mean(uint k)   {   return log.get_matrix<Matrix>(strategy_names()[k], "to_pos_mean", 1, n_sec); }
    MatrixMap to_neg_mean(uint k)   {   return log.get_matrix<Matrix>(strategy_names()[k], "to_neg_mean", 1, n_sec); }
    MatrixMap to_pos_count(uint k)   {   return log.get_matrix<Matrix>(strategy_names()[k], "to_pos_count", 1, n_sec); }
    MatrixMap to_neg_count(uint k)   {   return log.get_matrix<Matrix>(strategy_names()[k], "to_neg_count", 1, n_sec); }

    MatrixMap to_mean(std::string k)   {   return log.get_matrix<Matrix>(k, "to_mean", 1, n_sec); }
    MatrixMap to_count(std::string k)   {   return log.get_matrix<Matrix>(k, "to_count", 1, n_sec); }
    MatrixMap to_stdev(std::string k)   {   return log.get_matrix<Matrix>(k, "to_stdev", 1, n_sec); }
    MatrixMap to_pos_mean(std::string k)   {   return log.get_matrix<Matrix>(k, "to_pos_mean", 1, n_sec); }
    MatrixMap to_neg_mean(std::string k)   {   return log.get_matrix<Matrix>(k, "to_neg_mean", 1, n_sec); }
    MatrixMap to_pos_count(std::string k)   {   return log.get_matrix<Matrix>(k, "to_pos_count", 1, n_sec); }
    MatrixMap to_neg_count(std::string k)   {   return log.get_matrix<Matrix>(k, "to_neg_count", 1, n_sec); }

    void compute_statistics();

    const std::vector<std::string>& strategy_names() {  return _strategy_names; }
    const std::vector<std::string>& security_names() {  return _sec_names; }


    StrategyLog& get_log()  {   return log; }

private:
    StrategyLog& log;
    const std::vector<std::string>& _strategy_names;
    const std::vector<std::string>& _sec_names;

    uint days;
    uint n_strat;
    uint n_sec;
    DataFrame& df;
};

}

#undef CLASS_GLOBAL
#endif


