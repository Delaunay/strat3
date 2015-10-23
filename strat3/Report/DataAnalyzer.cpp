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


void DataAnalyzer::dump(Eigen::IOFormat& date_fmt, bool js)
{
    ADD_TRACE("Dumping Statistics");
    std::fstream file;
    Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols);
    std::string header;
    std::string sec_header;
    Matrix temp, data = assets(), time;
    int offset = 1;

    for (auto& i:strategy_names())
        header += i + " ";

    for (auto& i:security_names())
        sec_header += i + " ";

    // Generate Time matrix
    time = Matrix::Zero(data.rows(), 1);
    for(int i = 0; i < data.rows(); ++i)
        time(i, 0)= i;
    // end

    std::string ext = ".txt";
    std::string js_head = "";

    if (js)
    {
        ext = ".js";
        js_head = "//";

        file << "var strategy_names = [";

        for (auto& i:strategy_names())
            file << i + ", ";

        file << "];\n";


        file << "var security_names = [";

        for (auto& i:security_names())
            file << i + ", ";

        file << "];\n";
    }


    // Dump Assets
    // ===============

    temp = Matrix::Zero(data.rows(), data.cols() + offset);
    temp.leftCols(offset) = time;
    temp.rightCols(data.cols()) = data;

    if (!has_dates()){
        file.open("../assets" + ext, std::ios::out);
        file << "#time " << header << "\n" << temp.format(fmt);
        file.close();
    }
    else{
        file.open("../assets" + ext, std::ios::out);
        file << "#Year Month Day " << header << "\n";
        vwrite_temp(file, dates(), temp.rightCols(temp.cols() - 1), date_fmt);
        file.close();
    }

    // Dump Hpr
    // ===============

    data = hpr();
    temp = Matrix::Zero(data.rows(), data.cols() + offset);
    temp.leftCols(offset) = time;
    temp.rightCols(data.cols()) = data;

    if (!has_dates()){
        file.open("../hpr" + ext, std::ios::out);
        file << "#time " << header << "\n" <<  temp.format(fmt);
        file.close();
    }
    else{
        file.open("../hpr" + ext, std::ios::out);
        file << "#Year Month Day " << header << "\n";
        vwrite_temp(file, dates(), temp.rightCols(temp.cols() - 1), date_fmt);
        file.close();
    }

    // Dump Drawdown
    // ===============

    data = drawdown();
    temp = Matrix::Zero(data.rows(), data.cols() + offset);
    temp.leftCols(offset) = time;
    temp.rightCols(data.cols()) = data;

    if (!has_dates()){
        file.open("../drawdown" + ext, std::ios::out);
        file << "#time " << header << "\n" << temp.format(fmt);
        file.close();
    }
    else{
        file.open("../drawdown" + ext, std::ios::out);
        file << "#Year Month Day " << header << "\n";
        vwrite_temp(file, dates(), temp.rightCols(temp.cols() - 1), date_fmt);
        file.close();
    }

    // Dump Returns
    // ===============

    data = returns();
    temp = Matrix::Zero(data.rows(), data.cols() + offset);
    temp.leftCols(offset) = time.bottomRows(data.rows());
    temp.rightCols(data.cols()) = data;

    if (!has_dates()){
        file.open("../returns" + ext, std::ios::out);
        file << "#time " << header << "\n" << temp.format(fmt);
        file.close();
    }
    else{
        file.open("../returns" + ext, std::ios::out);
        file << "#Year Month Day " << header << "\n";
        vwrite_temp(file, dates().bottomRows(dates().rows() - 1), temp.rightCols(temp.cols() - 1), date_fmt);
        file.close();
    }


    // Dump Mov Stdev
    // ===============

    data = mov_stdev();
    temp = Matrix::Zero(data.rows(), data.cols() + offset);
    temp.leftCols(offset) = time.bottomRows(data.rows());
    temp.rightCols(data.cols()) = data;

    if (!has_dates()){
        file.open("../mov_stdev" + ext, std::ios::out);
        file << "#time " << header << "\n" << temp.format(fmt);
        file.close();
    }
    else{
        file.open("../mov_stdev" + ext, std::ios::out);
        file << "#Year Month Day " << header << "\n";
        vwrite_temp(file, dates().bottomRows(dates().rows() - 1), temp.rightCols(temp.cols() - 1), date_fmt);
        file.close();
    }

    // Dump Normalized Transaction Order
    // =================================
    for (auto& i:strategy_names())
    {
        file.open("../" + i + "_toNormalized" + ext, std::ios::out);

        if (!has_dates()){
            auto share = log.get_share<ArrayRM>(i);
            auto state = log.get_holdings<ArrayRM>(i);
            int n = share.rows();
            Array ar = share.bottomRows(n - 1) / (Array::Ones(n - 1, 1) * state.row(0));

            file << "#time " << log.header_string() << "\n"
                 << ar;
        }
        else{
            // auto share = log.get_share<ArrayRM>(i);
            auto state = log.get_holdings<ArrayRM>(i);
            int n = state.rows();

            Array ar = Array::Zero(n - 1, state.cols());

            for(int i = 0; i < n - 1; ++i)
                ar.row(i) = state.row(i + 1) / state.row(0);

            file << "#" << "Year Month Day " << log.header_string() << "\n";
            vwrite_temp(file, dates().bottomRows(dates().rows() - 1),
                              ar.rightCols(ar.cols() - 1) - 1, date_fmt);
        }
        file.close();
    }

    // Dump ret distri
    // ===============

    file.open("../ret_distri" + ext, std::ios::out);
    file << "#min   max  " << header << "\n" << return_distri().format(fmt);
    file.close();

    // Dump Statistc Points
    // ====================

    file.open("../statistics" + ext, std::ios::out);

    file << "#name     "  << header       << "\n"
            "means     "  << means()      << "\n"
            "pos_means "  << pos_means()  << "\n"
            "neg_means "  << neg_means()  << "\n"
            "stdev     "  << stdev()      << "\n"
            "pos_stdev "  << pos_stdev()  << "\n"
            "neg_stdev "  << neg_stdev()  << "\n"
            "variance  "  << variance()   << "\n"
            "kurtosis  "  << kurtosis()   << "\n"
            "skewness  "  << skewness()   << "\n"
            "vol_mean  "  << vol_mean()   << "\n"
            "vol_stdev "  << vol_stdev()  << "\n"
            "count     "  << count()      << "\n"
            "pos_count "  << pos_count()  << "\n"
            "neg_count "  << neg_count()  << "\n";

    file.close();

    // Dump Transaction Order
    // ======================

    for(const std::string& el:strategy_names())
    {
        file.open(std::string("../to_statistics" + el + ".txt").c_str(), std::ios::out);

        file <<  "#name        " << sec_header << "\n"
                 "to_mean      " << log.get_matrix<Matrix>(el, "to_mean",      1, n_sec) << "\n"
                 "to_count     " << log.get_matrix<Matrix>(el, "to_count",     1, n_sec) << "\n"
                 "to_stdev     " << log.get_matrix<Matrix>(el, "to_stdev",     1, n_sec) << "\n"
                 "to_pos_mean  " << log.get_matrix<Matrix>(el, "to_pos_mean",  1, n_sec) << "\n"
                 "to_neg_mean  " << log.get_matrix<Matrix>(el, "to_neg_mean",  1, n_sec) << "\n"
                 "to_pos_count " << log.get_matrix<Matrix>(el, "to_pos_count", 1, n_sec) << "\n"
                 "to_neg_count " << log.get_matrix<Matrix>(el, "to_neg_count", 1, n_sec) << "\n";

        file.close();
    }
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

    Array max_row = hpr().row(0);
    uint j = 0;

    for(int i = 1; i < days; ++i){
        j = i - 1;
        // HPR
        hpr().row(i) = hpr().row(j) + daily_returns.row(j);

        max_row = hpr().array().row(i).max(max_row);

        // Drawdown
        drawdown().row(i) = hpr().array().row(i) - max_row;

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

    // Volatility Stats
    // ===================
    compute_volatility_stats();

    // Transaction Order
    // ===================
    compute_transaction_order_statistics();
}

void DataAnalyzer::compute_volatility_stats()
{
    allocate(df, "vol_mean",  n_strat);
    allocate(df, "vol_stdev", n_strat);

    SimpleMeanVarianceVisitor vmv(n_strat);
    mov_stdev().visit(vmv);

    vol_mean() = vmv.get_means();
    vol_stdev() = vmv.get_sd();
}

void DataAnalyzer::compute_return_distribution()
{
    allocate(df, "return_distri"  ,  (n_strat + 2) * ((uint) sqrt(returns().rows())));

    return_distri() = frequency(returns(), (uint) sqrt(returns().rows()) , true);
}

void DataAnalyzer::compute_point_statistics()
{
    allocate(df, "means",           n_strat);
    allocate(df, "count",           n_strat);
    allocate(df, "stdev",           n_strat);
    allocate(df, "neg_means",       n_strat);
    allocate(df, "neg_stdev",       n_strat);
    allocate(df, "neg_count",       n_strat);
    allocate(df, "pos_count",       n_strat);
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

    count()     = vmv.usual.get_count();
    pos_count() = vmv.positive.get_count();
    neg_count() = vmv.negative.get_count();

    allocate(df, "kurtosis",        n_strat);
    allocate(df, "skewness",        n_strat);

    SkewKurtosisVisitor vsk(means(), stdev());
    returns().visit(vsk);

    kurtosis() = vsk.get_kurtosis();
    skewness() = vsk.get_skew();
}

void DataAnalyzer::compute_transaction_order_statistics()
{
    for(const std::string& el:strategy_names())
    {
        // Get Strategy DataFrame
        DataFrame& sdf = log.df(el);

        allocate(sdf, "to_mean",        n_sec);
        allocate(sdf, "to_count",       n_sec);
        allocate(sdf, "to_stdev",       n_sec);
        allocate(sdf, "to_pos_mean",    n_sec);
        allocate(sdf, "to_neg_mean",    n_sec);
        allocate(sdf, "to_pos_count",   n_sec);
        allocate(sdf, "to_neg_count",   n_sec);

        MatrixRMMap to = log.get_share<MatrixRowMajor>(el);

        MeanVarianceVisitor vmv(n_sec);
        to.rightCols(to.cols() - 1).visit(vmv);

        log.get_matrix<Matrix>(el, "to_mean",      1, n_sec) = vmv.usual.get_means().transpose();
        log.get_matrix<Matrix>(el, "to_count",     1, n_sec) = vmv.usual.get_count().transpose();
        log.get_matrix<Matrix>(el, "to_stdev",     1, n_sec) = vmv.usual.get_sd().transpose();
        log.get_matrix<Matrix>(el, "to_pos_mean",  1, n_sec) = vmv.positive.get_means().transpose();
        log.get_matrix<Matrix>(el, "to_neg_mean",  1, n_sec) = vmv.negative.get_means().transpose();
        log.get_matrix<Matrix>(el, "to_pos_count", 1, n_sec) = vmv.positive.get_count().transpose();
        log.get_matrix<Matrix>(el, "to_neg_count", 1, n_sec) = vmv.negative.get_count().transpose();
    }
}

}
