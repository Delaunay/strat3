//#ifndef STRAT3_ABSTRACT_STRATEGYLOG_HEADER
//#define STRAT3_ABSTRACT_STRATEGYLOG_HEADER

//#include "../enum.h"

//class TransactionWeight;
//class TransactionAnswer;
//class Transaction;

//class StrategyLog
//{
//public:

//    // Same as always
//    virtual void logPortfolioState      (const double& time, const Column& state) = 0;
//    virtual void logTransactionWeight   (const double& time, const TransactionWeight& tw) = 0;

//    virtual void logPortfolioValues     (const double& time, const double& invested, const double& cash,
//                                         const double& asset,const double& liabilities, const double& equity) = 0;

//    // does not exist if there are no market Engine
//    virtual void logTransactionAnswer   (const TransactionAnswer& m) = 0;

//    // two cases : with ME and without
//    virtual void logTransactionOrder    (const Transaction& m) = 0;
//    virtual void logTransactionOrder    (const double& time, const Column& m) = 0;

////    virtual Matrix transactionAnswer() = 0;
////    virtual Matrix transactionOrder () = 0;
////    virtual Matrix weightMatrix     () = 0;
////    virtual Matrix portfolioValues  () = 0;
////    virtual Matrix portfolioState   () = 0;

////    virtual Matrix readTransactionAnswer() const    { return transactionAnswer();  }
////    virtual Matrix readTransactionOrder () const    { return transactionOrder();   }
////    virtual Matrix readWeightMatrix     () const    { return weightMatrix();       }
////    virtual Matrix readPortfolioValues  () const    { return portfolioValues();    }
////    virtual Matrix readPortfolioState   () const    { return portfolioState();     }

//    virtual void save_all();
//protected:

//};

//#endif
