

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS}) #
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

aux_source_directory(. BT_CML_SRC)

add_executable(cml_strat3 ${BT_CML_SRC})
SET_PROPERTY(TARGET cml_strat3 PROPERTY CXX_STANDARD 11)
target_link_libraries(cml_strat3 backtest_library structs datamanager log ${SYSTEM_LIB})


#backtest_library structs datamanager
