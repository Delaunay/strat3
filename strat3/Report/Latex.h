#ifndef STRAT3_REPORT_LATEX_HEADER
#define STRAT3_REPORT_LATEX_HEADER

#include "Report.h"
#include "StrategyLog/StrategyLog.h"
#include "visitor.h"

#include <algorithm>
#include <fstream>

template<typename T>
const T& _min(const T& x, const T& y)    {   return ((x > y) ? (x) : (y));   }


#define STATIC_GLOBAL(fname, name, row, col) MatrixMap& fname() \
                     {  \
                        static MatrixMap _static_name(&df[name][0], row, col);\
                        return _static_name;\
                     }

namespace strat3{

/*
 *  Add a new DataFrame "statistics"
 *      - Returns ==>>> matrix
 */
class Latex : public Report
{
public:
    Latex(const std::string& file_name, const std::vector<std::string>& sn, StrategyLog& l):
        Report(file_name, sn, l), days(log.size()),n_strat(strategy_names().size())
    {
        os.open(file_name.c_str(), std::ios::out);
    }

    // I am not a big fan
    // somehow DataFrame is bugging and MatrixMap does not modify the underlying
    // DataFrame if we dont do that
    STATIC_GLOBAL(assets,  "assets",    days    , n_strat)
    STATIC_GLOBAL(hpr,     "hpr",       days    , n_strat)
    STATIC_GLOBAL(returns, "returns",   days - 1, n_strat)

    STATIC_GLOBAL(means,     "means",      1, n_strat)
    STATIC_GLOBAL(pos_means, "pos_means",  1, n_strat)
    STATIC_GLOBAL(neg_means, "neg_means",  1, n_strat)
    STATIC_GLOBAL(stdev,     "stdev",      1, n_strat)
    STATIC_GLOBAL(pos_stdev, "pos_stdev",  1, n_strat)
    STATIC_GLOBAL(neg_stdev, "neg_stdev",  1, n_strat)
    STATIC_GLOBAL(variance,  "variance",   1, n_strat)
    STATIC_GLOBAL(kurtosis,  "kurtosis",   1, n_strat)
    STATIC_GLOBAL(skewness,  "skewness",   1, n_strat)

    void dump();

    void compute_assets();
    void compute_returns(MatrixMap& assets);
    void compute_hpr(MatrixMap& daily_returns);

    void compute_stuff();

    ~Latex()    {   os.close(); }

    void head               () {}
    void foot               () {}

    void table_of_content   () {}
    void disclaimer         () {}
    void overview           () {}
    void risk               () {}
    void strategies         () {}

    void portfolio_value    () {}
    void holdings           () {}
    void transaction_order  () {}
    void target_weight      () {}

//    StrategyLog::DataFrame& df    {   return *_df;    }

private:
    std::fstream os;
    //StrategyLog::DataFrame& df;
    DataFrame df;

    uint days;
    uint n_strat;
};

}

#endif


//StrategyLog::DataFrame df;

//uint nb_strat   = strategy_names().size();
//uint value      = log.size();

//RESERVE("assets", nb_strat * value);
//RESERVE("returns", nb_strat * (value));

//ADD_TRACE("RESERVED MEMORY");

//log.add_data_frame("statistics", std::move(df));

//ADD_TRACE("STAT");
//_df = &log.df("statistics");

//ADD_TRACE("ASSETS");
//std::vector<double> &t = this->df["assets"];

//ADD_TRACE("SHORTCUTS DEFINED");

//for(auto& el:strategy_names())
//{
//    std::vector<double> &tt = log.df(el)["pv_asset"];
//    std::copy(tt.begin(), tt.end(), std::back_inserter(t));
//}

//std::cout << t.size() << std::endl;

//Eigen::IOFormat fmt;

//Eigen::Map<Matrix> data(&t[0], value, nb_strat);

//std::vector<double> &t2 = this->df["returns"];

//Eigen::Map<Matrix> ret(&t2[0], value - 1, nb_strat);

//ADD_TRACE("print");
//std::cout << ret.format(fmt) << std::endl;

//int n = data.rows();
//ret = data.bottomRows(n - 1).cwiseQuotient(data.topRows(n - 1));
//ret.array().log();
