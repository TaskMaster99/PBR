#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <sampler.hpp>
#include <cmath>
#include <numbers>
#include <span>


#define MAX_POINT 10000000

namespace PBR_ 
{


constexpr std::double_t VarianceMCESphereIntegral(const std::double_t radius)
{

    std::double_t tmp       = radius * radius * radius * radius * radius;
    tmp                    *= radius * radius * radius * radius * radius;
    const std::double_t a   = 16.0*(std::numbers::pi*std::numbers::pi)*(tmp)/21;
    const std::double_t b   = 16.0*(std::numbers::pi*std::numbers::pi)*(tmp)/25;

    return a - b;
}

template< typename  IntegralResultType, typename  FuncSample, typename  FuncPDF>
struct Integrator
{

    public:
    std::uint64_t        N;
    FuncPDF              pdf;
    FuncSample           sampling;

    
    Integrator(const std::uint64_t n) : N(n)
    {
        pdf = FuncPDF();
        sampling = FuncSample();
    };

    template<typename  RNGEngine>
    IntegralResultType SphereIntegral(RNGEngine& g, const std::double_t radius)
    {
        std::double_t pdf_value = 0.0f;
        IntegralResultType   Fn = IntegralResultType{};

        for(std::uint64_t i{0LL}; i < N; ++i)
        {
            auto [r, theta, phi] = sampling(g, radius);
            
            const std::double_t f = r*r;
            if constexpr (std::invocable<FuncPDF, std::double_t, std::double_t>) pdf_value = pdf(r, radius);
            else pdf_value = pdf(radius);
            Fn            += f/pdf_value;
        }

        Fn /= static_cast<std::double_t>(N);

        return Fn;
    }

    template<typename  RNGEngine>
    IntegralResultType SphereIntegral(RNGEngine& g,
                                      const std::double_t radius,
                                      std::span<std::double_t> x, 
                                      std::span<std::double_t> y,
                                      std::span<std::double_t> z)
    {
        std::double_t pdf_value  = 0.0;
        IntegralResultType   Fn = IntegralResultType{};

        for(std::uint64_t i{0LL}; i < N; ++i)
        {
            auto [r, theta, phi] = sampling(g, radius);

            x[i]           = r * std::cos(theta) * std::sin(phi);
            y[i]           = r * std::sin(phi)   * std::sin(theta);
            z[i]           = r * std::cos(phi);
            const std::double_t f = r*r;

            if constexpr (std::invocable<FuncPDF, std::double_t, std::double_t>) pdf_value = pdf(r, radius);
            else pdf_value = pdf(radius);

            Fn            += f/pdf_value;
        }

        Fn =  Fn/ static_cast<std::double_t>(N);

        return Fn;
    }
};

}

#endif