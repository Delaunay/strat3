#ifndef STRAT3_TESTER_HEADER
#define STRAT3_TESTER_HEADER

#include<vector>

#include "../enum.h"
#include "../Abstract/Portfolio.h"
#include "../Abstract/Strategy.h"
#include "../DataManager/MatrixManager.h"
#include "../DataManager/MatrixQuery.h"
#include "../StrategyLog/StrategyLog.h"

#include "DynamicObject.h"


namespace strat3{

using DynamicLoading::DynamicObject;

// define dynamicly loaded Actor
typedef DynamicObject<Strategy>     MStrategy;
typedef DynamicObject<Portfolio>    MPortfolio;
typedef DynamicObject<StrategyLog>  MStrategyLog;
//typedef DynamicObject<DataManager>  MDataManager;

//typedef DynamicObject<AbstractPredictor> MPredictor;
//typedef DynamicObject<AbstractMarketEngine> MMarketEngine;
//typedef DynamicObject<AbstractSecurityDatabase> MSecurityDatabase;

struct NodeTuple
{
    public:
        NodeTuple(MStrategy* s = 0, MPortfolio* p = 0/*, MMarketEngine* m = 0*/):
            _strat(s), _portfolio(p)//, market(m), log(0), predictor(0)
        {}

        void load_strategy(const std::string& name)
        {
            _strat = new MStrategy(name);
        }

        void load_portfolio(const std::string& name)
        {
            _portfolio = new MPortfolio(name);
        }

        ~NodeTuple()
        {
            delete _strat;
            delete _portfolio;
//            delete market;
//            delete log;
//            delete predictor;
        }

        MStrategy& strategy() { return *_strat;}
        MPortfolio& portfolio() { return *_portfolio;}

private:

        MStrategy*       _strat;
        MPortfolio*      _portfolio;
//        MMarketEngine*   market;
//        MDataLog*        log;
//        MPredictor*      predictor;
};

class Backtester
{
    public:
        Backtester():
            _price_matrix(""),
            /*_cash(1000),*/ _time(0), _strat_window(1), _using_dates(false),
            _data(0)
        {}

        void initialize()
        {
            std::vector<std::string> strat_vec;

            for(int i = 0; i < _strategies.size(); ++i)
                strat_vec.push_back(title(i));

            _slog.initialize(strat_vec, security_number(), max_period());
        }

        void        run_one_step   ();
        MatrixQuery make_query     ();
        uint        period_running () const;
        uint        max_period     () const;
        uint        security_number() const;
        const Row   last_price     () const;
        bool        should_run    (Index k);
        void add_strategy     (NodeTuple *x);
        void set_data_manager (MatrixManager* x, Key priceMatrix);

        inline       uint    size         () const   {  return _strategies.size();  }
        inline const uint&   time         () const   {  return _time;               }
        inline const uint&   strat_window () const   {  return _strat_window;       }
        inline MStrategy&    get_strategy (uint k)   {  return _strategies[k]->strategy();       }
        inline MPortfolio&   get_portfolio(uint k)   {  return _strategies[k]->portfolio();   }
        inline Matrix&       dates        ()         {  return _dates;}
        inline bool&         using_dates  ()         {  return _using_dates;    }
        inline void      set_strat_window (const uint& a)
        {
            assert(_time != 0 && "Modifying Configuration during Simulation");
            _strat_window = a;
        }

        inline const std::string& title(uint k) {  return get_strategy(k)->title; }

        // Shortcut
//        MMarketEngine*getMarketEngine(Index k);
//        MDataLog*     getLog         (Index k);
//        MSecurityDatabase* getSecurityDatabase();
//        void setSecurityDatabase(SecurityDatabase* sd);
        // currently useless
        // Matrix getDates() { _Data->date_matrix(); }
        //std::vector<std::string> get_securities();


        inline void log_weights(const std::string& strat, const TransactionWeight& tw)
        {
            _slog.log_transaction_weight(strat, _time, tw);
        }

        //log_porfolio_state(title(k), get_portfolio(k)->state());
        inline void log_portfolio_state(const std::string& strat, const Matrix& state)
        {
            _slog.log_portfolio_state(strat, _time, state);
        }

        inline void log_orders(const std::string& strat, const Matrix& orders)
        {
            _slog.log_transaction_order(strat, _time, orders);
        }

        inline void log_portfolio_values(const std::string& strat, const Matrix& invested, const Matrix& cash, const Matrix liab)
        {
            _slog.log_portfolio_values(strat, _time, invested, cash, liab);
        }

        inline StrategyLog& strategy_log()
        {
            return _slog;
        }

        // Print Current setup
        void print_config(std::ostream& out)
        {
            out << "Not Implemented";
        }

    protected:

        // Dates
        Matrix _dates;          // Dates
        bool   _using_dates;    // if we are using dates
        Key    _price_matrix;   // Matrix used for buy/sell
        uint   _time;           // Current time
        uint   _strat_window;   // Minimum number of days

        StrategyLog _slog;      // Logged

        MatrixManager* _data;   // Data needed

        //DataManager* _data;
        std::vector<NodeTuple*> _strategies;//  Strategies
};
}
#endif
