# Strat3 - a General Purpose Backtester
# Copyright 2014 Pierre Delaunay All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# * Neither the name of Google Inc. nor the names of its contributors may be
#   used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Authors: pierre.delaunay@outlook.com (Pierre Delaunay)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
CMAKE_POLICY(VERSION 2.8)

IF (COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF (COMMAND cmake_policy)

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

# ENABLE_TESTING()

#===============================================================================
#       Path to third party source
#===============================================================================

# windows
#INCLUDE_DIRECTORIES("/cygdrive/c/cygwin/usr/include")
#INCLUDE_DIRECTORIES("/cygdrive/c/Anaconda/include")

# linux
SET(GTEST_DIR "../../gtest/gtest")
INCLUDE_DIRECTORIES("/usr/include/python2.7")



# FIND_PACKAGE(Eigen REQUIRED)

# find boost - Python
FIND_PACKAGE(Boost 1.55
    COMPONENTS
        python)

#===============================================================================
#           Python Configuration
#===============================================================================

# compile python bindings
add_library(pyStrar3       SHARED
    "${PROJECT_SOURCE_DIR}/python/Matrix.cpp"
    "${PROJECT_SOURCE_DIR}/DataManager/DataManager.cpp"
)

SET_TARGET_PROPERTIES(pyStrat3 PROPERTIES
  VERSION ${STRAT3_VERSION}
  SOVERSION ${STRAT3_VERSION_MAJOR}
)

## compile python bindings
#add_library(MatrixQuery    SHARED
#    "${PROJECT_SOURCE_DIR}/python/test.cpp"
#    "${PROJECT_SOURCE_DIR}/DataManager/DataManager.cpp")

TARGET_LINK_LIBRARIES(pyStrat3       ${Boost_LIBRARIES} )
#TARGET_LINK_LIBRARIES(MatrixQuery    ${Boost_LIBRARIES} )

#===============================================================================
#           gtest Configuration
#===============================================================================

# Compile the gtest suite
include_directories(${GTEST_DIR})
add_library(gtest "${GTEST_DIR}/src/gtest-all.cc")



#===============================================================================
#           Project Source
#===============================================================================

# includes
include_directories(
    "${GTEST_DIR}/include"
    "${PROJECT_SOURCE_DIR}/DataManager"
    "${PROJECT_SOURCE_DIR}/Portfolio"
    "${PROJECT_SOURCE_DIR}/Strategy"
    "${PROJECT_SOURCE_DIR}/DataLog"
    "${PROJECT_SOURCE_DIR}/test"
)

# Sources
aux_source_directory( "${PROJECT_SOURCE_DIR}/DataManager"   SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Portfolio"     SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/Strategy"      SRC_LIST )
aux_source_directory( "${PROJECT_SOURCE_DIR}/DataLog"       SRC_LIST )

# project internal libraries
add_library(DataManager "${PROJECT_SOURCE_DIR}/DataManager/DataManager.cpp")
add_library(Portfolio
    "${PROJECT_SOURCE_DIR}/Portfolio/Portfolio.cpp"
    "${PROJECT_SOURCE_DIR}/Portfolio/Transaction.cpp"
    "${PROJECT_SOURCE_DIR}/Portfolio/MarketEngine.cpp"
    "${PROJECT_SOURCE_DIR}/Portfolio/TransactionAnswer.cpp")

add_library(Strategy "${PROJECT_SOURCE_DIR}/Strategy/Strategy.cpp")
add_library(Datalog "${PROJECT_SOURCE_DIR}/DataLog/DataLog.cpp")

#===============================================================================
#           Compiling
#===============================================================================

# link compiled libraries : including gtest
link_directories(${PROJECT_BINARY_DIR})

# executable and linking

IF (BUILD_TESTING)
    add_executable(tests "${PROJECT_SOURCE_DIR}/test/main_test.cpp" ${SRC_LIST})
    target_link_libraries(tests -isystem libgtest.a -pthread)
ENDIF (BUILD_TESTING)
