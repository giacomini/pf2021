#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "chain.hpp"

#include "doctest.h"

TEST_CASE("Hooke's law") {
  SUBCASE("Negative k throws") { CHECK_THROWS(Hooke{-1., 1.}); }
  SUBCASE("Negative l0 throws") { CHECK_THROWS(Hooke{1., -1.}); }

  SUBCASE("k=0 throws") { CHECK_THROWS(Hooke{0., 1.}); }

  SUBCASE("Nominal use, zero F") {
    Hooke hooke{10., 2.};
    PPState p1{1., 0., 0.};
    PPState p2{1., 2., 0.};
    CHECK(hooke(p1, p2) == doctest::Approx(0.));
  }

  SUBCASE("Nominal use, F > 0") {
    Hooke hooke{2., 10.};
    PPState p1{1., 0., 0.};
    PPState p2{1., 12., 0.};
    CHECK(hooke(p1, p2) == doctest::Approx(4.));
  }

  SUBCASE("Nominal use, F < 0") {
    Hooke hooke{2., 12.};
    PPState p1{1., 0., 0.};
    PPState p2{1., 10., 0.};
    CHECK(hooke(p2, p1) == doctest::Approx(-4.));
  }
}
