#ifndef STRAT3_PORTFOLIO_TRANSACTIONANSWER_HEADER
#define STRAT3_PORTFOLIO_TRANSACTIONANSWER_HEADER

#include "../enum.h"

struct BT_EXPORT TransactionAnswer
{
    public:
        // required for fixed size matrix
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        typedef Eigen::Matrix<double, 1, 6> Answer;

        enum Field
        {
            TickerIndex = 0,
            Size = 1,
            Price = 2,
            Time = 3,
            Cost = 4,
            ID = 5
        };

        TransactionAnswer(Index ticker, double size, double price, Index time, double cost, Index id)
        {
            answer(0, TickerIndex) = double(ticker);
            answer(0, Size)        = size;
            answer(0, Price)       = price;
            answer(0, Time)        = double(time);
            answer(0, Cost)        = cost;
            answer(0, ID)          = id;
        }

        inline void set_field(Field a, const double& val)   {   answer(0, a) = val;    }
        inline const double& get_field(Field a) const       {  return answer(0, a);        }
        inline const double& get_field(int   a) const       {  return get_field(Field(a)); }
        inline const double& index() const  {   return answer(0, TickerIndex); }
        inline const double& size () const  {   return answer(0, Size);        }
        inline const double& price() const  {   return answer(0, Price);       }
        inline const double& cost () const  {   return answer(0, Cost);        }
        inline const double& value() const  {   return answer(0, Price);       }
        inline const Index & id   () const  {   return answer(0, ID);          }

        Answer answer;
};


#endif
