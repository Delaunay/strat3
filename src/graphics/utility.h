#ifndef STRAT3_GRAPHICS_UTILITY_HEADER
#define STRAT3_GRAPHICS_UTILITY_HEADER

#include <vector>
#include <boost/random.hpp>

template<typename T>
T rand(const T& min = 0, const T& max = 1)
{
    static boost::random::mt19937 eng;
    static boost::random::uniform_real_distribution<> r(min, max);
    return r(eng);
}

template<typename T>
std::vector<T> make_random(size_t n, T min = 0, T max = 1)
{
    std::vector<T> ref(n);
    for(auto& x : ref) x = rand<T>(min, max);
    return ref;
}

template<typename T>
std::vector<T> lin_space(size_t n, T min = 0, T max = 1)
{
    std::vector<T> ref(n);
    double dt = (max - min) / (n - 1.f);

    if (min > max)
        dt = (min - max) / (n - 1.f);

    for(int i = 0; i < n; ++i)
        ref[i] = min + i * dt;

    return ref;
}

#endif
