SET(STRUCT_HDS
    DataStruct.h
    TransactionAnswer.h
    TransactionWeight.h
)

SET(STRUCT_SRC
    DataStruct.cpp
    TransactionWeight.cpp
)

add_library(structs ${STRUCT_HDS} ${STRUCT_SRC})
SET_PROPERTY(TARGET structs PROPERTY CXX_STANDARD 11)
