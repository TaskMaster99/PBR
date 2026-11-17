#ifndef MCE_HPP
#define MCE_HPP

#include "sampler.hpp"
#include <array>
#include <cmath>

namespace PBR_ 
{


constexpr std::double_t VarianceMCESphereIntegral(const std::double_t radius)
{

    std::double_t tmp       = radius * radius * radius * radius * radius;
    tmp                    *= radius * radius * radius * radius * radius;
    const std::double_t a   = 16.0*(M_PI*M_PI)*(tmp)/21;
    const std::double_t b   = 16.0*(M_PI*M_PI)*(tmp)/25;

    return a - b;
}

template<std::uint64_t N, auto PDF, auto SAMPLER>
void MonteCarloSphereIntegral(RNG& g, const std::double_t radius, 
                              const std::double_t Fn_, 
                              std::double_t* residual, std::double_t* Fn)
{
    std::double_t pdf_value  = PDF(radius);

    std::double_t r;

    for(std::uint64_t i{0LL}; i < N; ++i)
    {
        SAMPLER(g, radius, r, NULL, NULL);
        const std::double_t f = r*r;
        *Fn                   = *Fn + f;
    }

    *Fn =  (*Fn/pdf_value)/ static_cast<std::double_t>(N);

    *residual = (*Fn - Fn_);
    *residual *= *residual;
}

template<auto PDF, auto SAMPLER>
void MonteCarloSphereIntegral(std::uint64_t N, RNG& g, const std::double_t radius, 
                              const std::double_t Fn_, 
                              std::double_t* residual, std::double_t* Fn)
{
    std::double_t pdf_value  = PDF(radius);

    std::double_t r;
    std::double_t theta;
    std::double_t phi;

    for(std::uint64_t i{0LL}; i < N; ++i)
    {
        SAMPLER(g, radius, &r, &theta, &phi);
        const std::double_t f = r*r + 1;
        *Fn                   += f;
    }

    *Fn =  (*Fn/pdf_value)/ static_cast<std::double_t>(N);

    *residual = (*Fn - Fn_);
    *residual *= *residual;
}


template<std::uint64_t N, auto PDF, auto SAMPLER>
void MonteCarloSphereIntegralExt(RNG& g, 
                              const std::double_t radius, 
                              const std::double_t Fn_, 
                              std::double_t* residual, std::double_t* Fn,
                              std::array<std::double_t, N>& x, 
                              std::array<std::double_t, N>& y,
                              std::array<std::double_t, N>& z)
{
    std::double_t pdf_value  = PDF(radius);

    std::double_t r;
    std::double_t theta;
    std::double_t phi;

    for(std::uint64_t i{0LL}; i < N; ++i)
    {
        SAMPLER(g, radius, &r, &theta, &phi);

        x[i]           = r * std::cos(theta) * std::sin(phi);
        y[i]           = r * std::sin(phi)   * std::sin(theta);
        z[i]           = r * std::cos(phi);
        const std::double_t f = r*r;
        *Fn                   = *Fn + f;
    }

    *Fn =  (*Fn/pdf_value)/ static_cast<std::double_t>(N);

    *residual = (*Fn - Fn_);
    *residual *= *residual;
}

}

#endif