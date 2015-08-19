#ifndef STRAT3_LOG_TRACE_HEADER
#define STRAT3_LOG_TRACE_HEADER

#include <string>
#include <vector>
#include <iostream>

//
//  Debuging log
//
#define add_trace(msg) (Trace::instance()).add(__FILE__, __FUNCTION__, __LINE__, msg)

class Trace
{
public:

    static Trace& instance()
    {
        static Trace s;
        return s;
    }

    Trace():
        out(std::cout)
    {}

    static std::string clean_path(const std::string& s)
    {
        std::string s2;
        std::copy(s.begin() + path().size(), s.end(), std::back_inserter(s2));
        return s2;
    }

    static const std::string& path()
    {
        static const std::string s = std::string(__FILE__).substr(0, std::string(__FILE__).size() - 10);
        return s;
    }

    struct Element
    {
        Element(const std::string& file, const std::string& func, const unsigned int& line, const std::string& msg):
            msg(msg), line(line), file(file), func(func)
        {}

        std::string msg;
        unsigned int line;
        std::string file;
        std::string func;
        //std::string expr;

        void print(std::ostream& os)
        {
            os << line << "\t" << clean_path(file) << " " << func << "\t:" << msg << std::endl;
        }
    };

    void add(const std::string& file, const std::string& func, const unsigned int& line, const std::string& msg)
    {
        Element e(file, func, line, msg);

        e.print(out);

        return traceback.push_back(std::move(e));
    }

    void erase()
    {
        traceback.erase(traceback.begin(), traceback.end());
    }

    std::ostream&        out;
    std::vector<Element> traceback;

};

#endif
