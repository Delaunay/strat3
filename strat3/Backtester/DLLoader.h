#ifndef STRAT3_BACKTESTER_DLLOADER_HEADER
#define STRAT3_BACKTESTER_DLLOADER_HEADER

#include <string>
#include <cassert>
#include "ErrorPolicy.h"

#ifdef __linux__
#   include <dlfcn.h>
#   define DLL void*
#else
#   include <windows.h>
#   define dlopen(x, flags) LoadLibrary(x)
#   define DLL HINSTANCE
#   define dlsym(dll, function_name) GetProcAddress(dll, function_name)
#   define dlclose(dll)
#   define path_fix(x) x
#   define dlerror() ""
#   define RTLD_LAZY 1
#endif

#if STRAT3_THROW
#   include <memory> // Exception
#endif

namespace strat3{

class DLLoader
{
public:

    DLLoader();

    DLLoader(const std::string& name, int flag = RTLD_LAZY);

    ~DLLoader();

    void close_module();

    void load_module(const std::string& name, int flag = RTLD_LAZY);

    template<typename T>
    T get_function(const std::string& name) const
    {
        STHROW(_module == 0, std::runtime_error, "No Module is currently Loaded");
        T t = (T) dlsym(_module, name.c_str());
        STHROW(t == 0, std::runtime_error, "Unknown Symbol");
        return t;
    }

    template<typename T>
    T get_function_nocheck(const std::string& name) const
    {
        return (T) dlsym(_module, name.c_str());
    }

private:

    DLL         _module;

public:

    inline const char*       error() const  {   return dlerror();   }
};
}
// Remove Macro
#undef DLL
#ifndef __linux__
#   undef dlopen
#   undef dlsym
#   undef dlclose
#   undef path_fix
#   undef dlerror
#   undef RTLD_LAZY
#endif
#endif
