#include "MarketEngine.h"
#include "Portfolio.h"

MarketEngine::MarketEngine():
    _id(0)
{}

/*!
 * \brief addTransaction return the transaction ID so user can keep tracks of pending orders
 * \param t
 * \return -2 if error -1 if executed order id if the order is pending
 */
int MarketEngine::addTransaction(Transaction t)
{
    if (t.execution() == Transaction::MKT)
    {
        marketOrder(&t);
        return -1;
    }
    else
    {
        if (t.size() > 0)
        {
            bool processed = processSingleAsk(&t);

            if (!processed)
            {
                t.setID(_id);
                _id++;
                _Ask.push_back(t);
                std::sort(_Ask.begin(), _Ask.end());
                return _id - 1;
            }
            else
                return -1;
        }
        else
        {
            bool processed = processSingleBid(&t);

            if (!processed)
            {
                t.setID(_id);
                _id++;
                _Bid.push_back(t);
                std::sort(_Bid.begin(), _Bid.end());
                return _id - 1;
            }
            else
                return -1;
        }
    }

    return -2;
}

void MarketEngine::marketOrder(Transaction* t)
{
    // TransactionAnswer(Index ticker, double size, double price, Index time, double cost, Index id):
    TransactionAnswer ta(t->tickerIndex(),
                         t->size(),
                         (*_Prices)(t->tickerIndex(), 0),
                         _Time,
                         0,
                         t->id());

    t->parent()->transactionAnswer(&ta);
}

void MarketEngine::print_book(std::ostream& out)
{
    out << "ASK" << std::endl <<
           "Price          Qty         " << std::endl;

    for (int i = 0; i < _Ask.size(); i++)
        out << _Ask[i].price() << "\t\t" << _Ask[i].size() << std::endl;

    out << "BID" << std::endl <<
           "Price          Qty         " << std::endl;

    for (int i = 0; i < _Bid.size(); i++)
        out << _Bid[i].price() << "\t\t" << _Bid[i].size() << std::endl;
}

void MarketEngine::clearOrder()
{
    _Ask.clear();
    _Bid.clear();
    _id = 0;
}


bool MarketEngine::processSingleAsk(Transaction* a)
{
    double price = (*_Prices)(a->tickerIndex(), 0);

    if ((a->size() < 0) && (a->price() <= price) && (a->execution() == Transaction::LMT))
    {
        marketOrder(a);
        return true;
    }
    else if ((a->size() < 0) && (a->price() >= price) && (a->execution() == Transaction::STO))
    {
        marketOrder(a);
        return true;
    }

    return false;
}

bool MarketEngine::processSingleBid(Transaction* a)
{
    double price = (*_Prices)(a->tickerIndex(), 0);

    // if BUY and Target price is > than current price the LMT order become a mkt order
    if ((a->price() >= price) && (a->execution() == Transaction::LMT))
    {
        marketOrder(a);
        return true;
    }
    // if BUY and Target price is < than current price the STO order become a mkt order
    else if ((a->price() <= price) && (a->execution() == Transaction::STO))
    {
        marketOrder(a);
        return true;
    }

    return false;
}

void MarketEngine::processAsk()
{
    for (int i = 0; i < _Ask.size(); i++)
    {
        Transaction* a = &_Ask[i];
        double price = (*_Prices)(a->tickerIndex(), 0);

        if ((a->size() < 0) && (a->price() <= price) && (a->execution() == Transaction::LMT))
        {
            marketOrder(a);
            _Ask.erase(_Ask.begin() + i);
        }
        else if ((a->size() < 0) && (a->price() >= price) && (a->execution() == Transaction::STO))
        {
            marketOrder(a);
            _Ask.erase(_Ask.begin() + i);
        }
    }
}

void MarketEngine::processBid()
{
    for (int i = 0; i < _Bid.size(); i++)
    {
        Transaction* a = &_Bid[i];
        double price = (*_Prices)(a->tickerIndex(), 0);

        // if BUY and Target price is > than current price the LMT order become a mkt order
        if ((a->price() >= price) && (a->execution() == Transaction::LMT))
        {
            marketOrder(a);
            _Bid.erase(_Bid.begin() + i);
        }
        // if BUY and Target price is < than current price the STO order become a mkt order
        else if ((a->price() <= price) && (a->execution() == Transaction::STO))
        {
            marketOrder(a);
            _Bid.erase(_Bid.begin() + i);
        }
    }
}

void MarketEngine::setPrices(Row* prices) {   _Prices = prices; processBid(); processAsk();   }
