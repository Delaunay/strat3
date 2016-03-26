SET(DATAMANAGER_HDS
    Buffer.h
    MatrixManager.h
)

SET(DATAMANAGER_SRC
    Buffer.cpp
    MatrixManager.cpp
)

add_library(datamanager ${DATAMANAGER_HDS} ${DATAMANAGER_SRC})
SET_PROPERTY(TARGET datamanager PROPERTY CXX_STANDARD 11)
