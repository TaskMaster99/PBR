#include "rng.hpp"
#include "sampler.hpp"
#include <cmath>
#include <mce.hpp>
#include <cstdio>

#define NREP    500
#define N       1000

void writingDataMCESphereIntegral()
{
    PBR_::RNG generator;
    const std::double_t radius = 1.0;

    
    const std::double_t radius_3 = radius*radius*radius;
    const std::double_t radius_5 = radius*radius*radius*radius*radius;
    const std::double_t Fn_ = 4*M_PI*((radius_5)/5.0+(radius_3)/ 3.0);

    std::array<std::uint64_t, N> samples_size;


    std::uint64_t base{500ULL};

    for(std::uint64_t i{0ULL}; i < N; ++i)
    {
        samples_size[i] = (1 + i) * base;
    }


    std::FILE* data = std::fopen("data/mce_sphere_integral.csv", "w");

    std::fprintf(data, "size;idealMSE;idealRMSE;MSE;RMSE;Fn\n");

    const std::double_t variance = PBR_::VarianceMCESphereIntegral(radius);

    for(std::uint64_t i{0ULL}; i < N; ++i)
    {
        std::double_t res = 0.0;
        std::double_t I = 0.0;

        const std::uint64_t currentSize = samples_size[i];
        
        for(std::uint64_t p{0ULL}; p < NREP; ++p)
        {
            std::double_t residual = 0.0;
            std::double_t Fn       = 0.0;
            PBR_::MonteCarloSphereIntegral<PBR_::UniformSphereVolumPDF,PBR_::Sampler::SampleUniformSphereVolum>(currentSize, generator, radius, Fn_, &residual, &Fn);
            res += residual;
            I += Fn;


        }
        const std::double_t idealMSE    = variance/currentSize;
        const std::double_t idealRMSE   = std::sqrt(idealMSE);
        const std::double_t currentMSE  = res/static_cast<std::double_t>(NREP);
        const std::double_t currentRMSE = std::sqrt(currentMSE);
        const std::double_t currentFN   = I/static_cast<std::double_t>(NREP);


        std::fprintf(data, "%lu;%lf;%lf;%lf;%lf;%lf\n", currentSize, idealMSE, idealRMSE, currentMSE, currentRMSE, currentFN);
    }

    std::fclose(data);
}

int main() 
{
    writingDataMCESphereIntegral();
}