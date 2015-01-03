#include "TransactionAnswer.h"

TransactionAnswer::TransactionAnswer(Index ticker, double size, double price, Index time, double cost, Index id)
{
    answer(0, TickerIndex) = double(ticker);
    answer(0, Size)        = size;
    answer(0, Price)       = price;
    answer(0, Time)        = double(time);
    answer(0, Cost)        = cost;
    answer(0, ID)          = id;
}

double TransactionAnswer::getField(Field a)               {   return answer(0, int(a));   }
void   TransactionAnswer::setField(Field a, double val)   {   answer(0, int(a)) = val;   }

Index  TransactionAnswer::index() const  {   return Index(answer(0, TickerIndex));         }
double TransactionAnswer::size () const  {   return answer(0, Size);                       }
double TransactionAnswer::price() const  {   return answer(0, Price);                      }
double TransactionAnswer::cost () const  {   return answer(0, Cost);                       }
double TransactionAnswer::value() const  {   return answer(0, Price) * answer(0, Size);    }
Index  TransactionAnswer::id   () const  {   return Index(answer(0, ID));                  }
