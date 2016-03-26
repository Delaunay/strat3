#ifndef STRAT3_STRATEGYLOG_STRATEGYLOGSQLITE_HEADER
#define STRAT3_STRATEGYLOG_STRATEGYLOGSQLITE_HEADER

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "../enum.h"
#include "../Log/Log.h"
#include "../Struct/TransactionWeight.h"


class Transaction;
class TransactionAnswer;

#define RESERVE(name, size) df[name] = std::vector<double>();  df[name].reserve(size)

/*!
 * \brief The DataLog class
 *
 * for RAM save we use std::vector<double> since data are contiguous
 * we can cast them into a Eigen::Matrix using Eigen::Map
 * need to check pre allocation for better performance
 *
 * Real Time statistics will be called by Datalog
 */
/*! Save generated Data
 *  \param name StrategyName filename
 *  \param numsec Number of security used for matrix size
 *  \param market engine might be use if it changes market
 *  \param n size of entries for matrix n for memory pre allocation
 */

#define LOG_WARNING(x)
#ifdef __linux__
#   define NOEXCEPT noexcept
#else
#   define NOEXCEPT
#endif

class StrategyLogSQLite
{
    public:
        typedef std::string StrategyName;
        typedef std::string FieldName;
        typedef std::vector<double> TimeSeries;

        typedef std::unordered_map<FieldName, TimeSeries> DataFrame;
        typedef std::pair<StrategyName, FieldName> Identifier;
        typedef long unsigned int luint;

        enum FieldValues
        {
            Time = 0,
            Invested,
            Cash,
            Asset,
            Liabilities,
            Equity,
            FieldValuesMax,
        };

        typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMajorMatrix;


        // not exact
        inline luint used_memory() const NOEXCEPT {   return _vsize * (3 * _nsecurity + 9);   }

        void initialize(std::vector<StrategyName> v, uint nsec, uint v_size = 1000)
        {
            _nsecurity = nsec;
            _vsize = v_size;

            for(auto e:v)
                _data[e] = build_standard_data_frame(nsec, v_size);
        }

        inline const std::vector<double>& time_serie(const Identifier& i)  {   return _data[i.first][i.second];   }
        inline const std::vector<double>& time_serie(const StrategyName& s,
                                              const FieldName& f)  {   return _data[s][f];   }


        // return the holdings evolution of one particular security as a column
        // not sure about stride value
//        template<typename T>
//        T get_holdings(const StrategyName& s, const uint& sec_index)
//        {
//            std::vector<double>& t = time_serie(s, "ps_holdings");
//            return Eigen::Map<T>(t[sec_index], t.size() / (nsec + 1), 1, Eigen::Stride(0, _nsecurity));
//        }


        template<typename T>
        T get_holdings(const StrategyName& s)
        {
            std::vector<double>& t = time_serie_mod(s, "ps_holdings");
            return Eigen::Map<T>(&t[0], t.size() / (_nsecurity + 1), _nsecurity + 1);
        }

        template<typename T>
        T get_weights(const StrategyName& s)
        {
            std::vector<double>& t = time_serie_mod(s, "st_weights");
            return Eigen::Map<T>(&t[0], t.size() / (_nsecurity + 2), _nsecurity + 2);
        }

//        template<typename T>
//        T get_share(const StrategyName& s)
//        {
//            std::vector<double>& t = time_serie_mod(s, "to_share");
//            return Eigen::Map<T>(&t[0], t.size() / (_nsecurity + 1), _nsecurity + 1);
//        }

        template<typename T>
        T get_share(const StrategyName& s)
        {
            std::vector<double>& t = time_serie_mod(s, "to_share");
            return Eigen::Map<T>(&t[0], t.size() / (_nsecurity + 1), _nsecurity + 1);
        }

        // my_data = build_matrix({"Strategy", "pv_time"}, {"Strategy", "pv_invested"})
        Matrix build_matrix(const std::vector<Identifier>& fields)
        {
            // build a vector which will be casted into a Matrix;
            std::vector<double> v;
            v.reserve(fields.size() * _vsize);
            uint v_size = 0;

            for(auto e:fields)
            {
                std::vector<double>& t = time_serie_mod(e);

                // Setup the default row size

                v_size = std::max((uint) t.size(), (uint) v_size);

                // if the current time serie has a different number of row print a warning
                if (v_size != t.size()){
                    LOG_WARNING(e->first << " " << e->second << " Does not have the same amount of rows");
                }

                std::copy(t.begin(), t.begin() + t.size(), std::back_inserter(v));

            }

            return Eigen::Map<Matrix>(&v[0], v_size, fields.size());
        }

        StrategyLogSQLite(){}
        ~StrategyLogSQLite()
        {}

        inline const uint& security_number() const {    return _nsecurity;  }

        void log_portfolio_state(const StrategyName& s, const double& time, const Matrix& state)
        {
            std::vector<double>& t = time_serie_mod(s, "ps_holdings");
            t.push_back(time);

            matrix_to_vector(state, t);
        }

        void log_transaction_weight(const StrategyName& s,const double& time, const TransactionWeight& tw)
        {
            std::vector<double>& t = time_serie_mod(s, "st_weights");
            t.push_back(time);
            t.push_back(tw.type);

            matrix_to_vector(tw.weight, t);
        }

        void log_portfolio_values(const StrategyName& s,
                                  const double& time,  const double& invested, const double& cash,const double& liabilities)
        {
            double asset = invested + cash;
            time_serie_mod(s, "pv_time").push_back(time);
            time_serie_mod(s, "pv_invested").push_back(invested);
            time_serie_mod(s, "pv_cash").push_back(cash);
            time_serie_mod(s, "pv_asset").push_back(asset);
            time_serie_mod(s, "pv_liability").push_back(liabilities);
            time_serie_mod(s, "pv_equity").push_back(asset - liabilities);
        }


        void log_portfolio_values(const StrategyName& s,
                                  const double& time,  const Matrix& invested, const Matrix& cash,const Matrix& liabilities)
        {

            time_serie_mod(s, "pv_time").push_back(time);

            Matrix asset = invested + cash;

            for(int i = 0, n = invested.cols(); i < n; ++i)
            {
                time_serie_mod(s, "pv_invested").push_back(invested(0, i));
                time_serie_mod(s, "pv_cash").push_back(cash(0, i));
                time_serie_mod(s, "pv_liability").push_back(liabilities(0, i));
                time_serie_mod(s, "pv_asset").push_back(asset(0, i));
                time_serie_mod(s, "pv_equity").push_back(asset(0, i) - liabilities(0, i));
            }
        }

        void log_transaction_order    (const StrategyName& s,
                                       const double& time, const Matrix& m)
        {
            std::vector<double>& t = time_serie_mod(s, "to_share");
            t.push_back(time);

            matrix_to_vector(m, t);
        }

        void matrix_to_vector(const Matrix& m, std::vector<double>& t)
        {
            const double* v = &m(0, 0);
            for(uint i = 0, n = m.rows() * m.cols(); i < n; ++i, ++v)
            {
                t.push_back(*v);
            }
        }

        void dump()
        {
            // Open files
            for(auto& i:_data){
                ADD_TRACE("LOAD FILES");
                std::fstream pv; pv.open("../pv" + i.first + ".txt", std::ios::out);
                std::fstream ps; ps.open("../ps" + i.first + ".txt", std::ios::out);
                std::fstream tw; tw.open("../tw" + i.first + ".txt", std::ios::out);
                std::fstream to; to.open("../to" + i.first + ".txt", std::ios::out);

                Eigen::IOFormat fmt;

                ADD_TRACE("SAVE PORTFOLIOVALUES");
                // Portfolio Values
                pv << "time, invested, cash, liability\n"
                   << build_matrix({{i.first, "pv_time"},
                                    {i.first, "pv_invested"},
                                    {i.first, "pv_cash"},
                                    {i.first, "pv_liability"}});

                // Portfolio State
                ps << get_holdings<MatrixRowMajor>(i.first).format(fmt);

                // Transaction weight
                tw << get_weights<MatrixRowMajor>(i.first).format(fmt);

                // Transaction Order
                to << get_share<MatrixRowMajor>(i.first).format(fmt);

                // close files
                pv.close(); ps.close(); tw.close(); to.close();
            }
        }


private:
        // non const function are private
        inline std::vector<double>& time_serie_mod(const Identifier& i) {   return _data[i.first][i.second];   }
        inline std::vector<double>& time_serie_mod(const StrategyName& s,
                                              const FieldName& f) {   return _data[s][f];   }

    protected:
        uint _nsecurity;
        uint _vsize;
        std::unordered_map<StrategyName, DataFrame> _data;


public:


static DataFrame build_standard_data_frame(uint nsec, uint v_size = 1000, uint strat = 1)
{
    DataFrame df;
    // We are using reserve() because we want to always use push_back and never []
    // Portfolio values
    RESERVE("pv_time", v_size);
    RESERVE("pv_invested", v_size * strat);    // Net of investment value
    RESERVE("pv_asset", v_size * strat);       // investment + cash
    RESERVE("pv_liability", v_size * strat);   // Shorted Investment and Borrowed money
    RESERVE("pv_equity", v_size * strat);      // Long Investement + positive cash
    RESERVE("pv_cash", v_size * strat);

    // portfolio state
    RESERVE("ps_holdings", v_size * (nsec + 1) * strat);
    RESERVE("st_weights", v_size * (nsec + 2) * strat); // Strategy Target Weights
    RESERVE("to_share", v_size * (nsec + 1) * strat);

    return df;
}
};

#endif

