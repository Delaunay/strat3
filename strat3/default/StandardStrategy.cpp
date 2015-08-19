#define NEW_PLUGIN
#include "Abstract/Strategy.h"

class PLUGIN_EXPORT SStrategy : public Strategy
{

public:

    SStrategy()
    {
        this->title = "EqualWeighted";
    }

    TransactionWeight* operator() (DataStruct& ds)
    {
        return &_weight;
    }

};

void* create_object()
{
    return new SStrategy();
}
void destroy_object(void* o)
{
    delete (SStrategy*) o;
}
