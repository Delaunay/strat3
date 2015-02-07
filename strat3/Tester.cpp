#include "Tester.h"

#include "Portfolio/Portfolio.h"
#include "Strategy/Strategy.h"
#include "DataLog/DataLog.h"

#include "DataManager/all.h"

Tester::Tester():
    _PriceManager(""), _PriceMatrix(""),
    _Cash(1000), _CurrentTime(0), _StratWindow(1), _UsingDates(false)
{}

DataQuery Tester::makeQuery    ()   {   return _Data->dataQuery(0, _StratWindow + _CurrentTime);    }

Index     Tester::periodRunning()
{   return _Data->matrixManager(_PriceManager)
                ->matrix(_PriceMatrix)
                ->rows() - _StratWindow - _CurrentTime;   }

Index     Tester::max_period()
{   return _Data->matrixManager(_PriceManager)
                ->matrix(_PriceMatrix)
                ->rows() - _StratWindow - 0;   }

Row       Tester::lastPrice    ()
{
    return _Data->matrixManager(_PriceManager)
                ->matrix(_PriceMatrix)
                ->row(_CurrentTime + _StratWindow);
}

Index     Tester::time         ()   {   return _CurrentTime;    }
double    Tester::beginningCash()   {   return _Cash;           }

void    Tester::addStrategy     (NodeTuple* x)   {   _Strategies.push_back(x);   }
void    Tester::setDataManager  (DataManager* x, Key priceManager, Key priceMatrix)
{
    _Data = x;
    _PriceManager = priceManager;
    _PriceMatrix  = priceMatrix;
}

Strategy*    Tester::getStrategy    (Index k)   {   return _Strategies[k]->strat;  }
Portfolio*   Tester::getPortfolio   (Index k)   {   return _Strategies[k]->portfolio;  }
MarketEngine*Tester::getMarketEngine(Index k)   {   return _Strategies[k]->portfolio->marketEngine();  }
DataLog*     Tester::getLog         (Index k)   {   return _Strategies[k]->portfolio->log();  }

bool      Tester::shouldRun    (Index k)
{
    return (_CurrentTime == 0) ||
           (
                (getStrategy(k)->rebalanced()) &&
                (_CurrentTime % getStrategy(k)->frequency() == 0)
           );
}
void Tester::runOneStep()
{
    DataQuery           dq = makeQuery();
    Row                 lp = lastPrice();

    DataStruct ds;
               ds.dataManager = &dq;

    TransactionWeight*  w;


    for(Index k = 0; k < _Strategies.size(); k++)
    {
        if (shouldRun(k))
        {
            w = (*getStrategy(k))(&ds);
            getPortfolio(k)->processTransactionWeight(_CurrentTime, &lp, w);
        }
        else
        {
            getPortfolio(k)->logPortfolioFull(_CurrentTime, &lp);
        }
    }

    _CurrentTime++;
}

Index Tester::size() const {   return _Strategies.size(); }

void Tester::setStratWindow(int a) { _StratWindow = a;  }

// Matrix getDates() { _Data->date_matrix(); }
std::vector<std::string> getSecurities() {}

void Tester::setDates(Matrix Dates)
{
    _UsingDates = true;
    _Dates = Dates;
}

Matrix& Tester::dates() {   return _Dates;  }

bool Tester::usingDates()   {   return _UsingDates; }
Index Tester::stratWindow() {   return _StratWindow; }
