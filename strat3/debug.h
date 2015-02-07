#ifndef STRAT3_DEBUG_DEBUG_HEADER
#define STRAT3_DEBUG_DEBUG_HEADER

#define STRAT3_DEBUG 1

#if STRAT3_DEBUG

#include <cstdio>

#define DEBUG_IDX_INIT  unsigned int debug_index = 0
#define DEBUG_IDX_PRINT printf("%d \n", debug_index); ++debug_index

#define DEBUG_PRINT(x, y) printf(x); printf(" : %d \n", y)

#define DEBUG_LOOP(inner, outer) printf("INN: ");    printf("%d", inner);  \
                                 printf("\t OUT: "); printf("%d", outer); printf("\n")

#endif

#endif
