#include "Securities.h"


Security::Security(Index id, std::string ticker, std::string type,
           std::string market, std::string location,
           std::string currency):
    ID(id), ticker(ticker), type(type), market(market),
    location(location), currency(currency)
{}


SecurityDatabase::SecurityDatabase()
{}

void SecurityDatabase::add_security(Index id, std::string ticker, std::string type,
                  std::string market, std::string location, std::string currency)
{
    securities.push_back(Security(id, ticker, type,
                                    market, location, currency));
}

const Security& SecurityDatabase::operator[] (Index id)
{
    return securities[id];
}

Index SecurityDatabase::size()    {   return securities.size();   }

const std::string SecurityDatabase::ticker  (Index id)    {   return securities[id].ticker;   }
const std::string SecurityDatabase::type    (Index id)    {   return securities[id].type;     }
const std::string SecurityDatabase::market  (Index id)    {   return securities[id].market;   }
const std::string SecurityDatabase::location(Index id)    {   return securities[id].location; }
const std::string SecurityDatabase::currency(Index id)    {   return securities[id].currency; }
