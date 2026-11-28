#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <cassert>

#define ASSERT(exp, msg) assert((void(msg), exp))

#define EPSILONv1 10e-6
#define EPSILONv2 10e-7
#define EPSILONv3 10e-8
#define EPSILONv4 10e-9
#define EPSILONv5 10e-10

namespace PBR_ 
{

constexpr std::double_t radian(const std::double_t degree)
{
    return 0.01745329251 * degree;
}

constexpr std::double_t degree(const std::double_t radian)
{
    return 57.2957795131 * radian;
}

}

#endif