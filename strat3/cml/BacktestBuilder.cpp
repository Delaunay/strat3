#include "BacktestBuilder.h"

namespace strat3{

void BacktestBuilder::extract_report()
{
    const Settings& rs = report_settings();
}

void BacktestBuilder::extract_strategies()
{
    const Settings& ss = strategies_settings();

    for(Settings::const_iterator i = ss.begin(); i != ss.end(); ++i)
    {
        std::string strategy_name = (*i).first;
        const Settings& strategy_settings = (*i).second;
        // strat class
        const Settings& strat_sett = strategy_settings.get_child("strategy");

        boost::optional<int>  window = strat_sett.get_optional<int>("window");
        boost::optional<int>  freque = strat_sett.get_optional<int>("frequency");
        boost::optional<bool> rebala = strat_sett.get_optional<bool>("rebalanced");
        std::string            sfile = strat_sett.get<std::string>("file");

        // portfolio class
        const Settings& port_sett = strategy_settings.get_child("portfolio");

        std::string             pfile = port_sett.get<std::string>("file");
        boost::optional<double>  cash = strat_sett.get_optional<double>("cash");


        ADD_TRACE("ADD Strategy \"" + strategy_name + "\" from \"" + sfile + "\"");
        MStrategy* s = new MStrategy(sfile);

        THROW((*s)->get_type() != strat3::STRATEGY_TYPE, std::runtime_error, "WRONG Strategy Type");
        (*s)->title = strategy_name;

        if (freque.is_initialized())
            (*s)->frequency = freque.get();

        if (window.is_initialized())
            (*s)->strategy_window = window.get();

        if(rebala.is_initialized())
            (*s)->rebalanced = rebala.get();

        (*s)->initialize(_bt.security_number());

        ADD_TRACE("ADD Portfolio from \"" + pfile + "\"");
        MPortfolio* p = new MPortfolio(pfile);

        THROW((*p)->get_type() != strat3::PORTFOLIO_TYPE, std::runtime_error, "WRONG Portfolio Type");

        if (cash.is_initialized())
            (*p)->initialize(cash.get(), _bt.security_number());
        else
            (*p)->initialize(1000.0, _bt.security_number());

        _node.push_back(NodeTuple());
        NodeTuple& nt = _node[_node.size() - 1];

        nt._portfolio = p;
        nt._strat = s;

        _bt.add_strategy(&nt);
    }
}

void BacktestBuilder::extract_backtest()
{
    const Settings& bs = backtest_settings();

    // Extract data information
    const Settings& data_set = bs.get_child("data");

    // Read all matrices
    for(Settings::const_iterator i = data_set.begin(); i != data_set.end(); ++i)
    {
        std::string  matrix_name = (*i).first;
        const Settings& data_set = (*i).second;

        boost::optional<std::string> type = data_set.get_optional<std::string>("type");
        std::string mfile = data_set.get<std::string>("file");

        ADD_TRACE("ADD MATRIX \"" + matrix_name + "\" from \"" + mfile + "\"");
        CSVReader csv_dat(mfile);
        Matrix m = csv_dat.get_eigen3<MatrixRowMajor>();
        _data.add_matrix(matrix_name, std::move(m));

        boost::optional<bool> is_price_matrix = data_set.get_optional<bool>("price_matrix");

        if (is_price_matrix.is_initialized())
        {
            if (is_price_matrix.get() == true)
            {
                _bt.set_data_manager(&_data, matrix_name);
                ADD_TRACE("Price Matrix Was Added");
                _price_matrix_set = true;
            }
        }
    }
    // Backtest option
    std::string run_opt = bs.get<std::string>("run");

    if (run_opt == "all")
        _run_all = true;

    THROW(!_price_matrix_set, std::runtime_error, "No Prices were Given");
}
}
