#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <vecmath.hpp>


#define REQUIRE_TUPLE(u, real_res, EPSILON) \
{ \
    REQUIRE_THAT( u.x,Catch::Matchers::WithinAbs(real_res.x, EPSILON)); \
    REQUIRE_THAT( u.y,Catch::Matchers::WithinAbs(real_res.y, EPSILON)); \
    REQUIRE_THAT( u.z,Catch::Matchers::WithinAbs(real_res.z, EPSILON)); \
}


TEST_CASE("Vector is properly initialized by default to zero", "[Vector3]")
{
    PBR_::Vector3 u;

    REQUIRE_THAT( u.x,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
    REQUIRE_THAT( u.y,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
    REQUIRE_THAT( u.z,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
}



TEST_CASE("Vector is properly initialized with input values", "[Vector3]")
{
    const std::double_t x = -10;
    const std::double_t y = 0.2233655;
    const std::double_t z = -788;

    PBR_::Vector3 u{x, y, z};

    REQUIRE_THAT( u.x,Catch::Matchers::WithinAbs(x, EPSILONv5));
    REQUIRE_THAT( u.y,Catch::Matchers::WithinAbs(y, EPSILONv5));
    REQUIRE_THAT( u.z,Catch::Matchers::WithinAbs(z, EPSILONv5));
}

TEST_CASE("Vector is properly initialized with copy constructor", "[Vector3]")
{
    const std::double_t x = -10;
    const std::double_t y = 0.2233655;
    const std::double_t z = -788;

    PBR_::Vector3 u{x, y, z};
    PBR_::Vector3 v{u};

    REQUIRE_THAT( v.x,Catch::Matchers::WithinAbs(u.x, EPSILONv5));
    REQUIRE_THAT( v.y,Catch::Matchers::WithinAbs(u.y, EPSILONv5));
    REQUIRE_THAT( v.z,Catch::Matchers::WithinAbs(u.z, EPSILONv5));

    PBR_::Vector3 w = u;

    REQUIRE_THAT( w.x,Catch::Matchers::WithinAbs(u.x, EPSILONv5));
    REQUIRE_THAT( w.y,Catch::Matchers::WithinAbs(u.y, EPSILONv5));
    REQUIRE_THAT( w.z,Catch::Matchers::WithinAbs(u.z, EPSILONv5));

}

TEST_CASE("Vector's arithmetic operator", "[Vector3]")
{

    const std::double_t ux = -10;
    const std::double_t uy = 0.2233655;
    const std::double_t uz = -788;

    const std::double_t vx = 7855.0555;
    const std::double_t vy = -55211;
    const std::double_t vz = -6;

    const std::double_t k = 54.00588778;

    PBR_::Vector3 real_res_u_plus_v = {7845.0555, -55210.7766345, -794};
    PBR_::Vector3 real_res_u_minus_v = {-7865.0555, 55211.2233655, -782};
    PBR_::Vector3 real_res_u_over_k = {-0.185164996097, 0.004135947194, -14.591001692445};

    PBR_::Vector3 real_res_plus_v = {15700.1110, -110421.7766345, -800};
    PBR_::Vector3 real_res_minus_v = {-15720.1110, 110422.2233655, -776};
    PBR_::Vector3 real_res_over_k = {-0.003428607578, 0.000076583265, -0.270174277143};

    std::double_t real_res_dot = -86154.7876205;

    PBR_::Vector3 u {ux, uy, uz};
    PBR_::Vector3 v {vx, vy, vz};

    PBR_::Vector3 w0  = u + v;
    PBR_::Vector3 w1  = u - v;
    PBR_::Vector3 w2  = u / k;

    std::double_t dot = u * v;

    REQUIRE_TUPLE(w0, real_res_u_plus_v, EPSILONv5);
    REQUIRE_TUPLE(w1, real_res_u_minus_v, EPSILONv5);
    REQUIRE_TUPLE(w2, real_res_u_over_k, EPSILONv5);

    REQUIRE_THAT(dot, Catch::Matchers::WithinAbs(real_res_dot, EPSILONv5));

    w0 += v;
    w1 -= v;
    w2 /= k;

    REQUIRE_TUPLE(w0, real_res_plus_v, EPSILONv5);
    REQUIRE_TUPLE(w1, real_res_minus_v, EPSILONv5);
    REQUIRE_TUPLE(w2, real_res_over_k, EPSILONv5);
}

TEST_CASE("Vector's magnitude", "[Vector3]")
{

    const std::double_t ux = -10;
    const std::double_t uy = 0.2233655;
    const std::double_t uz = -788;

    const std::double_t vx = 7855.0555;
    const std::double_t vy = -55211;
    const std::double_t vz = -6;

    PBR_::Vector3 u {ux, uy, uz};
    PBR_::Vector3 v {vx, vy, vz};

    std::double_t real_res_magnitude_u = 788.0634808771;
    std::double_t real_res_magnitude_v = 55766.9835467912;

    REQUIRE_THAT(PBR_::magnitude(u),Catch::Matchers::WithinAbs(real_res_magnitude_u, EPSILONv5));
    REQUIRE_THAT(PBR_::magnitude(v),Catch::Matchers::WithinAbs(real_res_magnitude_v, EPSILONv5));

}

TEST_CASE("Vector3's normalize", "[Vector3]")
{

    const std::double_t ux = -10;
    const std::double_t uy = 0.2233655;
    const std::double_t uz = -788;

    const std::double_t vx = 7855.0555;
    const std::double_t vy = -55211;
    const std::double_t vz = -6;

    PBR_::Vector3 u{ux, uy, uz};
    PBR_::Vector3 v{vx, vy, vz};

    PBR_::Vector3 real_res_nu = {-0.012689333084, 0.000283435923, -0.999919447001};
    PBR_::Vector3 real_res_nv = {0.140854946788, -0.990030238119, -0.000107590542};

    PBR_::Vector3 nu = PBR_::normalize(u);
    PBR_::Vector3 nv = PBR_::normalize(v);

    REQUIRE_TUPLE(nu, real_res_nu, EPSILONv5);
    REQUIRE_TUPLE(nv, real_res_nv, EPSILONv5);
}

TEST_CASE("Vector's cross", "[Vector3]")
{

    const std::double_t ux = -10;
    const std::double_t uy = 0.2233655;
    const std::double_t uz = -788;

    const std::double_t vx = 7855.0555;
    const std::double_t vy = -55211;
    const std::double_t vz = -6;

    PBR_::Vector3 u{ux, uy, uz};
    PBR_::Vector3 v{vx, vy, vz};

    PBR_::Vector3 real_res_uxv = {-43506269.3401930, -6189843.7340, 550355.45160071475};
    PBR_::Vector3 real_res_vxu = {43506269.3401930, 6189843.7340, -550355.45160071475};

    PBR_::Vector3 uxv = PBR_::cross(u, v);
    PBR_::Vector3 vxu = PBR_::cross(v, u);

    REQUIRE_TUPLE(uxv, real_res_uxv, EPSILONv5);
    REQUIRE_TUPLE(vxu, real_res_vxu, EPSILONv5);
}

TEST_CASE("Vector's Coordinate System", "[Vector3]")
{

    const std::double_t ux = -10;
    const std::double_t uy = 0.2233655;
    const std::double_t uz = -788;

    const std::double_t vx = 7855.0555;
    const std::double_t vy = -55211;
    const std::double_t vz = -6;

    PBR_::Vector3 real_res_nut = { 0.9999194871701697,  1.798378849146404e-06, -0.01268933308376384};
    PBR_::Vector3 real_res_nub = {-1.798378849146404e-06,  0.9999999598304209,  0.0002834359228921452};

    PBR_::Vector3 real_res_nvt = { 0.9801620183446066,  0.1394356545508717,  0.1408549467878109};
    PBR_::Vector3 real_res_nvb = {-0.1394356545508717,  0.01994557219765325, -0.9900302381188557};

    PBR_::Vector3 u{ux, uy, uz};
    PBR_::Vector3 v{vx, vy, vz};

    PBR_::Vector3 nu = PBR_::normalize(u);
    PBR_::Vector3 nv = PBR_::normalize(v);

    auto [nut, nub] = PBR_::CoordinateSystem(nu);
    auto [nvt, nvb] = PBR_::CoordinateSystem(nv);


    REQUIRE_TUPLE(nut, real_res_nut, EPSILONv5);
    REQUIRE_TUPLE(nub, real_res_nub, EPSILONv5);

    REQUIRE_TUPLE(nvt, real_res_nvt, EPSILONv5);
    REQUIRE_TUPLE(nvb, real_res_nvb, EPSILONv5);
}

TEST_CASE("Vector's Flip", "[Vector3]")
{
    const std::double_t nx = 0.0;
    const std::double_t ny = 1.0;
    const std::double_t nz = 0.0;

    const std::double_t vx = 1.0;
    const std::double_t vy = 0.0;
    const std::double_t vz = 0.0;

    PBR_::Vector3 n{nx, ny, nz};
    PBR_::Vector3 v{vx, vy, vz};

    PBR_::Vector3 real_res_flipped_n = n;
    PBR_::Vector3 flipped_n = PBR_::flip(v, n);

    REQUIRE_TUPLE(flipped_n, real_res_flipped_n, EPSILONv5);    

    PBR_::Vector3 w{-0.8, -7, 0.0};
    real_res_flipped_n = -n;
    flipped_n = PBR_::flip(w, n);

    REQUIRE_TUPLE(flipped_n, real_res_flipped_n, EPSILONv5);
}




TEST_CASE("Point is properly initialized by default to zero", "[Point3]")
{
    PBR_::Point3 p;

    REQUIRE_THAT( p.x,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
    REQUIRE_THAT( p.y,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
    REQUIRE_THAT( p.z,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
}



TEST_CASE("Point is properly initialized with input values", "[Point3]")
{
    const std::double_t x = -10;
    const std::double_t y = 0.2233655;
    const std::double_t z = -788;

    PBR_::Point3 p{x, y, z};

    REQUIRE_THAT( p.x,Catch::Matchers::WithinAbs(x, EPSILONv5));
    REQUIRE_THAT( p.y,Catch::Matchers::WithinAbs(y, EPSILONv5));
    REQUIRE_THAT( p.z,Catch::Matchers::WithinAbs(z, EPSILONv5));
}

TEST_CASE("Point is properly initialized with copy constructor", "[Point3]")
{
    const std::double_t x = -10;
    const std::double_t y = 0.2233655;
    const std::double_t z = -788;

    PBR_::Point3 p{x, y, z};
    PBR_::Point3 c{p};

    REQUIRE_THAT( c.x,Catch::Matchers::WithinAbs(p.x, EPSILONv5));
    REQUIRE_THAT( c.y,Catch::Matchers::WithinAbs(p.y, EPSILONv5));
    REQUIRE_THAT( c.z,Catch::Matchers::WithinAbs(p.z, EPSILONv5));

    PBR_::Point3 o = p;

    REQUIRE_THAT( o.x,Catch::Matchers::WithinAbs(p.x, EPSILONv5));
    REQUIRE_THAT( o.y,Catch::Matchers::WithinAbs(p.y, EPSILONv5));
    REQUIRE_THAT( o.z,Catch::Matchers::WithinAbs(p.z, EPSILONv5));
}

TEST_CASE("Point's arithmetic operator [+, -, +=, -=]", "[Point3]")
{

    const std::double_t px = -10;
    const std::double_t py = 0.2233655;
    const std::double_t pz = -788;

    const std::double_t vx = 7855.0555;
    const std::double_t vy = -55211;
    const std::double_t vz = -6;

    PBR_::Point3 real_res_p_plus_v = {7845.0555, -55210.7766345, -794};
    PBR_::Point3 real_res_p_minus_v = {-7865.0555, 55211.2233655, -782};

    PBR_::Point3 real_res_plus_v = {15700.1110, -110421.7766345, -800};
    PBR_::Point3 real_res_minus_v = {-15720.1110, 110422.2233655, -776};

    PBR_::Point3 p {px, py, pz};
    PBR_::Vector3 v {vx, vy, vz};

    PBR_::Point3 w0  = p + v;
    PBR_::Point3 w1  = p - v;

    REQUIRE_TUPLE(w0, real_res_p_plus_v, EPSILONv5);
    REQUIRE_TUPLE(w1, real_res_p_minus_v, EPSILONv5);


    w0 += v;
    w1 -= v;

    REQUIRE_TUPLE(w0, real_res_plus_v, EPSILONv5);
    REQUIRE_TUPLE(w1, real_res_minus_v, EPSILONv5);

    PBR_::Point3 o{3, 3, 3};
    PBR_::Vector3 op = o - p;

    PBR_::Vector3 real_res_o_minus_p = {13, 2.7766345, 791};

    REQUIRE_TUPLE(op, real_res_o_minus_p, EPSILONv5);
}

TEST_CASE("Point's distance", "[Point3]")
{
    const std::double_t px = -10;
    const std::double_t py = 0.2233655;
    const std::double_t pz = -788;

    const std::double_t ox = 7855.0555;
    const std::double_t oy = -55211;
    const std::double_t oz = -6;

    const PBR_::Point3 p{px, py, pz};
    const PBR_::Point3 o{ox, oy, oz};

    const std::double_t dist = 55774.0962054358;

    REQUIRE_THAT(PBR_::distance(p, o),Catch::Matchers::WithinAbs(dist, EPSILONv5));
}
