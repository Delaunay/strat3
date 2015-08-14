//#ifndef STRAT3_DATALOG_CPP
//#define STRAT3_DATALOG_CPP

//#include "DataLog.h"
//#include "../Portfolio/Transaction.h"
//#include "../Abstract/AbstractStrategy.h"
//#include "../Portfolio/TransactionAnswer.h"


//DataLog::DataLog(std::string name, Index numsec, bool marketEngine, int n):
//    _Name(name), _Market(marketEngine), _NumSecurity(numsec), _StateEntry(0),
//    _AnswerEntry(0), _OrderEntry(0), _WeightEntry(0), _ValuesEntry(0)
//{
//    n = n + 10;

//    #if LOG_RAM
////    if (marketEngine)
////    {
////        _TransactionAnswer = Matrix::Zero(n * _NumSecurity,  6);
////        _TransactionOrder  = Matrix::Zero(n * _NumSecurity, 11);
////    }
////    else
////    {
////        _TransactionOrder  = Matrix::Zero(n, _NumSecurity + 1);
////    }
////    _PortfolioState    = Matrix::Zero(n,  _NumSecurity + 1);
////    _WeightMatrix      = Matrix::Zero(n,  _NumSecurity + 2);
////    _PortfolioValues   = Matrix::Zero(n, 6);

//    _Format = Eigen::IOFormat(4, Eigen::DontAlignCols, ",", "\n", "", "", "", "");
//    #endif

//    #if LOG_BIN && LOG_DISK
//    if (_Market){
//        _TransactionAnswerFile  = fopen((name + std::string(".TransactionAnswer")).c_str(), "wb+");
//    }

//    _TransactionOrderFile   = fopen((name + std::string(".TransactionOrder") ).c_str(), "wb+");
//    _WeightMatrixFile       = fopen((name + std::string(".MatrixWeight")     ).c_str(), "wb+");
//    _PortfolioStateFile     = fopen((name + std::string(".PortfolioState")   ).c_str(), "wb+");
//    _PortfolioValuesFile    = fopen((name + std::string(".PortfolioValues")  ).c_str(), "wb+");
//    #endif

//    #if LOG_CSV && LOG_DISK
//    if (_Market)
//        _TransactionAnswerFile  .open((name + std::string(".TransactionAnswer.csv") ).c_str(), std::ios::out);

//    _PortfolioStateFile     .open((name + std::string(".PortfolioState.csv")    ).c_str(), std::ios::out);
//    _WeightMatrixFile       .open((name + std::string(".MatrixWeight.csv")      ).c_str(), std::ios::out);
//    _TransactionOrderFile   .open((name + std::string(".TransactionOrder.csv")  ).c_str(), std::ios::out);
//    _PortfolioValuesFile    .open((name + std::string(".PortfolioValues.csv")   ).c_str(), std::ios::out);
//    _PortfolioValuesFile << "time,invested,cash,asset,liabilities,equity\n";

//    _Format = Eigen::IOFormat(4, Eigen::DontAlignCols, ",", "\n", "", "", "", "");
//    #endif
//}

//DataLog::~DataLog()
//{
//    #if LOG_RAM
//    this->save_all();
//    #endif

//    #if LOG_BIN && LOG_DISK
//    if (_Market){
//        fclose(_TransactionAnswerFile);
//    }

//    fclose(_TransactionOrderFile);
//    fclose(_WeightMatrixFile);
//    fclose(_PortfolioStateFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    if (_Market)
//        _TransactionAnswerFile  .close();

//    _PortfolioStateFile     .close();
//    _TransactionOrderFile   .close();
//    _WeightMatrixFile       .close();
//    #endif
//}

//void DataLog::logPortfolioState(double time, Column* state)
//{
//    #if LOG_RAM
//    // = Eigen::Zero(n, _NumSecurity)
////    _PortfolioState(this->_StateEntry, 0) = time;
////    _PortfolioState.block(this->_StateEntry, 1, 1, _NumSecurity) = state->transpose();

//    _PortfolioState.push_back(time);

////    std::cout << time << std::endl;
////    std::cout << *state << std::endl;

//    for (int i = 0; i < _NumSecurity; i++)
//        _PortfolioState.push_back( (*state)(i, 0) );

//    #endif

//    #if LOG_BIN && LOG_DISK
//    fwrite(&time,           sizeof(double), 1,              _PortfolioStateFile);
//    fwrite(&(*state)(0, 0), sizeof(double), state->size(),  _PortfolioStateFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    _PortfolioStateFile << time << ',' << state->transpose().format(_Format) << '\n';
//    #endif

//    _StateEntry++;
//}
//void DataLog::logTransactionWeight(double time, TransactionWeight* tw)
//{
//    #if LOG_RAM
//;
//    // = Eigen::Zero(n, _NumSecurity)
////    std::cout << "Order " <<_OrderEntry << std::endl;
////    std::cout << "Weight" <<_WeightEntry<< std::endl;
////    std::cout << "State " <<_StateEntry << std::endl;
////    std::cout << "Values" <<_ValuesEntry << std::endl;
////    std::cout << "Answer" <<_AnswerEntry << std::endl;
////    std::cout << " " << std::endl;

////    std::cout << "basta" << std::endl;
////    std::cout << _WeightMatrix.block(this->_WeightEntry, 2, 1, _NumSecurity) << std::endl;
////    std::cout << std::endl;
////    std::cout << tw->weight << std::endl;
////    std::cout << "ebasta" << std::endl;

////    _WeightMatrix(this->_WeightEntry, 0) = time;
////    _WeightMatrix(this->_WeightEntry, 1) = int(tw->type);
////    _WeightMatrix.block(this->_WeightEntry, 2, 1, _NumSecurity) = tw->weight.transpose();

//    _WeightMatrix.push_back(time);
//    _WeightMatrix.push_back(tw->type);

//    for (int i = 0; i < _NumSecurity; i++)
//        _WeightMatrix.push_back( tw->weight(i, 0) );

//    #endif

//    #if LOG_BIN && LOG_DISK
//    double i = int(tw->type);

//    fwrite(&time,               sizeof(double), 1,                  _WeightMatrixFile);
//    fwrite(&i,                  sizeof(double), 1,                  _WeightMatrixFile);
//    fwrite(&(tw->weight(0, 0)), sizeof(double), tw->weight.size(),  _WeightMatrixFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    _WeightMatrixFile << time << ',' << tw->weight.transpose().format(_Format) << '\n';
//    #endif

//    _WeightEntry++;
//}
//void DataLog::logTransactionOrder(Transaction* m)
//{
//    // log one transaction
//    #if LOG_RAM
//    for (int i = 0; i < 11; i++)
//        _TransactionOrder.push_back( m->getField(i) );

////    _TransactionOrder.row(this->_OrderEntry) = m->transactions;
//    #endif

//    #if LOG_BIN && LOG_DISK
//    fwrite(&m->transactions(0, 0), sizeof(double), m->transactions.size(), _TransactionOrderFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    _TransactionOrderFile << m->transactions.format(_Format) << '\n';
//    #endif

//    _OrderEntry++;
//}
//void DataLog::logTransactionOrder(double time, Column* m)
//{
//    // log all transaction
//    #if LOG_RAM
////    std::cout << _OrderEntry << " " << *m << std::endl;
////    _TransactionOrder.block(_OrderEntry, 0, m->rows(), 1) = time * Matrix::Ones(m->rows() , 1);
////    _TransactionOrder.block(_OrderEntry, 1, m->rows(), 1) = *m;

////    std::cout << _TransactionOrder.row(_OrderEntry) << std::endl;
////    std::cout << " " << std::endl;
////    std::cout << m->transpose() << std::endl;
////    std::cout << _TransactionOrder.block(_OrderEntry, 1, 1, m->rows()) << std::endl;

//    _TransactionOrder.push_back(time);

//    for (int i = 0; i < _NumSecurity; i++)
//        _TransactionOrder.push_back( (*m)(i, 0) );

//    //_TransactionOrder(_OrderEntry, 0) = time;
////    _TransactionOrder.block(_OrderEntry, 1, 1, m->rows()) = m->transpose();

////    std::cout << _TransactionOrder.row(_OrderEntry) << std::endl;
//    #endif

//    #if LOG_BIN && LOG_DISK
//    fwrite(&time, sizeof(double), 1, _TransactionOrderFile);
//    fwrite(&(*m)(0, 0), sizeof(double), m->size(), _TransactionOrderFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    _TransactionOrderFile << time << ',' << m->transpose().format(_Format) << '\n';
//    #endif

//    _OrderEntry++;
//}
//void DataLog::logTransactionAnswer(TransactionAnswer* m)
//{
//    #if LOG_RAM

//    _TransactionAnswer.push_back(m->getField(0));   //    TickerIndex = 0,
//    _TransactionAnswer.push_back(m->getField(1));   //    Size = 1,
//    _TransactionAnswer.push_back(m->getField(2));   //    Price = 2,
//    _TransactionAnswer.push_back(m->getField(3));   //    Time = 3,
//    _TransactionAnswer.push_back(m->getField(4));   //    Cost = 4,
//    _TransactionAnswer.push_back(m->getField(5));   //    ID = 5

//    //_TransactionAnswer.row(_AnswerEntry) = m->answer;
//    #endif

//    #if LOG_BIN && LOG_DISK
//    fwrite(&(m->answer)(0, 0), sizeof(double), m->size(), _TransactionAnswerFile);
//    #endif

//    #if LOG_CSV
//    _TransactionAnswerFile << m->answer.format(_Format) << '\n';
//    #endif

//    _AnswerEntry++;
//}

//void DataLog::logPortfolioValues(double time, double invested, double cash,
//                                 double asset, double liabilities, double equity)
//{
//    #if LOG_RAM
//    _PortfolioValues.push_back(time);
//    _PortfolioValues.push_back(invested);
//    _PortfolioValues.push_back(cash);
//    _PortfolioValues.push_back(asset);
//    _PortfolioValues.push_back(liabilities);
//    _PortfolioValues.push_back(equity);

////    _PortfolioValues(_ValuesEntry, 0) = time;
////    _PortfolioValues(_ValuesEntry, 1) = invested;
////    _PortfolioValues(_ValuesEntry, 2) = cash;
////    _PortfolioValues(_ValuesEntry, 3) = asset;
////    _PortfolioValues(_ValuesEntry, 4) = liabilities;
////    _PortfolioValues(_ValuesEntry, 5) = equity;
//    #endif

//    #if LOG_BIN && LOG_DISK
//    fwrite(&time,        sizeof(double), 1, _PortfolioValuesFile);
//    fwrite(&invested,    sizeof(double), 1, _PortfolioValuesFile);
//    fwrite(&cash,        sizeof(double), 1, _PortfolioValuesFile);
//    fwrite(&asset,       sizeof(double), 1, _PortfolioValuesFile);
//    fwrite(&liabilities, sizeof(double), 1, _PortfolioValuesFile);
//    fwrite(&equity,      sizeof(double), 1, _PortfolioValuesFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    _PortfolioValuesFile << time << ',' << invested << ',' << cash << ','
//                         << asset << ',' << liabilities << ',' << equity << '\n';
//    #endif

//    _ValuesEntry++;
//}


//#if LOG_DISK
//DataLog::RowMajorMatrix DataLog::readPortfolioState()
//{
//    #if LOG_RAM
//    int n = _NumSecurity + 1;
//    Matrix temp = Matrix::Zero(_StateEntry, n);
//    #endif

//    #if LOG_BIN && LOG_DISK
//    RowMajorMatrix A = RowMajorMatrix::Zero(_StateEntry, n);

//    fflush(_PortfolioStateFile);

//    FILE* file = fopen((_Name + std::string(".PortfolioState")).c_str(), "rb");
////    rewind(file);

//    RowMajorMatrix ret = RowMajorMatrix::Zero(_StateEntry, _NumSecurity + 1);

//    fread(&ret(0, 0), sizeof(double), ret.size(), file);

//    fclose(file);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    RowMajorMatrix A = RowMajorMatrix::Zero(_StateEntry, n);

//    // update the file
//    _PortfolioStateFile.flush();
//    std::string line;
//    std::ifstream file((_Name + std::string(".PortfolioState.csv")).c_str(), std::ios::in);
//    std::getline(file, line);
//    char c;

//    for (int j = 0; j < _StateEntry; j++)
//    {
//        std::getline(file, line);
//        std::istringstream ss(line);

//        for (int i = 0; i < n; i++)
//        {
//            if (i < _NumSecurity)
//                ss >> A(j, i) >> c;
//            else
//                ss >> A(j, i);
//        }
//    }

//    file.close();
//    #endif

//    return A;
//}

//DataLog::RowMajorMatrix DataLog::readTransactionAnswer()
//{
//    if (_Market)
//    {
//        RowMajorMatrix ret(_AnswerEntry, 6);

//        #if LOG_BIN && LOG_DISK
//        fread(&ret(0, 0), sizeof(double), ret.size(), _TransactionAnswerFile);
//        #endif

//        #if LOG_CSV && LOG_DISK
//        _TransactionAnswerFile.flush();
//        std::string line;
//        std::ifstream file((_Name + std::string(".TransactionAnswer.csv")).c_str(), std::ios::in);
//        std::getline(file, line);
//        char c;

//        for (int j = 0; j < _AnswerEntry; j++)
//        {
//            std::getline(file, line);
//            std::istringstream ss(line);

//            for (int i = 0; i < 6; i++)
//            {
//                if (i < 5)
//                    ss >> ret(j, i) >> c;
//                else
//                    ss >> ret(j, i);
//            }
//        }

//        file.close();
//        #endif

//        return ret;
//    }
//    else
//        return RowMajorMatrix(0,0);
//}

//DataLog::RowMajorMatrix DataLog::readTransactionOrder()
//{
//    if (_Market)
//    {
//        RowMajorMatrix ret(_OrderEntry, 11);

//        #if LOG_BIN && LOG_DISK
//        fread(&ret(0, 0), sizeof(double), ret.size(), _TransactionOrderFile);
//        #endif

//        #if LOG_CSV && LOG_DISK
//        _TransactionOrderFile.flush();
//        std::string line;
//        std::ifstream file((_Name + std::string(".TransactionOrder.csv")).c_str(), std::ios::in);
//        std::getline(file, line);
//        char c;

//        for (int j = 0; j < _OrderEntry; j++)
//        {
//            std::getline(file, line);
//            std::istringstream ss(line);

//            for (int i = 0; i < 11; i++)
//            {
//                if (i < 10)
//                    ss >> ret(j, i) >> c;
//                else
//                    ss >> ret(j, i);
//            }
//        }

//        file.close();
//        #endif

//        return ret;
//    }
//    else
//    {
//        RowMajorMatrix ret(_OrderEntry, _NumSecurity + 1);

//        #if LOG_BIN && LOG_DISK
//        fread(&ret(0, 0), sizeof(double), ret.size(), _TransactionOrderFile);
//        #endif

//        #if LOG_CSV && LOG_DISK
//        _TransactionOrderFile.flush();
//        std::string line;
//        std::ifstream file((_Name + std::string(".TransactionOrder.csv")).c_str(), std::ios::in);
//        std::getline(file, line);
//        char c;

//        for (int j = 0; j < _OrderEntry; j++)
//        {
//            std::getline(file, line);
//            std::istringstream ss(line);

//            for (int i = 0, n = _NumSecurity + 1; i < n; i++)
//            {
//                if (i < n - 1)
//                    ss >> ret(j, i) >> c;
//                else
//                    ss >> ret(j, i);
//            }
//        }

//        file.close();
//        #endif

//        return ret;
//    }
//}

//DataLog::RowMajorMatrix DataLog::readWeightMatrix()
//{
//    RowMajorMatrix ret(_WeightEntry, _NumSecurity + 1);

//    #if LOG_BIN && LOG_DISK
//    fread(&ret(0, 0), sizeof(double), ret.size(), _WeightMatrixFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    _WeightMatrixFile.flush();
//    std::string line;
//    std::ifstream file((_Name + std::string(".MatrixWeight.csv")).c_str(), std::ios::in);
//    std::getline(file, line);
//    char c;

//    for (int j = 0; j < _WeightEntry; j++)
//    {
//        std::getline(file, line);
//        std::istringstream ss(line);

//        for (int i = 0, n = _NumSecurity + 1; i < n; i++)
//        {
//            if (i < _NumSecurity)
//                ss >> ret(j, i) >> c;
//            else
//                ss >> ret(j, i);
//        }
//    }

//    file.close();
//    #endif

//    return ret;
//}

//DataLog::RowMajorMatrix DataLog::readPortfolioValues()
//{
//    RowMajorMatrix ret(_ValuesEntry, 6);

//    #if LOG_BIN && LOG_DISK
//    fread(&ret(0, 0), sizeof(double), ret.size(), _PortfolioValuesFile);
//    #endif

//    #if LOG_CSV && LOG_DISK
//    _PortfolioValuesFile.flush();
//    std::string line;
//    std::ifstream file((_Name + std::string(".PortfolioValues.csv")).c_str(), std::ios::in);
//    std::getline(file, line);
//    char c;

//    for (int j = 0; j < _ValuesEntry; j++)
//    {
//        std::getline(file, line);
//        std::istringstream ss(line);

//        for (int i = 0; i < 6; i++)
//        {
//            if (i < 5)
//                ss >> ret(j, i) >> c;
//            else
//                ss >> ret(j, i);
//        }
//    }

//    file.close();
//    #endif

//    return ret;
//}
//#endif

//#if LOG_RAM
//Matrix DataLog::transactionAnswer()
//{
//    Eigen::Map<RowMajorMatrix> map(&_TransactionAnswer[0], _TransactionAnswer.size() / 6, 6);
//    return map;
//}

//Matrix DataLog::transactionOrder()
//{
//    if (_Market)
//    {
//        Eigen::Map<RowMajorMatrix> map(&_TransactionOrder[0], _TransactionOrder.size() / 11, 11);
//        return map;
//    }

//    Eigen::Map<RowMajorMatrix> map(&_TransactionOrder[0], _OrderEntry, _NumSecurity + 1);
//    return map;
//}

//Matrix DataLog::weightMatrix()
//{
//    Eigen::Map<RowMajorMatrix> map(&_WeightMatrix[0], _WeightEntry, _NumSecurity + 2);
//    return map;
//}

//Matrix DataLog::portfolioValues()
//{
//    Eigen::Map<RowMajorMatrix> map(&_PortfolioValues[0], _ValuesEntry, 6);
//    return map;
//}

//Matrix DataLog::portfolioState()
//{
//    Eigen::Map<RowMajorMatrix> map(&_PortfolioState[0], _StateEntry, _NumSecurity + 1);
//    return map;
//}
//#endif


//#endif
