#
#   Closer to asynchronous Backtester
#



add_executable(server server.cpp)
target_link_libraries(server ${SFML_LIBRARIES})

add_executable(client client.cpp)
target_link_libraries(client ${SFML_LIBRARIES})
