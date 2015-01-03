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
