#define NEW_PLUGIN
#include "Abstract/Portfolio.h"

class SPortfolio : public Portfolio
{
public:

};

void* create_object()
{
    return new SPortfolio();
}
void destroy_object(void* o)
{
    delete (SPortfolio*) o;
}
