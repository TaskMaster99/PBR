#include "vecmath.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <ray.hpp>
#include <transform.hpp>
#include <utils.hpp>

#define REQUIRE_TRANSFORMATIONv0(trans, real_res, EPSILON)                     \
  {                                                                            \
    REQUIRE_THAT(trans(0, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res(0, 0), EPSILON));         \
    REQUIRE_THAT(trans(0, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res(0, 1), EPSILON));         \
    REQUIRE_THAT(trans(0, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res(0, 2), EPSILON));         \
    REQUIRE_THAT(trans(0, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res(0, 3), EPSILON));          \
                                                                               \
    REQUIRE_THAT(trans(1, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res(1, 0), EPSILON));         \
    REQUIRE_THAT(trans(1, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res(1, 1), EPSILON));         \
    REQUIRE_THAT(trans(1, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res(1, 2), EPSILON));         \
    REQUIRE_THAT(trans(1, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res(1, 3), EPSILON));          \
                                                                               \
    REQUIRE_THAT(trans(2, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res(2, 0), EPSILON));         \
    REQUIRE_THAT(trans(2, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res(2, 1), EPSILON));         \
    REQUIRE_THAT(trans(2, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res(2, 2), EPSILON));         \
    REQUIRE_THAT(trans(2, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res(2, 3), EPSILON));          \
                                                                               \
    REQUIRE_THAT(trans(3, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res(3, 0), EPSILON));         \
    REQUIRE_THAT(trans(3, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res(3, 1), EPSILON));         \
    REQUIRE_THAT(trans(3, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res(3, 2), EPSILON));         \
    REQUIRE_THAT(trans(3, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res(3, 3), EPSILON));          \
  }

#define REQUIRE_TRANSFORMATIONv1(trans, real_res, EPSILON)                     \
  {                                                                            \
    REQUIRE_THAT(trans(0, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res[0], EPSILON));            \
    REQUIRE_THAT(trans(0, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res[1], EPSILON));            \
    REQUIRE_THAT(trans(0, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res[2], EPSILON));            \
    REQUIRE_THAT(trans(0, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res[3], EPSILON));            \
                                                                               \
    REQUIRE_THAT(trans(1, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res[4], EPSILON));            \
    REQUIRE_THAT(trans(1, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res[5], EPSILON));            \
    REQUIRE_THAT(trans(1, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res[6], EPSILON));            \
    REQUIRE_THAT(trans(1, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res[7], EPSILON));            \
                                                                               \
    REQUIRE_THAT(trans(2, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res[8], EPSILON));            \
    REQUIRE_THAT(trans(2, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res[9], EPSILON));            \
    REQUIRE_THAT(trans(2, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res[10], EPSILON));           \
    REQUIRE_THAT(trans(2, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res[11], EPSILON));           \
                                                                               \
    REQUIRE_THAT(trans(3, 0),                                                  \
                 Catch::Matchers::WithinAbs(real_res[12], EPSILON));           \
    REQUIRE_THAT(trans(3, 1),                                                  \
                 Catch::Matchers::WithinAbs(real_res[13], EPSILON));           \
    REQUIRE_THAT(trans(3, 2),                                                  \
                 Catch::Matchers::WithinAbs(real_res[14], EPSILON));           \
    REQUIRE_THAT(trans(3, 3),                                                  \
                 Catch::Matchers::WithinAbs(real_res[15], EPSILON));           \
  }

#define REQUIRE_TUPLE(u, real_res, EPSILON) \
{ \
    REQUIRE_THAT( u.x,Catch::Matchers::WithinAbs(real_res.x, EPSILON)); \
    REQUIRE_THAT( u.y,Catch::Matchers::WithinAbs(real_res.y, EPSILON)); \
    REQUIRE_THAT( u.z,Catch::Matchers::WithinAbs(real_res.z, EPSILON)); \
}\

TEST_CASE("Transformation's default constructor is identity",
          "[Transformation]") {
  PBR_::Transformation t1;

  std::double_t identity[16] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};

  REQUIRE_TRANSFORMATIONv1(t1, identity, EPSILONv5);
}

TEST_CASE("Transformation's parameter constructor", "[Transformation]") {
  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  std::double_t res[16] = {1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                           9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  REQUIRE_TRANSFORMATIONv1(t, res, EPSILONv5);
}

TEST_CASE("Transformation's copy constructor", "[Transformation]") {
  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  PBR_::Transformation gg{t};

  REQUIRE_TRANSFORMATIONv0(t, gg, EPSILONv5);
}

TEST_CASE("Transformation's sum", "[Transformation]") {


  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  PBR_::Transformation gg{t};

  PBR_::Transformation res = t + gg;

  PBR_::Transformation real_res
  {
    2.0, 4.0, 6.0, 8.0, 
    10.0, 12.0, 14.0, 16.0,
    18.0, 20.0, 22.0, 24.0,
    26.0, 28.0, 30.0, 32.0
  };

  REQUIRE_TRANSFORMATIONv0(res, real_res, EPSILONv5);
}

TEST_CASE("Transformation's sub", "[Transformation]") {


  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  PBR_::Transformation gg{t};

  PBR_::Transformation res = t - gg;

  PBR_::Transformation real_res
  {
    0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0
  };

  REQUIRE_TRANSFORMATIONv0(res, real_res, EPSILONv5);
}

TEST_CASE("Transformation's mul [T * cste]", "[Transformation]") {


  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  PBR_::Transformation gg{t * 2.0};


  PBR_::Transformation real_res
  {
    2.0, 4.0, 6.0, 8.0, 
    10.0, 12.0, 14.0, 16.0,
    18.0, 20.0, 22.0, 24.0,
    26.0, 28.0, 30.0, 32.0
  };

  REQUIRE_TRANSFORMATIONv0(gg, real_res, EPSILONv5);
}

TEST_CASE("Transformation's mul [T * T]", "[Transformation]") {


  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  PBR_::Transformation gg{t * t};


  PBR_::Transformation real_res
  {
    90,100,110,120
    ,202,228,254,280
    ,314,356,398,440
    ,426,484,542,600
  };

  REQUIRE_TRANSFORMATIONv0(gg, real_res, EPSILONv5);
}


TEST_CASE("Transformation's mul [T * P]", "[Transformation]") {


  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};


  PBR_::Point3 p = {1, 2, 3};

  PBR_::Point3 res = t(p);


  PBR_::Point3 real_res
  {
    18,46,74
  };

  REQUIRE_TUPLE(res, real_res, EPSILONv5);
}


TEST_CASE("Transformation's mul [T * V]", "[Transformation]") {


  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};


  PBR_::Vector3 p = {1, 2, 3};

  PBR_::Vector3 res = t(p);


  PBR_::Vector3 real_res
  {
    14,38,62
  };

  REQUIRE_TUPLE(res, real_res, EPSILONv5);
}

TEST_CASE("Transformation's mul [T * R]", "[Transformation]") {


  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};


  PBR_::Point3 p = {1, 2, 3};

  PBR_::Vector3 d = {1, 2, 3};

  PBR_::Ray r{p,d, 0.0};

  PBR_::Ray res = t(r);


  PBR_::Vector3 real_res_d
  {
    14,38,62
  };

  PBR_::Point3 real_res_p
  {
    18,46,74
  };

  REQUIRE_TUPLE(res.origin, real_res_p, EPSILONv5);
  REQUIRE_TUPLE(res.direction, real_res_d, EPSILONv5);

}

TEST_CASE("Transformation's determinant 0", "[Transformation]")
{
  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  std::double_t det = PBR_::Determinant(t);

  REQUIRE_THAT( det,Catch::Matchers::WithinAbs(0.0, EPSILONv5));
}

TEST_CASE("Transformation's determinant positive", "[Transformation]")
{
  PBR_::Transformation t{10.0, 2.0,  3.0,  4.0,
  5.0,  60.0,  7.0,  8.0,
  9.0, 10.0, 110.0, 12.0, 
13.0, 14.0, 15.0, 160.0};

  std::double_t det = PBR_::Determinant(t);

  REQUIRE_THAT( det,Catch::Matchers::WithinAbs(9612432.0, EPSILONv5));
}

TEST_CASE("Transformation's determinant negative", "[Transformation]")
{
  PBR_::Transformation t{-10.0, 2.0,  3.0,  4.0,
  5.0,  60.0,  7.0,  8.0,
  9.0, 10.0, 110.0, 12.0, 
13.0, 14.0, 15.0, 160.0};
  std::double_t det = PBR_::Determinant(t);

  REQUIRE_THAT( det,Catch::Matchers::WithinAbs(-10868688.0, EPSILONv5));
}

TEST_CASE("Transformation's inverse", "[Transformation]")
{
  PBR_::Transformation t{-10.0, 2.0,  3.0,  4.0,
  5.0,  60.0,  7.0,  8.0,
  9.0, 10.0, 110.0, 12.0, 
13.0, 14.0, 15.0, 160.0};
  PBR_::Transformation res = 
  {-0.094220755991891572, 0.0022987135153755447, 0.002139724684340925, 0.0020801038727029427, 
    0.006233687083482385, 0.016858704564893204, -0.0011180742330629051, -0.00091492183785200204, 
    0.0064324231222756606, -0.0015552935184081095, 0.0091190399429995593, -0.00076697389786145305, 
    0.0065069491368231385, -0.0015160983552016582, -0.00093093112986590467, 0.0062329510240794472};

  REQUIRE_TRANSFORMATIONv0( PBR_::Inverse(t).value(), res, EPSILONv5);
}

TEST_CASE("Transformation's transpose", "[Transformation]")
{
  PBR_::Transformation t{1.0, 2.0,  3.0,  4.0,
                         5.0,  6.0,  7.0,  8.0,
                         9.0, 10.0, 11.0, 12.0,
                          13.0, 14.0, 15.0, 16.0};
  PBR_::Transformation res = 
  {
   1.0, 5.0, 9.0, 13.0,
   2.0, 6.0, 10.0, 14.0,
   3.0, 7.0, 11.0, 15.0,
   4.0, 8.0, 12.0, 16.0    
  };

  REQUIRE_TRANSFORMATIONv0( PBR_::Transpose(t), res, EPSILONv5);
}

TEST_CASE("Transformation's translation", "[Transformation]")
{
  PBR_::Transformation tr0        = PBR_::Translation(1, 2, 3);
  PBR_::Transformation tr1        = PBR_::Translation(PBR_::Point3{1, 2, 3});
  PBR_::Transformation tr2 = PBR_::Translation(PBR_::Vector3{1, 2, 3});

  PBR_::Point3 p = { 5, 7, -9};
  PBR_::Vector3 u = { 5, 7, -9};

  PBR_::Point3 res0{6, 9, -6};
  PBR_::Vector3 res1{ 5, 7, -9};

  REQUIRE_TUPLE(tr0(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr0(u), res1, EPSILONv5);
  REQUIRE_TUPLE(tr1(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr1(u), res1, EPSILONv5);
  REQUIRE_TUPLE(tr2(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr2(u), res1, EPSILONv5);
}

TEST_CASE("Transformation's scale", "[Transformation]")
{
  PBR_::Transformation tr0 = PBR_::Scale(1, 2, 3);

  PBR_::Point3 p = { 5, 7, -9};
  PBR_::Vector3 u = { 5, 7, -9};

  PBR_::Point3 res0{5, 14, -27};
  PBR_::Vector3 res1{ 5, 14, -27};

  REQUIRE_TUPLE(tr0(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr0(u), res1, EPSILONv5);
}

TEST_CASE("Transformation's rotation x", "[Transformation]")
{
  PBR_::Transformation tr0 = PBR_::RotationX(0.7);

  PBR_::Point3 p = { 5, 7, -9};
  PBR_::Vector3 u = { 5, 7, -9};

  PBR_::Point3 res0{5, 11.1518544961306389,-2.3740558748965590};
  PBR_::Vector3 res1{5,11.1518544961306389,-2.3740558748965590};

  REQUIRE_TUPLE(tr0(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr0(u), res1, EPSILONv5);
}

TEST_CASE("Transformation's rotation y", "[Transformation]")
{
  PBR_::Transformation tr0 = PBR_::RotationY(0.7);

  PBR_::Point3 p = { 5, 7, -9};
  PBR_::Vector3 u = { 5, 7, -9};

  PBR_::Point3 res0{-1.97374824871677657, 7, -10.10466812174885121};
  PBR_::Vector3 res1{-1.97374824871677657, 7, -10.10466812174885121};

  REQUIRE_TUPLE(tr0(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr0(u), res1, EPSILONv5);
}

TEST_CASE("Transformation's rotation z", "[Transformation]")
{
  PBR_::Transformation tr0 = PBR_::RotationZ(0.7);

  PBR_::Point3 p = { 5, 7, -9};
  PBR_::Vector3 u = { 5, 7, -9};

  PBR_::Point3 res0{-0.6853128742413945, 8.5749837471798749, -9};
  PBR_::Vector3 res1{-0.6853128742413945, 8.5749837471798749, -9};

  REQUIRE_TUPLE(tr0(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr0(u), res1, EPSILONv5);
}

TEST_CASE("Transformation's basis", "[Transformation]")
{
  PBR_::Transformation tr0 = PBR_::Basis({2.0, 47.55, 87}, {-7, -4, -11}, {7, 6, 0.5});

  PBR_::Point3 p = { 5, 7, -9};
  PBR_::Vector3 u = { 5, 7, -9};

  PBR_::Point3 res0{-102.0, 155.75, 353.5};
  PBR_::Vector3 res1{-102.0, 155.75, 353.5};

  REQUIRE_TUPLE(tr0(p), res0, EPSILONv5);
  REQUIRE_TUPLE(tr0(u), res1, EPSILONv5);
}