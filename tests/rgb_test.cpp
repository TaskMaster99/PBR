#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <color.hpp>
#include <utils.hpp>


#define REQUIRE_TUPLE(u, real_res, EPSILON) \
{ \
    REQUIRE_THAT( u.r,Catch::Matchers::WithinAbs(real_res.r, EPSILON)); \
    REQUIRE_THAT( u.g,Catch::Matchers::WithinAbs(real_res.g, EPSILON)); \
    REQUIRE_THAT( u.b,Catch::Matchers::WithinAbs(real_res.b, EPSILON)); \
}


TEST_CASE("RGB is properly initialized by default to zero", "[RGB]")
{
    PBR_::RGB c;

    REQUIRE_THAT( c.r,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
    REQUIRE_THAT( c.g,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
    REQUIRE_THAT( c.b,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
}



TEST_CASE("RGB is properly initialized with input values", "[RGB]")
{
    const std::double_t r = -10;
    const std::double_t g = 0.2233655;
    const std::double_t b = -788;

        PBR_::RGB c{r, g, b};

    REQUIRE_THAT( c.r,Catch::Matchers::WithinAbs(10, EPSILONv5));
    REQUIRE_THAT( c.g,Catch::Matchers::WithinAbs(0.2233655, EPSILONv5));
    REQUIRE_THAT( c.b,Catch::Matchers::WithinAbs(788, EPSILONv5));
}

TEST_CASE("RGB is properly initialized with copy constructor", "[Vector3]")
{
    const std::double_t r = -10;
    const std::double_t g = 0.2233655;
    const std::double_t b = -788;

    PBR_::RGB c{r, g, b};
    PBR_::RGB l{c};

    REQUIRE_THAT( l.r,Catch::Matchers::WithinAbs(c.r, EPSILONv5));
    REQUIRE_THAT( l.g,Catch::Matchers::WithinAbs(c.g, EPSILONv5));
    REQUIRE_THAT( l.b,Catch::Matchers::WithinAbs(c.b, EPSILONv5));

    PBR_::RGB e = c;

    REQUIRE_THAT( e.r,Catch::Matchers::WithinAbs(c.r, EPSILONv5));
    REQUIRE_THAT( e.g,Catch::Matchers::WithinAbs(c.g, EPSILONv5));
    REQUIRE_THAT( e.b,Catch::Matchers::WithinAbs(c.b, EPSILONv5));

}

TEST_CASE("RGB's arithmetic operator", "[RGB]")
{
    const std::double_t cr = -10;
    const std::double_t cg = 0.2233655;
    const std::double_t cb = -788;

    const std::double_t lr = 7855.0555;
    const std::double_t lg = -55211;
    const std::double_t lb = -6;

    const std::double_t k = 54.00588778;

    PBR_::RGB real_res_c_plus_l = {7865.0555, 55211.2233655, 794};
    PBR_::RGB real_res_c_over_k = {0.185164996097, 0.004135947194, 14.591001692445};

    PBR_::RGB real_res_plus_l = {15720.1110, 110422.2233655, 800};
    PBR_::RGB real_res_over_k = {0.003428607578, 0.000076583265, 0.270174277143};

    PBR_::RGB c {cr, cg, cb};
    PBR_::RGB l {lr, lg, lb};

    PBR_::RGB e0  = c + l;
    PBR_::RGB e1  = c / k;

    REQUIRE_TUPLE(e0, real_res_c_plus_l, EPSILONv5);
    REQUIRE_TUPLE(e1, real_res_c_over_k, EPSILONv5);

    e0 += l;
    e1 /= k;

    REQUIRE_TUPLE(e0, real_res_plus_l, EPSILONv5);
    REQUIRE_TUPLE(e1, real_res_over_k, EPSILONv5);
}