# required for C++11 features
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# project name + language used
PROJECT(strat3 CXX)

# debug/release
SET(CMAKE_RELEASE_POSTFIX "")       # Release is the default
SET(CMAKE_DEBUG_POSTFIX "-debug")

# Compiler-flag
IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    MESSAGE(STATUS "Building Debug Version")
ELSE()
    MESSAGE(STATUS "Building Release Version")
    # ADD_DEFINITIONS(-O2)                        # CMake Release is O3 by default
ENDIF()

# specify where compiled files must go
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# we want dll/so to be in the same directory
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# add cmake FindXXX script to find pre-compiled libraries if any
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Project Version
# ====================================

SET(STRAT3_VERSION_MAJOR 0)
SET(STRAT3_VERSION_MINOR 0)
SET(STRAT3_VERSION_PATCH 0)
SET(STRAT3_VERSION
    ${STRAT3_VERSION_MAJOR}.${STRAT3_VERSION_MINOR}.${STRAT3_VERSION_PATCH})

# Project's Options
# ====================================

OPTION(BUILD_TESTING        "Enable tests"       OFF)
OPTION(BUILD_BENCHMARK      "Build Benchmarks"   OFF)
OPTION(BUILD_DOCUMENTATION  "Build docs"         OFF)
OPTION(BUILD_DOXYGEN        "Build Doxygen docs" OFF)
OPTION(BUILD_SPHINX         "Build Sphinx docs"  OFF)

# Project's Configuration
# ====================================

SET(${CXX_STANDARD_REQUIRED} ON)    # the compiler must support C++11

#
# System config
# =====================================

IF(UNIX)
    MESSAGE(STATUS "Building for Unix")
    SET(SYSTEM_LIB -ldl)
ELSE()
    MESSAGE(STATUS "Building for Windows")
    SET(EIGEN_INCLUDE_DIR   ../../libraries/include)
    SET(SFML_ROOT           dependencies/SFML)
    SET(SFML_INCLUDE_DIR    dependencies/SFML/include)
    SET(BOOST_ROOT          C:/local/boost_1_59_0)
    SET(SYSTEM_LIB)
ENDIF()

# Binary/pre-compiled Dependencies
# ====================================

FIND_PACKAGE(Git REQUIRED)
FIND_PACKAGE(Eigen)   # Eigen | Matrix             | Mendatory
FIND_PACKAGE(SFML)    # SFML  | Network and OpenGL | used in network and graphics
FIND_PACKAGE(OpenGL)  #
FIND_PACKAGE(Boost)   # Boost | Json Parsing       | used in CML
FIND_PACKAGE(Qt5Gui)  # Qt    | GUI                | Optional
IF(Qt5Gui_FOUND)
    MESSAGE(STATUS "Qt5Gui Found")
ENDIF(Qt5Gui_FOUND)

# SET(CMAKE_AUTOMOC ON)
# SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# add_executable(helloworld WIN32 main.cpp)
# target_link_libraries(helloworld Qt5::Gui)

# Include Dependencies
# ====================================

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${EIGEN_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

# Subdirectories
# ====================================

# Find revision ID and hash of the sourcetree
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
INCLUDE(cmake/genrev.cmake)

# Dependencies to be compiled
ADD_SUBDIRECTORY(dependencies)

# How to compile main lib
ADD_SUBDIRECTORY(src)

# Compile tests ?
IF(BUILD_TESTING)
    ENABLE_TESTING()

    MESSAGE(STATUS "Building tests")
    ADD_SUBDIRECTORY(tests)
ENDIF(BUILD_TESTING)

IF (BUILD_BENCHMARK)
    MESSAGE(STATUS "Building Benchmarks")
    ADD_SUBDIRECTORY(benchmark)
ENDIF(BUILD_BENCHMARK)

# Gen doc ?
IF (BUILD_DOCUMENTATION)
    MESSAGE(STATUS "Documentation building is enabled")
    ADD_SUBDIRECTORY(docs)
ENDIF (BUILD_DOCUMENTATION)


