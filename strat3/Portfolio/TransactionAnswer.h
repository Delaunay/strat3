#ifndef STRAT3_PORTFOLIO_TRANSACTIONANSWER_HEADER
#define STRAT3_PORTFOLIO_TRANSACTIONANSWER_HEADER

#include "../enum.h"

struct TransactionAnswer
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

        TransactionAnswer(Index ticker, double size, double price, Index time, double cost, Index id);

        double getField(Field a);
        double getField(int a)  {   return getField(Field(a)); }
        void   setField(Field a, double val);

        Index  index() const;
        double size () const;
        double price() const;
        double cost () const;
        double value() const;
        Index  id   () const;

        Answer answer;
};


#endif
