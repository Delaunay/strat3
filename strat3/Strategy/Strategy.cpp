#include "Strategy.h"


Strategy::Strategy(Key managerKey, Key matrixkey, int securitySize, bool rebalanced, Index frequency):
    _Rebalanced(rebalanced), _Frequency(frequency), _Version(1),
    _Description(std::string("No Descritpion")), _Title(std::string("No Title")),
    _FeatureManagerKey(managerKey), _FeatureMatrixKey(matrixkey)
{
    _Weight.weight = Matrix::Zero(securitySize, 1);
}

TransactionWeight* Strategy::operator() (DataQuery* q)
{
    return &_Weight;
}

TransactionWeight* Strategy::weight() {   return &_Weight;    }

string &Strategy::title()        {   return _Title;        }
std::string Strategy::description()  {   return _Description;  }

Index Strategy::version()     {   return _Version;    }
Index Strategy::frequency()   {   return _Frequency;  }
bool  Strategy::rebalanced()  {   return _Rebalanced; }

void  Strategy::setFrequency(Index f)  {   _Frequency = f;  }
void  Strategy::setRebalanced(bool r)  {   _Rebalanced = r; }

//
TransactionWeight* Strategy::operator() (DataStruct* q)
{
    return &_Weight;
}


// new
TransactionWeight* Strategy::compute_weight(DataStruct* q)
{
    return &_Weight;
}

TransactionWeight* Strategy::compute_weight(DataQuery* q)
{
    return &_Weight;
}
