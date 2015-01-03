#ifndef STRAT3_ABSTRACT_PORTFOLIO_H_
#define STRAT3_ABSTRACT_PORTFOLIO_H_

class AbstractTransactionWeight;
class AbstractTransactionOrder;
class AbstractTransactionAnswer;

// 
class AbstractMarketEngine;
class AbstractLog;

template<typename TimeType, typename PricesType>
class AbstractPortfolio
{
    public:
        AbstractPortfolio()
        {
        }
        
        virtual double liability  ()            {}
        virtual double invested   (PricesType*) {}
        virtual double asset      (PricesType*) {} 
        virtual double equity     (PricesType*) {}

        virtual void clearOrders()   {}
        virtual void transactionAnswer      (AbstractTransactionAnswer*) {}

        virtual void processTransactionWeight(TimeType, PricesType, TransactionWeight*)
        {}
       
    protected:
    
        
};

#endif