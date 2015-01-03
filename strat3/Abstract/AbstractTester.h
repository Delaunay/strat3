#ifndef STRAT3_ABSTRACT_TESTER_H_
#define STRAT3_ABSTRACT_TESTER_H_

class AbstractStrategy;
class AbstractMarketEngine;
class AbstractPortfolio;
class AbstractDataQuery;

struct NodeTuple
{
    public:
        NodeTuple(AbstractStrategy* s, AbstractPortfolio* p, AbstractMarketEngine* m = 0):
            strat(s), portfolio(p), market(m)
        {}

        AbstractStrategy*       strat;
        AbstractPortfolio*      portfolio;
        AbstractMarketEngine*   market;
};

template<typename TimeType, typename PricesType>
class AbstractTester
{
    public:
        AbstractTester()
        {
        }
        
        AbstractDataQuery* makeQuery(){}
        
        PricesType  lastPrice  (){}
        TimeType    time       (){}
        void        addStrategy(AbstractStrategy* x){}
        
        void runOneStep()   {}  
};

#endif