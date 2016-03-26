SET(ABSTRACT_HEADER
    ../Abstract/Portfolio.h
    ../Abstract/Strategy.h
    ../Abstract/Portfolio.cpp
    ../Abstract/Strategy.cpp
#    ../Abstract/SinglePortfolio.h
#    ../Abstract/SinglePortfolio.cpp
#    ../Abstract/StrategyLog.h
#    ../Abstract/DataManager.h
)

SET(BACKTEST_HDS
    DynamicObject.h
    Pointer.h
    ErrorPolicy.h
    ../Report/visitor.h
)

#aux_source_directory(../DataManager/ DATAMANGER_SRC)
aux_source_directory(../StrategyLog/ STRATEGYLOG_SRC)
aux_source_directory(. BACKTEST_SRC)
aux_source_directory(../Report/ REPORT_SRC)

add_library(backtest_library
    ${BACKTEST_SRC}
    ${BACKTEST_HDS}
    ${ABSTRACT_HEADER}
    ${STRATEGYLOG_SRC}
    ${REPORT_SRC}
)
SET_PROPERTY(TARGET backtest_library PROPERTY CXX_STANDARD 11)

add_executable(backtester main.cpp)
SET_PROPERTY(TARGET backtester PROPERTY CXX_STANDARD 11)

target_link_libraries(backtester backtest_library structs datamanager log ${SYSTEM_LIB})





