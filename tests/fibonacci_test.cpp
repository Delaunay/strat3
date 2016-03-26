#ifndef VANAGANDR_TEST_EIGENDATE_HEADER
#define VANAGANDR_TEST_EIGENDATE_HEADER

#include <gtest/gtest.h>
#include "functions/my_header.h"

TEST(square2, int)
{
    for(int i = 0; i < 10; ++i)
        ASSERT_EQ(i * i, square2(i));
}

TEST(square2, float)
{
    for(int i = 0; i < 10; ++i){
        float g = i * 1.5;
        ASSERT_EQ(g * g, square2(g));
    }
}


TEST(fibonacci_working, float)
{
#define FIB_CHECK(N) \
    ASSERT_EQ(fibonacci_lkup(N), fibonacci_inefficient(N)); \
    ASSERT_EQ(fibonacci_lkup(N), fibonacci_dynp1(N)); \
    ASSERT_EQ(fibonacci_lkup(N), fibonacci_lkup(N)); \
    ASSERT_EQ(fibonacci_lkup(N), fibonacci_loop(N)); \
    ASSERT_EQ(fibonacci_lkup(N), fibonacci_frml(N))

    FIB_CHECK(0);
    FIB_CHECK(1);
    FIB_CHECK(2);
    FIB_CHECK(3);
    FIB_CHECK(4);
    FIB_CHECK(5);
#undef FIB_CHECK
}

TEST(fibonacci_fail, float)
{
#define FIB_CHECK(N) \
    ASSERT_EQ(fibonacci_lkup(N), fibonacci_fail(N))

    FIB_CHECK(0);
    FIB_CHECK(1);
    FIB_CHECK(2);
    FIB_CHECK(3);
    FIB_CHECK(4);
    FIB_CHECK(5);
#undef FIB_CHECK
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}

#endif

