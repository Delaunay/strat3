#ifndef STRAT3_REPORT_REPORT_HEADER
#define STRAT3_REPORT_REPORT_HEADER

#include <ctime>

#include "Statistics.h"
#include "../DataLog/DataLog.h"
#include "../Strategy/Strategy.h"
#include "../Tester.h"
#include "../smath.h"

#include "../Security/Securities.h"

#include "script.h"

#include "../debug.h"

#define STRAT3_DEBUG_REP 0

class Tester;


/*!
 * Analyse generated data after the backtest is over
 */
class DataAnalyser
{
public:

    enum Field
    {
        Mean         = 0,
        Variance     ,
        SD           ,
        Skew         ,
        Kurtosis     ,
        Positive     ,
        Negative     ,
        MeanPositive ,
        MeanNegative ,
        SDPositive   ,
        SDNegative,
        FieldMax,
        Var = Variance,

    };

    enum PathField
    {
        Time = 0,
        RawValue,
        Cumulative,
        Periodically,
        Drawdown,
        PathFieldMax
    };

    DataAnalyser(Tester* data):
        _Data(data)
    {
        _Format = Eigen::IOFormat(4, Eigen::DontAlignCols, ",", "\n", "", "", "", "");
    }


    void create_matrix()
    {
#if STRAT3_DEBUG_REP
        DEBUG_IDX_INIT;
        DEBUG_IDX_PRINT;    // 0
#endif

        int n   = _Data->size();
        int m   = _Data->getLog(0)->securityNumber();
        int end = _Data->max_period();

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 1
#endif

        // initialization
        _EquityPath = Matrix::Zero(end, n);
        _PathAnalysis = std::vector<Matrix>(n);
        _NegativeRet  = std::vector<std::vector<double> >(n);
        _PositiveRet  = std::vector<std::vector<double> >(n);

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 2
#endif

        //  Get portfolio values
        for(int i = 0; i < n; i++)
        {
            // generate the matrix with all portfolio value side by side
            _EquityPath.col(i) =_Data->getLog(i)->portfolioValues().col(DataLog::Invested);
            double cash        = _EquityPath(0, i);

            // setup
            _PathAnalysis[i]                 = Matrix::Zero(end, PathFieldMax);
            _PathAnalysis[i].col(Time)       = _Data->getLog(i)->portfolioValues().col(DataLog::Time);
            _PathAnalysis[i].col(RawValue)   = _EquityPath.col(i);
            _PathAnalysis[i].col(Cumulative) = (_EquityPath.col(i)/cash).unaryExpr(std::ptr_fun(log_double));
        }

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 3
#endif

        // compute periodic return
        _EquityRet    = compute_returns(_EquityPath);

        // compute path related statistics
        // Drawdown
        for(int i = 0; i < n; i++)
        {
            _PathAnalysis[i](0, Periodically) = 0;
            _PathAnalysis[i].col(Periodically).middleRows(1, end - 1) = _EquityRet.col(i);

            double max = 0;
            for (int j = 0; j < end; j++)
            {
                max = std::max(max, _PathAnalysis[i](j, Cumulative));
                _PathAnalysis[i](j, Drawdown) = _PathAnalysis[i](j, Cumulative) - max;
            }
        }

        // compute statistic point
        StatisticPoint md(n);
        _EquityRet.visit(md);

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 4
#endif

        _StatisticPoint = Matrix::Zero(FieldMax, n);

        _StatisticPoint.row(Mean        ) = md.usual.getAllMean();
        _StatisticPoint.row(Var         ) = md.usual.getAllVariance();
        _StatisticPoint.row(SD          ) = md.usual.getAllSD();

        _StatisticPoint.row(Positive    ) = get_matrix(md.positive.element).cast<double>();
        _StatisticPoint.row(Negative    ) = get_matrix(md.negative.element).cast<double>();
        _StatisticPoint.row(MeanPositive) = md.positive.getAllMean();
        _StatisticPoint.row(MeanNegative) = md.negative.getAllMean();
        _StatisticPoint.row(SDPositive  ) = md.positive.getAllSD();
        _StatisticPoint.row(SDNegative  ) = md.negative.getAllSD();

        SkewKurtosis sk(_StatisticPoint.row(Mean), _StatisticPoint.row(SD));
        _EquityRet.visit(sk);

        _StatisticPoint.row(Skew        ) = sk.getSkew();
        _StatisticPoint.row(Kurtosis    ) = sk.getKurtosis();

        // compute frequency
        _ReturnFrequency = frequency(_EquityRet);

        // compute moving standard deviation using visitor
        _MovingSD = _EquityPath;
        _MovingSD.fill(0);

        MovingStandardDeviation msd(20, _EquityRet.cols(), &_MovingSD);
        _EquityRet.visit(msd);

        StatisticPoint msdstat(n);
        _MovingSD.visit(msdstat);
        _MovingSDStat = Matrix::Zero(FieldMax, n);
        _MovingSDStat.row(Mean        ) = msdstat.usual.getAllMean();
        _MovingSDStat.row(Var         ) = msdstat.usual.getAllVariance();
        _MovingSDStat.row(SD          ) = msdstat.usual.getAllSD();
        _MovingSDStat.row(Positive    ) = get_matrix(msdstat.positive.element).cast<double>();

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 5
#endif
//        _NegativeRet = std::vector<std::vector<double> >(n); //= Matrix::Zero(md.negative.element);
//        _PositiveRet = std::vector<std::vector<double> >(n); //= Matrix::Zero();

        for (int i = 0; i < n; i++)
        {
            Matrix holdtemp = _Data->getLog(i)->readTransactionOrder().rightCols(m).bottomRows(end - 1);

            StatisticPoint holdstat(m);
            holdtemp.visit(holdstat);

            _HoldStat.push_back(Matrix::Zero(FieldMax, m));
            _HoldStat[i].row(Mean) = holdstat.usual.getAllMean();
            _HoldStat[i].row(SD)   = holdstat.usual.getAllSD();
            _HoldStat[i].row(MeanPositive) = holdstat.positive.getAllMean();
            _HoldStat[i].row(MeanNegative) = holdstat.negative.getAllMean();
            _HoldStat[i].row(Positive) = get_matrix(holdstat.positive.element).cast<double>();
            _HoldStat[i].row(Negative) = get_matrix(holdstat.negative.element).cast<double>();
        }

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 6

        DEBUG_PRINT("n   ", n);
        DEBUG_PRINT("end ", end);
#endif


        for(int i = 0; i < n; i++)
        {
            for (int l = 0; l < end; l++)
            {
#if STRAT3_DEBUG_REP
           //     DEBUG_LOOP(l, i);
#endif

                if (_PathAnalysis[i](l, Periodically) < 0)
                    _NegativeRet[i].push_back(_PathAnalysis[i](l, Periodically));

                else if (_PathAnalysis[i](l, Periodically) > 0)
                    _PositiveRet[i].push_back(_PathAnalysis[i](l, Periodically));
            }

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 7
#endif
            _NegativeFreq.push_back(frequency(Eigen::Map<Matrix>(&_NegativeRet[i][0], _NegativeRet[i].size(), 1),
                                    sqrt(_NegativeRet[i].size()), true));
#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 8
#endif

            _PositiveFreq.push_back(frequency(Eigen::Map<Matrix>(&_PositiveRet[i][0], _PositiveRet[i].size(), 1),
                                    sqrt(_PositiveRet[i].size()), true));
        }

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 9
#endif

        for(int i = 0; i < n; i++)
        {
            Matrix logthing = _Data->getLog(i)->portfolioState().block(0, 1, end, m).unaryExpr(std::ptr_fun(log_double));
            logthing = logthing.cast<double>();

            for(int j = 0; j < m; j++)
                logthing.col(j) = logthing.col(j) - logthing(0, j) * Matrix::Ones(rows_time(), 1);

            _HoldingsEvolution.push_back(logthing);
            _HoldingsVariation.push_back(logthing.middleRows(1, end - 1) - logthing.middleRows(0, end - 1));

        }

#if STRAT3_DEBUG_REP
        DEBUG_IDX_PRINT;    // 3
#endif
    }

    Index size()    {   return _Data->size(); }
    Key strategyName(Index k)  {    return _Data->getStrategy(k)->title(); }

    static Key getFieldAsString(int i);


    /*!
     * \brief generate data that are not in function of time
     */
    void gpDistributionData()
    {
#if 0
        DEBUG_IDX_INIT;
        DEBUG_IDX_PRINT;    // 0
#endif

        // init
        Eigen::IOFormat gpformat(4, Eigen::DontAlignCols, ",", "\n", "", "", "", "");
        std::fstream file;
        int n      = _Data->size();
        Key header("#ret,");
        Matrix temp = Matrix::Zero(_ReturnFrequency.rows(), n + 1);

        //========================
        // Overall
        //========================

        // histogram middle
        temp.col(0) =(_ReturnFrequency.col(0) + _ReturnFrequency.col(1))/2.0;

        for (int i = 0; i < _Data->size(); i++)
        {
            // set frequency side by side
            temp.col(i + 1) = _ReturnFrequency.col(i + 2);

            // generate the header
            if (i < _Data->size() - 1)
                header += _Data->getStrategy(i)->title() + ",";
            else
                header += _Data->getStrategy(i)->title() + "\n";
        }

        // OUT
        file.open("../gen/data/distri_ret.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();

        //========================
        // LOSS
        //========================
        header = "#";

        // the number of bin change for each strategy
        // we need to find which one has the ost bin
        int max = 0;
        for (int i = 0; i < n; i++)
            max = std::max(max, _NegativeFreq[i].rows());

        temp = Matrix::Zero(max, _EquityPath.cols() * 2);
#if 0
        DEBUG_IDX_PRINT;    // 1
#endif
        for (int i = 0; i < n; i++)
        {
            // prevent crash if no postive return were recorded
            if ((_NegativeFreq[i].rows() != 0) || (_NegativeFreq[i].cols() != 0))
            {
                // set frequency and bin
                temp.block(0, 2 * i, _NegativeFreq[i].rows(), 1) = (_NegativeFreq[i].col(0) + _NegativeFreq[i].col(1))/2.0;
                temp.block(0, 2 * i + 1, _NegativeFreq[i].rows(), 1) =_NegativeFreq[i].col(2);

                // generate the header that will be used twice
                if (i < n - 1)
                    header += "ret, " + _Data->getStrategy(i)->title() + ",";
                else
                    header += "ret, " + _Data->getStrategy(i)->title() + "\n";
            }
        }
#if 0
        DEBUG_IDX_PRINT;    // 2
#endif

        // OUT
        file.open("../gen/data/loss_distri_ret.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();

        //========================
        // GAIN
        //========================

        max = 0;
        for (int i = 0; i < n; i++)
            max = std::max(max, _PositiveFreq[i].rows());

        temp = Matrix::Zero(max, _EquityPath.cols() * 2);

        for (int i = 0; i < n; i++)
        {
            // prevent crash if no postive return were recorded
            if ((_PositiveFreq[i].rows() != 0) || (_PositiveFreq[i].cols() != 0))
            {
                temp.block(0, 2 * i, _PositiveFreq[i].rows(), 1) =(_PositiveFreq[i].col(0) + _PositiveFreq[i].col(1))/2.0;
                temp.block(0, 2 * i + 1, _PositiveFreq[i].rows(), 1) =_PositiveFreq[i].col(2);
            }
        }

        // OUT
        file.open("../gen/data/gain_distri_ret.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();
    }

    /*!
     * \brief generate data which has strat title as column
     */
    void gpTimeStratData()
    {
        //==================================
        //      Configuration
        //==================================

        Eigen::IOFormat gpformat(4, Eigen::DontAlignCols, ",", "\n", "", "", "", "");
        std::fstream file;

        bool dates = _Data->usingDates();
        int n      = _Data->size();                        // number of strategies
        int end    = _Data->max_period();                  // number of day passed
        int offset = 1;                                    // Number of column added
                                                           // to make place for the date
        Key header("#time,");                              // Header
        Matrix date;

        // set date related variable
        if (dates)
        {
            offset = 3; // add month and days
            header = "#year,month,days,";
            date = _Data->dates();
        }
        else
            date = _PathAnalysis[0].block(0, Time, end, 1);

        Matrix temp = Matrix::Zero(end - 1, n + offset);

        // generate header
        for (int i = 0; i < n; i++)
            if (i < n - 1)
                header += _Data->getStrategy(i)->title() + ",";
            else
                header += _Data->getStrategy(i)->title() + "\n";

        if (!dates)
        {
            temp.leftCols(offset) = date.bottomRows(end - 1);
        }
        else
            // the backtest only start after the stratWindow period
            // so the first days is stratWindow / is it end - 1 ??
            temp.leftCols(offset) = date.block(_Data->stratWindow(), 0, end - 1, offset);

        //==================================
        //      Daily Ret
        //==================================

        // set Daily returns cols
        temp.rightCols(n) = _EquityRet;

        // OUT
        file.open("../gen/data/daily_ret.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();

        //==================================
        //      Volatility
        //==================================
        // 20p windows
        // nevertheless we keep the partial result form 0-21

        temp = Matrix::Zero(_MovingSD.rows(), n + offset);

        if (!dates)
            temp.leftCols(offset) = date.bottomRows(end);
        else
            temp.leftCols(offset) = date.block(_Data->stratWindow(), 0, end, offset);

        for (int i = 0; i < n; i++)
            temp.col(i + offset) = _MovingSD.col(i) * sqrt(250.0);

        // OUT
        file.open("../gen/data/volatility_ret.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();

        //==================================
        //      HPR
        //==================================

        for (int i = 0; i < n; i++)
            temp.col(i + offset) = _PathAnalysis[i].col(Cumulative);

        // OUT
        file.open("../gen/data/hpr_ret.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();

        //==================================
        //      Drawdown
        //==================================

        for (int i =0; i < n; i++)
            temp.col(i + offset) = _PathAnalysis[i].col(Drawdown);

        // OUT
        file.open("../gen/data/drawdown_ret.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();
    }

    /*!
     * \brief generate data which has Sec title as column
     */
    void gpTimeSecData();

    void generate_gp(bool tex)
    {
        std::vector<std::string> strat(_Data->size());
        std::vector<std::string> sec(_Data->getLog(0)->securityNumber());

        for(int i = 0, n = _Data->size(); i < n; i++)
        {
            strat[i] = _Data->getStrategy(i)->title();
        }

        if (_Data->getSecurityDatabase() == 0)
            for(int i = 0, n = _Data->getLog(0)->securityNumber(); i < n; i++)
            {
                sec[i] = Key("Sec") + std::to_string(i);
            }
        else
            for(int i = 0, n = _Data->getSecurityDatabase()->size(); i < n; i++)
            {
                sec[i] = _Data->getSecurityDatabase()->ticker(i);
            }

        generate_gp_script(strat, sec, tex, _Data->usingDates());
    }

    int security_size() {   return _Data->getLog(0)->securityNumber();  }
    int rows_time()     {   return _Data->max_period();     }
    Matrix time_mat()   {   return _Data->getLog(0)->portfolioValues().col(0);  }
    Index obs()         {   return _EquityRet.rows();   }

    void generate_javascript_data();

    void save_all()
    {
        std::fstream statPoint;

        statPoint.open((Key("../gen/Strat3.StatisticPoint.csv")).c_str(), std::ios::out);


        statPoint << "stat,";

        for (int i =0; i < _Data->size(); i++)
            if (i < _Data->size() - 1)
                statPoint << _Data->getStrategy(i)->title() << ",";
            else
                statPoint << _Data->getStrategy(i)->title() << "\n";

        for (int i = 0; i < FieldMax; i++)
            statPoint << getFieldAsString(i) << "," << _StatisticPoint.row(i).format(_Format) << "\n";

        statPoint.close();

        for (int i = 0; i < _Data->size(); i++)
        {
            std::fstream pathStat;

            pathStat.open(Key(_Data->getLog(i)->name() + ".PathStatistic.csv").c_str(), std::ios::out);

            pathStat << "time,invested,cumulative,periodically,drawdown\n";

            pathStat << _PathAnalysis[i].format(_Format);

            pathStat.close();
        }
    }

//protected:

    std::vector<std::vector<double> > _NegativeRet;
    std::vector<std::vector<double> > _PositiveRet;

    std::vector<Matrix> _HoldingsVariation;
    std::vector<Matrix> _HoldingsEvolution;

    std::vector<Matrix> _NegativeFreq;
    std::vector<Matrix> _PositiveFreq;

    std::vector<Matrix> _HoldStat;
    std::vector<Matrix> _PathAnalysis;   // Strategy wise
    Matrix              _StatisticPoint; // All Strategies in one
    Matrix              _EquityPath;     // All Strategies in one

    Matrix              _MovingSD;
    Matrix              _MovingSDStat;
    Matrix              _ReturnFrequency;
    Matrix              _EquityPathLog;
    Matrix              _EquityRet;
    Tester*             _Data;
    Eigen::IOFormat     _Format;




//    DataLog*            _DataLog;
//    DataStruct*         _Data;
//    std::vector< std::vector<double> > _PointStatistic;
//    std::vector< std::vector<double> > _PathStatistic;

//    Matrix      _PointStatistic;
};






//        std::cout << md.negative.getAllMean() << "\t"
//                  << get_matrix(md.negative.element)  << "\t"
//                  << md.negative.getAllSD() << std::endl;

//        std::cout << md.positive.getAllMean() << "\t"
//                  << get_matrix(md.positive.element)  << "\t"
//                  << md.positive.getAllSD() << std::endl;

//        std::cout << md.usual.getAllMean()    << "\t"
//                  << get_matrix(md.usual.element) << "\t"
//                  << md.usual.getAllSD() << std::endl;

        //        std::cout << _EquityPath.topRows(10)      << std::endl;
        //        std::cout << _EquityPath.bottomRows(10)   << std::endl;
//std::cout << _EquityPathLog.middleRows(0, end - 1).rows() << std::endl;
//std::cout << _EquityPathLog.middleRows(1, end - 1).rows() << std::endl;
//std::cout << _EquityPath.topRows(10) << std::endl;
//std::cout << "NEW" << std::endl;
//std::cout << _EquityPathLog.middleRows(1, end - 1).topRows(10) << std::endl;
//std::cout << "OLD" << std::endl;
//std::cout << _EquityPathLog.middleRows(0, end - 1).topRows(10) << std::endl;


//        md.getAllMean();
//        std::cout << md.getMean(0) << std::endl;
//        std::cout << md.getMean(1) << std::endl;
//        std::cout << md.getAllMean()<< std::endl;
//        std::cout << md.getAllVariance()<< std::endl;
//        std::cout << md.getAllSD()<< std::endl;
//        std::cout << _EquityPath.bottomRows(10) << std::endl;
//        std::cout << _EquityPath.cols() << " " << _EquityPath.rows() << std::endl;
#endif
