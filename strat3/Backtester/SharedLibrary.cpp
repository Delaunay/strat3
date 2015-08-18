#include "SharedLibrary.h"

#ifdef __linux__
#else
#   define dlopen(x, flags) ::LoadLibraryA(x)
#   define dlsym(dll, function_name) GetProcAddress(dll, function_name)
#   define dlclose(dll) FreeLibrary(dll)
#   define path_fix(x) x
#   define dlerror() "" // GetLastError
#   define RTLD_LAZY 1
#endif

namespace DynamicLoading{
// Copy constructor Increase count and copy module
SharedLibrary::SharedLibrary(const SharedLibrary& lib):
    _module(lib._module), _ref_count(lib._ref_count)
{
    ++(*_ref_count);
}

SharedLibrary::SharedLibrary(const std::string& name, int flag):
    _module(nullptr), _ref_count(nullptr)
{
    // try loading
    _module = dlopen(name.c_str(), flag);

    // Throw
    THROW(_module == 0, std::runtime_error, "Module Loading Failure");

    // increasing ref only if loading was successful
    _ref_count = new size_type(1);
}

SharedLibrary& SharedLibrary::operator= (const SharedLibrary& lib)
{
    ++(*lib._ref_count);

    if (--(*_ref_count) == 0)
    {
        close_module();
        delete _ref_count;
    }

    _ref_count = lib._ref_count;
    _module = lib._module;

    return *this;
}

SharedLibrary::~SharedLibrary()
{
    if (--(*_ref_count) == 0){
        close_module();
        delete _ref_count;
    }
}

void SharedLibrary::close_module()
{
    if (_module)
        dlclose(_module);
    _module = nullptr;
}


const char* SharedLibrary::error() const
{
    return dlerror();
}
}

#ifndef __linux__
#   undef dlopen
#   undef dlsym
#   undef dlclose
#   undef path_fix
#   undef dlerror
#   undef RTLD_LAZY
#endif
