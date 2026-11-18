#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <cmath>
#include "rng.hpp"
#include <numbers>
#include <tuple>

#define OF 0.2

namespace PBR_ 
{
struct SampleUniformSphereVolume
{
    public:
    SampleUniformSphereVolume() = default;

    template<typename RNGEngine>
    auto operator()(RNGEngine&                   rng, 
                    const std::double_t    R) const
    {
        const std::double_t U1      = randFloat(rng, 0.0, 1.0);
        const std::double_t U2      = randFloat(rng, 0.0, 1.0);
        const std::double_t U3      = randFloat(rng, 0.0, 1.0);

        const std::double_t r                          = R  * std::cbrt(U1);
        const std::double_t theta                      = U2 * 2.0 * std::numbers::pi;
        const std::double_t phi                        = std::acos(1.0 - 2.0*U3);

        return std::make_tuple(r, theta, phi);

    }
};

struct SampleImportanceSphereVolume
{
    public:
    SampleImportanceSphereVolume() = default;
    template<typename RNGEngine>
    auto operator()(RNGEngine&           rng, 
                    const std::double_t    R) const
    {
        const std::double_t U1      = randFloat(rng, 0.0, 1.0);
        const std::double_t U2      = randFloat(rng, 0.0, 1.0);
        const std::double_t U3      = randFloat(rng, 0.0, 1.0);

        const std::double_t r                          = R  * std::pow(U1, OF);
        const std::double_t theta                      = U2 * 2.0 * std::numbers::pi;
        const std::double_t phi                        = std::acos(1.0 - 2.0*U3);

        return std::make_tuple(r, theta, phi);
    }
};

}


#endif