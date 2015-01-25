#include "script.h"

#include <cstdlib>
#include <fstream>

void generate_gp_script(const std::vector<std::string>& strat,
                        const std::vector<std::string>& sec,
                        bool tex,
                        bool date)
{
    int len_strat = strat.size();
    int len_sec = sec.size();

    std::fstream file;

    file.open("../gnuplot/gplot_script.gp", std::ios::out);

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
    "set datafile separator ','"                   << std::endl <<
    "set style data lines"                         << std::endl <<
    "percent(x) = x * 100.0"                       << std::endl <<
    "set grid"                                     << std::endl <<
    "# set format y \"%.2f\""                      << std::endl <<
    "set xtics \n";

    // Distribution
    file <<
    "# ======================\n"
    "# Distribution          \n"
    "# ======================\n\n"

    "set key top\n"
    "# set format x \"%.2f\"\n"
    "set output \"../gen/graph/distri_ret."<< ext <<"\"\n"

    "plot \"../gen/data/distri_ret.dat\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using (percent($1)):(percent($" << i + 2 << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using (percent($1)):(percent($" << i + 2 << ")) title \"" << strat[i] << "\" \n";
    }

    // Half
    // Loss
    file <<
    "# ======================\n"
    "# Loss                  \n"
    "# ======================\n\n"


    "set terminal " << term_s << " \n"

    "set key left\n"
    "set output \"../gen/graph/loss_distri_ret."<< ext <<"\"\n"

    "plot \"../gen/data/loss_distri_ret.dat\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using (percent($"<< 2 * i + 1 <<")):(percent($" << 2 * i + 2 << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using (percent($"<< 2 * i + 1 <<")):(percent($" << 2 * i + 2 << ")) title \"" << strat[i] << "\" \n";
    }

    // Gain
    file <<
    "# ======================\n"
    "# Gain                  \n"
    "# ======================\n\n"

    "set key right\n"
    "set output \"../gen/graph/gain_distri_ret."<< ext <<"\"\n"

    "plot \"../gen/data/gain_distri_ret.dat\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using (percent($"<< 2 * i + 1 <<")):(percent($" << 2 * i + 2 << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using (percent($"<< 2 * i + 1 <<")):(percent($" << 2 * i + 2 << ")) title \"" << strat[i] << "\" \n";
    }

    //==================================================================================================================
    //              DATE START HERE
    //==================================================================================================================

    // date option HERE
    int offset = 2;
    if (date)
    {
        file <<
            "set xdata time\n"
            "set timefmt \"%Y,%m,%d\"\n"
            "set format x \"%Y\"\n";

        offset = 4;
    }


    // Holding Evolution
    file <<
    "# ======================\n"
    "# Holding Evolution     \n"
    "# ======================\n\n"

    "set terminal "<< term_l << " \n"
    "set key right\n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \"../gen/graph/" << strat[i] << "_holding_evol."<< ext <<"\" \n"
        "plot \"../gen/data/"<< strat[i] << "_holding_evol.dat\" ";

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

    "set key right\n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \"../gen/graph/" << strat[i] << "_weight_target."<< ext <<"\" \n"
        "plot \"../gen/data/"<< strat[i] << "_weight_target.dat\" ";

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

    "set key right\n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \"../gen/graph/" << strat[i] << "_holding_var."<< ext <<"\" \n"
        "plot \"../gen/data/"<< strat[i] << "_holding_var.dat\" ";

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

    "set key left \n";

    for (int i = 0; i < len_strat; i++)
    {
        file <<
        "\nset output \"../gen/graph/" << strat[i] << "_values."<< ext <<"\" \n"
        "plot \"../gen/data/"<< strat[i] << "_values.dat\" using 1:"
             << offset <<" title \"Liabilities\", '' using 1:"
             << offset + 1<<" title \"Equity\", '' using 1:"
             << offset + 2<<" title \"Asset\" \n";
    }

    // Periodict Ret
    file <<
    "\n\n"
    "# ======================\n"
    "# Periodict Ret \n"
    "# ======================\n\n"
    "set key right\n"
    "set key bottom\n"

    "set output \"../gen/graph/daily_ret."<< ext <<"\"" << std::endl <<
    "plot \"../gen/data/daily_ret.dat\" ";

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


    "set output \"../gen/graph/holding_ret."<< ext <<"\" \n"
    "plot \"../gen/data/hpr_ret.dat\" ";

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

    "set key bottom\n"
    "set output \"../gen/graph/drawdown_ret."<< ext <<"\" \n"
    "plot \"../gen/data/drawdown_ret.dat\" ";

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

    "set key top\n"
    "set output \"../gen/graph/volatility_ret."<< ext <<"\" \n"
    "plot \"../gen/data/volatility_ret.dat\" ";

    for (int i = 0; i < len_strat; i++)
    {
        if (i < len_strat - 1)
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\", '' ";
        else
            file << "using 1:(percent($" << i + offset << ")) title \"" << strat[i] << "\" \n";
    }

    file.close();

    // generate the graphs
    int a = system("gnuplot ../gnuplot/gplot_script.gp");

    // TODO add a log
    if (a == - 1)
        fprintf(stderr, "error starting gnuplot, is gnuplot or gnuplot.exe in your path?\n");
}

std::string format_double(double x, int pre, int nb)
{
    // %[flags][width][.precision][length]
    std::string a("                ");
    std::string format = "% #" + std::to_string(nb) + "." + std::to_string(pre) + "f";

    sprintf(&a.at(0), format.c_str(), x);

    return a;
}
