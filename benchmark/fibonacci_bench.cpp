#ifndef VANAGANDR_BENCH_EIGENDATE_HEADER
#define VANAGANDR_BENCH_EIGENDATE_HEADER

#include <hayai.hpp>
#include "functions/my_header.h"


BENCHMARK(Math, fibonacci_inefficient, 10, 10000)
{
    for(int i = 0; i < 20; ++i)
        fibonacci_inefficient(i);
}

BENCHMARK(Math, fibonacci_dynp1, 10, 10000)
{
    for(int i = 0; i < 20; ++i)
        fibonacci_dynp1(i);
}

BENCHMARK(Math, fibonacci_frml, 10, 10000)
{
    for(int i = 0; i < 20; ++i)
        fibonacci_frml(i);
}

BENCHMARK(Math, fibonacci_loop, 10, 10000)
{
    for(int i = 0; i < 20; ++i)
        fibonacci_loop(i);
}

BENCHMARK(Math, fibonacci_lkup, 10, 10000)
{
    for(int i = 0; i < 20; ++i)
        fibonacci_lkup(i);
}

#endif

