CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
PROJECT(strat3)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O1 -O2 -O3")

#SET(CMAKE_RELEASE_POSTFIX "")
#SET(CMAKE_DEBUG_POSTFIX "-debug")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

SET(STRAT3_VERSION_MAJOR 0)
SET(STRAT3_VERSION_MINOR 0)
SET(STRAT3_VERSION_PATCH 0)
SET(STRAT3_VERSION
    ${STRAT3_VERSION_MAJOR}.${STRAT3_VERSION_MINOR}.${STRAT3_VERSION_PATCH})

INCLUDE_DIRECTORIES(C:/Users/pastafarian/Dropbox/libraries/include)
INCLUDE_DIRECTORIES(.)

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

# does not work
#SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# I should copy Struct and Abstract source files into a public header
SET(STRUCT_SRC
    Struct/DataStruct.h
    Struct/DataStruct.cpp
    Struct/TransactionAnswer.h
    Struct/TransactionWeight.h
    Struct/TransactionWeight.cpp
)

