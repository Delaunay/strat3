#ifndef STRAT3_PORTFOLIO_TRANSACTION_HEADER
#define STRAT3_PORTFOLIO_TRANSACTION_HEADER

#include "../enum.h"

class Portfolio;

struct Transaction
{
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        typedef Eigen::Matrix<double, 1, 11> Transactions;

        enum Field
        {
            TickerIndex    =  0,
            Size           =  1,
            ExecutionField =  2,
            ValidityField  =  3,
            Price          =  4,
            Option1        =  5,
            Option2        =  6,
            Date           =  7,
            DisplayField   =  8,
            CurrentDate    =  9,
            ID             = 10,
        };

        bool operator< (const Transaction& a) const;
        bool operator> (const Transaction& a) const;

        Transaction(Portfolio* parent);

        void   setField(Field a, double val);
        double getField(Field a);
        double getField(int a) { return getField(Field(a)); }

        int    execution  () const;
        double price      () const;
        double size       () const;
        Index  tickerIndex() const;
        Index  id         () const;
        void   setID      (Index id);

        Portfolio* parent();

        Transactions transactions;

    protected:
        Portfolio*   _Parent;

    public:
        enum Execution
        {
            Market = 1,         // Buy/Sell at the current market price
            Limit  = 2,         // Buy(Sell) if the price drop(rise) below(above) a target price
            Stop   = 3,         // Buy(Sell) if the price rise(drop) above(below) a target price
            MKT = Market,
            LMT = Limit,
            STO = Stop
        };

        enum Validity
        {
            GoodTillDate,
            GoodOnDay,
            GoodTillCancelled,
            ImmediateOrCancel,
            GoodOnClose,
            GoodOnOpen,

            FillOrKill    = ImmediateOrCancel,
            MarketOnClose = GoodOnClose,
            MarketOnOpen  = GoodOnOpen,

            GTD = GoodTillDate,
            GOD = GoodOnDay,
            GTC = GoodTillCancelled,
            FOK = ImmediateOrCancel,
            IOC = ImmediateOrCancel,
            GOC = GoodOnClose,
            COO = GoodOnOpen,
            MOC = GoodOnClose,
            MOO = GoodOnOpen
        };

        enum Option
        {
            None,
            AllOrNothing,
            Hidden,
            Display,
            AON = AllOrNothing,
            HID = Hidden,
            DIS = Display
        };
};

//1 Index       _iTicker;
//2 double      _Size;          // Number of Share/Contracts
//3 Execution   _Execution;     // Execution type MKT/LMT/STOP
//4 Validity    _Validity;      // Validity GoodTillDate
//5 Price       _Price;         // Execution price if STOP/LMT order
//6 Option      _Option1;       // Additional option
//7 Option      _Option2;       // Additional option
//8 int         _Date;          // Date for good-till-date
//9 double      _Display;       // DisplaySize
//


#endif
