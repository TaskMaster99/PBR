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
    Vector3 P_O = P - pl.origin;

    Vector3 u = pl.u;
    Vector3 v = pl.v;

    std::double_t uu = u * u;
    std::double_t uv = u * v;
    std::double_t vv = v * v;

    std::double_t denom = 1.0/(uu*vv - uv*uv);
    std::double_t alpha = P_O*(u*vv - v*uv)*denom + 0.5;
    
    std::double_t beta = P_O*(v*uu - u*uv)*denom + 0.5;

    if(alpha <= EPSILONv5 || alpha > 1.0 || beta <= EPSILONv5 || beta > 1.0)
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;   
    }

    return true;
}

struct alignas(128) Triangle
{
    public:
    RGB rgb;
    Point3 origin;
    Point3 a;
    Point3 b;
    Point3 c;

    constexpr Triangle() = default;
    constexpr Triangle(const Point3& p, const Point3& a_, const Point3& b_, 
                       const Point3& c_, const RGB& rgb_) : rgb(rgb_), origin(p), 
                                                            a({a_.x + p.x, a_.y + p.y, a_.z + p.z}), 
                                                            b({b_.x + p.x, b_.y + p.y, b_.z + p.z}), 
                                                            c({c_.x + p.x, c_.y + p.y, c_.z + p.z}) {};

    constexpr Triangle(const Triangle& tri) = default;
    constexpr Triangle(Triangle&& tri) = default;

    constexpr Triangle& operator=(const Triangle& tri) = default;
    constexpr Triangle& operator=(Triangle&& tri) = default;
};

constexpr bool intersect(const Triangle& tri, Ray& ray)
{

    Vector3 edge1 = tri.b - tri.a;
    Vector3 edge2 = tri.c - tri.a;

    const Vector3 normal = cross(edge1, edge2);
	if ((normal * ray.direction) > 0) 
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }

    Vector3 ray_cross_e2 = cross(ray.direction, edge2);
    std::double_t det = edge1 * ray_cross_e2;

    if (std::abs(det) < EPSILONv5) 
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }

    std::double_t inv_det = 1.0 / det;
    Vector3 s = ray.origin - tri.a;
    std::double_t u = inv_det * (s * ray_cross_e2);

    if (u < -EPSILONv5 || u - 1 > EPSILONv5) 
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }

    Vector3 s_cross_e1 = cross(s, edge1);
    std::double_t v = inv_det * (ray.direction * s_cross_e1);

    if (v < -EPSILONv5 || u + v - 1 > EPSILONv5) 
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }

    std::double_t t = inv_det * (edge2 * s_cross_e1);

    if (t > EPSILONv5)
    {
        ray.t = t;
        return  true;
    }
    else 
    {
        ray.t = std::numeric_limits<std::double_t>::lowest();
        return false;
    }
}

}

#endif