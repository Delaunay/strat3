#ifndef STRAT3_ABSTRACT_MARKETENGINE_H_
#define STRAT3_ABSTRACT_MARKETENGINE_H_

class AbstractTransactionOrder;
class AbstractTransactionAnswer;
class AbstractPortfolio

template<typename TimeType, typename PricesType>
class AbstractMarketEngine
{
    public:
        AbstractMarketEngine()
        {}
        
        virtual int addTransaction(AbstractTransactionOrder t)   {}
        virtual void marketOrder(AbstractTransactionOrder* t)    {}
        
        virtual void clearOrder()   {}
        
        virtual bool processSingleAsk(AbstractTransactionOrder* a)  {}
        virtual bool processSingleBid(AbstractTransactionOrder* a)  {}

        virtual void processAsk()   {}
        virtual void processBid()   {}

        void setPrices(PricesType* prices) {}

    protected:
        TimeType     _Time;
        PricesType*  _Prices;
};

#endif