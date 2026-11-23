#include "ray.hpp"
#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <limits>
#include <primitive.hpp>

TEST_CASE("Plane intersection [When ray intersect]", "[Plane]") {
  PBR_::Plane pl0 = {{0.46,-0.6,1.72}, {2.62, 0.0, 0.0}, {0.0, 4.34, 0.0}, {1.0, 0.0, 0.0}};

  PBR_::Ray ray0 = {{0.0, 0.0, 0.0}, {1.0, 0.0, 2.0}, 0.0};


  bool test = intersect(pl0, ray0);

  REQUIRE_THAT(ray0.t,Catch::Matchers::WithinAbs(0.86, EPSILONv5));
  REQUIRE((test == true));
}

TEST_CASE("Plane intersection [When ray doesn't intersect]", "[Plane]") {
  PBR_::Plane pl0 = {{0.46,-0.6,1.72}, {2.62, 0.0, 0.0}, {0.0, 4.34, 0.0}, {1.0, 0.0, 0.0}};

  PBR_::Ray ray0 = {{0.0, 0.0, 0.0}, {1.0, 0.0, -2.0}, 0.0};


  bool test = intersect(pl0, ray0);

  REQUIRE_THAT(ray0.t,Catch::Matchers::WithinAbs(std::numeric_limits<std::double_t>::lowest(), EPSILONv5));
  REQUIRE((test == false));
}

TEST_CASE("Plane intersection [When ray is parallel to the plane, so its doesn't intersect]", "[Plane]") {
  PBR_::Plane pl0 = {{0.46,-0.6,1.72}, {2.62, 0.0, 0.0}, {0.0, 4.34, 0.0}, {1.0, 0.0, 0.0}};

  PBR_::Ray ray0 = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 0.0};


  bool test = intersect(pl0, ray0);

  REQUIRE_THAT(ray0.t,Catch::Matchers::WithinAbs(std::numeric_limits<std::double_t>::lowest(), EPSILONv5));
  REQUIRE((test == false));
}

TEST_CASE("Plane intersection [When ray is perpandicular and point at the opposite of the plane, so its doesn't intersect]", "[Plane]") {
  PBR_::Plane pl0 = {{0.46,-0.6,1.72}, {2.62, 0.0, 0.0}, {0.0, 4.34, 0.0}, {1.0, 0.0, 0.0}};

  PBR_::Ray ray0 = {{0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}, 0.0};


  bool test = intersect(pl0, ray0);

  REQUIRE_THAT(ray0.t,Catch::Matchers::WithinAbs(std::numeric_limits<std::double_t>::lowest(), EPSILONv5));
  REQUIRE((test == false));
}
