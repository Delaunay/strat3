#ifndef STRAT3_ABSTRACT_STRATEGY_H_
#define STRAT3_ABSTRACT_STRATEGY_H_

class AbstractDataQuery;

template<typename Weight>
class AbstractStrategy
{
    public:
        AbstractStrategy()
        {}
        
        virtual Weight* operator() (AbstractDataQuery*)
        {
        }
        
    protected:
    
        Weight _Weight;
};

#endif