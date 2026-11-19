#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>
#include <vecmath.hpp>

namespace PBR_
{
struct Ray
{
    public:
    Point3         origin;
    Vector3        direction;
    std::double_t  t;

};
}

#endif