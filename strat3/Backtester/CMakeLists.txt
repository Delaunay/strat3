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
)

#aux_source_directory(../DataManager/ DATAMANGER_SRC)
aux_source_directory(../StrategyLog/ STRATEGYLOG_SRC)
aux_source_directory(. BACKTEST_SRC)

add_library(backtest_library
    ${BACKTEST_SRC}
    ${BACKTEST_HDS}
    ${ABSTRACT_HEADER}
    ${STRATEGYLOG_SRC}
)

add_executable(backtester main.cpp)

target_link_libraries(backtester backtest_library structs datamanager log)


