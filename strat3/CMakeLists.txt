CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
CMAKE_POLICY(VERSION 2.8)

#IF (COMMAND cmake_policy)
#  CMAKE_POLICY(SET CMP0003 NEW)
#ENDIF (COMMAND cmake_policy)

PROJECT(strat3)

# Useless for now
# Make CMake aware of the cmake folder for local FindXXX scripts,
# append rather than set in case the user has passed their own
# additional paths via -D.
# LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

aux_source_directory(. SRC_LIST)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O1 -O2 -O3")

SET(STRAT3_VERSION_MAJOR 1)
SET(STRAT3_VERSION_MINOR 0)
SET(STRAT3_VERSION_PATCH 0)
SET(STRA3_VERSION
    ${CERES_VERSION_MAJOR}.${CERES_VERSION_MINOR}.${CERES_VERSION_PATCH})


ENABLE_TESTING()

OPTION(BUILD_TESTING "Enable tests" ON)

#===============================================================================
#       Path to third party source
#===============================================================================

# windows
#INCLUDE_DIRECTORIES("/cygdrive/c/cygwin/usr/include")
#INCLUDE_DIRECTORIES("/cygdrive/c/Anaconda/include")

# linux
SET(GTEST_DIR "../../gtest/gtest")
#INCLUDE_DIRECTORIES("/usr/include/python2.7")

#===============================================================================
#           Boost.Python / Python Configuration
#===============================================================================

# FIND_PACKAGE(Eigen REQUIRED)

## find boost - Python
#FIND_PACKAGE(Boost 1.55
#    COMPONENTS
#        python)

## compile python bindings
#add_library(pyStrat3       SHARED
#    "${PROJECT_SOURCE_DIR}/python/Matrix.cpp"
#    "${PROJECT_SOURCE_DIR}/DataManager/DataManager.cpp"
#    "${PROJECT_SOURCE_DIR}/Portfolio/Portfolio.cpp"
#    "${PROJECT_SOURCE_DIR}/Portfolio/Transaction.cpp"
#    "${PROJECT_SOURCE_DIR}/Portfolio/TransactionAnswer.cpp"
#    "${PROJECT_SOURCE_DIR}/Portfolio/MarketEngine.cpp"
#    "${PROJECT_SOURCE_DIR}/Strategy/Strategy.cpp"
#    "${PROJECT_SOURCE_DIR}/DataLog/DataLog.cpp"
#)

## compile python bindings
#add_library(MatrixQuery    SHARED
#    "${PROJECT_SOURCE_DIR}/python/test.cpp"
#    "${PROJECT_SOURCE_DIR}/DataManager/DataManager.cpp")

#TARGET_LINK_LIBRARIES(pyStrat3       ${Boost_LIBRARIES} )
#TARGET_LINK_LIBRARIES(MatrixQuery    ${Boost_LIBRARIES} )

#===============================================================================
#           gtest Configuration
#===============================================================================

# Compile the gtest suite
include_directories(${GTEST_DIR})
include_directories("${GTEST_DIR}/include")
add_library(gtest "${GTEST_DIR}/src/gtest-all.cc")

#===============================================================================
#           Project Source
#===============================================================================

# Directories
add_subdirectory( "${PROJECT_SOURCE_DIR}/DataManager")
add_subdirectory( "${PROJECT_SOURCE_DIR}/Portfolio"  )
add_subdirectory( "${PROJECT_SOURCE_DIR}/Strategy"   )
add_subdirectory( "${PROJECT_SOURCE_DIR}/DataLog"    )
add_subdirectory( "${PROJECT_SOURCE_DIR}/Report"     )
add_subdirectory( "${PROJECT_SOURCE_DIR}/test"       )

# Sources
aux_source_directory( "${PROJECT_SOURCE_DIR}/DataManager"   SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Portfolio"     SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Strategy"      SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/DataLog"       SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Report"        SRC_LIST )

## project internal libraries
#add_library(DataManager "${PROJECT_SOURCE_DIR}/DataManager/DataManager.cpp")
#add_library(Portfolio
#    "${PROJECT_SOURCE_DIR}/Portfolio/Portfolio.cpp"
#    "${PROJECT_SOURCE_DIR}/Portfolio/Transaction.cpp"
#    "${PROJECT_SOURCE_DIR}/Portfolio/MarketEngine.cpp"
#    "${PROJECT_SOURCE_DIR}/Portfolio/TransactionAnswer.cpp")

#add_library(Strategy "${PROJECT_SOURCE_DIR}/Strategy/Strategy.cpp")
#add_library(Datalog "${PROJECT_SOURCE_DIR}/DataLog/DataLog.cpp")

#add_library(Report
#    "${PROJECT_SOURCE_DIR}/Report/Report.cpp"
#    "${PROJECT_SOURCE_DIR}/Report/Statistics.cpp"
#    "${PROJECT_SOURCE_DIR}/Report/HTMLReport.cpp"
#    "${PROJECT_SOURCE_DIR}/Report/script.cpp"
#)

add_library(Strat3 ${SRC_LIST})

#===============================================================================
#           Compiling
#===============================================================================

# link compiled libraries : including gtest
link_directories(${PROJECT_BINARY_DIR})

# executable and linking
add_executable(tests "${PROJECT_SOURCE_DIR}/test/main_test.cpp" ${SRC_LIST})
#target_link_libraries(tests -isystem libgtest.a libStrat3.a -pthread)
target_link_libraries(tests -isystem libgtest.a -pthread)
