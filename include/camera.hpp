#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vecmath.hpp"


namespace PBR_ 
{

struct Camera
{

    public:
    Point3 position;
    Vector3 front;
    Vector3 right;
    Vector3 up;


    constexpr Camera() : position(0.0, 0.0, 0.0), front(0.0, 0.0, -1.0), right(1.0, 0.0, 0.0), up(0.0, 1.0, 0.0) {};
    constexpr Camera(const Point3& pos) : position(pos)
    {
        front = {0.0, 0.0, -1.0};
        right = {1.0, 0.0, 0.0};
        up    = {0.0, 1.0, 0.0};
    }

    constexpr Camera(const Camera& cam) = default;
    constexpr Camera& operator=(const Camera& cam) = default;
};

}

#endif