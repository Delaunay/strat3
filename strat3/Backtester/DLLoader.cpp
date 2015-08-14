#include "DLLoader.h"

namespace strat3{

DLLoader::DLLoader():
    _module(0)
{}

DLLoader::DLLoader(const std::string& name, int flag):
    _module(dlopen(name.c_str(), flag))
{
    load_module(name, flag);
}

DLLoader::~DLLoader()
{
    close_module();
}

void DLLoader::close_module()
{
    if (_module)
        dlclose(_module);
}

void DLLoader::load_module(const std::string& name, int flag)
{
    _module = dlopen(name.c_str(), flag);
    STHROW(_module == 0, std::runtime_error, "Module Loading Failure");
}

}
