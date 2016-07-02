#include "script.h"

#include <cstdlib>
#include <fstream>


#define STRAT_LEGEND(legend)    if (legend) \
                                    file << "title \"" << strat[i] << "\""; \
                                else \
                                    file << "notitle"; \
                                if (i < len_strat - 1) \
                                    file << ", '' "; \
                                else \
                                    file << "\n"; \

using namespace std;


string gp_file               = "../../gnuplot/gplot_script.gp";
string output_folder         = "../../gen/graph/";
string data_folder           = "../";               // "../gen/data/";

string return_distribution   = "ret_distri.txt";    // "distri_ret.dat";
string daily_return          = "returns.txt";       // "daily_ret.dat";
string drawdown              = "drawdown.txt";      // "drawdown_ret.dat";
string holding_period_return = "hpr.txt";           // "hpr_ret.dat";
string volatility            = "mov_stdev.txt";     // "volatility_ret.dat";

string holding_evolution     = "_ps.txt";
string weight                = "_tw.txt";
string holding_variation     = "_toNormalized.txt";
string values                = "_pv.txt";
string separator             = " ";


void generate_gp_script(const std::vector<std::string>& strat,
                        const std::vector<std::string>& sec,
                        bool tex,
                        bool date)
{

    int len_strat = strat.size();
    int len_sec = sec.size();

    bool legend = true;
//    bool legend2 = true;

    std::fstream file;
    file.open(gp_file.c_str(), std::ios::out);

    std::string term_l("svg size 1200,300 dynamic mouse");
    std::string term_s("svg size 600,300 dynamic mouse");
    std::string ext("svg");

    bool color = true;

    if (tex)
    {
        if (color)
        {
        //cairolatex eps size 8 cm,6.8 cm
            term_l = "cairolatex eps size 16.59 cm,6.8 cm";
            term_s = "cairolatex eps size 8.5 cm,6.8 cm";
            ext = "tex";
        }
        else
        {
            term_l = "epslatex size 16.59 cm,6.8 cm";
            term_s = "epslatex size 8.5 cm,6.8 cm";
            ext = "tex";
        }
    }

    // main config
     file <<
    "set terminal " << term_l                      << std::endl <<
    "set datafile separator '" << separator << "'" << std::endl <<
    "set style data lines"                         << std::endl <<
    "percent(x) = x * 100.0"                       << std::endl <<
    "set grid"                                     << std::endl <<
    "# set format y \"%.2f\""                      << std::endl <<
    "set xtics \n";

    // Distribution
    file <<
    "# ======================\n"
    "# Distribution          \n"
    "# ======================\n\n";

    if (len_strat > 10)
        file << "set key off\n unset key\n";
    else
        file << "set key on\n" "set key top\n";

    file <<
    "# set format x \"%.2f\"\n"
    "set output \"" << output_folder << "distri_ret."<< ext <<"\"\n"

    "plot \"" << data_folder << return_distribution << "\" ";


    for (int i = 0; i < len_strat; i++)
    {
        file << "using (percent($1)):(percent($" << i + 2 + 1 << ")) ";

        STRAT_LEGEND(legend);
    }

//    // Half
//    // Loss
//    file <<
//    "# ======================\n"
//    "# Loss                  \n"
//    "# ======================\n\n"


//    "set terminal " << term_s << " \n";

//    if (len_strat > 10)
//        file << "set key off\n unset key\n";
//    else
//        file << "set key on\n set key left\n";

//    file <<
//    "set output \"../gen/graph/loss_distri_ret."<< ext <<"\"\n"

//    "plot \"../gen/data/loss_distri_ret.dat\" ";

//    for (int i = 0; i < len_strat; i++)
//    {
//        file << "using (percent($"<< 2 * i + 1 <<")):(percent($" << 2 * i + 2 << ")) ";

//        STRAT_LEGEND(legend);
//    }

//    // Gain
//    file <<
//    "# ======================\n"
//    "# Gain                  \n"
//    "# ======================\n\n";

//    if (len_strat > 10)
//        file << "set key off\n unset key\n";
//    else
//        file << "set key on\n set key right\n";

//    file <<
//    "set output \"../gen/graph/gain_distri_ret."<< ext <<"\"\n"

//    "plot \"../gen/data/gain_distri_ret.dat\" ";

//    for (int i = 0; i < len_strat; i++)
//    {
//        file << "using (percent($"<< 2 * i + 1 <<")):(percent($" << 2 * i + 2 << "))";

//        STRAT_LEGEND(legend);
//    }

    //==================================================================================================================
    //              DATE START HERE
    //==================================================================================================================

    // date option HERE
    int offset = 2;
    if (date)
    {
        file <<
            "set xdata time\n"
            "set timefmt \"%Y %m %d\"\n"
            "set format x \"%Y\"\n";

        offset = 4;
    }


    // Holding Evolution
    file <<
    "# ======================\n"
    "# Holding Evolution     \n"
    "# ======================\n\n"

    "set terminal "<< term_l << " \n"
    "set key on\n set key right\n";

    if (len_sec > 10)
        file << "set key off\n unset key\n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \"" << output_folder << strat[i] << "_holding_evol."<< ext <<"\" \n"
        "plot \"" << data_folder << strat[i] << holding_evolution << "\" ";

        for(int j = 0; j < len_sec; j++)
        {
            if (j < len_sec - 1)
                file << "using 1:" << j + offset << " title \"" << sec[j] << "\", '' ";
            else
                file << "using 1:" << j + offset << " title \"" << sec[j] << "\" \n";
        }
    }

    // Weight Target
    file <<
    "# ======================\n"
    "# Weight Target         \n"
    "# ======================\n\n"

    "set key on\n set key right\n";

    if (len_sec > 10)
        file << "set key off\n unset key\n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \""<< output_folder << strat[i] << "_weight_target."<< ext <<"\" \n"
        "plot \""<< data_folder << strat[i] << weight << "\" ";

        for(int j = 0; j < len_sec; j++)
        {
            if (j < len_sec - 1)
                file << "using 1:(percent($" << j + offset << ")) title \"" << sec[j] << "\", '' ";
            else
                file << "using 1:(percent($" << j + offset << ")) title \"" << sec[j] << "\" \n";
        }
    }

    // Holding var
    file <<
    "# ======================\n"
    "# Holding var           \n"
    "# ======================\n\n"

    "set key on\n set key right\n";

    if (len_sec > 10)
        file << "set key off\n unset key\n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \"" << output_folder << strat[i] << "_holding_var."<< ext <<"\" \n"
        "plot \"" << data_folder << strat[i] << holding_variation << "\" ";

        for(int j = 0; j < len_sec; j++)
        {
            if (j < len_sec - 1)
                file << "using 1:" << j + offset << " title \"" << sec[j] << "\", '' ";
            else
                file << "using 1:" << j + offset << " title \"" << sec[j] << "\" \n";
        }
    }


    // Values
    file <<
    "# ======================\n"
    "# Portfolio Values      \n"
    "# ======================\n\n"

    "set key on\n set key left \n";

//    if (len_strat > 10)
//        file << "set key off\n unset key\n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \""<< output_folder << strat[i] << "_values."<< ext <<"\" \n"
        "plot \""<< data_folder << strat[i] << values << "\" using 1:"
             << offset     << " title \"Liabilities\", '' using 1:"
             << offset + 1 << " title \"Equity\", '' using 1:"
             << offset + 2 << " title \"Asset\" \n";
    }

    // Periodict Ret
    file <<
    "\n\n"
    "# ======================\n"
    "# Periodict Ret \n"
    "# ======================\n\n"
    "set key right\n"
    "set key on\n set key bottom\n";

    if (len_strat > 10)
        file << "set key off\n unset key\n";

    file <<

    "set output \"" << output_folder << "daily_ret."<< ext <<"\"" << std::endl <<
    "plot \"" << data_folder << daily_return << "\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\" \n";
    }

    //Holding period Return
    file <<
    "\n\n"
    "# ======================\n"
    "# Holding Period Return \n"
    "# ======================\n\n"

    "set key on\n set key bottom\n";

    if (len_strat > 10)
        file << "set key off\n unset key\n";

    file <<
    "set output \"" << output_folder << "holding_ret."<< ext <<"\" \n"
    "plot \""<< data_folder << holding_period_return << "\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\" \n";
    }

    // Drawdown
    file <<
    "# ======================\n"
    "# Drawdown              \n"
    "# ======================\n\n"

    "set key on\n set key bottom\n";

    if (len_strat > 10)
        file << "set key off\n unset key\n";

    file <<
    "set output \"" << output_folder << "drawdown_ret."<< ext <<"\" \n"
    "plot \""<< data_folder << drawdown << "\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\" \n";
    }

    // Volatility
    file <<
    "# ======================\n"
    "# Volatility            \n"
    "# ======================\n\n"

    "set key on\n set key top\n";

    if (len_strat > 10)
        file << "set key off\n unset key\n";

    file <<
    "set output \"" << output_folder << "volatility_ret."<< ext <<"\" \n"
    "plot \""<< data_folder << volatility << "\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\" \n";
    }

    file.close();

    // generate the graphs
    int a = system(string("gnuplot " + gp_file).c_str());

    // TODO add a log
    if (a == - 1)
        fprintf(stderr, "error starting gnuplot, is gnuplot or gnuplot.exe in your path?\n");
}

std::string format_double(double x, int pre, int nb)
{
    if (x == 0)
    {
        std::string s("0.");

        for(int i = 0; i < pre; ++i)
            s += "0";

        return s;
    }


    // %[flags][width][.precision][length]
    //std::string a("                ");
    //  printf("%s \n", c);

    std::string format = "% #" + std::to_string(nb) + "." + std::to_string(pre) + "f";

    // you should use c string because if you use C++ string
    // sprintf add \0 which break everything in a file
    char c[] = "                ";    // &a.at(0)

    sprintf(c, format.c_str(), x);

    return std::string(c);;
}
