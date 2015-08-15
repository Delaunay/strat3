#include "Abstract/Portfolio.h"
#include "Abstract/Plugin.h"

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
