#ifndef STRAT3_REPORT_SCRIPT_HEADER
#define STRAT3_REPORT_SCRIPT_HEADER

#include <vector>
#include <string>
#include <cstdio>


extern std::string gp_file;
extern std::string output_folder;
extern std::string data_folder;

extern std::string return_distribution;
extern std::string daily_return;
extern std::string drawdown;
extern std::string holding_period_return;
extern std::string volatility;

extern std::string holding_evolution;
extern std::string weight;
extern std::string holding_variation;
extern std::string values;
extern std::string separator;


// generate gnuplot code
void generate_gp_script(const std::vector<std::string>& strat,
                        const std::vector<std::string>& sec,
                        bool tex = false,
                        bool date = false);

// format a double to a nice string which look nice on a document
std::string format_double(double x, int pre = 4, int nb = 8);

#endif






