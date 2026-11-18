#ifndef PDF_HPP
#define PDF_HPP

#include <numbers>
#include <cmath>

namespace PBR_ 
{
 

struct UniformSphereVolumePDF
{
    public:
    UniformSphereVolumePDF() = default;
    inline std::double_t operator()(const std::double_t R) const
    {
        const std::double_t R_3 = R*R*R;
        return 3.0/(4.0*std::numbers::pi*(R_3));
    };
};

struct ImportanceSphereVolumePDF
{
    public:
    ImportanceSphereVolumePDF() = default;
    inline std::double_t operator()(const std::double_t r, const std::double_t R) const
    {
        const std::double_t R_5 = R*R*R*R*R;
        return 5.0*(r*r)/(4.0*std::numbers::pi*R_5);
    }
};

}

#endif