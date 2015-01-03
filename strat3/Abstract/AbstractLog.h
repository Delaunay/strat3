#ifndef STRAT3_ABSTRACT_LOG_H_
#define STRAT3_ABSTRACT_LOG_H_

class AbstractTransactionWeight;
class AbstractTransactionAnswer;
class AbstractTransactionOrder;

template<typename ReadRet, typename TimeType, typename PortfolioState, typename RawOrder>
class AbstractLog
{
    public:
        AbstractLog()
        {}
        
        virtual void logPortfolioState      (TimeType time, PortfolioState* state)           {}
        virtual void logTransactionWeight   (TimeType time, AbstractTransactionWeight* tw)   {}
        virtual void logTransactionOrder    (RawOrder* m)    {}
        
        // only exist when orders are passed to a MarketEngine
        virtual void logTransactionOrder    (AbstractTransactionOrder* m)  {}
        virtual void logTransactionAnswer   (AbstractTransactionAnswer* m) {}
        
        ReadRet readPortfolioState   () {   return ReadRet();   }
        ReadRet readTransactionWeight() {   return ReadRet();   }
        ReadRet readTransactionAnswer() {   return ReadRet();   }
        ReadRet readTransactionOrder () {   return ReadRet();   }
};

#endif