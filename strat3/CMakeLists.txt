CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
PROJECT(strat3)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O1 -O2 -O3")

SET(CMAKE_RELEASE_POSTFIX "")
SET(CMAKE_DEBUG_POSTFIX "-debug")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

SET(STRAT3_VERSION_MAJOR 0)
SET(STRAT3_VERSION_MINOR 0)
SET(STRAT3_VERSION_PATCH 0)
SET(STRAT3_VERSION
    ${STRAT3_VERSION_MAJOR}.${STRAT3_VERSION_MINOR}.${STRAT3_VERSION_PATCH})

INCLUDE_DIRECTORIES(.)

add_subdirectory(Abstract)
add_subdirectory(Struct)
add_subdirectory(Backtester)
add_subdirectory(StrategyLog)
add_subdirectory(GUI)

SET(STRUCT_SRC
    Struct/DataStruct.h
    Struct/TransactionAnswer.h
    Struct/TransactionWeight.h
    Struct/TransactionWeight.cpp
)

add_library(StandardStrategy SHARED
    default/StandardStrategy.cpp
    ${STRUCT_SRC}
)

add_library(StandardPortfolio SHARED
    default/StandardPortfolio.cpp
    ${STRUCT_SRC}
)
