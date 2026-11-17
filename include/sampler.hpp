#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <cmath>
#include "rng.hpp"

#define OF 0.2

namespace PBR_ 
{
  
constexpr std::double_t UniformSphereVolumPDF(const std::double_t R)
{
    const std::double_t R_3 = R*R*R;
    return 3.0/(4.0*M_PI*(R_3));
}



constexpr std::double_t ImportanceSphereVolumPDF(const std::double_t r, const std::double_t R)
{
    const std::double_t R_5 = R*R*R*R*R;
    return 5.0*(r*r)/(4.0*M_PI*R_5);
}

struct Sampler
{
    public:

    static void SampleUniformSphereVolum(RNG&                   rng, 
                                         const std::double_t    R, 
                                         std::double_t * const  r, 
                                         std::double_t * const  theta, 
                                         std::double_t * const  phi)
    {
        const std::double_t U1      = rng.randFloat(0.0, 1.0);
        const std::double_t U2      = rng.randFloat(0.0, 1.0);
        const std::double_t U3      = rng.randFloat(0.0, 1.0);

        *r                          = R  * std::cbrt(U1);
        *theta                      = U2 * 2.0 * M_PI;
        *phi                        = std::acos(1.0 - 2.0*U3);
    }

    static void SampleImportanceSphereVolum(RNG&                   rng, 
                                            const std::double_t    R, 
                                            std::double_t * const  r, 
                                            std::double_t * const  theta, 
                                            std::double_t * const  phi)
    {
        const std::double_t U1      = rng.randFloat(0.0, 1.0);
        const std::double_t U2      = rng.randFloat(0.0, 1.0);
        const std::double_t U3      = rng.randFloat(0.0, 1.0);

        *r                          = R  * std::pow(U1, OF);
        *theta                      = U2 * 3.0 * M_PI;
        *phi                        = std::acos(1.0 - 2.0*U3);
    }

    

};

}


#endif