#include <gtest/gtest.h>

#include "option_reader.h"

#if __linux__

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

#endif