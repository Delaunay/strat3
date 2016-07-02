Strat3
======

Strat3 is a general backtester meant to measure performance and diagnostic strategies. It is mainly built in C++. The programming design was inspired by Agent Based models in economics. Each action are broken down into small pieces allowing maximum flexibility.

Each module can be compiled as a shared library (dll) and reloaded by the backtester
without requiring strat3 recompilation (hot reloading).

A Backtester can be configured through a json configuration file:

    {
        // define DataManager format
        Data:{
            config:{
                file: data.csv
            },
        },

        Backtest:{
            cash:10000,
            min_window:20,
        }

        Strategies:{
            EqualWeight:{
                file: strategy/equalweight.dll,

                config:{
                    predictor: None,
                    market: default,
                    log: default,
                    portfolio: default
                }
            },

            VarianceMin:{
                file: strategy/varmin.dll,

                config:{
                    predictor: HistoricalCovariance,
                    market: default,
                    log: default,
                    portfolio: default
                }
            }
        }
    }

Requirement
-----------

* gtest
* Boost (configuration file)
* gnuplot (plot drawing)
* latex (if tex report is used)


TODO
-------

* Finish the configuration parser (mostly done)
* Add a get data module
* finish market engine implementation
* Rebuild unit tests

Futures
---------

* Server/Client Backtester
    * Market engine is server side
    * FIXME: Portfolio should be server side.
* Bloomberg Module
* SQLite Module
* Strat3 GUI 'Compiler'


