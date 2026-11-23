#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>
#include <vecmath.hpp>

namespace PBR_
{
struct alignas(64) Ray
{
    public:
    Point3         origin;
    Vector3        direction;
    std::double_t  t;

    constexpr Ray() noexcept = default;
    constexpr Ray(const Point3& o, const Vector3& d, const std::double_t dt) noexcept : origin(o), direction(d), t(dt) {};
    constexpr Ray(const Ray& ray) noexcept = default;
    constexpr Ray(Ray&& ray) noexcept = default;

    constexpr Ray& operator=(const Ray& ray) noexcept = default;
    constexpr Ray& operator=(Ray&& ray) noexcept = default;

};

constexpr Point3 lerp(const Ray& r) {return r.origin + r.direction * r.t;};
constexpr Point3 lerp(const Ray& r, const std::double_t dt) {return r.origin +r.direction * dt;};

}

#endif