#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
#include <tuple>

namespace PBR_ 
{

struct Vector3
{
    public:
    std::double_t x;
    std::double_t y;
    std::double_t z;

    constexpr Vector3()                 = default;
    constexpr Vector3(std::double_t a, std::double_t b, std::double_t c) : x(a), y(b), z(c) {};
    constexpr Vector3(const Vector3& u) = default;
    constexpr Vector3(Vector3&& u) = default;
    constexpr Vector3&         operator=(const Vector3& u)             = default;
    constexpr Vector3&         operator=(Vector3&& u)             = default;

    constexpr Vector3          operator+(const Vector3& u)      const {return {x+u.x , y+u.y , z+u.z};};
    constexpr Vector3&         operator+=(const Vector3& u)     
    {
        *this = {x+u.x , y+u.y , z+u.z};
        return *this;
    };

    constexpr Vector3         operator-()
    {
        return {-x , -y , -z};
    };

    constexpr Vector3          operator-(const Vector3& u)      const {return {x-u.x , y-u.y , z-u.z};};
    constexpr Vector3&         operator-=(const Vector3& u)     
    {
        *this = {x-u.x , y-u.y , z-u.z};
        return *this;
    };

    constexpr std::double_t    operator*(const Vector3& u)      const {return x*u.x + y*u.y + z*u.z;};
    constexpr Vector3          operator*(const std::double_t k) const {return {x * k, y * k, z * k};}
    constexpr Vector3&         operator*=(const std::double_t k)     
    {
        *this = *this * k;
        return *this;
    };

    constexpr Vector3          operator/(const std::double_t k) const {return {x / k, y / k, z / k};}
    constexpr Vector3&         operator/=(const std::double_t k)     
    {
        *this = *this / k;
        return *this;
    };
};


constexpr std::double_t magnitude(const Vector3& u)
{
    return std::sqrt(u*u);
}

constexpr Vector3 normalize(const Vector3& u)
{
    std::double_t len = magnitude(u);
    return len > EPSILONv5 ? u/len : u;
}

constexpr Vector3 cross(const Vector3& u1, const Vector3& u2)        
{
    return 
    {
            u1.y * u2.z - u1.z * u2.y, 
            u1.z * u2.x - u1.x * u2.z, 
            u1.x * u2.y - u1.y * u2.x
    };
}

constexpr auto CoordinateSystem(const Vector3& u1)                           
{
    std::double_t sign = copysign(1.0, u1.z);
    std::double_t a = -1.0/(sign + u1.z);
    std::double_t b = u1.x*u1.y*a;

    std::double_t uxx = u1.x*u1.x;
    std::double_t uyy = u1.y*u1.y;

    Vector3 u2 = {1.0 + sign*uxx*a, sign*b, -sign* u1.x};
    Vector3 u3 = {b, 1.0 + sign*uyy*a, -sign * u1.y};

    return std::make_tuple(u2, u3);
}

constexpr Vector3 flip(const Vector3& u, Vector3& n, const std::double_t epsilon = 0.0)
{
    return (u * n) < epsilon ? -n : n;
};


struct Point3
{
    std::double_t x;
    std::double_t y;
    std::double_t z;

    constexpr Point3()                 = default;
    constexpr Point3(std::double_t a, std::double_t b, std::double_t c) : x(a), y(b), z(c) {};
    constexpr Point3(const Point3& p)  = default;
    constexpr Point3(Point3&& p)  = default;

    constexpr Point3&       operator=(const Point3& p)             = default;
    constexpr Point3&       operator=(Point3&& p)             = default;

    constexpr Point3        operator+(const Vector3& u) const { return {x+u.x , y+u.y , z+u.z};};
    constexpr Point3&       operator+=(const Vector3& u)
    {
        *this = *this + u; 
        return *this;
    };

    constexpr Point3        operator-() const { return {-x , -y , -z};};
    constexpr Point3        operator-(const Vector3& u) const { return {x-u.x , y-u.y , z-u.z};};
    constexpr Point3&       operator-=(const Vector3& u)
    {
        *this = *this - u; 
        return *this;
    };

    constexpr Vector3       operator-(const Point3&  p) const { return {x-p.x , y-p.y , z-p.z};};
};

constexpr std::double_t distance(const Point3&  p1 ,const Point3&  p2) 
{
    return magnitude(p2- p1);
};

}

#endif