#ifndef REPORT_REPORT_HEADER
#define REPORT_REPORT_HEADER

#include "StrategyLog/StrategyLog.h"

namespace strat3{

class Report
{
public:
    Report(const std::string& file_name,
           const std::vector<std::string>& strategy_names,
           StrategyLog& l):
        log(l), _strategy_names(strategy_names)
    {}

    virtual void head()= 0;
    virtual void foot() = 0;

    virtual void generate()
    {
        head();

        table_of_content();

        disclaimer();

        overview();
        risk();
        strategies();

        data();
        foot();
    }

    virtual void table_of_content   () = 0;
    virtual void disclaimer         () = 0;
    virtual void overview           () = 0;
    virtual void risk               () = 0;
    virtual void strategies         () = 0;

    virtual void portfolio_value    () = 0;
    virtual void holdings           () = 0;
    virtual void transaction_order  () = 0;
    virtual void target_weight      () = 0;

    virtual void data()
    {
        portfolio_value();
        holdings();
        transaction_order();
        target_weight();
    }

    const std::vector<std::string>& strategy_names() {  return _strategy_names; }

protected:
    StrategyLog& log;
    const std::vector<std::string>& _strategy_names;
};

}

#endif
