#ifndef STRAT3_ABSTRACT_STRATEGY_HEADER
#define STRAT3_ABSTRACT_STRATEGY_HEADER

#include <string>
#include <vector>

#include "Plugin.h"
#include "../enum.h"
#include "../Struct/TransactionWeight.h"

struct PLUGIN_EXPORT  DataStruct;
typedef unsigned int uint;

class PLUGIN_EXPORT Strategy
{
    public:
        Strategy():
            title("Empty Strategy"), description("No Description")
        {}

        virtual const TransactionWeight* operator() (const DataStruct& ds) = 0;

        virtual void initialize(const uint& nsecurity, const uint& nstrat = 1, const void* user_data = 0)
        {
            _nsecurity = nsecurity;
            weight() = Matrix::Constant(_nsecurity, nstrat, 1.0 / double(_nsecurity));
        }

        virtual void log_custom_data(std::vector<double>& t) {   return; }

        const uint& nsecurity  () const {   return _nsecurity;      }
        Matrix    & weight     ()       {   return _weight.weight;  }
        WeightType& weight_type()       {   return _weight.type;    }
        const TransactionWeight& tw() const {   return _weight; }

    // Public attributes
        std::string title;
        std::string description;

        uint strategy_window{1};
        uint frequency{1};
        bool rebalanced{true};
        bool log_implemented{false};

    // Need to use accessor
    protected:
        TransactionWeight _weight;
        uint _nsecurity;

};

#endif
