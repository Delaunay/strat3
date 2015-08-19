#ifndef STRAT3_ABSTRACT_PORTFOLIO_HEADER
#define STRAT3_ABSTRACT_PORTFOLIO_HEADER

#include "Plugin.h"
#include "../Struct/TransactionWeight.h"
#include "../enum.h"

class PLUGIN_EXPORT StrategyLog;
class PLUGIN_EXPORT TransactionAnswer;

//
//  Portfolio Track Asset Ownership
//
class PLUGIN_EXPORT Portfolio
{
    public:
        // m = number of Strategies
        typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMajorMatrix;

        // Portfolio is init
        Portfolio() = default;

        virtual void initialize(double cash, const uint& nsecurity, const uint nstrategy = 1, const void* user_data = 0)
        {
            _nsecurity = nsecurity;
            _cash = Matrix::Constant(1, nstrategy, cash);
            _state = Matrix::Zero(nsecurity, nstrategy);
        }

        ~Portfolio()    {}

        // remove all pending orders: currently useless
        virtual void clear_orders(){}

        // processing transaction weight
        virtual Matrix transaction_weight(const uint& time, const Row& price, const TransactionWeight& tw)
        {
            Matrix nbshare(_state.rows(), _state.cols());

            order(tw, price, nbshare);

            return nbshare;
        }

        //                  invested = (1 x n) * (n x m) = (1 x m)
        inline Matrix invested   (const Row& prices) const {    return (prices * _state); }
        inline Matrix asset      (const Row& prices) const {    return (prices * _state) + _cash; }
        inline Matrix equity     (const Row& prices) const {    return asset(prices) - liability(prices); }
        inline Matrix liability  (const Row& prices) const
        {
            return _cash.cwiseProduct((_cash.array() < 0).cast<double>().matrix()) + shorted(prices);
        }

        inline Matrix shorted(const Row& prices) const
        {
            return (prices *(_state.array() * (_state.array() < 0).cast<double>()).matrix());
        }

        // Compute the number of share we need to buy
        void order(const TransactionWeight& tw, const Row& price, Matrix& nbshare)  const
        {
            order(tw, price, _state, nbshare);
        }

        void order(const TransactionWeight& tw, const Row& price, const Matrix& holding, Matrix& nbshare) const
        {
            Matrix val = asset(price);

            switch(tw.type)
            {
                case TotalPercentage:
                    nbshare = (tw.weight * val).cwiseQuotient(price.transpose()) - holding;
                    break;
                case DifferentialPercentage:
                    nbshare = (tw.weight * val).cwiseQuotient(price.transpose());
                    break;
                case TotalShare:
                    nbshare = tw.weight - holding;
                    break;
                case DifferentialShare:
                    nbshare = tw.weight;
                    break;
                case NoTransaction:
                    nbshare = Matrix::Zero(tw.weight.rows(), tw.weight.cols());
                    break;
            }
        }

        // not virtual users cannot modify _state and _cash
        // this one should be server side
        // _cash and _state should be server side hum...
        inline void transaction_answer(const Matrix& nbshare, const Row& prices)
        {
            // remove cash
            _cash -= prices * nbshare;
            // add shares
            _state += nbshare;
        }

        // users cannot modify the state and cash
        inline const Matrix& state() const {   return _state;   }
        inline const Matrix& cash () const {   return _cash;    }
        inline const double& time()  const {   return _time;    }
        inline const uint&   number_security() const  { return _nsecurity;    }

    private:    // replicated variable
        double        _time;
        uint          _nsecurity;       // Security
        Matrix        _cash;            // Cash must a Matrix
        Matrix        _state;           // Hold number of shares
};

#endif
