#ifndef STRAT3_REPORT_HTML_HEADER
#define STRAT3_REPORT_HTML_HEADER

#include <fstream>

#include "DataAnalyzer.h"
#include "Backtester/Backtester.h"
#include "Report.h"
#include "script.h"

#include "HTMLdef.h"
//#define LIST_LI(name) "<li><a href=#" #name ">" #name "</a></li>"
//#define SCRIPT(name)  "<script src=" #name "></script>"
//#define LINK_CSS(name)"<link rel=\"stylesheet\" href=" #name " type=\"text/css\" >"
//#define TITLE(title)  "<title> " #title " </title>"
//#define HEAD(html)    "<html>" #html "</html>"
//#define DIV(opt, html) "<div " #opt ">" #html "</div>"

namespace strat3{

class HTML : public Report
{
public:
    HTML(DataAnalyzer& da_, Backtester& bt_):
        Report(da_, bt_), html_out("strat3_report"), file_name("../../gen/strat3_report")
    {
        os.open((file_name + ".html").c_str(), std::ios::out);

        std::cout << "Dump Data for D3" << std::endl;
        da.get_log().dump();

        da.dump();

        //std::cout << "Generate D3 Script" << std::endl;
        //generate_gp_script(da.strategy_names(), da.security_names(), true, da.has_dates());
    }

    ~HTML()
    {
        os.close();
    }

    void generate()
    {
        head();
        table_of_content();
        foot();
    }

    void head               ()
    {
       os <<"<!DOCTYPE html>"
            "<html lang=\"en\">"
                HEAD(
                    "<meta charset=\"utf-8\">"
                    "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
                    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"

                    CSS_FILE(S(css/bootstrap.css))
                    CSS_FILE(S(css/bootstrap-responsive.css))
                    CSS_FILE(S(css/styles.css))
                    "<link rel=\"shortcut icon\" href=\"images/alepht.png\">"

                    JS_SCRIPT(S(js/jquery.js))
                    JS_SCRIPT(S(js/bootstrap.js))
                    JS_SCRIPT(S(js/d3.js))
                    JS_SCRIPT(S(js/d3.js))

                    TITLE(S(Strat3 HTML))
                )
                "<body>";
    }
    void foot()
    {
        os <<   "</body>"
            "</html>";
    }

    void table_of_content()
    {
        os <<
        DIV(
            H1(S(EW.V0R1F2))
            H2(S(Table of Contents))
                OL(
                LIST_LI(S(Overview))
                    OL(
                    LIST_LI(S(Holding Period Return))
                    LIST_LI(S(Statistics))
                    )
                LIST_LI(S(Risk))
                    OL(
                    LIST_LI(S(Periodict Return))
                    LIST_LI(S(Volatility Evolution))
                    LIST_LI(S(Drawdown))
                    LIST_LI(S(Density))
                    LIST_LI(S(Loss Distribution))
                    LIST_LI(S(Gain Distribution))
                    )
                LIST_LI(S(Performance))
                    OL(
                    LIST_LI(S(Transactions))
                    LIST_LI(S(Assets))
                    LIST_LI(S(Strategies))
                    LIST_LI(S(Data))
                        OL(
                        LIST_LI(S(Portfolio Values))
                        LIST_LI(S(Holdings))
                        LIST_LI(S(Transaction Order))
                        LIST_LI(S(Target Weight))
                        )
                    LIST_LI(S(Definitions))
                    LIST_LI(S(Disclaimer))
                    )
                ),
            ID("table_of_contents"), CLASS("well")
        );
    }
    void disclaimer         () {}
    void overview           () {}
    void risk               () {}
    void strategies         () {}

    void portfolio_value    () {}
    void holdings           () {}
    void transaction_order  () {}
    void target_weight      () {}

private:
    std::fstream os;
    std::string html_out;
    std::string file_name;
};

}

#endif
