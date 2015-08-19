#define NEW_PLUGIN
#include "Abstract/Strategy.h"

class PLUGIN_EXPORT SStrategy : public Strategy
{

public:

    SStrategy()
    {
        this->title = "EqualWeighted";
    }

    const TransactionWeight* operator() (const DataStruct& ds)
    {
        return &tw();
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
