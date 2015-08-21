#ifndef REPORT_LATEX_HEADER
#define REPORT_LATEX_HEADER

#include "Report.h"
#include "StrategyLog/StrategyLog.h"

#include <fstream>

namespace strat3{

/*
 *  Add a new DataFrame "statistics"
 *      - Returns ==>>> matrix
 */
class Latex : public Report
{
public:
    Latex(const std::string& file_name, const std::vector<std::string>& sn, StrategyLog& l):
        Report(file_name, sn, l)
    {
        os.open(file_name.c_str(), std::ios::out);
    }

    void compute_stuff()
    {
        uint nb_strat   = strategy_names().size();
        uint value      = log.size();

        RESERVE("asset"  , nb_strat * value);
        RESERVE("returns", nb_strat *(value - 1));

        std::vector<double>& vec = df["asset"];

        for(auto& el:strategy_names())
        {
            std::vector<double> &temp = log.df(el)["pv_asset"];
            std::copy(temp.begin(), temp.end(), std::back_inserter(vec));
        }

        // Get Asset Data
        Matrix data = Eigen::Map<Matrix>(&vec[0], value, nb_strat);
        uint n = data.rows();
        Matrix ret = (data.bottomRows(n - 1).cwiseQuotient(data.topRows(n - 1))).array().log();

        // Copy
        std::vector<double>& vc = df["returns"];
        double* ptr = &ret(0, 0);
        std::copy(ptr, ptr + ret.rows() * ret.cols(), std::back_inserter(vc));

        Matrix average_return = ret.colwise().mean();

        // std::cout << average_return << std::endl;
        // I tried to not copy the Matrix but it does not work
    }

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

//    StrategyLog::DataFrame& df()    {   return *_df;    }

private:
    std::fstream os;
    StrategyLog::DataFrame df;
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
//std::vector<double> &t = this->df()["assets"];

//ADD_TRACE("SHORTCUTS DEFINED");

//for(auto& el:strategy_names())
//{
//    std::vector<double> &tt = log.df(el)["pv_asset"];
//    std::copy(tt.begin(), tt.end(), std::back_inserter(t));
//}

//std::cout << t.size() << std::endl;

//Eigen::IOFormat fmt;

//Eigen::Map<Matrix> data(&t[0], value, nb_strat);

//std::vector<double> &t2 = this->df()["returns"];

//Eigen::Map<Matrix> ret(&t2[0], value - 1, nb_strat);

//ADD_TRACE("print");
//std::cout << ret.format(fmt) << std::endl;

//int n = data.rows();
//ret = data.bottomRows(n - 1).cwiseQuotient(data.topRows(n - 1));
//ret.array().log();
