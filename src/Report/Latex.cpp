#include "Latex.h"

namespace strat3{
void Latex::head(std::string title)
{
    os <<
    "\\documentclass[11pt, openany]{book}\n"
    "\\usepackage[top=2.5cm, bottom=2.5cm, left=2.5cm, right=2.5cm]{geometry}\n"
    //"\\usepackage[colorlinks=true,linkcolor=blue]{hyperref}\n"
    "\\usepackage{amsmath}\n"
    "\\usepackage{amssymb}\n"
    "\\usepackage{graphicx}\n"
    "\\usepackage{color}\n"
    "\\usepackage{multicol}\n"
    "\\usepackage[colorlinks=true,linkcolor=blue,\n"
                 "bookmarks,\n"
                 "bookmarksnumbered=true,\n"
                 "pdftitle={"<< title <<"},\n"
                 "pdfauthor={Pierre Delaunay},\n"
                 "pdfsubject={Strat3},\n"
               // "pdfcreator={},\n"
               // "pdfkeywords={...}\n"
               "]{hyperref}\n"

    //"\\usepackage{lmodern}\n"
    "\\definecolor{linkcolour}{rgb}{0,0.2,0.6}\n"
    "%\\usepackage{multirow}\n\n"
    "\\usepackage{fancyhdr}\n"
    //"\\defaultfontfeatures{Mapping=tex-text}n"

    //"\\usepackage{xunicode,xltxtra,url,parskip}\n"
    "\\usepackage{draftwatermark}\n"
    "\\SetWatermarkText{PRE ALPHA}\n"
    "\\SetWatermarkScale{5}\n"
    //\SetWatermarkColor[rgb]{1,0,0}
    //\SetWatermarkColor[gray]{0.5}

    "\\title{"<< title <<"}\n"

    "\\author{Strat 3 - Version: 0.0.0}\n\n"
    "\\date{\\today}\n"
    "\\pagestyle{fancy}\n"

    //"\\cfoot{Title \\copyright Pierre Delaunay}\n"
    //"\\lfoot{Strat3}\n"
    //\\copyright Pierre Delaunay
    //"\\cfoot{\\thepage}\n"
    //"\\rfoot{\\thepage}\n"

    "\\begin{document}\n\n"

    "\\maketitle\n"
    "\\tableofcontents\n"
    ;
}

std::ostream& Latex::add_figure(Key input, Key caption, Key label)
{
    os <<
//    "\\begin{figure}[htbp]\n"
//        "\\begin{center}\n"
            "\\input{"<< input <<"}\n"
//        "\\end{center}\n"
    ;

//    if (!caption.empty())
//        os << "\\caption{"<< caption <<"}\n";

//    if (!caption.empty())
//        os << "\\label{"<< label <<"}\n";

//    os << "\\end{figure}\n";

    return os;
}


void Latex::overview           ()
{
    int n_strat = da.strategy_names().size();

    os <<   "\\chapter{Overview}\n"
                "\\section{Holding Period Return}\n";

           add_figure(output_folder + "holding_ret.tex", "Holding Period Return");

    os <<   "\\section{Statistics}\n"

            "\\begin{center}\n"
                "\\begin{tabular}{|r|rrrrrrr|}\n";

    os <<       "\\hline \n"
                    "Strategies & Mean & St. Dev. & Sharp & Skew & Kurtosis & Positive & Negative \\\\ \n"
                "\\hline \n";

    for (int i = 0; i < n_strat; i++)
    {
        os  << da.strategy_names()[i]                                   << " & "
            << format_double(da.means()(0, i) * 250.0 * 100.0, 2)       << " & "
            << format_double(da.stdev()(0, i) * sqrt(250.0) * 100.0, 2) << " & "
            << format_double(da.means()(0, i) * 250.0 / (da.stdev()(0, i) * sqrt(250.0)), 4)     << " & "
            << format_double(da.skewness()(0, i), 4)                    << " & "
            << format_double(da.kurtosis()(0, i), 2)                    << " & "
            << da.pos_count()(0, i)                                     << " & "
            << da.neg_count()(0, i)                                     << " \\\\ \n "
        ;
    }

    os <<       "\\hline \n";
    os <<       "\\end{tabular} \n"
            "\\end{center}\n";
}


void Latex::disclaimer         ()
{
    os <<
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
         "POSSIBILITY OF SUCH DAMAGE.\n"

    "\\section{Report Disclaimer}\n"

        "This report was generated automaticly by Strat3 (Version: " << 0 << "." << 0 << "." << 0 <<")"
        "It is the users' responsibility to verify any information that are provided "
        "by this report. This report is provided \"AS IS\" "
        "AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE "
        "IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE "
        "ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE "
        "LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR "
        "CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF "
        "SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS "
        "INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN "
        "CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) "
        "ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE "
        "POSSIBILITY OF SUCH DAMAGE.\n"
    ;
}

void Latex::risk()
{
    os <<
    "\\chapter{Risk}\n"
        "\\section{Periodict Return}\n";

            add_figure(output_folder + "daily_ret.tex", "Periodic Return") <<

        "\\section{Volatility Evolution}\n";

            add_figure(output_folder + "volatility_ret.tex", "Volatility") <<

        "\n"

        "\\begin{center}\n"
        "\\begin{tabular}{|r|rrr|}\n"

            "\\hline \n"
            "\\  & Mean & St. Dev. & Count \\\\ \n"
            "\\hline \n";

            for(int i = 0; i < da.strategy_names().size(); i++)
                os << da.strategy_names()[i]  << " & " <<
                      format_double(da.vol_mean()(0, i)  * 100.0 * sqrt(250.0), 2)  << " & " <<
                      format_double(da.vol_stdev()(0, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                      da.count()(0, i)  << " \\\\ \n ";

    os <<   "\\hline \n"
        "\\end{tabular}\n"
        "\\end{center}\n"

    "\\section{Drawdown}\n";
         add_figure(output_folder + "drawdown_ret.tex", "Drawdown") <<

    "\\section{Density}\n";
         add_figure(output_folder + "distri_ret.tex", "Return Distribution") <<

    "\\begin{center}\n"
    "\\begin{tabular}{rr}\n"

//         "\\input{" << output_folder << "loss_distri_ret.tex} & \\input{"
//                    << output_folder << "gain_distri_ret.tex} \\\\ \n"

         "\\begin{tabular}{|r|rrr|}\n"

            "\\hline \n"
            "\\  & Mean & St. Dev. & Count (\\%) \\\\ \n"
            "\\hline \n";

            for(int i = 0; i < da.strategy_names().size(); i++)
                os << da.strategy_names()[i] << " & " <<
                      format_double(da.neg_means()(0, i) * 100.0 * 250.0, 2)  << " & " <<
                      format_double(da.neg_stdev()(0, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                      format_double(double(da.neg_count()(0, i) * 100.0) / da.count()(0, i), 2)  << " \\\\ \n ";

   os << "\\hline \n"
         "\\end{tabular}\n"

         " & \n"

         "\\begin{tabular}{|r|rrr|}\n"

            "\\hline \n"
            "\\  & Mean & St. Dev. & Count (\\%) \\\\ \n"
            "\\hline \n";

           for(int i = 0; i < da.strategy_names().size(); i++)
               os << da.strategy_names()[i] << " & " <<
                     format_double(da.pos_means()(0, i) * 100.0 * 250.0, 2)  << " & " <<
                     format_double(da.pos_stdev()(0, i) * 100.0 * sqrt(250.0), 2)  << " & " <<
                     format_double(double(da.pos_count()(0, i) * 100.0) / da.count()(0, i), 2)  << " \\\\ \n ";

   os << "\\hline \n"
         "\\end{tabular}\n"

    "\\end{tabular}\n\n"
    "\\end{center}\n";
}

void Latex::strategies()
{
    os <<   "\\chapter{Strategies}\n"
            "\\begin{multicols}{2}\n";

    for(int i = 0, n = da.strategy_names().size(); i < n; i++)
    {
        os <<
        "\\section{" << da.strategy_names()[i] <<"}\n"
            "\\subsection{Description} \n" <<
                bt.get_strategy(i)->description << "\n"
            "\\subsection{Configuration}\n"

                 "\\begin{tabular}{|r|r|}\n"
                 "\\hline \n"
                    "Frequency & "  << bt.get_strategy(i)->frequency << "\\\\ \n"
                    //"Version  & "   << bt.get_strategy(i)->version << "\\\\ \n"
                    "Rebalanced & " << get_bool_as_string(bt.get_strategy(i)->rebalanced) << "\\\\ \n"
                 "\\hline \n"
                 "\\end{tabular}\n"
                 ;
    }

    os << "\\end{multicols}";
}

void Latex::data()
{
    os <<"\\chapter{Data}\n"
            // =================================
            "\\section{Portfolio Values}\n";

        for (int i = 0; i < da.strategy_names().size(); i++)
        {
            os << "\\subsection{"<< da.strategy_names()[i] <<"}\n";

            add_figure(output_folder + da.strategy_names()[i] + "_values.tex",  da.strategy_names()[i] + " Assets");
        }

        // =================================
        os <<"\\section{Holdings}\n";

        for (int i = 0; i < da.strategy_names().size(); i++)
        {
            os << "\\subsection{"<<  da.strategy_names()[i] <<"}\n";

            add_figure(output_folder +  da.strategy_names()[i] + "_holding_var.tex",  da.strategy_names()[i] + " Holdings percentage variation");
        }                                                       // _holding_var.tex
                                                                // _holding_evol.tex

        // =================================
        os <<"\\section{Transaction Order}\n"
              "Statistics about the number of Asset's unit bought/sold. The first observation is skipped";

        for (int k = 0; k <  da.strategy_names().size(); k++)
        {
            os << "\\subsection{"<<  da.strategy_names()[k] <<"}\n"
                  "\\begin{center}\n";

            int j = 0;
            for(int i = 0, n = da.security_names().size(); i < n; i++)
            {
                 if (j == 0)
                 {
                     os << "\\begin{tabular}{|r|rrrrrr|}\n"
                              "\\hline\n"
                              "\\ & Mean & Mean (Bought) & Mean (Sold) & St. Dev. & \\% Buy & \\% Sell \\\\ \n"
                              "\\hline\n";
                 }

                 os <<  da.security_names()[i]                    << " & " <<
                        format_double(da.to_mean(k)    (0, i), 4) << " & " <<
                        format_double(da.to_pos_mean(k)(0, i), 2) << " & " <<
                        format_double(da.to_neg_mean(k)(0, i), 2) << " & " <<
                        format_double(da.to_stdev(k)   (0, i), 2) << " & " <<
                        format_double(da.to_pos_count(k)(0, i) * 100.0/ da.to_count(k)(0, i), 2) << " & " <<
                        format_double(da.to_neg_count(k)(0, i) * 100.0/ da.to_count(k)(0, i), 2) << " \\\\ \n";

                 j++;

                 if (j == 40)
                 {
                     os << "\\hline\n"
                     "\\end{tabular}\n \\newpage";
                     j = 0;
                 }
             }

            os << "\\hline\n"
            "\\end{tabular}\n"
            "\\end{center}\n";
        }

        // =================================
        os <<"\\section{Target Weight}\n";

        for (int i = 0; i < da.strategy_names().size(); i++)
        {
            os << "\\subsection{"<< da.strategy_names()[i] <<"}\n";
                     add_figure(output_folder + da.strategy_names()[i] + "_weight_target.tex", da.strategy_names()[i] + " Target Weight");
        }
}

}
