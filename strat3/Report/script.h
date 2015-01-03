#ifndef STRAT3_REPORT_SCRIPT_HEADER
#define STRAT3_REPORT_SCRIPT_HEADER

#include <vector>
#include <string>

// generate gnuplot code
void generate_gp_script(const std::vector<std::string>& strat,
                        const std::vector<std::string>& sec,
                        bool tex = false,
                        bool date = false);

#endif






