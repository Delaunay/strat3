#include "BacktestBuilder.h"
#include <iostream>

using strat3::BacktestBuilder;

// "../../data/config.s3"
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Wrong Number of arguments\n"
                     "Usage: cml_strat3 my_config_file\n";
        return -1;

    }

    BacktestBuilder(std::string(argv[1])).all();

    return 0;
}
