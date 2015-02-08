#ifndef STRAT3_PORTFOLIO_MARKETENGINE_HEADER
#define STRAT3_PORTFOLIO_MARKETENGINE_HEADER

#include <algorithm>
#include <vector>

#include "Transaction.h"

class MarketEngine
{
    public:
        MarketEngine();

        virtual int  addTransaction(Transaction  t);
        virtual void marketOrder   (Transaction* t);

        void print_book(std::ostream& out);
        void clearOrder();

    protected:

        virtual bool processSingleAsk(Transaction* a);
        virtual bool processSingleBid(Transaction* a);

        virtual void processAsk();
        virtual void processBid();

        void setPrices(Row* prices);

        Index   _Time;      // those two variables are set by the class Tester

    private:
        Row*    _Prices;

    protected:
        Index                    _id;
        std::vector<Transaction> _Ask; // Sell
        std::vector<Transaction> _Bid; // Buy
};

#endif
