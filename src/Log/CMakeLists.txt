aux_source_directory(. LOG_SRC)

add_library(log ${LOG_SRC})
SET_PROPERTY(TARGET log PROPERTY CXX_STANDARD 11)
