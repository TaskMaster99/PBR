#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <rng.hpp>

TEST_CASE("Seed still same across RNG","[RNG]")
{
    const std::uint8_t n = 128;

    PBR_::LCGEngine lcg0{65};
    PBR_::LCGEngine lcg1{65};

    PBR_::PCGEngine pcg0{458};
    PBR_::PCGEngine pcg1{458};

    for(std::uint8_t i = 0; i < n; ++i)
    {
        REQUIRE(lcg0.next() == lcg1.next());
        REQUIRE(pcg0.next() == pcg1.next());
    }

}


TEST_CASE("Seed follow the expected pattern","[RNG]")
{
    const std::uint64_t lcg_expected_seeds[10] = 
    {
        3916031, 1392223607, 120345137, 1858605732, 
        289408462, 37560379, 2064581282, 376838348, 
        592839833, 1682434798
    };

    const std::uint64_t pcg_expected_seeds[10] = 
    {
        29053652, 834078890, 831421985, 4046866903, 592970506,
        331237045, 3371395801, 4116351050, 418486, 2683398622
    };

    PBR_::LCGEngine lcg0{233};

    PBR_::PCGEngine pcg0{233};

    for(std::uint8_t i = 0; i < 10; ++i)
    {
        REQUIRE(lcg0.next() == lcg_expected_seeds[i]);
        REQUIRE(pcg0.next() == pcg_expected_seeds[i]);
    }
}

TEST_CASE("RNG generate value between two values","[RNG]")
{
    PBR_::LCGEngine lcg0{123456};
    PBR_::PCGEngine pcg0{123456};

    for(std::uint8_t i = 0; i < 100; ++i)
    {
        std::int64_t lcgIvalue  = randInt(lcg0, -1000, 1000);
        std::double_t lcgFvalue = randFloat(lcg0, -1000.0, 1000.0);

        std::int64_t pcgIvalue  = randInt(pcg0, -1000, 1000);
        std::double_t pcgFvalue = randFloat(pcg0, -1000.0, 1000.0);


        REQUIRE(((-1000 <= lcgIvalue) && (lcgIvalue <= 1000)));
        REQUIRE(((-1000.0 <= lcgFvalue) && (lcgFvalue <= 1000.0)));

        REQUIRE(((-1000 <= pcgIvalue) && (pcgIvalue <= 1000)));
        REQUIRE(((-1000.0 <= pcgFvalue) && (pcgFvalue <= 1000.0)));
    }
}