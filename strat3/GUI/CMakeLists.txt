# Qt Setup
#--------------

SET(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
FIND_PACKAGE(Qt5Widgets)

include_directories(${Qt5Widgets_INCLUDE_DIRS})


# Source
#--------------

aux_source_directory(. GUI_SRC)


# Compiling
#--------------

LINK_DIRECTORIES(${PROJECT_BINARY_DIR})
ADD_EXECUTABLE(strat3-gui ${GUI_SRC})
target_link_libraries(strat3-gui Qt5::Widgets backtest_library )
