#ifndef STRAT3_REPORT_LATEX_HEADER
#define STRAT3_REPORT_LATEX_HEADER

#include <fstream>

#include "DataAnalyzer.h"
#include "Backtester/Backtester.h"
#include "Report.h"
#include "script.h"

#include <cstdlib>

namespace strat3{

/*
 *  Add a new DataFrame "statistics"
 *      - Returns ==>>> matrix
 */
class Latex : public Report
{
public:
    Latex(DataAnalyzer& da_, Backtester& bt_):
        Report(da_, bt_), latex_out("strat3_report.pdf"), file_name("strat3_report")
    {
        os.open((file_name + ".tex").c_str(), std::ios::out);

        generate_gp_script(da.strategy_names(), da.security_names(), true, da.has_dates());
    }

    std::string latex_out;
    std::string file_name;

    ~Latex()    {   os.close(); }

    void head(std::string title = std::string("Strat 3 Tex Report"));
    void foot               ()
    {
        os << "\\end{document}\n";
    }

    virtual void body               ()
    {
        os << "\n \\frontmatter \n";
        disclaimer();

        os << "\n \\mainmatter \n";
        overview();
        risk();
        performance();
        transactions();
        assets();
        strategies();
        data();

        os << "\n \\appendix \n";
        definitions();
    }

    void generate()
    {
        head();
        body();
        foot();

        os.close();

        // the DVI will be in the binary folder
        int a = system(std::string("latex -interaction=batchmode " + file_name + ".tex").c_str());

        if (a == - 1)
            fprintf(stderr, "error compiling latex \n");
        else
        {
            a = system(std::string("latex -interaction=batchmode " + file_name + ".tex").c_str());

            // compile into PS
            a = system(std::string("dvips -q " + file_name  + ".dvi").c_str());

            // compile into pdf
            if (a != -1)
            {
                a = system(std::string("ps2pdf " + file_name + ".ps " + latex_out).c_str());
                if (a == -1)
                    fprintf(stderr, "error converting ps to pdf \n");
            }
            else
                fprintf(stderr, "error converting dvi to ps \n");
        }
    }

    void table_of_content   () {}

    void portfolio_value    () {}
    void holdings           () {}
    void transaction_order  () {}
    void target_weight      () {}

    virtual void transactions() {}
    virtual void definitions(){}
    virtual void assets(){}
    virtual void performance() {}


    virtual std::ostream& add_figure(Key input, Key caption="", Key label="");
    void overview           ();
    void disclaimer         ();
    void risk               ();
    void strategies         ();
    void data               ();


private:
    std::fstream os;
};

}

#endif
