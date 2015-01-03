#include "TEXReport.h"

void TEXReport::overview()
{

    int m = _Data->size();

    _file <<
    "\\chapter{Overview}\n"
        "\\section{Holding Period Return}\n"
        "\\input{../gen/graph/holding_ret.tex}\n"
        "\\section{Statistics}\n";

    _file <<
    "\\begin{center}\n"
    "\\begin{tabular}{|r|";
    for (int i = 0; i < m; i++)
        _file <<"r";

    _file << "|}\n \\hline \n";

    // line 1
    _file << "n = " << _Data->obs() << " & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file << _Data->strategyName(i) << " & " ;
        else
            _file << _Data->strategyName(i) << "\\\\ \n";

    _file << "\\hline \n";

    // line 2
    _file << "Mean & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file << trunc(_Data->_StatisticPoint(DataAnalyser::Mean, i) * 100.0 * 250.0, 2) << " & ";
        else
            _file <<  trunc(_Data->_StatisticPoint(DataAnalyser::Mean, i) * 100.0 * 250.0, 2) << "\\\\ \n";

    // line 3
    _file << "St. Dev & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file <<  trunc(_Data->_StatisticPoint(DataAnalyser::SD, i) * sqrt(250.0) * 100.0, 2) << " & ";
        else
            _file <<  trunc(_Data->_StatisticPoint(DataAnalyser::SD, i) * sqrt(250.0) * 100.0, 2) << "\\\\ \n";

    // line 4
    _file << "Sharp & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file << trunc(_Data->_StatisticPoint(DataAnalyser::Mean, i) * 250.0 / (_Data->_StatisticPoint(DataAnalyser::SD, i) * sqrt(250.0)), 4) << " & ";
        else
            _file << trunc(_Data->_StatisticPoint(DataAnalyser::Mean, i) * 250.0 / (_Data->_StatisticPoint(DataAnalyser::SD, i) * sqrt(250.0)), 4) << "\\\\ \n";

    // line 5
    _file << "Skew & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file << "NA" << " & ";
        else
            _file << "NA"  << "\\\\ \n";

    // line 6
    _file << "Kurtosis & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file << "NA" << " & ";
        else
            _file << "NA"  << "\\\\ \n";

    // line 7
    _file << "Positive & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file << _Data->_StatisticPoint(DataAnalyser::Positive, i) << " & ";
        else
            _file << _Data->_StatisticPoint(DataAnalyser::Positive, i) << "\\\\ \n";

    // line 8
    _file << "Negative & ";

    for (int i = 0; i < m; i++)
        if (i < m - 1)
            _file << _Data->_StatisticPoint(DataAnalyser::Negative, i) << " & ";
        else
            _file << _Data->_StatisticPoint(DataAnalyser::Negative, i) << "\\\\ \n";

    _file << "\\hline \n";
    _file << "\\end{tabular} \n"
             "\\end{center}\n";
}

void TEXReport::disclaimer()
{
    _file <<
    "\\chapter{Disclaimer}\n"
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
         "POSSIBILITY OF SUCH DAMAGE."
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
    int a = system("latex ../gen/strat3_report.tex ");

    if (a == - 1)
        fprintf(stderr, "error compiling latex \n");
    else
    {
        a = system("latex ../gen/strat3_report.tex ");

        // compile into PS
        a = system("dvips strat3_report.dvi");

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
        "\\section{Periodict Return}\n"
            "\\input{../gen/graph/daily_ret.tex}\n"

        "\\section{Volatility Evolution}\n"
            "\\input{../gen/graph/volatility_ret.tex}\n\n"

            "\\begin{center}\n"
            "\\begin{tabular}{|r|rrr|}\n"

                "\\hline \n"
                "\\  & Mean & St. Dev. & Count \\\\ \n"
                "\\hline \n";

                for(int i = 0; i < _Data->size(); i++)
                    _file << _Data->strategyName(i) << " & " <<
                             trunc(_Data->_MovingSDStat(DataAnalyser::Mean, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                             trunc(_Data->_MovingSDStat(DataAnalyser::SD, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                             _Data->_MovingSDStat(DataAnalyser::Positive, i)  << " \\\\ \n ";

       _file << "\\hline \n"
            "\\end{tabular}\n"
            "\\end{center}\n"

        "\\section{Drawdown}\n"
             "\\input{../gen/graph/drawdown_ret.tex}\n"

        "\\section{Density}\n"
             "\\input{../gen/graph/distri_ret.tex}\n\n"

        "\\begin{center}\n"
        "\\begin{tabular}{rr}\n"

             "\\input{../gen/graph/loss_distri_ret.tex} & \\input{../gen/graph/gain_distri_ret.tex} \\\\ \n"


             "\\begin{tabular}{|r|rrr|}\n"

                "\\hline \n"
                "\\  & Mean & St. Dev. & Count (\\%) \\\\ \n"
                "\\hline \n";

                for(int i = 0; i < _Data->size(); i++)
                    _file << _Data->strategyName(i) << " & " <<
                             trunc(_Data->_StatisticPoint(DataAnalyser::MeanNegative, i) * 100.0 * 250.0, 2)  << " & " <<
                             trunc(_Data->_StatisticPoint(DataAnalyser::SDNegative, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                             trunc(double(_Data->_StatisticPoint(DataAnalyser::Negative, i) * 100.0) / n, 2)  << " \\\\ \n ";

       _file << "\\hline \n"
             "\\end{tabular}\n"

             " & \n"

             "\\begin{tabular}{|r|rrr|}\n"

                "\\hline \n"
                "\\  & Mean & St. Dev. & Count (\\%) \\\\ \n"
                "\\hline \n";

                   for(int i = 0; i < _Data->size(); i++)
                       _file << _Data->strategyName(i) << " & " <<
                                trunc(_Data->_StatisticPoint(DataAnalyser::MeanPositive, i) * 100.0 * 250.0, 2)  << " & " <<
                                trunc(_Data->_StatisticPoint(DataAnalyser::SDPositive, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                                trunc(double(_Data->_StatisticPoint(DataAnalyser::Positive, i) * 100.0) / n, 2)  << " \\\\ \n ";

       _file << "\\hline \n"
             "\\end{tabular}\n"


        "\\end{tabular}\n\n"
        "\\end{center}\n";
}

void TEXReport::strategies()
{
    _file <<
    "\\chapter{Strategies}\n";

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

}


void TEXReport::data()
{
    int m = _Data->obs();

    _file <<
    "\\chapter{Data}\n"
        // =================================
        "\\section{Portfolio Values}\n";

        for (int i = 0; i < _Data->size(); i++)
            _file << "\\subsection{"<< _Data->strategyName(i) <<"}\n"
                        "\\input{../gen/graph/"<< _Data->strategyName(i) <<"_values.tex}\n";

        // =================================
        _file <<"\\section{Holdings}\n"
                "Holdings'' percentage variation ";

        for (int i = 0; i < _Data->size(); i++)
            _file << "\\subsection{"<< _Data->strategyName(i) <<"}\n"
                        "\\input{../gen/graph/"<< _Data->strategyName(i) <<"_holding_evol.tex}\n";

        // =================================
        _file <<"\\section{Transaction Order}\n"
              "Statistics about the number of Asset's unit bought/sold. The first observation is skipped"
         ;

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
                                  trunc(_Data->_HoldStat[k](DataAnalyser::Mean, i), 4)         << " & " <<
                                  trunc(_Data->_HoldStat[k](DataAnalyser::MeanPositive, i), 2) << " & " <<
                                  trunc(_Data->_HoldStat[k](DataAnalyser::MeanNegative, i), 2) << " & " <<
                                  trunc(_Data->_HoldStat[k](DataAnalyser::SD, i), 2)           << " & " <<
                                  trunc(_Data->_HoldStat[k](DataAnalyser::Positive, i) * 100.0/ m, 2) << " & " <<
                                  trunc(_Data->_HoldStat[k](DataAnalyser::Negative, i) * 100.0/ m, 2) << " \\\\ \n";

                     _file << "\\hline\n"
                     "\\end{tabular}\n"
                     "\\end{center}\n";
        }

        // =================================
        _file <<"\\section{Target Weight}\n";

        for (int i = 0; i < _Data->size(); i++)
            _file << "\\subsection{"<< _Data->strategyName(i) <<"}\n"
                        "\\input{../gen/graph/"<< _Data->strategyName(i) <<"_weight_target.tex}\n";
}
