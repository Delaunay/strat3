#       Sphinx
# ==================================

IF(USE_SPHINX)

    FIND_PACKAGE(Sphinx REQUIRED)

    IF(SPHINX_FOUND)
        # HTML output directory
        SET(SPHINX_HTML_DIR "${CMAKE_BINARY_DIR}/docs/html")

        ADD_CUSTOM_TARGET(docs-sp ALL sphinx-build -b html
            "${CMAKE_SOURCE_DIR}/docs/"
            "${SPHINX_HTML_DIR}"
        )
    ENDIF(SPHINX_FOUND)

ENDIF(USE_SPHINX)

#       Doxygen
# ==================================

IF(USE_DOXYGEN)
    # from from https://majewsky.wordpress.com/2010/08/14/tip-of-the-day-cmake-and-doxygen/
    FIND_PACKAGE(Doxygen REQUIRED)

    IF(DOXYGEN_FOUND)
        CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                       ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

        ADD_CUSTOM_TARGET(docs-doxy ${DOXYGEN_EXECUTABLE}
                                    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
             COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
    ENDIF(DOXYGEN_FOUND)

ENDIF(USE_DOXYGEN)


# Building using 'make_docs.py' python script
#ADD_CUSTOM_TARGET(docs ALL
#                  python
#                  "${CMAKE_SOURCE_DIR}/scripts/make_docs.py"
#                  "${CMAKE_SOURCE_DIR}"
#                  "${CMAKE_BINARY_DIR}/docs"
#                  "${SPHINX_EXECUTABLE}"
#                  COMMENT "Building HTML documentation with Sphinx")
