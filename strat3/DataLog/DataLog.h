#ifndef STRAT3_DATALOG_HEADER
#define STRAT3_DATALOG_HEADER

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <stdio.h>
#include <string>

#include "../enum.h"

//#define LOG_CSV 1
//#define LOG_BIN 1
//#define LOG_DISK 1
#define LOG_RAM 1


//enum LoggingType
//{
//    Disk,
//    Ram
//};

//enum LoggingFormat
//{
//    Binnary,
//    CSV
//};

class Transaction;
class TransactionWeight;
class TransactionAnswer;


//template<typename >
/*!
 * \brief The DataLog class
 *
 * for RAM save we use std::vector<double> since data are contiguous
 * we can cast them into a Eigen::Matrix using Eigen::Map
 * need to check pre allocation for better performance
 *
 * Real Time statistics will be called by Datalog
 */
class DataLog
{
    public:

        enum FieldValues
        {
            Time = 0,
            Invested,
            Cash,
            Asset,
            Liabilities,
            Equity,
            FieldValuesMax,
        };

        typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMajorMatrix;

        /*! Save generated Data
         *  \param name StrategyName filename
         *  \param numsec Number of security used for matrix size
         *  \param market engine might be use if it changes market
         *  \param n size of entries for matrix n for memory pre allocation
         */
        DataLog(std::string name, Index numsec, bool marketEngine = false, int n = 4000);
        ~DataLog();

        Index securityNumber() {    return _NumSecurity;  }

        // Same as always
        void logPortfolioState      (double time, Column* state);
        void logTransactionWeight   (double time, TransactionWeight* tw);
        void logPortfolioValues     (double time,  double invested,    double cash,
                                     double asset, double liabilities, double equity);

        // does not exist if there are no market Engine
        void logTransactionAnswer   (TransactionAnswer* m);

        // two cases : with ME and without
        void logTransactionOrder    (Transaction* m);
        void logTransactionOrder    (double time, Column* m);

#if LOG_DISK
        RowMajorMatrix readPortfolioState();
        RowMajorMatrix readTransactionAnswer();
        RowMajorMatrix readTransactionOrder();
        RowMajorMatrix readWeightMatrix();
        RowMajorMatrix readPortfolioValues();
#endif

        const std::string& name()    {   return _Name; }
#if LOG_RAM
        Matrix transactionAnswer();
        Matrix transactionOrder();
        Matrix weightMatrix();
        Matrix portfolioValues();
        Matrix portfolioState();

        Matrix readTransactionAnswer()   { return transactionAnswer();  }
        Matrix readTransactionOrder()    { return transactionOrder();   }
        Matrix readWeightMatrix()        { return weightMatrix();       }
        Matrix readPortfolioValues()     { return portfolioValues();    }
        Matrix readPortfolioState()      { return portfolioState();     }

        void save_all()
        {
//            std::cout << _WeightMatrix << std::endl;
//            portfolioValuesFile << _TransactionOrder;

            std::fstream portfolioStateFile;
            std::fstream transactionOrderFile;
            std::fstream weightMatrixFile;
            std::fstream portfolioValuesFile;

            portfolioStateFile     .open((_Name + Key(".PortfolioState.csv")    ).c_str(), std::ios::out);
            weightMatrixFile       .open((_Name + Key(".MatrixWeight.csv")      ).c_str(), std::ios::out);
            transactionOrderFile   .open((_Name + Key(".TransactionOrder.csv")  ).c_str(), std::ios::out);
            portfolioValuesFile    .open((_Name + Key(".PortfolioValues.csv")   ).c_str(), std::ios::out);

            std::string str_sec;
            for(int i = 0; i < _NumSecurity - 1; i++)
                str_sec += "Sec" + std::to_string(i) + ",";

            str_sec += "Sec" + std::to_string(_NumSecurity - 1);

            if (_Market)
            {
                std::fstream transactionAnswerFile;
                transactionAnswerFile.open((_Name + std::string(".TransactionOrder.csv")  ).c_str(), std::ios::out);
                transactionAnswerFile << "tickerindex,size,price,time,cost,id\n" << transactionAnswer().format(_Format);
                transactionOrderFile  << "time,shares\n"<< transactionOrder().format(_Format);
                transactionAnswerFile.close();
            }
            else
            {
                transactionOrderFile << "time," << str_sec << "\n" << transactionOrder().format(_Format);
            }

            portfolioValuesFile << "time,invested,cash,asset,liabilities,equity\n" << portfolioValues().format(_Format);
            weightMatrixFile    << "time,type," << str_sec << "\n" << weightMatrix().format(_Format);
            portfolioStateFile  << "time," << str_sec << "\n" << portfolioState().format(_Format);

            portfolioStateFile.close();
            transactionOrderFile.close();
            weightMatrixFile.close();
            portfolioValuesFile.close();
        }
#endif

    protected:

        std::string _Name;
        bool        _Market;

        Index _NumSecurity;
        Index _StateEntry;
        Index _AnswerEntry;
        Index _OrderEntry;
        Index _WeightEntry;
        Index _ValuesEntry;

#if LOG_RAM

        std::vector<double> _PortfolioState;
        std::vector<double> _TransactionAnswer;
        std::vector<double> _TransactionOrder;
        std::vector<double> _WeightMatrix;
        std::vector<double> _PortfolioValues;

//        Matrix _PortfolioState;
//        Matrix _TransactionAnswer;
//        Matrix _TransactionOrder;
//        Matrix _WeightMatrix;
//        Matrix _PortfolioValues;

        Eigen::IOFormat _Format;

//        std::vector<Column, Eigen::aligned_allocator<Column>>             _PortfolioStateFile;
//        std::vector<TransactionAnswer>  _TransactionAnswerFile;
//        std::vector<Transaction>        _TransactionOrderFile;
//        std::vector<TransactionWeight>  _WeightMatrixFile;
//        std::vector<Column, Eigen::aligned_allocator<Column>>             _PortfolioValuesFile;
#endif
#if LOG_BIN && LOG_DISK
        FILE* _PortfolioStateFile;
        FILE* _TransactionAnswerFile;
        FILE* _TransactionOrderFile;
        FILE* _WeightMatrixFile;
        FILE* _PortfolioValuesFile;
#endif

#if LOG_CSV && LOG_DISK
        std::fstream _PortfolioStateFile;
        std::fstream _TransactionAnswerFile;
        std::fstream _TransactionOrderFile;
        std::fstream _WeightMatrixFile;
        std::fstream _PortfolioValuesFile;
        Eigen::IOFormat _Format;
#endif
};

#endif

//        Matrix readPortfolioState()
//        {
//            std::ifstream file((_Name + std::string(".PortfolioState.csv")).c_str(), std::ios::in);
//            std::getline(file, line);
//            char c;
//            for (int j = 0; j < _WeightEntry; j++)
//            {
//                std::getline(file, line);
//                std::istringstream ss(line);
//                for (int i = 0, n = _NumSecurity + 1; i < n; i++)
//                {
//                    if (i < _NumSecurity)
//                        ss >> ret(j, i) >> c;
//                    else
//                        ss >> ret(j, i);
//                }
//            }
//            file.close();
//        }
