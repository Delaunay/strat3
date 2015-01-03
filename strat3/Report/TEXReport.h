#ifndef STRAT3_REPORT_TEXREPORT_HEADER
#define STRAT3_REPORT_TEXREPORT_HEADER

#include "Report.h"

// latex my_file.tex    => my_file.dvi
// dvips file.dvi -o    => my_file.ps
// ps2pdf file.ps       => my_file.pdf

class TEXReport
{
public:
    TEXReport(Key rep_filename, DataAnalyser* data):
        _Data(data)
    {
        _file.open(Key(Key("../gen/") + rep_filename).c_str(), std::ios::out);
    }

    // Report Body
    void body()
    {
        _file << "\n \\frontmatter \n";
        disclaimer();

        _file << "\n \\mainmatter \n";
        overview();
        risk();
        performance();
        transactions();
        assets();
        strategies();
        data();

        _file << "\n \\appendix \n";

        definitions();
    }

    void head(std::string title = std::string("Strat 3 Tex Report"))
    {
        _file <<
        "\\documentclass[11pt, openany]{book}\n"
        "\\usepackage[top=2.5cm, bottom=2.5cm, left=2.5cm, right=2.5cm]{geometry}\n"
        "\\usepackage{hyperref}\n"
        "\\usepackage{amsmath}\n"
        "\\usepackage{amssymb}\n"
        "\\usepackage{graphicx}\n"
        "\\usepackage{color}\n"
        "\\definecolor{linkcolour}{rgb}{0,0.2,0.6}\n"
        "%\\usepackage{multirow}\n\n"

        "\\title{"<< title <<"}\n"
        "\\author{Strat 3}\n\n"

        "\\begin{document}\n\n"

        "\\maketitle\n"
        "\\tableofcontents\n";
    }

    void data();

    void performance()
    {
//        _file <<
//        "\\chapter{Performance}\n"
//            "\\section{Stochastic Dominance}\n";
    }

    void transactions()
    {
//        _file <<
//        "\\chapter{Transactions}\n";
    }

    void assets()
    {
//        _file <<
//        "\\chapter{Assets}\n";
    }

    void definitions()
    {
//        _file <<
//        "\\chapter{Definitions}\n";
    }

    // generate the whole thing
    void generate();

    void overview();
    void risk();
    void strategies();
    void disclaimer();
    void foot();

protected:

    std::fstream _file;
    DataAnalyser* _Data;
};
#endif
