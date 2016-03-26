#ifndef STRAT3_REPORT_REPORT_HEADER
#define STRAT3_REPORT_REPORT_HEADER

//#include "DataAnalyzer.h"



namespace strat3{

class DataAnalyzer;
class Backtester;

class Report
{
public:
    Report(DataAnalyzer& da_, Backtester& bt_):
        da(da_), bt(bt_)
    {}

    virtual void head(){}
    virtual void foot(){}

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

    virtual void table_of_content   () {}
    virtual void disclaimer         () {}
    virtual void overview           () {}
    virtual void risk               () {}
    virtual void strategies         () {}

    virtual void portfolio_value    () {}
    virtual void holdings           () {}
    virtual void transaction_order  () {}
    virtual void target_weight      () {}

    virtual void data()
    {
        portfolio_value();
        holdings();
        transaction_order();
        target_weight();
    }

protected:
    DataAnalyzer& da;
    Backtester& bt;
};

}

#endif
