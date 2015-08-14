#ifndef STRAT3_ABSTRACT_PORTFOLIO_HEADER
#define STRAT3_ABSTRACT_PORTFOLIO_HEADER

#include "../enum.h"

#include "../Struct/TransactionWeight.h"

class StrategyLog;
class TransactionAnswer;


void order(const TransactionWeight& tw, const Row& price, const Matrix& holding, Matrix& nbshare);

class Portfolio
{
    public:
        typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMajorMatrix;

        Portfolio() {}
        ~Portfolio()    {}

        virtual void clear_orders() = 0;
        //virtual void transaction_answer(const TransactionAnswer& m) = 0;

        virtual Matrix transaction_weight(const uint& time, const Row& price, const TransactionWeight& tw)
        {
            Matrix nbshare(_state.rows(), _state.cols());

            order(tw, price, nbshare);

            return nbshare;
        }

        virtual void transaction_answer(const Matrix& nbshare)
        {
            _state += nbshare;
        }

        //virtual void logPortfolioFull(Index time, Row* price);

        void set_cash(const double& cash)   {   _cash = cash;   }
        void set_security_number(const uint& n){
            _nsecurity = n;
            _state = Column::Constant(_nsecurity, 1.0 / double(_nsecurity));
        }

        const Matrix& state() const           {   return _state; }

        // All those must be matrices too
        double  invested   (const Row& prices) const {    return (prices * _state)(0, 0); }
        double  asset      (const Row& prices) const {    return (prices * _state)(0, 0) + _cash; }
        double  equity     (const Row& prices) const {    return asset(prices) - liability(prices); }
        double  liability  (const Row& prices) const
        {
            return std::min(_cash, 0.0) +
                    (prices *(_state.array() * (_state.array() < 0).cast<double>()).matrix()).sum();
        }

        // Compute the number of share we need to buy
        void order(const TransactionWeight& tw, const Row& price, Matrix& nbshare)  const
        {
            ::order(tw, price, _state, nbshare);
        }

    protected:

        double        _time;
        double        _cash;            // Cash must a Matrix
        Matrix        _state;           // Hold number of shares
        uint          _nsecurity;       // Security
};

#endif
