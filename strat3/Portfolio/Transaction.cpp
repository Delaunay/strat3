#include "Transaction.h"

bool Transaction::operator< (const Transaction& a) const
{
    // buy Low first
    if (size() > 0)
        return a.price() < this->price();
    // sell high first
    else
        return a.price() > this->price();
}

bool Transaction::operator> (const Transaction& a) const
{
    // buy
    if (size() > 0)
        return a.price() > this->price();
    // sell
    else
        return a.price() < this->price();
}

Transaction::Transaction(Portfolio* parent):
    _Parent(parent)
{
    transactions(0, TickerIndex   ) = -1;
    transactions(0, Size          ) =  0;
    transactions(0, ExecutionField) = MKT;
    transactions(0, ValidityField ) = GTC;
    transactions(0, Price         ) = -1;
    transactions(0, Option1       ) = -1;
    transactions(0, Option2       ) = -1;
    transactions(0, Date          ) = -1;
    transactions(0, Display       ) = -1;
    transactions(0, CurrentDate   ) = -1;
    transactions(0, ID            ) = -1;
}

void   Transaction::setField(Field a, double val)  {   transactions(0, int(a)) = val; }
double Transaction::getField(Field a)              {   return transactions(0, int(a)); }

int    Transaction::execution  () const   {   return transactions(0, ExecutionField);}
double Transaction::price      () const   {   return transactions(0, Price);         }
double Transaction::size       () const   {   return transactions(0, Size);          }
Index  Transaction::tickerIndex() const   {   return transactions(0, TickerIndex);   }
Index  Transaction::id         () const   {   return transactions(0, ID);            }

void       Transaction::setID(Index id)  {   transactions(0, ID) = double(id);   }
Portfolio* Transaction::parent()         {   return _Parent; }
