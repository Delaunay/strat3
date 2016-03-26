#ifndef STRAT3_CML_SETTINGS_HEADER
#define STRAT3_CML_SETTINGS_HEADER

#include <string>
#include <iostream>

#include <boost/property_tree/ptree.hpp>

namespace strat3{

typedef boost::property_tree::ptree Settings;

Settings load_settings(const std::string& file_name);

void save_settings(const std::string& file_name, const Settings& s);

std::ostream& operator << (std::ostream& s, const Settings& set);

}

#endif
