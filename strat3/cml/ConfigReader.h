#ifndef STRAT3_CML_CONFIGREADER_HEADER
#define STRAT3_CML_CONFIGREADER_HEADER

#include <fstream>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <unordered_map>
#include <ostream>
#include <memory>

namespace strat3{

struct Configuration
{
    ~Configuration();

    void print(std::ostream& s, int i) const;

    std::unordered_map<std::string, std::string> value;
    std::unordered_map<std::string, Configuration*> options;
};

std::ostream& operator<< (std::ostream& os, const Configuration& s);

std::unique_ptr<Configuration> read_configuration(const std::string&  file_name);

}

#endif
