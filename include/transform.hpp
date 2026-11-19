#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP



#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <vecmath.hpp>
#include <cstdio>

namespace PBR_
{
struct Transformation
{
    public:
    std::double_t SquareMatrix4x4[16];

    constexpr Transformation()
    {
        SquareMatrix4x4[0]  = 1.0;SquareMatrix4x4[1]  = 0.0;SquareMatrix4x4[2]  = 0.0;SquareMatrix4x4[3]  = 0.0;
        SquareMatrix4x4[4]  = 0.0;SquareMatrix4x4[5]  = 1.0;SquareMatrix4x4[6]  = 0.0;SquareMatrix4x4[7]  = 0.0;
        SquareMatrix4x4[8]  = 0.0;SquareMatrix4x4[9]  = 0.0;SquareMatrix4x4[10] = 1.0;SquareMatrix4x4[11] = 0.0;
        SquareMatrix4x4[12] = 0.0;SquareMatrix4x4[13] = 0.0;SquareMatrix4x4[14] = 0.0;SquareMatrix4x4[15] = 1.0;
    }

    constexpr Transformation(const std::double_t m00, const std::double_t m01, const std::double_t m02, const std::double_t m03,
                             const std::double_t m04, const std::double_t m05, const std::double_t m06, const std::double_t m07,
                             const std::double_t m08, const std::double_t m09, const std::double_t m10, const std::double_t m11,
                             const std::double_t m12, const std::double_t m13, const std::double_t m14, const std::double_t m15)
    {
        SquareMatrix4x4[0]  = m00;SquareMatrix4x4[1]  = m01;SquareMatrix4x4[2]  = m02;SquareMatrix4x4[3]  = m03;
        SquareMatrix4x4[4]  = m04;SquareMatrix4x4[5]  = m05;SquareMatrix4x4[6]  = m06;SquareMatrix4x4[7]  = m07;
        SquareMatrix4x4[8]  = m08;SquareMatrix4x4[9]  = m09;SquareMatrix4x4[10] = m10;SquareMatrix4x4[11] = m11;
        SquareMatrix4x4[12] = m12;SquareMatrix4x4[13] = m13;SquareMatrix4x4[14] = m14;SquareMatrix4x4[15] = m15;
    }

    constexpr std::double_t  operator()(std::uint8_t i, std::uint8_t j) const {return SquareMatrix4x4[i*4+j];}
    constexpr std::double_t& operator()(std::uint8_t i, std::uint8_t j) {return SquareMatrix4x4[i*4+j];}

    constexpr Transformation(const Transformation& trans) = default;
    constexpr Transformation& operator=(const Transformation& trans) = default;

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
    constexpr Transformation& operator+=(const Transformation& trans)
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

    constexpr Vector3 operator()(const Vector3& u) 
    {
        const std::double_t x =  this->operator()(0,0) * u.x +  this->operator()(0,1) * u.y +  this->operator()(0,2) * u.z +  this->operator()(0, 3);
        const std::double_t y =  this->operator()(1,0) * u.x +  this->operator()(1,1) * u.y +  this->operator()(1,2) * u.z +  this->operator()(1, 3);
        const std::double_t z =  this->operator()(2,0) * u.x +  this->operator()(2,1) * u.y +  this->operator()(2,2) * u.z +  this->operator()(2, 3);

        return {x, y, z};
    }

};

constexpr std::double_t determinant(const Transformation& trans)
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
    std::double_t c      =   c06 * (trans(2,1) * trans(3,3) - trans(2,3) * trans(3,1)) - c07 * (trans(2,0) * trans(3,3) - trans(2,3)) * trans(3,0) + c08 * (trans(2,0) * trans(3,1) - trans(2,1) * trans(3,0));
    std::double_t d      = - c09 * (trans(2,1) * trans(3,2) - trans(2,2) * trans(3,1)) + c10 * (trans(2,0) * trans(3,2) - trans(2,2) * trans(3,0)) - c11 * (trans(2,0) * trans(3,1) - trans(2,1) * trans(3,0));

    std::double_t result = a + b + c + d;

    return result;
}

constexpr Transformation inverse(const Transformation& trans)
{
    std::double_t det = determinant(trans);

    if(det == 0.0)
    {
        std::printf("This matrix is not incersible.\n");
        std::exit(EXIT_FAILURE);
    }

    Transformation result;

    result(0,1) =  -(trans(1,0) * (trans(2,2)*trans(3,3) - trans(2,3)*trans(3,2))
                        - trans(1,2) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(1,3) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0)));

    result(1,1) =    trans(0,0) * (trans(2,2)*trans(3,3) - trans(2,3)*trans(3,2))
                        - trans(0,2) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(0,3) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0));

    result(2,1) =  -(trans(0,0) * (trans(1,2)*trans(3,3) - trans(1,3)*trans(3,2))
                        - trans(0,2) * (trans(1,0)*trans(3,3) - trans(1,3)*trans(3,0))
                        + trans(0,3) * (trans(1,0)*trans(3,2) - trans(1,2)*trans(3,0)));

    result(3,1) =  +(trans(0,0) * (trans(1,2)*trans(2,3) - trans(1,3)*trans(2,2))
                        - trans(0,2) * (trans(1,0)*trans(2,3) - trans(1,3)*trans(2,0))
                        + trans(0,3) * (trans(1,0)*trans(2,2) - trans(1,2)*trans(2,0)));

    result(0,2) =  +(trans(1,0) * (trans(2,1)*trans(3,3) - trans(2,3)*trans(3,1))
                        - trans(1,1) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(1,3) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0)));

    result(1,2) =  -(trans(0,0) * (trans(2,1)*trans(3,3) - trans(2,3)*trans(3,1))
                        - trans(0,1) * (trans(2,0)*trans(3,3) - trans(2,3)*trans(3,0))
                        + trans(0,3) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0)));

    result(2,2) =  +(trans(0,0) * (trans(1,1)*trans(3,3) - trans(1,3)*trans(3,1))
                        - trans(0,1) * (trans(1,0)*trans(3,3) - trans(1,3)*trans(3,0))
                        + trans(0,3) * (trans(1,0)*trans(3,1) - trans(1,1)*trans(3,0)));

    result(3,2) =  -(trans(0,0) * (trans(1,1)*trans(2,3) - trans(1,3)*trans(2,1))
                        - trans(0,1) * (trans(1,0)*trans(2,3) - trans(1,3)*trans(2,0))
                        + trans(0,3) * (trans(1,0)*trans(2,1) - trans(1,1)*trans(2,0)));


    result(0,3) =  -(trans(1,0) * (trans(2,1)*trans(3,2) - trans(2,2)*trans(3,1))
                        - trans(1,1) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0))
                        + trans(1,2) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0)));

    result(1,3) =    trans(0,0) * (trans(2,1)*trans(3,2) - trans(2,2)*trans(3,1))
                        - trans(0,1) * (trans(2,0)*trans(3,2) - trans(2,2)*trans(3,0))
                        + trans(0,2) * (trans(2,0)*trans(3,1) - trans(2,1)*trans(3,0));

    result(2,3) =  -(trans(0,0) * (trans(1,1)*trans(3,2) - trans(1,2)*trans(3,1))
                        - trans(0,1) * (trans(1,0)*trans(3,2) - trans(1,2)*trans(3,0))
                        + trans(0,2) * (trans(1,0)*trans(3,1) - trans(1,1)*trans(3,0)));

    result(3,3) =    trans(0,0) * (trans(1,1)*trans(2,2) - trans(1,2)*trans(2,1))
                        - trans(0,1) * (trans(1,0)*trans(2,2) - trans(1,2)*trans(2,0))
                        + trans(0,2) * (trans(1,0)*trans(2,1) - trans(1,1)*trans(2,0));

    return result*(1.0/std::abs(det));
}

constexpr Transformation transpose(const Transformation& trans)
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

    result(3,0) = trans(0,2);
    result(3,1) = trans(1,2);
    result(3,2) = trans(2,2);
    result(3,3) = trans(3,2);

    return result;
}

constexpr Transformation RasterToNDC(std::double_t w, std::double_t h)
{
    return {
        1.0/w,0.0,  0.0, 0.0,
        0.0  ,1.0/h,0.0, 0.0,
        0.0  ,0.0,  1.0, 0.0,
        0.0  ,0.0,  0.0, 1.0
    };
}

constexpr Transformation NDCToScreen(const std::double_t aspect_ratio, const std::double_t fov)
{
    return {
        2.0 * fov * aspect_ratio , 0.0 ,0.0,-fov * aspect_ratio,
        0.0                      ,-2.0, 0.0, fov,
        0.0                      , 0.0 ,1.0, 0.0,
        0.0                      , 0.0, 0.0, 1.0
    };
}

}


#endif