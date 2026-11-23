#include "ray.hpp"
#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <limits>
#include <primitive.hpp>


TEST_CASE("Arbitrary sphere intersection","[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         1.0,
        {0.0, 0.0, 1.0}
    };

    PBR_::Sphere sph1 = {
         {-1.0, -1.0, 2.0},
         1.0,
        {0.0, 0.0, 0.0}
    };

    PBR_::Sphere sph2 = {
         {-1.0, -1.0, -2.0},
         1.0,
        {1.0, 0.6471, 0.0}
    };

    PBR_::Ray ray0 = {
        {0.0, 1.0, 1.0}, {-2.0, -2.0, -2.0}, 0.0
    };

    PBR_::Ray ray1 = {
        {0.0, -1, 1.025}, {-1 ,1.2, 2.7}, 0.0
    };

    PBR_::Ray ray2 = {
        {-1, -1, 4.025}, {-1.5 ,-1.5, -4.3}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == false));
    REQUIRE((intersect(sph1, ray0) == false));
    REQUIRE((intersect(sph2, ray0) == false));

    REQUIRE((intersect(sph0, ray1) == false));
    REQUIRE((intersect(sph1, ray1) == true));
    REQUIRE((intersect(sph2, ray1) == false));

    REQUIRE((intersect(sph0, ray2) == false));
    REQUIRE((intersect(sph1, ray2) == true));
    REQUIRE((intersect(sph2, ray2) == false));
}

TEST_CASE("Two intersections","[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         2.37,
        {0.0, 0.0, 1.0}
    };


    PBR_::Ray ray0 = {
        {-1.0,1.0,-1.0}, {1.00, 0.0,1.0}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == true));
    REQUIRE_THAT(ray0.t, Catch::Matchers::WithinAbs(0.324156928588, EPSILONv5));

}

TEST_CASE("Complete miss","[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         2.37,
        {0.0, 0.0, 1.0}
    };


    PBR_::Ray ray0 = {
        {-2.4,2.1,0.84}, {1.00, 0.0,1.0}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == false));
    REQUIRE_THAT(ray0.t, Catch::Matchers::WithinAbs(std::numeric_limits<std::double_t>::lowest(), EPSILONv5));

}

TEST_CASE("Ray pointing away", "[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         2.37,
        {0.0, 0.0, 1.0}
    };


    PBR_::Ray ray0 = {
        {-2.4,2.1,0.84}, {0.00, 0.0,1.0}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == false));
    REQUIRE_THAT(ray0.t, Catch::Matchers::WithinAbs(std::numeric_limits<std::double_t>::lowest(), EPSILONv5));

}

TEST_CASE("Origin inside sphere", "[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         2.37,
        {0.0, 0.0, 1.0}
    };


    PBR_::Ray ray0 = {
        {1.0, 1.0, 1.0}, {0.0, 0.0,1.0}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == true));
    REQUIRE_THAT(ray0.t, Catch::Matchers::WithinAbs(2.37, EPSILONv5));
}

TEST_CASE("Tangent ray", "[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         2.37,
        {0.0, 0.0, 1.0}
    };


    PBR_::Ray ray0 = {
        {2.2, -1.1, 1.0}, {-0.6, 0.0,1.0}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == true));
    REQUIRE_THAT(ray0.t, Catch::Matchers::WithinAbs(0.199442436153, EPSILONv5));
}


TEST_CASE("Origin on surface, outward", "[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         2.37,
        {0.0, 0.0, 1.0}
    };


    PBR_::Ray ray0 = {
        {1.0, -1.36, 0.7}, {2.8, -4.0,1.0}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == false));
    REQUIRE_THAT(ray0.t, Catch::Matchers::WithinAbs(std::numeric_limits<std::double_t>::lowest(), EPSILONv5));
}

TEST_CASE("Origin on surface, inward", "[Sphere]")
{
    PBR_::Sphere sph0 = {
         {1.0, 1.0, 1.0},
         2.37,
        {0.0, 0.0, 1.0}
    };


    PBR_::Ray ray0 = {
        {1.0, -1.36, 0.7}, {2.8, 5.0,1.0}, 0.0
    };

    REQUIRE((intersect(sph0, ray0) == true));
    REQUIRE_THAT(ray0.t, Catch::Matchers::WithinAbs(0.00176883794109, EPSILONv5));
}