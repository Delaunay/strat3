#ifndef STRAT3_REPORT_SCRIPT_HEADER
#define STRAT3_REPORT_SCRIPT_HEADER

#include <vector>
#include <string>
#include <cstdio>

// generate gnuplot code
void generate_gp_script(const std::vector<std::string>& strat,
                        const std::vector<std::string>& sec,
                        bool tex = false,
                        bool date = false);

// format a double to a nice string which look nice on a document
std::string format_double(double x, int pre = 4, int nb = 8);

#endif






