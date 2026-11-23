#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <utils.hpp>
#include <cmath>
#include <vecmath.hpp>
#include <ray.hpp>
#include <color.hpp>

namespace PBR_
{
struct alignas(64) Sphere
{
    public:
    RGB           rgb;
    Point3        origin;
    std::double_t radius;

    constexpr Sphere() = default;
    constexpr Sphere(const Point3& p, const std::double_t rad, 
                     const std::double_t r, const std::double_t g, const std::double_t b) : 
                    rgb(r,g,b), origin(p), radius(rad) {};
    constexpr Sphere(const Point3& p, const std::double_t rad, 
                     const RGB& c) : 
                    rgb(c), origin(p), radius(rad){};
    constexpr Sphere(const Sphere& sph) = default;
    constexpr Sphere(Sphere&& sph) = default;

    constexpr Sphere& operator=(const Sphere& sph) = default;
    constexpr Sphere& operator=(Sphere&& sph) = default;

};

constexpr bool intersect(const Sphere& sph ,Ray& ray)
{
    Vector3 oc          = ray.origin - sph.origin;
    std::double_t a     = ray.direction * ray.direction;
    std::double_t b     = ray.direction * oc;
    std::double_t c     = (oc * oc) - sph.radius * sph.radius;

    std::double_t delta = b * b - a * c;

    if(delta < EPSILONv5)
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }

    auto sqrt_delta = std::sqrt(delta);

    auto t1 = (- b - sqrt_delta)/a;
    if(t1 <= EPSILONv5)
    {
        t1 = (- b + sqrt_delta)/a;
        if(t1 <= EPSILONv5)
        {
            ray.t = std::numeric_limits<std::double_t>::lowest();
            return false;
        }
    }
    ray.t = t1;
    return true;
}

struct alignas(128) Plane
{
    public:
    RGB           rgb;
    Point3        origin;
    Vector3       u;
    Vector3       v;
    Vector3       n;

    constexpr Plane() = default;
    constexpr Plane(const Point3& p, const Vector3& u_, const Vector3& v_,
                    const std::double_t r, const std::double_t g, const std::double_t b) : 
                    rgb(r, g, b), origin(p), u(u_), v(v_) 
                    {
                        n = normalize(cross(u_, v_));
                    };
    constexpr Plane(const Point3& p, const Vector3& u_, const Vector3& v_,
                    const RGB& c) : 
                    rgb(c), origin(p), u(u_), v(v_) 
                    {
                        n = normalize(cross(u_, v_));
                    };
    constexpr Plane(const Plane& pl) = default;
    constexpr Plane(Plane&& pl)      = default;

    constexpr Plane& operator=(const Plane& pl) = default;
    constexpr Plane& operator=(Plane&& pl) = default;

};

constexpr bool intersect(const Plane& pl ,Ray& ray)
{
    std::double_t a = pl.n * (pl.origin - ray.origin);
    std::double_t b = pl.n * ray.direction;

    if(std::abs(b) <= EPSILONv5)
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }

    std::double_t t = a/b;

    if(t <= EPSILONv5)
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }

    
    Point3 P = lerp(ray, t);

    std::double_t alpha = ((P - pl.origin)*pl.u/(pl.u * pl.u)) + 0.5;

    
    std::double_t beta = ((P - pl.origin)*pl.v/(pl.v * pl.v)) + 0.5;

    if(alpha <= EPSILONv5 || alpha > 1.0 || beta <= EPSILONv5 || beta > 1.0)
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;   
    }

    return true;
}


}

#endif