#ifndef STRAT3_DATAMANAGER_BUFFER_HEADER
#define STRAT3_DATAMANAGER_BUFFER_HEADER

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "../enum.h"


class CSVReader
{
public:
    typedef std::size_t size_type;

    enum Token
    {
        tok_newline = -1,
        tok_value = -2,
        tok_eof = -3,
    };

    CSVReader(const std::string& file_name, const std::string sep = ","):
        _separator(sep)
    {
        _file = fopen(file_name.c_str(), "r");

        if (_file == 0)
            throw std::runtime_error("Requested File does not exist");
    }

    char nextc()   {

        static char c = ' ';

        if (c != EOF)
            c = getc(_file);
        else
            return EOF;

        return c;
    }

    void skip_row()
    {
        int v = get_token();
        while(v != tok_newline && v != tok_eof){
            v = get_token();
        }
    }

    template<typename T> T get_eigen3(bool header =true)
    {
        std::vector<double> v = get_vector(header);
        return Eigen::Map<T>(&v[0], _row, _max_col + 1);
    }

    std::vector<double> get_vector(bool header = true)
    {
        if (header)
            skip_row();

        std::vector<double> vec;

        int v = get_token();

        while(true)
        {
            if (v == tok_eof)
                return vec;

            if (v == tok_value)
                vec.push_back(strtod(_value.c_str(), 0));

            v = get_token();
        }

        return vec;
    }

    int get_token()
    {
        static char c = ' ';

        if (c == EOF)
            return tok_eof;

        if (c == '\n'){
            _row++;
            _max_col = _max_col > _col ? _max_col : _col; // std::max(_max_col, _col);
            _col = 0;
            c = nextc();
            return tok_newline;
        }

        while(isspace(c) && c != '\n')
            c = nextc();

        _value = "";
        while(!isspace(c) && c != separator()[0])
        {
            _value += c;
            c = nextc();
        }

        if (c == separator()[0])
            _col++;

        if (c != '\n')
            c = nextc();

        return tok_value;
    }

    const std::string& separator() const {   return _separator;  }

public:

    CSVReader(const CSVReader&) = delete;
    CSVReader& operator= (const CSVReader&) = delete;

private:
    size_type _row{0};
    size_type _col{0};
    size_type _max_col{0};

    FILE*       _file{0};
    std::string _separator;
    std::string _value;
};



//std::vector<double> read_csv(std::string name,
//                             int& row, int& col_, char sep = ',', int skip_col=0, bool header=true)
//{
//    FILE* file = fopen(name.c_str(), "r");

//    if (file == 0)
//        return std::vector<double>();

//    char c = getc(file);

//    if (header)
//        while(c != '\n')
//            c = getc(file);

//    std::vector<double> vec;
//    std::string val;

//    col_ = 0;
//    int col = 0;
//    row = 0;

//    while(c != EOF)
//    {
//        if (c == '\n')
//        {
//            vec.push_back(strtod(val.c_str(), 0));
//            col_  = std::max(col, col_);
//            row++;      col = 0;    val = "";
//        }
//        else if (c == sep)
//        {
//            if (col  + 1 > skip_col)
//                vec.push_back(strtod(val.c_str(), 0));

//            val = "";   col++;
//        }

//        val += c;
//    }

//    return vec; //Eigen::Map<T>(&vec[0], row, col_max);
//}


//class CSVBuffer
//{
//public:
//    typedef std::string string;
//    typedef std::vector<string> Header;

//    CSVBuffer(const char* str, char sep = ','):
//        _sep(sep), _line(1), _col(1), _cursor(-1), _maxline(0), _maxcol(1)
//    {
//        char c = ' ';

//        FILE* file = fopen(str, "r");

//        _buffer = string("");

//        c = getc(file);
//        bool first_new = true;

//        while(c != EOF)
//        {
//            if (c == '\n')
//            {
//                first_new = false;
//                _maxline++;
//            }
//            else if (c == sep && first_new)
//                _maxcol++;

//            _buffer += c;

//            c = getc(file);
//        }

//        _buffer += EOF;

//        fclose(file);
//    }

//    ~CSVBuffer()
//    {}

//    const char& operator[] (int idx) const
//    {
//        return _buffer[idx];
//    }

//    const char& nextc()
//    {
//        if (_buffer[_cursor + 1] == '\n')
//        {
//            _line++;
//            _col = 1;
//        }
//        else if (_buffer[_cursor + 1] == _sep)
//            _col++;

//        if (_cursor == _buffer.size() - 1)
//           return _buffer[_cursor];

//        _cursor++;
//        return _buffer[_cursor];
//    }

//    const char& prevc()
//    {
//        if (_buffer[_cursor - 1] = '\n')
//        {
//            _line--;
//            _col = _maxcol;
//        }
//        else if (_buffer[_cursor - 1] = _sep)
//            _col--;

//        _cursor--;
//        return _buffer[_cursor];
//    }

//    std::vector<std::string> read_col(int idx)
//    {
//        std::vector<std::string> ret(_maxline);

//        for (int j = 0; j < _maxline; j++)
//        {
//            for (int i = 0; i < idx; i++)
//                next_item();

//            ret[j] = next_item(); //function(next_item());
//            //ret.push_back(function(next_item()));

//            // Go to the end of line
//            while(current_pos() != '\n' && current_pos() != EOF)
//                nextc();
//        }

//        return ret;
//    }

//    Matrix read_dates(int header)
//    {
//        restart();

//        if (header)
//            skip_line();

//        Matrix date(_maxline - header, 3);

//        for(int i = 0; i < _maxline - header; ++i)
//        {
//            for (int j = 0; j < 3; ++j)
//                date(i, j) = strtod(next_item('-').c_str(), 0);

//            skip_line();
//        }

//        return date;
//    }

//    void skip_line()
//    {
//        while(current_pos() != '\n' && current_pos() != EOF)
//            nextc();
//    }


//    Matrix read_data(int skip, int header)
//    {
//        restart();

//        if (header)
//            // Skip first lile
//            skip_line();

//        Matrix A(_maxline - header, _maxcol - skip);

//        for(int i = 0; i < _maxline - header; ++i)
//        {
//            for(int k = 0; k < skip; ++k)
//                next_item();

//            for(int j = 0; j < _maxcol; ++j)
//            {
//                if (current_pos() == '\n' || current_pos() == EOF)
//                    break;

//                A(i, j) = strtod(next_item().c_str(), 0);
//            }
//        }

//        return A;
//    }

//    template<typename T>
//    std::vector<T> read_line(T (*function)(string), int skip_col = 0)
//    {
//        std::vector<T> ret(_maxcol - skip_col);


//        for (int i = 0; i < skip_col; i++)
//        {
//            next_item();

//            if (current_pos() == '\n')
//                return ret;
//        }

//        for(int i = 0 ; i < _maxcol - skip_col; i++)
//        {
//            ret[i] = function(next_item());

//            if (current_pos() != '\n' && current_pos() != EOF)
//                break;
//        }

//        return ret;
//    }


//    Header read_header(int skip)
//    {
//        restart();
//        Header ret(_maxcol - skip);

//        for (int i = 0; i < skip; ++i)
//            next_item();

//        for(int i = 0; i < _maxcol - skip; ++i)
//        {
//            if (current_pos() == '\n' && current_pos() == EOF)
//                break;

//            ret[i] = next_item();
//        }

//        return ret;
//    }

//    const char& current_pos()
//    {
//        if (_cursor == -1)
//            return _buffer[0];
//        return _buffer[_cursor];
//    }

//    string next_item()
//    {
//        return next_item(_sep);
//    }

//    string next_item(const char& sep)
//    {
//        char c;
//        string item = "";

//        while(true)
//        {
//            c = nextc();

//            if (c == '\n' || c == sep || c == EOF)
//                return item;
//            else
//                item += c;
//        }
//    }

//    void restart()
//    {
//        _cursor = -1;
//        _line = 1;
//        _col = 1;
//    }

//    int& cursor()           {   return _cursor; }
//    const int size() const  {   return _buffer.size();  }

//    const int&    line   () const {   return _line;     }
//    const int&    col    () const {   return _col;      }
//    const int&    maxline() const {   return _maxline;  }
//    const int&    maxcol () const {   return _maxcol;   }

//    const string& buffer()  {   return _buffer; }

//protected:

//    char   _sep;
//    int    _line;
//    int    _col;
//    int    _cursor;
//    int    _maxline;
//    int    _maxcol;
//    string _buffer;
//};

#endif
