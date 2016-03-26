#
#   If people don't build test don't add gtest
#
IF(BUILD_TESTING)
    # compile gtest
    ADD_SUBDIRECTORY(gtest)

    # does this work ?
    SET(${BUILD_GMOCK} OFF)
    SET(${BUILD_GTEST} OFF)

ENDIF(BUILD_TESTING)

IF (BUILD_BENCHMARK)

    ADD_SUBDIRECTORY(hayai)
    INCLUDE_DIRECTORIES(hayai/src)

ENDIF(BUILD_BENCHMARK)

# ADD_SUBDIRECTORY(opencv)
