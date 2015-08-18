#include "MainWindow.h"

using strat3::Backtester;

Backtester& backtest_instance()
{
    static Backtester b;
    return b;
}

MatrixManager& matrix_manager_instance()
{
    static MatrixManager mm;
    return mm;
}
