#ifndef STRAT3_STRATEGYLOG_STRATEGYLOG_HEADER
#define STRAT3_STRATEGYLOG_STRATEGYLOG_HEADER

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "../enum.h"
#include "../Struct/TransactionWeight.h"
#include "../Log/Log.h"

#define LOG_RAM 1

class Transaction;
class TransactionAnswer;


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

typedef std::string StrategyName;
typedef std::string FieldName;
typedef std::vector<double> TimeSeries;

typedef std::unordered_map<FieldName, TimeSeries> DataFrame;
typedef std::pair<StrategyName, FieldName> Identifier;
typedef long unsigned int luint;


inline void reserve(DataFrame& df, std::string name, uint n)
{
    df[name] = std::vector<double>();
    df[name].reserve(n);
}

inline void allocate(DataFrame& df, std::string name, uint n)
{
    df[name] = std::vector<double>(n);
}

inline void matrix_to_vector(Matrix& m, std::vector<double>& v)
{
    double* ptr = &m(0, 0);
    uint n = m.rows() * m.cols();
    std::copy(ptr, ptr + n, std::back_inserter(v));
}

class StrategyLog
{
    public:
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

        void initialize(const std::vector<StrategyName>& v, uint nsec, uint v_size = 1000)
        {
            _nsecurity = nsec;
            _vsize = v_size;

            for(auto e:v){
                build_standard_data_frame(add_data_frame(e), nsec, v_size);
            }

            _strategy_names = &v;
        }

        inline const std::vector<double>& time_serie(const Identifier& i)  {   return _data[i.first][i.second];   }
        inline const std::vector<double>& time_serie(const std::string& s,
                                              const std::string& f)  {   return _data[s][f];   }


        // return the holdings evolution of one particular security as a column
        // not sure about stride value
//        template<typename T>
//        T get_holdings(const StrategyName& s, const uint& sec_index)
//        {
//            std::vector<double>& t = time_serie(s, "ps_holdings");
//            return Eigen::Map<T>(t[sec_index], t.size() / (nsec + 1), 1, Eigen::Stride(0, _nsecurity));
//        }

        template<typename T>
        Eigen::Map<T> get_matrix(const std::string& dfname, const std::string& matrix_name,
                     uint rows, uint cols)
        {
            return Eigen::Map<T>(&time_serie_mod(dfname, matrix_name)[0], rows, cols);
        }

//        template<typename T>
//        const T get_matrix(const std::string& dfname, const std::string& matrix_name,
//                     uint rows, uint cols)
//        {
//            return Eigen::Map<T>(_data[dfname][matrix_name], rows, cols);
//            //return Eigen::Map<const T>(&time_serie(dfname, matrix_name)[0], rows, cols);
//        }

        template<typename T>
        Eigen::Map<T> get_holdings(const StrategyName& s)
        {
            std::vector<double>& t = time_serie_mod(s, "ps_holdings");
            return Eigen::Map<T>(&t[0], t.size() / (_nsecurity + 1), _nsecurity + 1);
        }

        template<typename T>
        Eigen::Map<T> get_weights(const StrategyName& s)
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
        Eigen::Map<T> get_share(const StrategyName& s)
        {
            std::vector<double>& t = time_serie_mod(s, "to_share");
            return Eigen::Map<T>(&t[0], t.size() / (_nsecurity + 1), _nsecurity + 1);
        }

        // my_data = build_matrix({"Strategy", "pv_time"}, {"Strategy", "pv_invested"})
        // we need to make 2 copies
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

        StrategyLog():
            _strategy_names(nullptr)
        {}

        ~StrategyLog()
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
            time_serie_mod(s, "pv_liability").push_back(liabilities);

            time_serie_mod(s, "pv_asset").push_back(asset);
            time_serie_mod(s, "pv_equity").push_back(asset - liabilities);
        }


        void log_portfolio_values(const StrategyName& s,
                                  const double& time,  const Matrix& invested, const Matrix& cash,const Matrix& liabilities)
        {
            time_serie_mod(s, "pv_time").push_back(time);

            Matrix asset = invested + cash;

            for(uint i = 0, n = invested.cols(); i < n; ++i)
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
            if (_strategy_names)
            {
                Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols);

                // I had some trouble with MinGW and C++11 ranges
                const std::vector<std::string>& sn = *_strategy_names;

                //for(const std::string& i:sn){
                for(uint i = 0, n = sn.size(); i < n; ++i)
                {
                    ADD_TRACE("LOAD FILES");
                    std::fstream pv; pv.open("../" + sn[i] + "_pv.txt", std::ios::out);
                    std::fstream ps; ps.open("../" + sn[i] + "_ps.txt", std::ios::out);
                    std::fstream tw; tw.open("../" + sn[i] + "_tw.txt", std::ios::out);
                    std::fstream to; to.open("../" + sn[i] + "_to.txt", std::ios::out);

                    ADD_TRACE("SAVE PORTFOLIOVALUES");

                    // Portfolio Values
                    pv << "#time liability equity asset\n"
                       << build_matrix({{sn[i], "pv_time"},
                                        {sn[i], "pv_liability"},
                                        {sn[i], "pv_equity"},
                                        {sn[i], "pv_asset"}}).format(fmt);

                    // Portfolio State
                    ps << get_holdings<MatrixRowMajor>(sn[i]).format(fmt);

                    // Transaction weight
                    tw << get_weights<MatrixRowMajor>(sn[i]).format(fmt);

                    // Transaction Order
                    to << get_share<MatrixRowMajor>(sn[i]).format(fmt);

                    // close files
                    pv.close(); ps.close(); tw.close(); to.close();
                }
            }
        }

        DataFrame& add_data_frame(const StrategyName& name)
        {
            _data[name] = DataFrame();
            return _data[name];
        }


        // compute the max size
        uint size()
        {
            uint s = 0;

            for(auto& el:_data)
                s = s > el.second["pv_time"].size() ? s: el.second["pv_time"].size();

            return s;
        }

        DataFrame& df(const std::string& name) {   return _data[name]; }

        const std::vector<StrategyName>& strategy_names()    {   return *_strategy_names; }

private:
        // non const function are private
        inline std::vector<double>& time_serie_mod(const Identifier& i) {   return _data[i.first][i.second];   }
        inline std::vector<double>& time_serie_mod(const StrategyName& s,
                                              const FieldName& f) {   return _data[s][f];   }

    protected:
        uint _nsecurity;
        uint _vsize;
        std::unordered_map<StrategyName, DataFrame> _data;
        const std::vector<StrategyName>* _strategy_names;

public:


static void build_standard_data_frame(DataFrame& df, uint nsec, uint v_size = 1000, uint strat = 1)
{
    // We are using reserve() because we want to always use push_back and never []
    // Portfolio values
    reserve(df, "pv_time", v_size);
    reserve(df, "pv_invested", v_size * strat);    // Net of investment value
    reserve(df, "pv_asset", v_size * strat);       // investment + cash
    reserve(df, "pv_liability", v_size * strat);   // Shorted Investment and Borrowed money
    reserve(df, "pv_equity", v_size * strat);      // Long Investement + positive cash
    reserve(df, "pv_cash", v_size * strat);

    // portfolio state
    reserve(df, "ps_holdings", v_size * (nsec + 1) * strat);
    reserve(df, "st_weights", v_size * (nsec + 2) * strat); // Strategy Target Weights
    reserve(df, "to_share", v_size * (nsec + 1) * strat);

}
};

#endif

