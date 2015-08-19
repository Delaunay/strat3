#include "ConfigReader.h"
#include <iostream>

using strat3::read_configuration;
using strat3::Configuration;

int main()
{

    std::unique_ptr<Configuration> cg = read_configuration("../../data/config.s3");

    std::cout << (*cg) << "\n";

    return 0;
}
