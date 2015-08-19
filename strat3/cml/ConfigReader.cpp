#include "ConfigReader.h"

namespace strat3{
enum{
    tok_identifier  = -1,
    tok_newline     = -2,
    tok_def         = -3,
    tok_eof         = -4,
    tok_start       = -5,
    tok_end         = -6,
};

class Lexer
{
public:
    Lexer(const std::string&  file_name)
    {
        _file.open(file_name.c_str(), std::ios::in);
        if (!_file.is_open())
            throw std::runtime_error("FILE NOT FOUND");
    }

    int nextc()
    {
        return _file.get();
    }

    int get_token()
    {
        static char c = ' ';

        if (c == '\n'){
            c = nextc();
        }

        if (c == EOF)
            return tok_eof;

        while(c == ' ')
            c = nextc();

        if (c == ':')
        {
            c = nextc();
            return tok_def;
        }

        if (isalnum(c) || c == '"' || c == '\'')
        {
            _identifier = "";

            while(isalnum(c) || c == '@' || c == '.' || c == '/' || c == '"'
                  || c == '\'' || c == '_')
            {
                if (c != '"' && c != '\'')
                    _identifier += c;

                c = nextc();
            }

            c = nextc();
            return tok_identifier;
        }

        if (c == '{')
        {
            c = nextc();
            return tok_start;
        }

        if (c == '}')
        {
            c = nextc();
            return tok_end;
        }

        // if unknown
        c = nextc();
    }

    const std::string& identifier()  const {   return _identifier; }


private:
    std::string _identifier;
    std::fstream _file;
};

class ConfigReader
{
public:

    ConfigReader(const std::string&  file_name):
        _lexer(file_name)
    {}

    const std::string& identifier()  const {   return _lexer.identifier(); }

    std::unique_ptr<Configuration> read(bool first = true)
    {
        std::unique_ptr<Configuration> cf(new Configuration());
        std::string name = "";

        if (first)
            next_token();

        while(token() != tok_eof && (token() != tok_end || first))
        {
            if (token() == tok_identifier)
            {
                name = identifier();

                next_token();

                if(token() == tok_def)
                    next_token();

                if(token() == tok_start)
                {
                    next_token();
                    cf->options[name] = read(false).release();
                }

                else if (token() == tok_identifier)
                {
                    cf->value[name] = identifier();
                    next_token();
                }
            }
            else
                next_token();
        }

        next_token(); // eat tok_end

        return cf;
    }

    int& next_token()
    {
        _tok = _lexer.get_token();
        return _tok;
    }

    int& token()
    {
        return _tok;
    }

private:
    int _tok;
    Lexer _lexer;
};


Configuration::~Configuration()
{
    for(auto& j:options)
    {
        delete j.second;
        j.second = nullptr;
    }
}

// for some reason VC has trouble with std::ostream& << std::string
void Configuration::print(std::ostream& s, int i) const
{
    for(auto& j:value){
        s << std::string(i * 4, ' ').c_str();
        s << j.first.c_str() << ":" << j.second.c_str() << "\n";
    }

    for(auto& j:options)
    {
        s << std::string( i * 4, ' ').c_str()      << j.first.c_str() << ":{\n";
        j.second->print(s, i + 1) ;
        s << std::string( i * 4, ' ').c_str()      << "}\n";
    }
}

std::ostream& operator<< (std::ostream& os, const Configuration& s)
{
    s.print(os, 1);
    return os;
}

std::unique_ptr<Configuration> read_configuration(const std::string&  file_name)
{
    return ConfigReader(file_name).read();
}
}
