INCLUDE_DIRECTORIES(.)

# subdir
add_subdirectory(Abstract)
add_subdirectory(Struct)
add_subdirectory(Backtester)
add_subdirectory(StrategyLog)
add_subdirectory(GUI)
add_subdirectory(cml)
add_subdirectory(graphics)
add_subdirectory(default)
add_subdirectory(DataManager)
add_subdirectory(Log)
add_subdirectory(Report)
add_subdirectory(network)


# I should copy Struct and Abstract source files into a public header
SET(STRUCT_SRC
    Struct/DataStruct.h
    Struct/DataStruct.cpp
    Struct/TransactionAnswer.h
    Struct/TransactionWeight.h
    Struct/TransactionWeight.cpp
)
