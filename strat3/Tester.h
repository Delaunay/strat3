#ifndef STRAT3_TESTER_HEADER
#define STRAT3_TESTER_HEADER

#include "enum.h"
#include "DataManager/DataQuery.h"

class Predictor;
class Strategy;
class Portfolio;
class DataLog;
class DataManager;
class MarketEngine;

struct NodeTuple
{
    public:
        NodeTuple(Strategy* s = 0, Portfolio* p = 0, MarketEngine* m = 0):
            strat(s), portfolio(p), market(m), log(0)
        {}

        Strategy*       strat;
        Portfolio*      portfolio;
        MarketEngine*   market;
        DataLog*        log;
        Predictor*      predictor;
};

class Tester
{
    public:
        Tester();

        DataQuery makeQuery    ();
        Index     periodRunning();
        Index     max_period   ();
        Row       lastPrice    ();
        Index     time         ();
        double    beginningCash();

        void         addStrategy    (NodeTuple* x);

        void         setDataManager (DataManager* x, Key priceManager, Key priceMatrix);
        void         setStratWindow (int a);
        void         setDates       (Matrix Dates);

        // Shortcut
        Strategy*    getStrategy    (Index k);
        Portfolio*   getPortfolio   (Index k);
        MarketEngine*getMarketEngine(Index k);
        DataLog*     getLog         (Index k);

        bool         shouldRun      (Index k);
        void         runOneStep     ();
        Index        size           () const;

        Matrix&      dates();
        bool         usingDates();

        // Options
        Index        stratWindow();

        // currently useless
        // Matrix getDates() { _Data->date_matrix(); }
        std::vector<std::string> getSecurities();

    protected:

        // Dates
        Matrix  _Dates;
        bool    _UsingDates;

        // Price
        Key     _PriceManager;
        Key     _PriceMatrix;
        double  _Cash;
        Index   _CurrentTime;
        Index   _StratWindow;

        DataManager* _Data;

        std::vector<NodeTuple*> _Strategies;

};

#endif
