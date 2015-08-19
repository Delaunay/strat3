#find_package(OpenGL REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIR})

SET(SFML_STATIC_LIBRARIES TRUE)

IF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    SET(SFML_ROOT C:/Users/pastafarian/Downloads/SFML-2.3.1)
ELSE(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    SET(SFML_ROOT C:/Users/pastafarian/Downloads/SFML-2.3.1)
ENDIF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")


FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
INCLUDE_DIRECTORIES(C:/Users/pastafarian/Downloads/SFML-2.3.1/include)

aux_source_directory(. GRAPHICS_SRC)

add_executable(graphs main.cpp ${GRAPHICS_SRC})
target_link_libraries(graphs ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
