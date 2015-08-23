#include "DataAnalyzer.h"
namespace strat3{

//  ColWise Sort (must be colwise)
Matrix sort(const Matrix& x)
{
    Matrix temp = x;

    for (int j = 0, m = x.cols(); j < m; j++)
    {
        std::sort(&temp(0, j), &temp(0, j) + temp.rows());
    }

    return temp;
}

Matrix frequency(const Matrix& x, uint bucket, bool percentage)
{
    if ((x.rows() == 0) || (x.cols() == 0))
        return Matrix::Zero(1, 1);

    double min = x.minCoeff();
    double max = x.maxCoeff();

    double step = (max - min) / double(bucket);
    Matrix freq = Matrix::Zero(bucket, x.cols() + 2);

    for (uint i = 0; i < bucket; i ++)
    {
        freq(i, 0) = double(i) * step + min;          // lower bound
        freq(i, 1) = double(i + 1) * step + min;      // upper bound
    }

    // Sorting
     Matrix temp = sort(x);

//     std::cout << bucket << std::endl;

    // Counting
     for (uint k = 0, m = x.cols(); k < m; ++k)
     {
        uint j = 0; // Current Bucket

         // rows
        for (uint i = 0, n = x.rows(); i < n; ++i)
        {
             // if the current value is not in the bucket change bucket
            while(!(temp(i, k) < freq(j, 1)))
            {
                ++j;

                if (j >= bucket)
                {
                    // Consume the last value
                    freq(bucket - 1, k + 2) += 1;
                    break;
                }
            }

            if (j >= bucket)
                break;

            // increase bucket count
            freq(j, k + 2) += 1;
        }
    }

    // Normalize
    if (percentage)
        freq.block(0, 2, freq.rows(), x.cols()) = freq.block(0, 2, freq.rows(), x.cols()) / x.rows();

    return freq;
}


//for (int i = 0, n = x.rows(); i < n; i++)
//{
//    min = temp(i, j);

//    for (int k = i; k < n; k++)
//        if (min > temp(k, j))
//        {
//            buf = temp(k, j);
//            temp(k, j) = min;
//            temp(i, j) = buf;
//            min = buf;
//        }
//}

void DataAnalyzer::dump()
{
    ADD_TRACE("Dumping Statistics");
    std::fstream file;
    Eigen::IOFormat fmt;
    std::string header;

    for (auto& i:strategy_names())
        header += i;

    // Dump Assets
    // ===============

    file.open("../assets.txt", std::ios::out);
    file << header << "\n" << assets().format(fmt);
    file.close();

    // Dump Returns
    // ===============

    file.open("../returns.txt", std::ios::out);
    file << header << "\n" << returns().format(fmt);
    file.close();

    // Dump Hpr
    // ===============

    file.open("../hpr.txt", std::ios::out);
    file << header << "\n" << hpr().format(fmt);
    file.close();

    // Dump Drawdown
    // ===============

    file.open("../drawdown.txt", std::ios::out);
    file << header << "\n" << hpr().format(fmt);
    file.close();

    // Dump Mov Stdev
    // ===============

    file.open("../mov_stdev.txt", std::ios::out);
    file << header << "\n" << mov_stdev().format(fmt);
    file.close();

    // Dump ret distri
    // ===============

    file.open("../ret_distri.txt", std::ios::out);
    file << "min   max  " << header << "\n" << return_distri().format(fmt);
    file.close();

    // Dump Statistc Points
    // ====================

    file.open("../statistics.txt", std::ios::out);

    file << "          "  << header       << "\n" <<
            "means     "  << means()      << "\n" <<
            "pos_means "  << pos_means()  << "\n" <<
            "neg_means "  << neg_means()  << "\n" <<
            "stdev     "  << stdev()      << "\n" <<
            "pos_stdev "  << pos_stdev()  << "\n" <<
            "neg_stdev "  << neg_stdev()  << "\n" <<
            "variance  "  << variance()   << "\n" <<
            "kurtosis  "  << kurtosis()   << "\n" <<
            "skewness  "  << skewness()   << "\n";

    file.close();
}

void DataAnalyzer::compute_assets()
{
    reserve(df, "assets", n_strat * days);

    for(auto& el:strategy_names())
    {
        std::vector<double> &temp = log.df(el)["pv_asset"];
        std::copy(temp.begin(), temp.end(), std::back_inserter(df["assets"]));
    }
}

void DataAnalyzer::compute_returns(MatrixMap& assets)
{
    allocate(df, "returns", n_strat * (days - 1));

    returns() = (assets.bottomRows(days - 1).cwiseQuotient(assets.topRows(days - 1))).array().log();
}

void DataAnalyzer::compute_hpr(MatrixMap& daily_returns, uint window)
{
    allocate(df, "hpr"     ,     n_strat *  days);
    allocate(df, "drawdown",     n_strat *  days);
    allocate(df, "mov_stdev", n_strat * (days - 1));

    Matrix data = Matrix::Zero(window, n_strat);

    hpr().row(0).fill(0);
    drawdown().row(0).fill(0);
    uint j = 0;

    for(int i = 1; i < days; ++i){
        j = i - 1;
        // HPR
        hpr().row(i) = hpr().row(j) + daily_returns.row(j);

        // Drawdown
        drawdown().row(i) = drawdown().array().row(i).max(hpr().array().row(i));

        // Moving Standard Deviation
        data.row(j % window) = daily_returns.row(j);
        mov_stdev().row(j) = (data.cwiseProduct(data).colwise().mean().array() -
                              data.colwise().mean().array().pow(2)).array().sqrt();

    }
}

void DataAnalyzer::compute_statistics()
{
    ADD_TRACE("Compute Statistics");

    compute_assets();
    compute_returns(assets());

    // Compute - HPR
    //         - Drawdown
    //         - Moving Vol
    compute_hpr(returns());

    // Return Distribution
    // ===================
    compute_return_distribution();

    // Pos return distri
    // ===================

    // Neg return distri
    // ===================

    // Point Statistics
    // ===================
    compute_point_statistics();
}

void DataAnalyzer::compute_return_distribution()
{
    allocate(df, "return_distri"  ,  (n_strat + 2) * ((uint) sqrt(returns().rows())));

    return_distri() = frequency(returns(), (uint) sqrt(returns().rows()) , true);
}

void DataAnalyzer::compute_point_statistics()
{
    allocate(df, "means"  ,         n_strat);
    allocate(df, "stdev",           n_strat);
    allocate(df, "neg_means",       n_strat);
    allocate(df, "neg_stdev",       n_strat);
    allocate(df, "pos_means",       n_strat);
    allocate(df, "pos_stdev",       n_strat);
    allocate(df, "variance",        n_strat);

    MeanVarianceVisitor vmv(n_strat);
    returns().visit(vmv);

    means() = vmv.usual.get_means();
    variance() = vmv.usual.get_variance();
    stdev() = variance().array().sqrt();

    neg_means() = vmv.negative.get_means();
    neg_stdev() = vmv.negative.get_sd();

    pos_means() = vmv.positive.get_means();
    pos_stdev() = vmv.positive.get_sd();

    allocate(df, "kurtosis",        n_strat);
    allocate(df, "skewness",        n_strat);

    SkewKurtosisVisitor vsk(means(), stdev());
    returns().visit(vsk);

    kurtosis() = vsk.get_kurtosis();
    skewness() = vsk.get_skew();
}

}
