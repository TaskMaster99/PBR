#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <cmath>
#include <limits>
#include <vecmath.hpp>
#include <ray.hpp>

#define EPSILON 10e-6

namespace PBR_
{
struct Sphere
{
    public:
    Point3        origin;
    std::double_t radius;

    std::double_t r;
    std::double_t g;
    std::double_t b;

    bool intersect(Ray& r, std::double_t& t)
    {
       auto oc      = r.origin - origin;
       auto a = r.direction * r.direction;
       auto b = r.direction * oc;
       auto c = (oc *oc) - radius*radius;

       auto delta = b*b - a*c;

       if(delta < EPSILON)
       {
            t = std::numeric_limits<std::double_t>::lowest();
            return false;
       }

       auto sqrt_delta = std::sqrt(delta);

       auto t1 = (- b - sqrt_delta)/a;
       if(t1 <= EPSILON)
       {
            t1 = (- b + sqrt_delta)/a;
            if(t1 <= EPSILON)
            {
                return false;
            }
       }
       t = t1;
       return true;
    }

};
}

#endif