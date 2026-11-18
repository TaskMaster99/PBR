#ifndef RAND_G_HPP
#define RAND_G_HPP

#include <cmath>
#include <cstdint>
#include <ctime>

namespace PBR_{

struct LCGEngine
{
    public:
    std::uint64_t state;
    static constexpr std::uint64_t modulus              = 2147483647;
    static constexpr std::uint64_t multiplier           = 16807;
    static constexpr std::uint64_t additive_constant    = 0;
    static constexpr std::double_t normalizer           = 2147483647.0;


    LCGEngine()                                       = delete;
    explicit LCGEngine(const std::uint64_t init_seed) : state(init_seed % modulus ? init_seed % modulus : 123456789){}

    LCGEngine(const LCGEngine& rng)            = default;
    LCGEngine& operator=(const LCGEngine& rng) = default;

    std::uint64_t next()
    {
        state = (multiplier*state + additive_constant) % modulus;
        return state;
    }
};


struct PCGEngine
{
    public:
    std::uint64_t state;
    static constexpr std::uint64_t multiplier = 6364136223846793005u;
    static constexpr std::double_t normalizer = 4294967296.0;

    PCGEngine()                                       : state(2 * 0xcafef00dd15ea5e5u + 1){}
    explicit PCGEngine(const std::uint64_t init_seed) : state(2* init_seed + 1){}

    PCGEngine(const PCGEngine& rng)            = default;
    PCGEngine& operator=(const PCGEngine& rng) = default;

    std::uint32_t next()
    {
        auto x = state;
        auto count = (std::uint64_t)(x >> 61);
        state = x * multiplier;
        x^= x >> 22;
        return static_cast<std::uint32_t>(x >> (22 + count));
    }
};


template<typename  RNGEngine>
std::uint64_t randInt(RNGEngine& g ,std::uint64_t minValue, std::uint64_t maxValue)
{
    std::uint64_t delta_x = maxValue - minValue + 1;
    return minValue + (g.next() % delta_x);
}

template<typename  RNGEngine>
std::double_t randFloat(RNGEngine& g , std::double_t minValue, std::double_t maxValue)
{
    std::double_t delta_x = maxValue - minValue;
    return minValue + (static_cast<std::double_t>(g.next())/g.normalizer * delta_x);
}


};


#endif