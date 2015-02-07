#include "TEXReport.h"

typedef std::unordered_map<std::string, double> MapStringKey;
typedef MapStringKey::iterator Iterator;

void TEXReport::overview()
{

    int m = _Data->size();

    _file <<
    "\\chapter{Overview}\n"
        "\\section{Holding Period Return}\n";

        addFigure("../gen/graph/holding_ret.tex", "Holding Period Return");
        _file << "\\section{Statistics}\n";

    _file <<
    "\\begin{center}\n"
    "\\begin{tabular}{|r|rrrrrrr|}\n";

    _file << "\\hline \n"
             "Strategies & Mean & St. Dev. & Sharp & Skew & Kurtosis & Positive & Negative \\\\ \n"
             "\\hline \n";

    for (int i = 0; i < m; i++)
    {
        _file << _Data->strategyName(i)                                                                  << " & "
                << format_double(_Data->_StatisticPoint(DataAnalyser::Mean, i) * 250.0 * 100.0, 2)       << " & "
                << format_double(_Data->_StatisticPoint(DataAnalyser::SD, i)   * sqrt(250.0) * 100.0, 2) << " & "
                << format_double(_Data->_StatisticPoint(DataAnalyser::Mean, i) * 250.0 /
                                (_Data->_StatisticPoint(DataAnalyser::SD, i)   * sqrt(250.0)), 4)        << " & "
                << format_double(_Data->_StatisticPoint(DataAnalyser::Skew, i), 4)                       << " & "
                << format_double(_Data->_StatisticPoint(DataAnalyser::Kurtosis, i), 2)                   << " & "
                << _Data->_StatisticPoint(DataAnalyser::Positive, i)                                     << " & "
                << _Data->_StatisticPoint(DataAnalyser::Negative, i)                                     << " \\\\ \n "
                 ;
    }

    _file << "\\hline \n";
    _file << "\\end{tabular} \n"
             "\\end{center}\n";
}

void TEXReport::disclaimer()
{
    _file <<
    "\\chapter{Disclaimer}\n"

    "\\section{Strat3 Disclaimer}\n"
         "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" "
         "AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE "
         "IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE "
         "ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE "
         "LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR "
         "CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF "
         "SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS "
         "INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN "
         "CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) "
         "ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE "
         "POSSIBILITY OF SUCH DAMAGE.\\n"

    "\\section{Report Disclaimer}\n"
        "To the best of our knowledge, the information contained herein is accurate"
        "and reliable as of the date of publication; however, we do not assume any liability"
        "whatsoever for the accuracy and completeness of the above information. "<<

        "Strat3" << " makes no warranties which extend beyond the"
        "description contained herein. Any information given in this statement does not"
        "constitute any warranty of merchantability or fitness for a particular use. It is the"
        "customers' responsibility to inspect and to"
        "test our products in order to satisfy"
        "themselves as to the suitability of the products to their particular purpose.\n"
    ;
}

void TEXReport::foot()
{
    _file <<
    "\\end{document}";
}


void TEXReport::generate()
{
    head();
    body();
    foot();

    _file.close();

    // the DVI will be in the binary folder
    int a = system("latex -interaction=batchmode ../gen/strat3_report.tex ");

    if (a == - 1)
        fprintf(stderr, "error compiling latex \n");
    else
    {
        a = system("latex -interaction=batchmode ../gen/strat3_report.tex ");

        // compile into PS
        a = system("dvips -q strat3_report.dvi");

        // compile into pdf
        if (a != -1)
        {
            a = system("ps2pdf strat3_report.ps ../gen/strat3_report.pdf");
            if (a == -1)
                fprintf(stderr, "error converting ps to pdf \n");
        }
        else
            fprintf(stderr, "error converting dvi to ps \n");
    }
}

void TEXReport::risk()
{
    int n = _Data->obs();
    _file <<
    "\\chapter{Risk}\n"
        "\\section{Periodict Return}\n";

            addFigure("../gen/graph/daily_ret.tex", "Periodic Return") <<
            //"\\input{../gen/graph/daily_ret.tex}\n"

        "\\section{Volatility Evolution}\n";

            addFigure("../gen/graph/volatility_ret.tex", "Volatility") <<
            //"\\input{../gen/graph/volatility_ret.tex}\n\n"

            "\n"
            "\\begin{center}\n"
            "\\begin{tabular}{|r|rrr|}\n"

                "\\hline \n"
                "\\  & Mean & St. Dev. & Count \\\\ \n"
                "\\hline \n";

                for(int i = 0; i < _Data->size(); i++)
                    _file << _Data->strategyName(i) << " & " <<
                             format_double(_Data->_MovingSDStat(DataAnalyser::Mean, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                             format_double(_Data->_MovingSDStat(DataAnalyser::SD, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                             _Data->_MovingSDStat(DataAnalyser::Positive, i)  << " \\\\ \n ";

       _file << "\\hline \n"
            "\\end{tabular}\n"
            "\\end{center}\n"

        "\\section{Drawdown}\n";
             addFigure("../gen/graph/drawdown_ret.tex", "Drawdown") <<
             //"\\input{../gen/graph/drawdown_ret.tex}\n"

        "\\section{Density}\n";
             addFigure("../gen/graph/distri_ret.tex", "Return Distribution") <<
             //"\\input{../gen/graph/distri_ret.tex}\n\n"

        "\\begin{center}\n"
        "\\begin{tabular}{rr}\n"

             //addFigure("../gen/graph/loss_distri_ret.tex") << " & ";
             //addFigure("../gen/graph/gain_distri_ret.tex") << " \\\\ \n ";
             "\\input{../gen/graph/loss_distri_ret.tex} & \\input{../gen/graph/gain_distri_ret.tex} \\\\ \n"

             "\\begin{tabular}{|r|rrr|}\n"

                "\\hline \n"
                "\\  & Mean & St. Dev. & Count (\\%) \\\\ \n"
                "\\hline \n";

                for(int i = 0; i < _Data->size(); i++)
                    _file << _Data->strategyName(i) << " & " <<
                             format_double(_Data->_StatisticPoint(DataAnalyser::MeanNegative, i) * 100.0 * 250.0, 2)  << " & " <<
                             format_double(_Data->_StatisticPoint(DataAnalyser::SDNegative, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                             format_double(double(_Data->_StatisticPoint(DataAnalyser::Negative, i) * 100.0) / n, 2)  << " \\\\ \n ";

       _file << "\\hline \n"
             "\\end{tabular}\n"

             " & \n"

             "\\begin{tabular}{|r|rrr|}\n"

                "\\hline \n"
                "\\  & Mean & St. Dev. & Count (\\%) \\\\ \n"
                "\\hline \n";

                   for(int i = 0; i < _Data->size(); i++)
                       _file << _Data->strategyName(i) << " & " <<
                                format_double(_Data->_StatisticPoint(DataAnalyser::MeanPositive, i) * 100.0 * 250.0, 2)  << " & " <<
                                format_double(_Data->_StatisticPoint(DataAnalyser::SDPositive, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                                format_double(double(_Data->_StatisticPoint(DataAnalyser::Positive, i) * 100.0) / n, 2)  << " \\\\ \n ";

       _file << "\\hline \n"
             "\\end{tabular}\n"


        "\\end{tabular}\n\n"
        "\\end{center}\n";
}

void TEXReport::strategies()
{
    _file <<
    "\\chapter{Strategies}\n"
    "\\begin{multicols}{2}\n";

    for(int i = 0, n = _Data->size(); i < n; i++)
    {
        _file <<
        "\\section{" << _Data->strategyName(i) <<"}\n"
            "\\subsection{Description} \n" <<
                _Data->_Data->getStrategy(i)->description() << "\n"
            "\\subsection{Configuration}\n"

                 "\\begin{tabular}{|r|r|}\n"
                 "\\hline \n"
                    "Frequency & " << _Data->_Data->getStrategy(i)->frequency() << "\\\\ \n"
                    "Version  & " << _Data->_Data->getStrategy(i)->version() << "\\\\ \n"
                    "Rebalanced & " << get_bool_as_string(_Data->_Data->getStrategy(i)->rebalanced()) << "\\\\ \n"
                 "\\hline \n"
                 "\\end{tabular}\n"
                 ;
    }

    _file << "\\end{multicols}";
}


void TEXReport::data()
{
    int m = _Data->obs();

    _file <<
    "\\chapter{Data}\n"
        // =================================
        "\\section{Portfolio Values}\n";

        for (int i = 0; i < _Data->size(); i++)
        {
            _file << "\\subsection{"<< _Data->strategyName(i) <<"}\n";

            //"\\input{../gen/graph/"<< _Data->strategyName(i) <<"_values.tex}\n";
            addFigure("../gen/graph/" + _Data->strategyName(i) + "_values.tex", _Data->strategyName(i) + " Assets");
        }

        // =================================
        _file <<"\\section{Holdings}\n";
                //"Holdings'' percentage variation ";

        for (int i = 0; i < _Data->size(); i++)
        {
            _file << "\\subsection{"<< _Data->strategyName(i) <<"}\n";

            //"\\input{../gen/graph/"<< _Data->strategyName(i) <<"_holding_evol.tex}\n";
            addFigure("../gen/graph/" + _Data->strategyName(i) + "_holding_evol.tex", _Data->strategyName(i) + " Holdings percentage variation");
        }

        // =================================
        _file <<"\\section{Transaction Order}\n"
              "Statistics about the number of Asset's unit bought/sold. The first observation is skipped";

        for (int k = 0; k < _Data->size(); k++)
        {
            _file << "\\subsection{"<< _Data->strategyName(k) <<"}\n"

                     "\\begin{center}\n"
                     "\\begin{tabular}{|r|rrrrrr|}\n"
                     "\\hline\n"
                     "\\ & Mean & Mean (Bought) & Mean (Sold) & St. Dev. & \\% Buy & \\% Sell \\\\ \n"
                     "\\hline\n";

                     for(int i = 0, n = _Data->security_size(); i < n; i++)
                         _file << "Sec" << std::to_string(i) << " & " <<
                                  format_double(_Data->_HoldStat[k](DataAnalyser::Mean, i), 4)         << " & " <<
                                  format_double(_Data->_HoldStat[k](DataAnalyser::MeanPositive, i), 2) << " & " <<
                                  format_double(_Data->_HoldStat[k](DataAnalyser::MeanNegative, i), 2) << " & " <<
                                  format_double(_Data->_HoldStat[k](DataAnalyser::SD, i), 2)           << " & " <<
                                  format_double(_Data->_HoldStat[k](DataAnalyser::Positive, i) * 100.0/ m, 2) << " & " <<
                                  format_double(_Data->_HoldStat[k](DataAnalyser::Negative, i) * 100.0/ m, 2) << " \\\\ \n";

                     _file << "\\hline\n"
                     "\\end{tabular}\n"
                     "\\end{center}\n";
        }

        // =================================
        _file <<"\\section{Target Weight}\n";

        for (int i = 0; i < _Data->size(); i++)
        {
            _file << "\\subsection{"<< _Data->strategyName(i) <<"}\n";
                     //"\\input{../gen/graph/"<< _Data->strategyName(i) <<"_weight_target.tex}\n";
                     addFigure("../gen/graph/" + _Data->strategyName(i) + "_weight_target.tex", _Data->strategyName(i) + " Target Weight");
        }
}

std::fstream& TEXReport::addFigure(Key input, Key caption, Key label)
{
    _file <<
//    "\\begin{figure}[htbp]\n"
//        "\\begin{center}\n"
            "\\input{"<< input <<"}\n"
//        "\\end{center}\n"
    ;

//    if (!caption.empty())
//        _file << "\\caption{"<< caption <<"}\n";

//    if (!caption.empty())
//        _file << "\\label{"<< label <<"}\n";

//    _file << "\\end{figure}\n";

    return _file;
}
