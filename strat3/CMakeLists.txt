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

SET(STRAT3_VERSION_MAJOR 0)
SET(STRAT3_VERSION_MINOR 0)
SET(STRAT3_VERSION_PATCH 0)
SET(STRA3T_VERSION
    ${STRAT3_VERSION_MAJOR}.${STRAT3_VERSION_MINOR}.${STRAT3_VERSION_PATCH})


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
add_subdirectory( "${PROJECT_SOURCE_DIR}/Predictor"  )
add_subdirectory( "${PROJECT_SOURCE_DIR}/Error"      )

# Sources
aux_source_directory( "${PROJECT_SOURCE_DIR}/DataManager"   SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Portfolio"     SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Strategy"      SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/DataLog"       SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Report"        SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Predictor"     SRC_LIST )
#aux_source_directory( "${PROJECT_SOURCE_DIR}/test"          SRC_LIST )

# main lib
add_library(strat3 ${SRC_LIST})

#SET(CML_SRC_LIST)

# Command line prog
AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/cml"        CML_SRC_LIST)

#===============================================================================
#           Compiling
#===============================================================================

# link compiled libraries : including gtest
link_directories(${PROJECT_BINARY_DIR})

#cml ex
ADD_EXECUTABLE(cstrat3 "${PROJECT_SOURCE_DIR}/cml/main.cpp" ${CML_SRC_LIST})

# executable and linking
add_executable(tests "${PROJECT_SOURCE_DIR}/test/main_test.cpp" ${SRC_LIST})

#target_link_libraries(tests -isystem libgtest.a libStrat3.a -pthread)
target_link_libraries(tests -isystem libgtest.a -pthread)

#===============================================================================
#           Test
#===============================================================================


#MACRO (CERES_TEST NAME)
#    ADD_EXECUTABLE(${NAME}_test ${NAME}_test.cc)
#    TARGET_LINK_LIBRARIES(${NAME}_test test_util ceres gtest)
#    ADD_TEST(NAME ${NAME}_test
#             COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}_test
#             --test_srcdir
#             ${CMAKE_SOURCE_DIR}/data)
#  ENDMACRO (CERES_TEST)

#  CERES_TEST(array_utils)

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
