#include <boost/property_tree/json_parser.hpp>
#include <exception>

#include "Settings.h"

namespace strat3{

Settings load_settings(const std::string& file_name)
{
    Settings pt;
    try{
        read_json(file_name, pt);
    }
    catch (std::exception &e){
        std::cout << "Error: " << e.what() << "\n";
    }
    return pt;
}

void save_settings(const std::string& file_name, const Settings& s)
{
    try{
        write_json(file_name, s);
    }
    catch (std::exception &e){
        std::cout << "Error: " << e.what() << "\n";
    }
}

void internal_print(std::ostream& os, const Settings& pt, int k = 1)
{
    if (pt.size() == 0){
        os << pt.data() << "\n";
    }
    else{
        os << "{\n";

        for(Settings::const_iterator i = pt.begin(); i != pt.end(); ++i)
        {
            os << std::string(k * 2, ' ') << (*i).first << ": ";

            internal_print(os, (*i).second, k + 1);
        }

        os << std::string((k - 1) * 2, ' ') << "}\n";
    }
}

std::ostream& operator << (std::ostream& os, const Settings& set)
{
    internal_print(os, set);
    return os;
}

}
