#ifndef STRAT3_TESTER_HEADER
#define STRAT3_TESTER_HEADER

#include "DataManager/DataManager.h"
#include "Portfolio/Portfolio.h"
#include "Strategy/Strategy.h"
#include "DataLog/DataLog.h"


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
        // Predictor
};

class Tester
{
    public:
        Tester():
            _PriceManager(""), _PriceMatrix(""),
            _Cash(1000), _CurrentTime(0), _StratWindow(1), _UsingDates(false)
        {}

        DataQuery makeQuery    ()   {   return _Data->dataQuery(0, _StratWindow + _CurrentTime);    }

        Index     periodRunning()
        {   return _Data->matrixManager(_PriceManager)
                        ->matrix(_PriceMatrix)
                        ->rows() - _StratWindow - _CurrentTime;   }

        Index     max_period()
        {   return _Data->matrixManager(_PriceManager)
                        ->matrix(_PriceMatrix)
                        ->rows() - _StratWindow - 0;   }

        Row       lastPrice    ()
        {
            return _Data->matrixManager(_PriceManager)
                        ->matrix(_PriceMatrix)
                        ->row(_CurrentTime + _StratWindow);
        }

        Index     time         ()   {   return _CurrentTime;    }
        double    beginningCash()   {   return _Cash;           }

        void    addStrategy     (NodeTuple* x)   {   _Strategies.push_back(x);   }
        void    setDataManager  (DataManager* x, Key priceManager, Key priceMatrix)
        {
            _Data = x;
            _PriceManager = priceManager;
            _PriceMatrix  = priceMatrix;
        }

        Strategy*    getStrategy    (Index k)   {   return _Strategies[k]->strat;  }
        Portfolio*   getPortfolio   (Index k)   {   return _Strategies[k]->portfolio;  }
        MarketEngine*getMarketEngine(Index k)   {   return _Strategies[k]->portfolio->marketEngine();  }
        DataLog*     getLog         (Index k)   {   return _Strategies[k]->portfolio->log();  }

        bool      shouldRun    (Index k)
        {
            return (_CurrentTime == 0) ||
                   (
                        (getStrategy(k)->rebalanced()) &&
                        (_CurrentTime % getStrategy(k)->frequency() == 0)
                   );
        }
        void runOneStep()
        {
            DataQuery           dq = makeQuery();
            Row                 lp = lastPrice();

            TransactionWeight*  w;

            for(Index k = 0; k < _Strategies.size(); k++)
            {
                if (shouldRun(k))
                {
                    w = (*getStrategy(k))(&dq);
                    getPortfolio(k)->processTransactionWeight(_CurrentTime, &lp, w);
                }
                else
                {
                    getPortfolio(k)->logPortfolioFull(_CurrentTime, &lp);
                }
            }

            _CurrentTime++;
        }

        Index size() const {   return _Strategies.size(); }

        void setStratWindow(int a) { _StratWindow = a;  }

        // Matrix getDates() { _Data->date_matrix(); }
        std::vector<std::string> getSecurities() {}

        void setDates(Matrix Dates)
        {
            _UsingDates = true;
            _Dates = Dates;
        }

        Matrix& dates() {   return _Dates;  }

        bool usingDates()   {   return _UsingDates; }
        Index stratWindow() {   return _StratWindow; }

    protected:

        Matrix _Dates;
        bool _UsingDates;
        std::vector<NodeTuple*> _Strategies;
        Key _PriceManager;
        Key _PriceMatrix;

        double  _Cash;
        Index   _CurrentTime;
        Index   _StratWindow;

        DataManager* _Data;

};

#endif
