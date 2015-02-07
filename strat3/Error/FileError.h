#ifndef STRAT3_ERROR_FILEERROR_HEADER
#define STRAT3_ERROR_FILEERROR_HEADER

#include <exception>

class FileError : std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "FileError, does it exist ?";
    }

} FileError;

#endif
