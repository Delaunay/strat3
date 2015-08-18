#ifndef DYNAMICLOADING_ERRORPOLICY_HEADER
#define DYNAMICLOADING_ERRORPOLICY_HEADER

// default: assert
#ifndef DYNAMICLOADING_THROW
#   define DYNAMICLOADING_THROW 0
#endif

#ifndef DYNAMICLOADING_NDEBUG
#   define DYNAMICLOADING_NDEBUG 0
#endif

#if DYNAMICLOADING_NDEBUG
#   define ASSERT(x)
#else
#   include <cassert>
#   define ASSERT(x) assert(x)
#endif

#if DYNAMICLOADING_THROW
#   define THROW(predicate, error, message) if((predicate)) throw error(message)
#elif !DYNAMICLOADING_NDEBUG
#   define THROW(predicate, error, message) assert(!(predicate) && message)
#else
#   define THROW(predicate, error, message)
#endif

#endif
