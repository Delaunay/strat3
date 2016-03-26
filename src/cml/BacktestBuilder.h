#ifndef STRAT3_CML_BACKTESTBUILDER_HEADER
#define STRAT3_CML_BACKTESTBUILDER_HEADER

#include "../Abstract/Types.h"

#include "Settings.h"
#include "Log/Log.h"
#include "DataManager/Buffer.h"
#include "Backtester/Backtester.h"

#include <stdexcept>

namespace strat3{

class BacktestBuilder
{
public:

    BacktestBuilder(const std::string&  file_name):
        _conf(std::move(load_settings(file_name)))
    {}

    // add interface enabling Setting modification

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

    void extract_strategies();

    void extract_backtest();

    void extract_report();

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

#endif
