#ifndef STRAT3_CML_BACKTESTBUILDER_HEADER
#define STRAT3_CML_BACKTESTBUILDER_HEADER

#include "Settings.h"
#include "Log/Log.h"
#include "DataManager/Buffer.h"
#include "Backtester/Backtester.h"

#include "../Abstract/Types.h"

#include <stdexcept>

namespace strat3{

class BacktestBuilder
{
public:

    BacktestBuilder(const std::string&  file_name):
        _conf(std::move(load_settings(file_name)))
    {
    }

    void all()
    {
        build();
        run();
        report();
    }

    void build()
    {
        ADD_TRACE("Extracting Config");
        extract_backtest();
        extract_strategies();
        extract_report();

        ADD_TRACE("Initalizing");
        _bt.initialize();
    }

    void run()
    {
        ADD_TRACE("Running");
        if (_run_all)
        {
            std::cout << "Will Run :" << _bt.max_period() << "\n"
                      << "Start at :" << _bt.strat_window() << "\n";

            for(int i = 0, n = _bt.max_period(); i < n; ++i)
                _bt.run_one_step();
        }
        else
            _bt.run_one_step();
    }

    void report()
    {
        ADD_TRACE("Building Report");
    }

protected:

    const Settings& strategies_settings() const {   return _conf.get_child("Strategies"); }
    const Settings& backtest_settings  () const {   return _conf.get_child("Backtest");   }
    const Settings& report_settings    () const {   return _conf.get_child("Report");     }

    void extract_strategies()
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

    void extract_backtest()
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

    void extract_report()
    {
        const Settings& rs = report_settings();
    }


private:
    bool                   _run_all{false};
    bool                   _price_matrix_set{false};
    Backtester             _bt;
    MatrixManager          _data;
    Settings               _conf;
    std::vector<MStrategy> _strategy;
    std::vector<MPortfolio>_portfolio;
    std::vector<NodeTuple> _node;

};

}


/*
    NodeTuple for_each_strategy(Configuration::const_OptionsPair& i)
    {
        NodeTuple node;
        std::string strategy_name = i.first;
        ADD_TRACE("Reading Strategy " + strategy_name);

        Configuration::OptionsMap& strategy_option = i.second->options;

        if (strategy_option.count("strategy") == 0)
            throw std::runtime_error("No Strategy was Specified");

        Configuration* sv = strategy_option["strategy"];

        Configuration::ValuesMap& strategy_value = sv->value;

        std::string window = "";
        std::string frequency = "";
        std::string rebalanced = "";

        if (strategy_value.count("file") == 0)
            throw std::runtime_error("No Shared Library was specified");

        std::string strat_file = strategy_value["file"];

        ADD_TRACE("Reading Options");

        if (strategy_value.count("window") != 0)
            window = strategy_value["window"];

        if (strategy_value.count("frequency") != 0)
            frequency = strategy_value["frequency"];

        if (strategy_value.count("rebalanced") != 0)
            rebalanced = strategy_value["rebalanced"];

        std::string cash;
        std::string port_file;

        // use default portolio
        if (strategy_option.count("portfolio") == 0)
        {
            node.load_portfolio("./StandardPortfolio.dll");
        }
        else
        {
            ADD_TRACE("Configure Portfolio");

            sv = strategy_option["portfolio"];
            Configuration::ValuesMap& portfolio_value = sv->value;

            if (portfolio_value.count("file") == 0)
                throw std::runtime_error("No Shared Library was specified");

            port_file = portfolio_value["file"];

            if (portfolio_value.count("cash") != 0)
                cash = portfolio_value["cash"];
        }

//        ADD_TRACE("Loading DLL");
//        node.load_portfolio(port_file);
//        node.load_strategy(strat_file);

//        node.strategy()->title = strategy_name;
//        std::cout << node.strategy()->title << std::endl;

        return node;
    }

    void add_strategy()
    {
        ADD_TRACE("Reading Strategy Configuration");

        if (conf().options.count("Strategies") == 0)
            throw std::runtime_error("No Strategies were Specified");

        const Configuration& sc = strategies_conf();

        for(Configuration::const_OptionsPair& i:sc.options) //
        {
            _strat.push_back(std::move(for_each_strategy(i)));
            ADD_TRACE("LOOP END");
        }

        ADD_TRACE("ConfigReading Over");
        return ;
    }

    void conf_backtest()
    {
        if (conf().options.count("Backtest") == 0)
            throw std::runtime_error("No Backtest was Specified");


    }*/

#endif
