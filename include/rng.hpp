#ifndef RAND_G_HPP
#define RAND_G_HPP

#include <cmath>
#include <cstdint>
#include <ctime>

namespace PBR_{

struct RNG
{
    public:
    std::uint64_t seed;
    std::uint64_t modulus;
    std::uint64_t multiplier;
    std::uint64_t additive_constant;


    RNG()
    {
        seed = static_cast<std::uint64_t>(std::time(NULL));
        modulus = 2147483647;
        multiplier = 16807;
        additive_constant = 0;
    }

    RNG(const std::uint64_t& s, const std::uint64_t& m, const std::uint64_t& ac)
    {
        seed              = s;
        modulus           = m;
        additive_constant = ac;
    }

    RNG(const RNG& rng)
    {
        seed              = rng.seed;
        modulus           = rng.modulus;
        additive_constant = rng.additive_constant;
    }

    std::uint64_t LCG()
    {
        seed = (multiplier*seed + additive_constant) % modulus;
        return seed;
    }

    std::uint64_t randInt(std::uint64_t minValue, std::uint64_t maxValue)
    {
        std::uint64_t delta_x = maxValue - minValue + 1;
        return minValue + (LCG() % delta_x);
    }

    std::double_t randFloat(std::double_t minValue, std::double_t maxValue)
    {
        std::double_t delta_x = maxValue - minValue;
        return minValue + (static_cast<std::double_t>(LCG())/modulus * delta_x);
    }


};

};


#endif