#ifndef STRAT3_BACKTESTER_ERRORPOLICY_HEADER
#define STRAT3_BACKTESTER_ERRORPOLICY_HEADER

// Error Handling
#ifndef STRAT3_THROW
#   define STRAT3_THROW 0
#endif

#ifndef STRAT3_NDEBUG
#   define STRAT3_NDEBUG 0
#endif

#if STRAT3_NDEBUG
#   define SASSERT(x)
#else
#   include <cassert>
#   define SASSERT(x) assert(x)
#endif

#if STRAT3_THROW
#   define STHROW(predicate, error, message) if((predicate)) throw error(message)
#elif !STRAT3_NDEBUG
#   define STHROW(predicate, error, message) assert(!(predicate) && message)
#else
#   define STHROW(predicate, error, message)
#endif

#endif
