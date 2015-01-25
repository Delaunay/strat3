#include "Portfolio.h"
#include "MarketEngine.h"
#include "../DataLog/DataLog.h"

#include <iostream>

Portfolio::Portfolio(int securityNum, double cash, std::string name, MarketEngine* marketEngine):
    _Time(0), _Cash(cash), _PortfolioState(Column::Zero(securityNum, 1)), _Market(marketEngine),
    _DeleteLog(true)
{
    _PortfolioState = Column::Zero(securityNum, 1);
    _Log = new DataLog(name, securityNum);
}

Portfolio::~Portfolio()
{
    if (_DeleteLog)
        delete _Log;
}

double Portfolio::invested  (Row* prices)   {  return (*prices * _PortfolioState)(0, 0);           }
double Portfolio::asset     (Row* prices)   {  return (*prices * _PortfolioState)(0, 0) + _Cash;   }
double Portfolio::liability (Row* prices)
{
    // Shorted sec is liability
    return std::min(_Cash, 0.0) + (*prices *(_PortfolioState.array() * (_PortfolioState.array() < 0).cast<double>()).matrix()).sum();
}

double Portfolio::equity    (Row* prices)   {  return asset(prices) - liability(prices);                 }

/*!
 * \brief processTransactionWeight process Weight sent by Strategy and send orders to the
 * market engine
 * \param time
 * \param price
 * \param tw
 */
void Portfolio::processTransactionWeight(Index time, Row *price, TransactionWeight* tw)
{
    Column nbshare = Column::Zero(price->cols(), 1);
    order(tw->type, price, &tw->weight, &_PortfolioState, &nbshare);

    _Time = time;

    // Transaction Weight
    _Log->logTransactionWeight(time, tw);

    // check if a market engine is specified
    // if not, orders are filled instantly without any further processing
    if (_Market)
    {
        Transaction m(this);
        // enabled fields
        m.setField(Transaction::ExecutionField, Transaction::MKT);
        m.setField(Transaction::ValidityField,  Transaction::GTC);
        m.setField(Transaction::CurrentDate, time);

        // disabled fields
        m.setField(Transaction::Price,   -1);
        m.setField(Transaction::Date,    -1);
        m.setField(Transaction::Option1, -1);
        m.setField(Transaction::Option2, -1);
        m.setField(Transaction::DisplayField, -1);

        // TransactionOrder

        for(int i = 0; i < nbshare.rows(); i++)
        {
            m.setField(Transaction::TickerIndex, i);
            m.setField(Transaction::Size,        nbshare(i, 0));
            _Log->logTransactionOrder(&m);

            // market send back the ID of the transaction
            // if an error occured ID = -1
            /*int k =*/ _Market->addTransaction(m);
        }
    }
    else
    {
        _Log->logTransactionOrder(time, &nbshare);
        _Cash -= (*price * nbshare)(0, 0);
        _PortfolioState += nbshare;
    }

    _Log->logPortfolioState(time, &_PortfolioState);
    _Log->logPortfolioValues(time, invested(price), _Cash,
                             asset(price), liability(price), equity(price));
}

void Portfolio::clearOrders()
{
    _Market->clearOrder();
}

void Portfolio::transactionAnswer(TransactionAnswer* m)
{
    _Cash -= m->value();
    _Cash -= m->cost();
    _PortfolioState(m->index(), 0) += m->size();

    _Log->logTransactionAnswer(m);
}
/*!
 * \brief return the number of share we should buy/sell to reach targeted weight
 * \param a
 * \param price
 * \param target
 * \param holding
 * \return
 */
void Portfolio::order(WeightType a, Row* price, Column* target, Column* holding, Column* nbshare)
{
    double val = asset(price);

    switch(a)
    {
        case TotalPercentage:
            (*nbshare) = (*target * val).cwiseQuotient(price->transpose()) - *holding;
            break;
        case DifferentialPercentage:
            (*nbshare) = (*target * val).cwiseQuotient(price->transpose());
            break;
        case TotalShare:
            (*nbshare) = *target - *holding;
            break;
        case DifferentialShare:
            (*nbshare) = *target;
            break;
        case NoTransaction:
            (*nbshare) = Column::Zero(target->rows(), target->cols());
            break;
    }
}

void Portfolio::order(WeightType a, Row* price, Matrix* target, Column* holding, Column* nbshare)
{
    double val = asset(price);

    switch(a)
    {
        case TotalPercentage:
            (*nbshare) = (*target * val).cwiseQuotient(price->transpose()) - *holding;
            break;
        case DifferentialPercentage:
            (*nbshare) = (*target * val).cwiseQuotient(price->transpose());
            break;
        case TotalShare:
            (*nbshare) = *target - *holding;
            break;
        case DifferentialShare:
            (*nbshare) = *target;
            break;
        case NoTransaction:
            (*nbshare) = Column::Zero(target->rows(), target->cols());
            break;
    }
}

void Portfolio::logPortfolioFull(Index time, Row* price)
{
    _Log->logPortfolioState (time, &_PortfolioState);
    _Log->logPortfolioValues(time, invested(price), _Cash, asset(price), liability(price), equity(price));
}
