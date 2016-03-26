add_library(StandardStrategy SHARED
            StandardStrategy.cpp
    ${STRUCT_SRC}
)
SET_PROPERTY(TARGET StandardStrategy PROPERTY CXX_STANDARD 11)

add_library(StandardPortfolio SHARED
            StandardPortfolio.cpp
    ${STRUCT_SRC}
)
SET_PROPERTY(TARGET StandardPortfolio PROPERTY CXX_STANDARD 11)

# Compile order is wrong
SET(MASRC
    ../DataManager/Buffer.h
    ../DataManager/MatrixManager.h
    ../DataManager/Buffer.cpp
    ../DataManager/MatrixManager.cpp
)

add_library(MovingAverageStrategy SHARED
            MovingAverageStrategy.cpp
    ${STRUCT_HDS}
    ${ABSTRACT_HDS}
    ${DATAMANAGER_HDS}
    ${MASRC}
)
SET_PROPERTY(TARGET MovingAverageStrategy PROPERTY CXX_STANDARD 11)
