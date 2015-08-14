#ifndef STRAT3_DATAMANAGER_BUFFER_HEADER
#define STRAT3_DATAMANAGER_BUFFER_HEADER

#include <string>
#include <vector>

#include "../enum.h"

class CSVBuffer
{
public:
    typedef std::string string;
    typedef std::vector<string> Header;

    CSVBuffer(const char* str, char sep = ','):
        _sep(sep), _line(1), _col(1), _cursor(-1), _maxline(0), _maxcol(1)
    {
        char c = ' ';

        FILE* file = fopen(str, "r");

        _buffer = string("");

        c = getc(file);
        bool first_new = true;

        while(c != EOF)
        {
            if (c == '\n')
            {
                first_new = false;
                _maxline++;
            }
            else if (c == sep && first_new)
                _maxcol++;

            _buffer += c;

            c = getc(file);
        }

        _buffer += EOF;

        fclose(file);
    }

    ~CSVBuffer()
    {}

    const char& operator[] (int idx) const
    {
        return _buffer[idx];
    }

    const char& nextc()
    {
        if (_buffer[_cursor + 1] == '\n')
        {
            _line++;
            _col = 1;
        }
        else if (_buffer[_cursor + 1] == _sep)
            _col++;

        if (_cursor == _buffer.size() - 1)
           return _buffer[_cursor];

        _cursor++;
        return _buffer[_cursor];
    }

    const char& prevc()
    {
        if (_buffer[_cursor - 1] = '\n')
        {
            _line--;
            _col = _maxcol;
        }
        else if (_buffer[_cursor - 1] = _sep)
            _col--;

        _cursor--;
        return _buffer[_cursor];
    }

    std::vector<std::string> read_col(int idx)
    {
        std::vector<std::string> ret(_maxline);

        for (int j = 0; j < _maxline; j++)
        {
            for (int i = 0; i < idx; i++)
                next_item();

            ret[j] = next_item(); //function(next_item());
            //ret.push_back(function(next_item()));

            // Go to the end of line
            while(current_pos() != '\n' && current_pos() != EOF)
                nextc();
        }

        return ret;
    }

    Matrix read_dates(int header)
    {
        restart();

        if (header)
            skip_line();

        Matrix date(_maxline - header, 3);

        for(int i = 0; i < _maxline - header; ++i)
        {
            for (int j = 0; j < 3; ++j)
                date(i, j) = strtod(next_item('-').c_str(), 0);

            skip_line();
        }

        return date;
    }

    void skip_line()
    {
        while(current_pos() != '\n' && current_pos() != EOF)
            nextc();
    }


    Matrix read_data(int skip, int header)
    {
        restart();

        if (header)
            // Skip first lile
            skip_line();

        Matrix A(_maxline - header, _maxcol - skip);

        for(int i = 0; i < _maxline - header; ++i)
        {
            for(int k = 0; k < skip; ++k)
                next_item();

            for(int j = 0; j < _maxcol; ++j)
            {
                if (current_pos() == '\n' || current_pos() == EOF)
                    break;

                A(i, j) = strtod(next_item().c_str(), 0);
            }
        }

        return A;
    }

    template<typename T>
    std::vector<T> read_line(T (*function)(string), int skip_col = 0)
    {
        std::vector<T> ret(_maxcol - skip_col);


        for (int i = 0; i < skip_col; i++)
        {
            next_item();

            if (current_pos() == '\n')
                return ret;
        }

        for(int i = 0 ; i < _maxcol - skip_col; i++)
        {
            ret[i] = function(next_item());

            if (current_pos() != '\n' && current_pos() != EOF)
                break;
        }

        return ret;
    }


    Header read_header(int skip)
    {
        restart();
        Header ret(_maxcol - skip);

        for (int i = 0; i < skip; ++i)
            next_item();

        for(int i = 0; i < _maxcol - skip; ++i)
        {
            if (current_pos() == '\n' && current_pos() == EOF)
                break;

            ret[i] = next_item();
        }

        return ret;
    }

    const char& current_pos()
    {
        if (_cursor == -1)
            return _buffer[0];
        return _buffer[_cursor];
    }

    string next_item()
    {
        return next_item(_sep);
    }

    string next_item(const char& sep)
    {
        char c;
        string item = "";

        while(true)
        {
            c = nextc();

            if (c == '\n' || c == sep || c == EOF)
                return item;
            else
                item += c;
        }
    }

    void restart()
    {
        _cursor = -1;
        _line = 1;
        _col = 1;
    }

    int& cursor()           {   return _cursor; }
    const int size() const  {   return _buffer.size();  }

    const int&    line   () const {   return _line;     }
    const int&    col    () const {   return _col;      }
    const int&    maxline() const {   return _maxline;  }
    const int&    maxcol () const {   return _maxcol;   }

    const string& buffer()  {   return _buffer; }

protected:

    char   _sep;
    int    _line;
    int    _col;
    int    _cursor;
    int    _maxline;
    int    _maxcol;
    string _buffer;
};

#endif
