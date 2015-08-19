#include "Backtester.h"

#include "../Struct/DataStruct.h"
#include "../DataManager/MatrixManager.h"

#include <iostream>

namespace strat3{

void Backtester::run_one_step()
{
    MatrixQuery         dq = make_query();  // Get Available Data
    Row                 lp = last_price();  // Get Last price

    // Making public data available
    DataStruct ds(_price_matrix);

          ds.data_manager = &dq;
          //ds.predictors  = &this->_GlobalPredictors;
          //ds.securities  = this->_SecurityDatabase;

    const TransactionWeight*  w;

    Eigen::IOFormat fmt;

    for(Index k = 0, n = _strategies.size(); k < n; k++)
    {
       if (should_run(k))
       {
           // Compute Target owning
           w = (*get_strategy(k))(ds);

           // log current target
           log_weights(title(k), *w);

           // Compute effective Buy/Sell
           Matrix orders = get_portfolio(k)->transaction_weight(_time, lp, *w);

           log_orders(title(k), orders);

           // update portfolio state
           get_portfolio(k)->transaction_answer(orders, lp);

           // Log current holdings
           log_portfolio_state(title(k), get_portfolio(k)->state());
       }

       MPortfolio& p = get_portfolio(k);

       // log current portfolio value
       log_portfolio_values(title(k), p->invested(lp), p->cash(), p->liability(lp));
    }

    // one period has passed
    _time++;
}

//DataQuery make_query    ();

MatrixQuery Backtester::make_query    ()
{
    return _data->make_query(0, _strat_window + _time);
}

uint      Backtester::period_running() const
{
    return _data->matrix(_price_matrix)
                ->rows() - _strat_window - _time;
}

uint      Backtester::max_period    () const
{
    return _data->matrix(_price_matrix)
                ->rows() - _strat_window - 1;
}

uint Backtester::security_number() const
{
    return  _data->matrix(_price_matrix)->cols();
}

const Row       Backtester::last_price    () const
{
    return _data->matrix(_price_matrix)
                ->row(_time + _strat_window);
}

void Backtester::add_strategy    (NodeTuple* x)
{
    _strategies.push_back(x);
}
void Backtester::set_data_manager (MatrixManager* x, Key priceMatrix)
{
    _data = x;
    _price_matrix  = priceMatrix;
}

bool Backtester::should_run      (Index k)
{
    return (_time == 0) || ((get_strategy(k)->rebalanced) &&
           (_time % get_strategy(k)->frequency == 0));
}

}
