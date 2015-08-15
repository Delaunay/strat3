#include "Abstract/Strategy.h"
#include "Abstract/Plugin.h"

class SStrategy : public Strategy
{

public:

    SStrategy()
    {
        this->title = "EqualWeighted";
    }

     PLUGIN TransactionWeight* operator() (DataStruct& ds)
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
