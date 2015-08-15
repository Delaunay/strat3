SET(ABSTRACT_HEADER
    ../Abstract/Portfolio.h
    ../Abstract/Strategy.h
    ../Abstract/Portfolio.cpp
    ../Abstract/Strategy.cpp
#    ../Abstract/StrategyLog.h
#    ../Abstract/DataManager.h
)

SET(STRUCT_HEADER
    ../Struct/DataStruct.h
    ../Struct/TransactionAnswer.h
    ../Struct/TransactionWeight.h
)

SET(BACKTEST_HDS
    DynamicObject.h
    Pointer.h
    ErrorPolicy.h
)

aux_source_directory(../DataManager/ DATAMANGER_SRC)
aux_source_directory(../StrategyLog/ STRATEGYLOG_SRC)
aux_source_directory(. BACKTEST_SRC)

add_executable(backtester main.cpp
    ${BACKTEST_SRC}
    ${BACKTEST_HDS}
    ${STRUCT_HEADER}
    ${ABSTRACT_HEADER}
    ${DATAMANGER_SRC}
    ${STRATEGYLOG_SRC}
)
target_link_libraries(backtester -ldl)

