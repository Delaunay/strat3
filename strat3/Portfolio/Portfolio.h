#ifndef STRAT3_PORTFOLIO_HEADER
#define STRAT3_PORTFOLIO_HEADER

#include <iostream>

#include "../Strategy/Strategy.h"
#include "Transaction.h"
#include "TransactionAnswer.h"

class MarketEngine;
class DataLog;


//enum TresholdType
//{
//    AbsoluteTreshold,            // order value > X $$
//    RelativeTresholdPortfolio,   // order value > X % portfolio
//    RelativeTresholdPosition,    // order value > X % current position
//};

class Portfolio
{
    public:
        typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMajorMatrix;

        Portfolio(int securityNum, double cash, std::string name, MarketEngine* marketEngine);
        ~Portfolio();

        const
        Column* state      ()           {   return &_PortfolioState; }
        double  liability  (Row* prices);
        double  invested   (Row* prices);
        double  asset      (Row* prices);
        double  equity     (Row* prices);

        void clearOrders();
        void transactionAnswer      (TransactionAnswer* m);

        virtual
        void processTransactionWeight(Index time, Row* price, TransactionWeight* tw);
        void order(WeightType a, Row* price, Column* target, Column* holding, Column* nbshare);
        void order(WeightType a, Row* price, Matrix* target, Column* holding, Column* nbshare);

        DataLog*      log()             {   return _Log;    }
        MarketEngine* marketEngine()    {   return _Market; }

        void     deleteLog(bool t)      {   _DeleteLog = t; }
        void     logPortfolioFull(Index time, Row* price);

    protected:

        DataLog*    _Log;
        bool        _DeleteLog;

        double        _Time;
        double        _Cash;
        Column        _PortfolioState; // Hold number of shares
        MarketEngine* _Market;
};

#endif
