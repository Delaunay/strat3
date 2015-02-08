#ifndef STRAT3_STRATEGY_STRATEGY_HEADER
#define STRAT3_STRATEGY_STRATEGY_HEADER

#include "../DataManager/DataManager.h"
#include "DataStruct.h"

enum WeightType{
    TotalPercentage,
    DifferentialPercentage,
    TotalShare,
    DifferentialShare,
    NoTransaction
};

struct TransactionWeight
{
    public:
        TransactionWeight():
            type(TotalPercentage)
        {}

        Matrix     weight;
        WeightType type;
};

class DataLog;
class Predictor;

/*!
 * \brief The Strategy class
 */
class Strategy
{
    public:
        //! when user inherit this class it is recommand to give a title to the strategy
        Strategy(Key managerKey, Key matrixkey, int securitySize,
                 bool rebalanced = true, Index frequency = 1);

        virtual ~Strategy()
        {}

        virtual TransactionWeight* operator() (DataStruct* ds, Predictor* p = 0) = 0;
        //virtual TransactionWeight* compute_weight(DataStruct* ds, Predictor* p = 0) = 0;

        //else
        virtual std::string &title();
        virtual std::string description();

        Index version();
        Index frequency();
        bool  rebalanced();

        TransactionWeight* weight();
        void  setFrequency(Index f);
        void  setRebalanced(bool r);

        // divide the weight by the sum of the weight
        static void force100(Strategy* s)
        {

        }

        // divide the weight by the sum of the absolute of the weight
        static void removeLeverage(Strategy* s)
        {

        }

    protected:

        //! Weight
        TransactionWeight _Weight;
        bool              _Rebalanced;
        Index             _Frequency;

        //! for repporting
        Index             _Version;
        std::string       _Description;
        std::string       _Title;

        //! Key specify on which Matrix the Strategy is applied
        Key               _FeatureManagerKey;
        Key               _FeatureMatrixKey;
};

#endif
