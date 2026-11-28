#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP



#include "ray.hpp"
#include <cmath>
#include <cstdint>
#include "vecmath.hpp"
#include <cstdio>
#include "camera.hpp"
#include <optional>
namespace PBR_
{
struct Transformation
{
    public:
    std::double_t SquareMatrix4x4[16];

    constexpr Transformation() noexcept
    {
        SquareMatrix4x4[0]  = 1.0;SquareMatrix4x4[1]  = 0.0;SquareMatrix4x4[2]  = 0.0;SquareMatrix4x4[3]  = 0.0;
        SquareMatrix4x4[4]  = 0.0;SquareMatrix4x4[5]  = 1.0;SquareMatrix4x4[6]  = 0.0;SquareMatrix4x4[7]  = 0.0;
        SquareMatrix4x4[8]  = 0.0;SquareMatrix4x4[9]  = 0.0;SquareMatrix4x4[10] = 1.0;SquareMatrix4x4[11] = 0.0;
        SquareMatrix4x4[12] = 0.0;SquareMatrix4x4[13] = 0.0;SquareMatrix4x4[14] = 0.0;SquareMatrix4x4[15] = 1.0;
    }

    constexpr Transformation(const std::double_t m00, const std::double_t m01, const std::double_t m02, const std::double_t m03,
                             const std::double_t m04, const std::double_t m05, const std::double_t m06, const std::double_t m07,
                             const std::double_t m08, const std::double_t m09, const std::double_t m10, const std::double_t m11,
                             const std::double_t m12, const std::double_t m13, const std::double_t m14, const std::double_t m15) noexcept
    {
        SquareMatrix4x4[0]  = m00;SquareMatrix4x4[1]  = m01;SquareMatrix4x4[2]  = m02;SquareMatrix4x4[3]  = m03;
        SquareMatrix4x4[4]  = m04;SquareMatrix4x4[5]  = m05;SquareMatrix4x4[6]  = m06;SquareMatrix4x4[7]  = m07;
        SquareMatrix4x4[8]  = m08;SquareMatrix4x4[9]  = m09;SquareMatrix4x4[10] = m10;SquareMatrix4x4[11] = m11;
        SquareMatrix4x4[12] = m12;SquareMatrix4x4[13] = m13;SquareMatrix4x4[14] = m14;SquareMatrix4x4[15] = m15;
    }
    constexpr Transformation(const Transformation& trans) noexcept = default;
    constexpr Transformation(Transformation&& trans) noexcept = default;

    constexpr Transformation& operator=(const Transformation& trans) noexcept = default;
    constexpr Transformation& operator=(Transformation&& trans) noexcept = default;

    constexpr std::double_t  operator()(std::uint8_t i, std::uint8_t j) const {return SquareMatrix4x4[i*4+j];}
    constexpr std::double_t& operator()(std::uint8_t i, std::uint8_t j) {return SquareMatrix4x4[i*4+j];}


    constexpr Transformation operator+(const Transformation& trans)
    {
        Transformation result;

        result(0, 0) =  this->operator()(0,0) + trans(0, 0);
        result(0, 1) =  this->operator()(0,1) + trans(0, 1);
        result(0, 2) =  this->operator()(0,2) + trans(0, 2);
        result(0, 3) =  this->operator()(0,3) + trans(0, 3);

        result(1, 0) =  this->operator()(1,0) + trans(1, 0);
        result(1, 1) =  this->operator()(1,1) + trans(1, 1);
        result(1, 2) =  this->operator()(1,2) + trans(1, 2);
        result(1, 3) =  this->operator()(1,3) + trans(1, 3);

        result(2, 0) =  this->operator()(2,0) + trans(2, 0);
        result(2, 1) =  this->operator()(2,1) + trans(2, 1);
        result(2, 2) =  this->operator()(2,2) + trans(2, 2);
        result(2, 3) =  this->operator()(2,3) + trans(2, 3);

        result(3, 0) =  this->operator()(3,0) + trans(3, 0);
        result(3, 1) =  this->operator()(3,1) + trans(3, 1);
        result(3, 2) =  this->operator()(3,2) + trans(3, 2);
        result(3, 3) =  this->operator()(3,3) + trans(3, 3);

        return result;
    };

    constexpr Transformation& operator+=(const Transformation& trans) noexcept
    {
         this->operator()(0, 0) =  this->operator()(0,0) + trans(0, 0);
         this->operator()(0, 1) =  this->operator()(0,1) + trans(0, 1);
         this->operator()(0, 2) =  this->operator()(0,2) + trans(0, 2);
         this->operator()(0, 3) =  this->operator()(0,3) + trans(0, 3);

         this->operator()(1, 0) =  this->operator()(1,0) + trans(1, 0);
         this->operator()(1, 1) =  this->operator()(1,1) + trans(1, 1);
         this->operator()(1, 2) =  this->operator()(1,2) + trans(1, 2);
         this->operator()(1, 3) =  this->operator()(1,3) + trans(1, 3);

         this->operator()(2, 0) =  this->operator()(2,0) + trans(2, 0);
         this->operator()(2, 1) =  this->operator()(2,1) + trans(2, 1);
         this->operator()(2, 2) =  this->operator()(2,2) + trans(2, 2);
         this->operator()(2, 3) =  this->operator()(2,3) + trans(2, 3);

         this->operator()(3, 0) =  this->operator()(3,0) + trans(3, 0);
         this->operator()(3, 1) =  this->operator()(3,1) + trans(3, 1);
         this->operator()(3, 2) =  this->operator()(3,2) + trans(3, 2);
         this->operator()(3, 3) =  this->operator()(3,3) + trans(3, 3);

        return *this;
    };

    constexpr Transformation operator-(const Transformation& trans)
    {
        Transformation result;

        result(0, 0) =  this->operator()(0,0) - trans(0, 0);
        result(0, 1) =  this->operator()(0,1) - trans(0, 1);
        result(0, 2) =  this->operator()(0,2) - trans(0, 2);
        result(0, 3) =  this->operator()(0,3) - trans(0, 3);

        result(1, 0) =  this->operator()(1,0) - trans(1, 0);
        result(1, 1) =  this->operator()(1,1) - trans(1, 1);
        result(1, 2) =  this->operator()(1,2) - trans(1, 2);
        result(1, 3) =  this->operator()(1,3) - trans(1, 3);

        result(2, 0) =  this->operator()(2,0) - trans(2, 0);
        result(2, 1) =  this->operator()(2,1) - trans(2, 1);
        result(2, 2) =  this->operator()(2,2) - trans(2, 2);
        result(2, 3) =  this->operator()(2,3) - trans(2, 3);

        result(3, 0) =  this->operator()(3,0) - trans(3, 0);
        result(3, 1) =  this->operator()(3,1) - trans(3, 1);
        result(3, 2) =  this->operator()(3,2) - trans(3, 2);
        result(3, 3) =  this->operator()(3,3) - trans(3, 3);

        return result;
    };

    constexpr Transformation& operator-=(const Transformation& trans)
    {
         this->operator()(0, 0) =  this->operator()(0,0) - trans(0, 0);
         this->operator()(0, 1) =  this->operator()(0,1) - trans(0, 1);
         this->operator()(0, 2) =  this->operator()(0,2) - trans(0, 2);
         this->operator()(0, 3) =  this->operator()(0,3) - trans(0, 3);

         this->operator()(1, 0) =  this->operator()(1,0) - trans(1, 0);
         this->operator()(1, 1) =  this->operator()(1,1) - trans(1, 1);
         this->operator()(1, 2) =  this->operator()(1,2) - trans(1, 2);
         this->operator()(1, 3) =  this->operator()(1,3) - trans(1, 3);

         this->operator()(2, 0) =  this->operator()(2,0) - trans(2, 0);
         this->operator()(2, 1) =  this->operator()(2,1) - trans(2, 1);
         this->operator()(2, 2) =  this->operator()(2,2) - trans(2, 2);
         this->operator()(2, 3) =  this->operator()(2,3) - trans(2, 3);

         this->operator()(3, 0) =  this->operator()(3,0) - trans(3, 0);
         this->operator()(3, 1) =  this->operator()(3,1) - trans(3, 1);
         this->operator()(3, 2) =  this->operator()(3,2) - trans(3, 2);
         this->operator()(3, 3) =  this->operator()(3,3) - trans(3, 3);

        return *this;
    };

    constexpr Transformation operator*(const std::double_t k)
    {
        Transformation result;

        result(0,0) = this->operator() (0,0) * k;
        result(0,1) = this->operator() (0,1) * k;
        result(0,2) = this->operator() (0,2) * k;
        result(0,3) = this->operator() (0,3) * k;

        result(1,0) = this->operator() (1,0) * k;
        result(1,1) = this->operator() (1,1) * k;
        result(1,2) = this->operator() (1,2) * k;
        result(1,3) = this->operator() (1,3) * k;

        result(2,0) = this->operator() (2,0) * k;
        result(2,1) = this->operator() (2,1) * k;
        result(2,2) = this->operator() (2,2) * k;
        result(2,3) = this->operator() (2,3) * k;

        result(3,0) = this->operator() (3,0) * k;
        result(3,1) = this->operator() (3,1) * k;
        result(3,2) = this->operator() (3,2) * k;
        result(3,3) = this->operator() (3,3) * k;

        return result;
    }

    constexpr Transformation operator*(const Transformation& trans)
    {
        const std::double_t m00 =  this->operator()(0,0) * trans(0,0) +  this->operator()(0,1) * trans(1,0) +  this->operator()(0,2) * trans(2,0)+  this->operator()(0,3) * trans(3,0);
        const std::double_t m01 =  this->operator()(0,0) * trans(0,1) +  this->operator()(0,1) * trans(1,1) +  this->operator()(0,2) * trans(2,1)+  this->operator()(0,3) * trans(3,1);
        const std::double_t m02 =  this->operator()(0,0) * trans(0,2) +  this->operator()(0,1) * trans(1,2) +  this->operator()(0,2) * trans(2,2)+  this->operator()(0,3) * trans(3,2);
        const std::double_t m03 =  this->operator()(0,0) * trans(0,3) +  this->operator()(0,1) * trans(1,3) +  this->operator()(0,2) * trans(2,3)+  this->operator()(0,3) * trans(3,3);

        const std::double_t m10 =  this->operator()(1,0) * trans(0,0) +  this->operator()(1,1) * trans(1,0) +  this->operator()(1,2) * trans(2,0)+  this->operator()(1,3) * trans(3,0);
        const std::double_t m11 =  this->operator()(1,0) * trans(0,1) +  this->operator()(1,1) * trans(1,1) +  this->operator()(1,2) * trans(2,1)+  this->operator()(1,3) * trans(3,1);
        const std::double_t m12 =  this->operator()(1,0) * trans(0,2) +  this->operator()(1,1) * trans(1,2) +  this->operator()(1,2) * trans(2,2)+  this->operator()(1,3) * trans(3,2);
        const std::double_t m13 =  this->operator()(1,0) * trans(0,3) +  this->operator()(1,1) * trans(1,3) +  this->operator()(1,2) * trans(2,3)+  this->operator()(1,3) * trans(3,3);

        const std::double_t m20 =  this->operator()(2,0) * trans(0,0) +  this->operator()(2,1) * trans(1,0) +  this->operator()(2,2) * trans(2,0)+  this->operator()(2,3) * trans(3,0);
        const std::double_t m21 =  this->operator()(2,0) * trans(0,1) +  this->operator()(2,1) * trans(1,1) +  this->operator()(2,2) * trans(2,1)+  this->operator()(2,3) * trans(3,1);
        const std::double_t m22 =  this->operator()(2,0) * trans(0,2) +  this->operator()(2,1) * trans(1,2) +  this->operator()(2,2) * trans(2,2)+  this->operator()(2,3) * trans(3,2);
        const std::double_t m23 =  this->operator()(2,0) * trans(0,3) +  this->operator()(2,1) * trans(1,3) +  this->operator()(2,2) * trans(2,3)+  this->operator()(2,3) * trans(3,3);

        const std::double_t m30 =  this->operator()(3,0) * trans(0,0) +  this->operator()(3,1) * trans(1,0) +  this->operator()(3,2) * trans(2,0)+  this->operator()(3,3) * trans(3,0);
        const std::double_t m31 =  this->operator()(3,0) * trans(0,1) +  this->operator()(3,1) * trans(1,1) +  this->operator()(3,2) * trans(2,1)+  this->operator()(3,3) * trans(3,1);
        const std::double_t m32 =  this->operator()(3,0) * trans(0,2) +  this->operator()(3,1) * trans(1,2) +  this->operator()(3,2) * trans(2,2)+  this->operator()(3,3) * trans(3,2);
        const std::double_t m33 =  this->operator()(3,0) * trans(0,3) +  this->operator()(3,1) * trans(1,3) +  this->operator()(3,2) * trans(2,3)+  this->operator()(3,3) * trans(3,3);


        return 
        {
            m00, m01, m02, m03,
            m10, m11, m12, m13,
            m20, m21, m22, m23,
            m30, m31, m32, m33
        };
    }

    constexpr Point3 operator()(const Point3& p) 
    {
        const std::double_t x =  this->operator()(0,0) * p.x +  this->operator()(0,1) * p.y +  this->operator()(0,2) * p.z + this->operator()(0,3);
        const std::double_t y =  this->operator()(1,0) * p.x +  this->operator()(1,1) * p.y +  this->operator()(1,2) * p.z + this->operator()(1,3);
        const std::double_t z =  this->operator()(2,0) * p.x +  this->operator()(2,1) * p.y +  this->operator()(2,2) * p.z + this->operator()(2,3);

        return {x, y, z};
    }

    constexpr Vector3 operator()(const Vector3& u) 
    {
        const std::double_t x =  this->operator()(0,0) * u.x +  this->operator()(0,1) * u.y +  this->operator()(0,2) * u.z;
        const std::double_t y =  this->operator()(1,0) * u.x +  this->operator()(1,1) * u.y +  this->operator()(1,2) * u.z;
        const std::double_t z =  this->operator()(2,0) * u.x +  this->operator()(2,1) * u.y +  this->operator()(2,2) * u.z;

        return {x, y, z};
    }

    constexpr Ray operator()(const Ray& ray) 
    {
        return{this->operator()(ray.origin), this->operator()(ray.direction), ray.t};
    }

};

constexpr std::double_t Determinant(const Transformation& trans)
{
    const std::double_t c00 = trans(0,0) * trans(1,1);
    const std::double_t c01 = trans(0,0) * trans(1,2);
    const std::double_t c02 = trans(0,0) * trans(1,3);
    
    const std::double_t c03 = trans(0,1) * trans(1,0);
    const std::double_t c04 = trans(0,1) * trans(1,2);
    const std::double_t c05 = trans(0,1) * trans(1,3);

    const std::double_t c06 = trans(0,2) * trans(1,0);
    const std::double_t c07 = trans(0,2) * trans(1,1);
    const std::double_t c08 = trans(0,2) * trans(1,3);

    const std::double_t c09 = trans(0,3) * trans(1,0);
    const std::double_t c10 = trans(0,3) * trans(1,1);
    const std::double_t c11 = trans(0,3) * trans(1,2);


    std::double_t a      =   c00 * (trans(2,2) * trans(3,3) - trans(2,3) * trans(3,2)) - c01 * (trans(2,1) * trans(3,3) - trans(2,3) * trans(3,1)) + c02 * (trans(2,1) * trans(3,2) - trans(2,2) * trans(3,1));
    std::double_t b      = - c03 * (trans(2,2) * trans(3,3) - trans(2,3) * trans(3,2)) + c04 * (trans(2,0) * trans(3,3) - trans(2,3) * trans(3,0)) - c05 * (trans(2,0) * trans(3,2) - trans(2,2) * trans(3,0));
    std::double_t c      =   c06 * (trans(2,1) * trans(3,3) - trans(2,3) * trans(3,1)) - c07 * (trans(2,0) * trans(3,3) - trans(2,3) * trans(3,0)) + c08 * (trans(2,0) * trans(3,1) - trans(2,1) * trans(3,0));
    std::double_t d      = - c09 * (trans(2,1) * trans(3,2) - trans(2,2) * trans(3,1)) + c10 * (trans(2,0) * trans(3,2) - trans(2,2) * trans(3,0)) - c11 * (trans(2,0) * trans(3,1) - trans(2,1) * trans(3,0));

    std::double_t result = a + b + c + d;

    return result;
}

constexpr std::optional<Transformation> Inverse(const Transformation& trans)
{
    std::double_t det = Determinant(trans);

    if(det == 0.0)
    {
        std::printf("This matrix is not incersible.\n");
        return {};
    }

    Transformation result;

    result(0,0) = +(trans(1,1) * (trans(2,2)*trans(3,3) - trans(2,3)*trans(3,2))
                       - trans(1,2) * (trans(2,1)*trans(3,3) - trans(2,3)*trans(3,1))
                       + trans(1,3) * (trans(2,1)*trans(3,2) - trans(2,2)*trans(3,1)));

    result(0,1) = -(trans(0,1) * (trans(2,2)*trans(3,3) - trans(2,3)*trans(3,2))
                       - trans(0,2) * (trans(2,1)*trans(3,3) - trans(2,3)*trans(3,1))
                       + trans(0,3) * (trans(2,1)*trans(3,2) - trans(2,2)*trans(3,1)));

    result(0,2) = + (trans(0,1) * (trans(1,2)*trans(3,3) - trans(1,3)*trans(3,2))
                        - trans(0,2) * (trans(1,1)*trans(3,3) - trans(1,3)*trans(3,1))
                        + trans(0,3) * (trans(1,1)*trans(3,2) - trans(1,2)*trans(3,1)));

    result(0,3) = -(trans(0,1) * (trans(1,2)*trans(2,3) - trans(1,3)*trans(2,2))
                       - trans(0,2) * (trans(1,1)*trans(2,3) - trans(1,3)*trans(2,1))
                       + trans(0,3) * (trans(1,1)*trans(2,2) - trans(1,2)*trans(2,1)));

    result(1, 0) =  -(trans(1,0) * (trans(2,2)*trans(3,3) - trans(2,3)*trans(3,2))
                        - trans(1,2) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(1,3) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0)));

    result(1,1) =    trans(0,0) * (trans(2,2)*trans(3,3) - trans(2,3)*trans(3,2))
                        - trans(0,2) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(0,3) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0));

    result(1, 2) =  -(trans(0,0) * (trans(1,2)*trans(3,3) - trans(1,3)*trans(3,2))
                        - trans(0,2) * (trans(1,0)*trans(3,3) - trans(1,3)*trans(3,0))
                        + trans(0,3) * (trans(1,0)*trans(3,2) - trans(1,2)*trans(3,0)));

    result(1, 3) =  +(trans(0,0) * (trans(1,2)*trans(2,3) - trans(1,3)*trans(2,2))
                        - trans(0,2) * (trans(1,0)*trans(2,3) - trans(1,3)*trans(2,0))
                        + trans(0,3) * (trans(1,0)*trans(2,2) - trans(1,2)*trans(2,0)));

    result(2, 0) =  +(trans(1,0) * (trans(2,1)*trans(3,3) - trans(2,3)*trans(3,1))
                        - trans(1,1) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(1,3) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0)));

    result(2, 1) =  -(trans(0,0) * (trans(2,1)*trans(3,3) - trans(2,3)*trans(3,1))
                        - trans(0,1) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(0,3) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0)));

    result(2,2) =  +(trans(0,0) * (trans(1,1)*trans(3,3) - trans(1,3)*trans(3,1))
                        - trans(0,1) * (trans(1,0)*trans(3,3) - trans(1,3)*trans(3,0))
                        + trans(0,3) * (trans(1,0)*trans(3,1) - trans(1,1)*trans(3,0)));

    result(2, 3) =  -(trans(0,0) * (trans(1,1)*trans(2,3) - trans(1,3)*trans(2,1))
                        - trans(0,1) * (trans(1,0)*trans(2,3) - trans(1,3)*trans(2,0))
                        + trans(0,3) * (trans(1,0)*trans(2,1) - trans(1,1)*trans(2,0)));


    result(3, 0) =  -(trans(1,0) * (trans(2,1)*trans(3,2) - trans(2,2)*trans(3,1))
                        - trans(1,1) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0))
                        + trans(1,2) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0)));

    result(3, 1) =    trans(0,0) * (trans(2,1)*trans(3,2) - trans(2,2)*trans(3,1))
                        - trans(0,1) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0))
                        + trans(0,2) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0));

    result(3, 2) =  -(trans(0,0) * (trans(1,1)*trans(3,2) - trans(1,2)*trans(3,1))
                        - trans(0,1) * (trans(1,0)*trans(3,2) - trans(1,2)*trans(3,0))
                        + trans(0,2) * (trans(1,0)*trans(3,1) - trans(1,1)*trans(3,0)));

    result(3,3) =    trans(0,0) * (trans(1,1)*trans(2,2) - trans(1,2)*trans(2,1))
                        - trans(0,1) * (trans(1,0)*trans(2,2) - trans(1,2)*trans(2,0))
                        + trans(0,2) * (trans(1,0)*trans(2,1) - trans(1,1)*trans(2,0));

    return result*(1.0/det);
}

constexpr Transformation Transpose(const Transformation& trans)
{
    Transformation result;

    result(0,0) = trans(0,0);
    result(0,1) = trans(1,0);
    result(0,2) = trans(2,0);
    result(0,3) = trans(3,0);

    result(1,0) = trans(0,1);
    result(1,1) = trans(1,1);
    result(1,2) = trans(2,1);
    result(1,3) = trans(3,1);

    result(2,0) = trans(0,2);
    result(2,1) = trans(1,2);
    result(2,2) = trans(2,2);
    result(2,3) = trans(3,2);

    result(3,0) = trans(0,3);
    result(3,1) = trans(1,3);
    result(3,2) = trans(2,3);
    result(3,3) = trans(3,3);

    return result;
}

constexpr Transformation Translation(std::double_t dx, std::double_t dy, std::double_t dz)
{
    return {
        1.0,0.0,  0.0, dx,
        0.0  ,1.0,0.0, dy,
        0.0  ,0.0,  1.0, dz,
        0.0  ,0.0,  0.0, 1.0
    };
}



constexpr Transformation Translation(const Vector3& du)
{
    return {
        1.0,0.0,  0.0, du.x,
        0.0  ,1.0,0.0, du.y,
        0.0  ,0.0,  1.0, du.z,
        0.0  ,0.0,  0.0, 1.0
    };
}

constexpr Transformation Translation(const Point3& du)
{
    return {
        1.0,0.0,  0.0, du.x,
        0.0  ,1.0,0.0, du.y,
        0.0  ,0.0,  1.0, du.z,
        0.0  ,0.0,  0.0, 1.0
    };
}

constexpr Transformation Scale(std::double_t kx, std::double_t ky, std::double_t kz)
{
    return {
        kx,0.0,  0.0, 0.0,
        0.0  ,ky,0.0, 0.0,
        0.0  ,0.0,  kz, 0.0,
        0.0  ,0.0,  0.0, 1.0
    };
}


constexpr Transformation RotationX(const std::double_t rad)
{
    return {
        1.0, 0.0, 0.0, 0.0,
        0.0, std::cos(rad), -std::sin(rad), 0.0,
        0.0, std::sin(rad),  std::cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0,

    };
}

constexpr Transformation RotationY(const std::double_t rad)
{
    return {
        std::cos(rad), 0.0,  std::sin(rad), 0.0,
        0.0,             1.0,  0.0,              0.0,
        -std::sin(rad), 0.0,  std::cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0,

    };
}

constexpr Transformation RotationZ(const std::double_t rad)
{
    return {
        std::cos(rad),-std::sin(rad), 0.0, 0.0,
        std::sin(rad), std::cos(rad), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,

    };
}

constexpr Transformation Basis(const Vector3& u, const Vector3& v, const Vector3& w)
{
    return {
        u.x,v.x,w.x,0.0,
        u.y,v.y,w.y,0.0,
        u.z,v.z,w.z,0.0,
        0.0,0.0,0.0,1.0
    };
}

constexpr Transformation NDCFromRaster(std::double_t w, std::double_t h)
{
    return Scale(1.0/w, 1.0/h, 1.0) * Translation(0.5, 0.5, 0);
}

constexpr Transformation ScreenFromNDC(const std::double_t aspect_ratio, const std::double_t fov)
{
    return Translation(-aspect_ratio*fov, fov, 0) * Scale(2.0*aspect_ratio*fov, -2.0*fov, 1.0);
}

constexpr Transformation LookAt( Camera& cam)
{
    return Translation(cam.position) * (Basis(cam.right, cam.up, -cam.front));
}

}

#endif