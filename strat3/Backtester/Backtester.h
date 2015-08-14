#ifndef STRAT3_TESTER_HEADER
#define STRAT3_TESTER_HEADER

#include "../enum.h"
#include "../Abstract/Portfolio.h"
#include "../Abstract/Strategy.h"
#include "../Abstract/StrategyLog.h"

#include "../DataManager/DataManager.h"
#include "../StrategyLog/StrategyLog.h"

#include "../DataManager/DataQuery.h"

#include "DynamicObject.h"

#include<vector>

namespace strat3{


// define dynamicly loaded Actor
typedef DynamicObject<Strategy>     MStrategy;
typedef DynamicObject<Portfolio>    MPortfolio;
typedef DynamicObject<StrategyLog>  MStrategyLog;
typedef DynamicObject<DataManager>  MDataManager;

//typedef DynamicObject<AbstractPredictor> MPredictor;
//typedef DynamicObject<AbstractMarketEngine> MMarketEngine;
//typedef DynamicObject<AbstractSecurityDatabase> MSecurityDatabase;

struct NodeTuple
{
    public:
        NodeTuple(MStrategy* s = 0, MPortfolio* p = 0/*, MMarketEngine* m = 0*/):
            _strat(s), _portfolio(p)//, market(m), log(0), predictor(0)
        {
        }

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
            _price_manager(""), _price_matrix(""),
            _cash(1000), _time(0), _strat_window(1), _using_dates(false),
            _data(0)
        {}

        DataQuery make_query    ();
        uint      period_running();
        uint      max_period    ();
        Row       last_price    ();
        void      run_one_step  ();
        void add_strategy    (NodeTuple* x);
        void set_data_manager (DataManager* x, Key priceManager, Key priceMatrix);
        bool         should_run      (Index k);

        inline       uint    size         () const   {  return _strategies.size();  }
        inline const uint&   time         () const   {  return _time;               }
        inline const double& begin_cash   () const   {  return _cash;               }
        inline const uint&   strat_window () const   {  return _strat_window;       }
        inline MStrategy&    get_strategy (uint k)  {  return _strategies[k]->strategy();       }
        inline MPortfolio&   get_portfolio(uint k)  {  return _strategies[k]->portfolio();   }
        inline Matrix&       dates        ()         {  return _dates;}
        inline bool&         using_dates  ()         {   return _using_dates;    }
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

        inline void log_portfolio_values(const std::string& strat, const Matrix& price)
        {
        }

    protected:

        // Dates
        Matrix _dates;
        bool   _using_dates;
        Key    _price_manager;
        Key    _price_matrix;
        double _cash;
        uint   _time;
        uint   _strat_window;

        StrategyLog _slog;

        DataManager* _data;
        std::vector<NodeTuple*> _strategies;
//        std::vector<Predictor>  _GlobalPredictors;
//        MSecurityDatabase*      _SecurityDatabase;
};
}
#endif
