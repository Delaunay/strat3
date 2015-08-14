#ifndef STRAT3_ABSTRACT_STRATEGY_HEADER
#define STRAT3_ABSTRACT_STRATEGY_HEADER

#include <string>

#include "../Struct/TransactionWeight.h"

class DataStruct;
typedef unsigned int uint;

class Strategy
{
    public:

        virtual TransactionWeight* operator() (DataStruct& ds) = 0;

        void set_security_number(const uint& n){
            _nsecurity = n;
            weight() = Column::Constant(_nsecurity, 1.0 / double(_nsecurity));
        }

        const uint& nsecurity  () const {   return _nsecurity;      }
        Matrix    & weight     ()       {   return _weight.weight;  }
        WeightType& weight_type()       {   return _weight.type;    }

    // Public attributes
        std::string title;
        std::string description;

        uint frequency;
        bool rebalanced;

    // Need to use accessor
    private:
        TransactionWeight _weight;
        uint _nsecurity;

};

#endif
