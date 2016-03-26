# tests need source header
INCLUDE_DIRECTORIES(../src)
INCLUDE_DIRECTORIES(../dependencies/hayai/src)

# Add your test to CMAKE
# to run all tests run 'make test'
MACRO(BENCH_MACRO NAME) # LIBRARIES
    ADD_EXECUTABLE(${NAME}_bench ${NAME}_bench.cpp)
    TARGET_LINK_LIBRARIES(${NAME}_bench project_test hayai_main ${LIB_TIMING})
    # TARGET_LINK_LIBRARIES(${NAME}_test ${LIBRARIES} gtest -pthread)

    ADD_TEST(NAME ${NAME}_bench
        COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}_bench)
    
    # gtest need to be compiled first
    ADD_DEPENDENCIES(${NAME}_bench hayai_main)
ENDMACRO(BENCH_MACRO)

# add test here
# file_name_test.cpp ==> CBTEST_MACRO(file_name)
BENCH_MACRO(fibonacci)


