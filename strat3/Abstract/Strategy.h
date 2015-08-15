#ifndef STRAT3_ABSTRACT_STRATEGY_HEADER
#define STRAT3_ABSTRACT_STRATEGY_HEADER

#include <string>

#include "Config.h"
#include "../enum.h"
#include "../Struct/TransactionWeight.h"

class DataStruct;
typedef unsigned int uint;

class Strategy
{
    public:

        virtual PLUGIN TransactionWeight* operator() (DataStruct& ds) = 0;

        void set_security_number(const uint& n){
            _nsecurity = n;
            weight() = Matrix::Constant(_nsecurity, 1, 1.0 / double(_nsecurity));
        }

        const uint& nsecurity  () const {   return _nsecurity;      }
        Matrix    & weight     ()       {   return _weight.weight;  }
        WeightType& weight_type()       {   return _weight.type;    }

    // Public attributes
        std::string title{"Empty Strategy"};
        std::string description{"No Description"};

        uint frequency{1};
        bool rebalanced{true};

    // Need to use accessor
    protected:
        TransactionWeight _weight;
        uint _nsecurity;

};

#endif
