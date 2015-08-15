#include "Backtester.h"

#include "../Struct/DataStruct.h"
#include "../DataManager/MatrixManager.h"

#include <iostream>

namespace strat3{

void Backtester::run_one_step()
{
    DataQuery           dq = make_query();  // Get Available Data
    Row                 lp = last_price();  // Get Last price

    // Making public data available
    DataStruct ds(this->_price_manager, this->_price_matrix);

          ds.dataManager = &dq;
          //ds.predictors  = &this->_GlobalPredictors;
          //ds.securities  = this->_SecurityDatabase;

    TransactionWeight*  w;

    Eigen::IOFormat fmt;

    for(Index k = 0, n = _strategies.size(); k < n; k++)
    {
       if (should_run(k))
       {
           // Compute Target owning
           w = (*get_strategy(k))(ds);

           cout << w->weight.transpose().format(fmt) << "\n";

           // log current target
           log_weights(title(k), *w);

           // Compute effective Buy/Sell
           Matrix orders = get_portfolio(k)->transaction_weight(_time, lp, *w);

           log_orders(title(k), orders);
           get_portfolio(k)->transaction_answer(orders);

           // Log current holdings
           log_portfolio_state(title(k), get_portfolio(k)->state());
       }

       // log current portfolio value
       log_portfolio_values(title(k), lp);
    }

    // one period has passed
    _time++;
}

//DataQuery make_query    ();

DataQuery Backtester::make_query    ()
{
    return _data->dataQuery(0, _strat_window + _time);
}

uint      Backtester::period_running()
{
    return _data->matrixManager(_price_manager)
                    ->matrix(_price_matrix)
                    ->rows() - _strat_window - _time;
}

uint      Backtester::max_period    ()
{
    return _data->matrixManager(_price_manager)
                    ->matrix(_price_matrix)
                    ->rows() - _strat_window - 0;
}

uint Backtester::security_number()
{
    return  _data->matrixManager(_price_manager)
            ->matrix(_price_matrix)->cols();
}

Row       Backtester::last_price    ()
{
    return _data->matrixManager(_price_manager)
                   ->matrix(_price_matrix)
                   ->row(_time + _strat_window);
}

void Backtester::add_strategy    (NodeTuple* x)
{
    _strategies.push_back(x);
}
void Backtester::set_data_manager (DataManager* x, Key priceManager, Key priceMatrix)
{
    _data = x;
    _price_manager = priceManager;
    _price_matrix  = priceMatrix;
}

bool Backtester::should_run      (Index k)
{
    return (_time == 0) || ((get_strategy(k)->rebalanced) &&
           (_time % get_strategy(k)->frequency == 0));
}

}
