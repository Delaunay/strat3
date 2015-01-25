#include "Report.h"


void DataAnalyser::generate_javascript_data()
{
    std::fstream file;
    file.open((Key("../gen/js/graph_data.js")).c_str(), std::ios::out);


    Eigen::IOFormat jsformat(4, Eigen::DontAlignCols, ",", ",\n", "[", "]", "", "");
    Matrix cont = Matrix::Zero(_Data->max_period(), 2);

    time_t t = time(0);
    tm* bt;
    bt = localtime(&t);

    // the problem with ctime is the fucking null-character
    file << "var generation_time = \"" << get_week(bt->tm_wday) << " "
                                       << get_month(bt->tm_mon)  << " "
                                       << bt->tm_mday << " "
                                       << bt->tm_hour << ":"
                                       << bt->tm_min  << ":"
                                       << bt->tm_sec  << " "
                                       << bt->tm_year + 1900<<"\";";

    file << "var point_header  = [\"stat\",";

    for (int i = 0; i < _Data->size(); i++)
    {
        if (i < _Data->size() - 1)
            file << "\"" << _Data->getStrategy(i)->title() << "\"" << ",";
        else
            file << "\"" << _Data->getStrategy(i)->title() << "\"" << "\n";
    }

    file << "];";

    /*************************************************
    *           Curve
    *************************************************/
    // Cumulative ret
    file << "var cumul_ret = [";
    for (int i = 0; i < _Data->size(); i++)
    {
        cont.col(0) = _PathAnalysis[i].col(Time);
        cont.col(1) = _PathAnalysis[i].col(Cumulative);
        file << "[" << cont.format(jsformat) << "],";
    }
    file << "];";
    // Daily ret
    file << "var period_ret = [";
    for (int i = 0; i < _Data->size(); i++)
    {
        cont.col(0) = _PathAnalysis[i].col(Time);
        cont.col(1) = _PathAnalysis[i].col(Periodically);
        file << "[" << cont.format(jsformat) << "],";
    }
    file << "];";

    // Drawdown
    file << "var draw_ret = [";
    for (int i = 0; i < _Data->size(); i++)
    {
        cont.col(0) = _PathAnalysis[i].col(Time);
        cont.col(1) = _PathAnalysis[i].col(Drawdown);
        file << "[" << cont.format(jsformat) << "],";
    }
    file << "];";

    // Volatility
    file << "var mv_vol = [";
    for (int i = 0; i < _Data->size(); i++)
    {
        cont.col(0) = _PathAnalysis[i].col(Time);
        cont.col(1) = _MovingSD.col(i);
        file << "[" << cont.format(jsformat) << "],";
    }
    file << "];";

    /*************************************************
    *           Histogram
    *************************************************/
    // ret Density
    cont = Matrix::Zero(_ReturnFrequency.rows(), 2);
    file << "var frequency_ret = [";
    for (int i = 0; i < _Data->size(); i++)
    {
        cont.col(0) = (_ReturnFrequency.col(0) + _ReturnFrequency.col(1))/2; // lower bound
        cont.col(1) = _ReturnFrequency.col(i + 2);
        file << "[" << cont.format(jsformat) << "],";
    }
    file << "];";


    // positive Density
    file << "var freq_positive = [";
    for (int i = 0; i < _Data->size(); i++)
    {
        cont = _PositiveFreq[i].rightCols(2);
        cont.col(0) = (_PositiveFreq[i].col(0) + _PositiveFreq[i].col(1))/2.0;
        cont.col(1) = _PositiveFreq[i].col(2);
        file << "[" << cont.format(jsformat) << "],";
    }
    file << "];";

    // Negative Density
    file << "var freq_negative = [";
    for (int i = 0; i < _Data->size(); i++)
    {
        cont = - _NegativeFreq[i].rightCols(2);
        cont.col(0) = (_NegativeFreq[i].col(0) + _NegativeFreq[i].col(1))/2.0;
        cont.col(1) = _NegativeFreq[i].col(2);
        file << "[" << cont.format(jsformat) << "],";
    }
    file << "];";

        // Staked Curve
            // Holdings

        // Transaction frequencies

    //std::cout << sort(_PathAnalysis[0]) << std::endl;



    file.close();

}


Key DataAnalyser::getFieldAsString(int i)
{
    switch(i)
    {
    case Mean:
        return "Mean";
    case Variance:
        return "Variance";
    case SD:
        return "Sd";
    case Skew:
        return "Skew";
    case Kurtosis:
        return "Kurtosis";
    case Positive:
        return "Positive";
    case Negative:
        return "Negative";
    case MeanPositive:
        return "MeanPositive";
    case MeanNegative:
        return "MeanNegative";
    case SDPositive:
        return "SDPositive";
    case SDNegative:
        return "SDNegative";
    }
}

double negative_unary(double x)
{
    return -x;
}


void DataAnalyser::gpTimeSecData()
{
    //==================================
    //      Configuration
    //==================================

    Eigen::IOFormat gpformat(4, Eigen::DontAlignCols, ",", "\n", "", "", "", "");
    std::fstream file;

    int m      = _Data->getLog(0)->securityNumber();   // number of securities
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

    Matrix temp = Matrix::Zero(end, m + offset);

    // set dates
    if (!dates)
        temp.leftCols(offset) = date.bottomRows(end);
    else
        temp.leftCols(offset) = date.block(_Data->stratWindow(), 0, end, offset);

    // generate the header
    for (int i = 0; i < m; i++)
    {
        if (i < security_size() - 1)
            header += "Sec" + std::to_string(i) + ",";
        else
            header += "Sec" + std::to_string(i) + "\n";
    }

    //==================================
    //      Holding Evol
    //==================================

    for(int k  = 0; k < n; k++)
    {
        temp.block(0, offset, end, m) = _HoldingsEvolution[k];

        // OUT
        file.open("../gen/data/" + _Data->getStrategy(k)->title() + "_holding_evol.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();
    }

    //==================================
    //      Holding Variations
    //==================================

    for(int i = 0; i < m; i ++)
        temp(0, i + offset) = 0;

    for(int k  = 0; k < n; k++)
    {
        temp.block(1, offset, end - 1, m) = _HoldingsVariation[k];

        // OUT
        file.open("../gen/data/" + _Data->getStrategy(k)->title() + "_holding_var.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();
    }

    //==================================
    //      Target Weights
    //==================================

    for(int k  = 0; k < n; k++)
    {
        temp.block(0, offset, end, m) = _Data->getLog(k)->weightMatrix().rightCols(m);

        // OUT
        file.open("../gen/data/" + _Data->getStrategy(k)->title() + "_weight_target.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();
    }

    //==================================
    //      Portfolio Values
    //==================================

    temp = Matrix::Zero(end, 3 + offset);

    if (dates)
    {
        header = "#year,month,days,liabilities,equity,asset\n";
        temp.leftCols(offset) = date.block(_Data->stratWindow(), 0, end, offset);
    }
    else
    {
        header = "#time,liabilities,equity,asset\n";
        temp.leftCols(offset) = date.bottomRows(end);
    }

    for(int k  = 0; k < n; k++)
    {
        temp.col(offset)     = - _Data->getLog(k)->portfolioValues().col(DataLog::Liabilities);
        temp.col(offset + 1) = /*temp.col(offset) +*/ _Data->getLog(k)->portfolioValues().col(DataLog::Equity);
        temp.col(offset + 2) = _Data->getLog(k)->portfolioValues().col(DataLog::Asset);

        // OUT
        file.open("../gen/data/" + _Data->getStrategy(k)->title() + "_values.dat", std::ios::out);

        file << header;

        file << temp.format(gpformat);

        file.close();
    }
}

