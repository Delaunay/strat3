CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
PROJECT(strat3)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#SET(CMAKE_RELEASE_POSTFIX "")
#SET(CMAKE_DEBUG_POSTFIX "-debug")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake")

SET(STRAT3_VERSION_MAJOR 0)
SET(STRAT3_VERSION_MINOR 0)
SET(STRAT3_VERSION_PATCH 0)
SET(STRAT3_VERSION
    ${STRAT3_VERSION_MAJOR}.${STRAT3_VERSION_MINOR}.${STRAT3_VERSION_PATCH})

# INCLUDE_DIRECTORIES(C:/Users/pastafarian/Dropbox/libraries/include)

# Dependencies lookup
SET(SFML_ROOT ../../dependencies/)
SET(EIGEN_ROOT ../../dependencies/)
SET(GTEST_ROOT ../../dependencies/)

# Eigen
find_package(Eigen3) # no Library

# SFML
FIND_PACKAGE(SFML) #

# Gtest
# find_package(gtest)

# Misc
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${EIGEN_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

#IF(${SFML_FOUND})
#    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
#ENDIF()

#INCLUDE_DIRECTORIES(C:/Users/pastafarian/Dropbox/libraries/include)
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
add_subdirectory(Report)
add_subdirectory(network)

# does not work
#

# add sqlite source

# I should copy Struct and Abstract source files into a public header
SET(STRUCT_SRC
    Struct/DataStruct.h
    Struct/DataStruct.cpp
    Struct/TransactionAnswer.h
    Struct/TransactionWeight.h
    Struct/TransactionWeight.cpp
)

SET(WINDOWS WIN32 || MSVC)

IF(WINDOWS)
    SET(SYSTEM_LIB )
ELSE()
    SET(SYSTEM_LIB -ldl)
ENDIF()

#SET(SQLITE_SRC C:/sqlite/sqlite3.c)
#INCLUDE_DIRECTORIES(C:/sqlite/)

#SET(BOOST_ROOT C:/Boost/)
#SET(BOOST_LIBRARYDIR C:/Boost/lib64-msvc-12.0)

FIND_PACKAGE(Boost)

