#ifndef STRAT3_ERROR_IMPLEMENTATIONERROR_HEADER
#define STRAT3_ERROR_IMPLEMENTATIONERROR_HEADER

#include <exception>

class ImplementationError : std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Implementation Error:\n"
                    "\t You haven't implemented the required method.\n";
    }

} ImplementationError;

#endif
