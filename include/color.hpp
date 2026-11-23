#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>

namespace PBR_ 
{
struct RGB
{
    public:
    std::double_t r;
    std::double_t g;
    std::double_t b;

    constexpr RGB() = default;
    constexpr RGB(const std::double_t a, const std::double_t b, const std::double_t c) : r(std::abs(a)), g(std::abs(b)), b(std::abs(c)) {};
    constexpr RGB(const RGB& rgb) = default;
    constexpr RGB(RGB&& rgb) = default;

    constexpr RGB& operator=(const RGB& rgb) = default;
    constexpr RGB& operator=(RGB&& rgb) = default;

    constexpr RGB operator+(const RGB& rgb) const {return {r + rgb.r, g + rgb.g, b + rgb.b};};
    constexpr RGB operator*(const RGB& rgb) const {return {r * rgb.r, g * rgb.g, b * rgb.b};};
    constexpr RGB operator*(const std::double_t k) const {return {r * k, g * k, b * k};};
    constexpr RGB operator/(const std::double_t k) const {return {r / k, g / k, b / k};};

    constexpr RGB& operator+=(const RGB& rgb) 
    {
        this->r += rgb.r; 
        this->g += rgb.g; 
        this->b += rgb.b;
        return *this;
    };
    constexpr RGB& operator*=(const RGB& rgb)
    {
        this->r *= rgb.r; 
        this->g *= rgb.g; 
        this->b *= rgb.b;
        return *this;
    };
    constexpr RGB& operator*=(const std::double_t k)
    {
        this->r *= k; 
        this->g *= k; 
        this->b *= k;
        return *this;
    };
    constexpr RGB& operator/=(const std::double_t k)
    {
        this->r /= k; 
        this->g /= k; 
        this->b /= k;
        return *this;
    };
};
}


#endif