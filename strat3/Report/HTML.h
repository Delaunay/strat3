#ifndef STRAT3_REPORT_HTML_HEADER
#define STRAT3_REPORT_HTML_HEADER

#include "Report.h"

namespace strat3{

class HTML : public Report
{
public:
    HTML(const std::string& file_name, DataAnalyzer& da):
        Report(file_name, da)
    {}

    void head               () {}
    void foot               () {}

    void table_of_content   () {}
    void disclaimer         () {}
    void overview           () {}
    void risk               () {}
    void strategies         () {}

    void portfolio_value    () {}
    void holdings           () {}
    void transaction_order  () {}
    void target_weight      () {}
};

}

#endif
