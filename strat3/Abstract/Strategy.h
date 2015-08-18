#ifndef STRAT3_ABSTRACT_STRATEGY_HEADER
#define STRAT3_ABSTRACT_STRATEGY_HEADER

#include <string>

#include "Config.h"
#include "../enum.h"
#include "../Struct/TransactionWeight.h"

class PLUGIN  DataStruct;
typedef unsigned int uint;

class Strategy
{
    public:

        virtual PLUGIN TransactionWeight* operator() (DataStruct& ds) = 0;

        virtual void initialize(const uint& nsecurity, const uint& nstrat = 1, const void* user_data = 0)
        {
            _nsecurity = nsecurity;
            weight() = Matrix::Constant(_nsecurity, nstrat, 1.0 / double(_nsecurity));
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
