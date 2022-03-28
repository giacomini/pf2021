#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "regression.hpp"

#include "doctest.h"

TEST_CASE("Testing Regression") {
  Regression reg;

  REQUIRE(reg.size() == 0);

  SUBCASE("Fitting with no points throws") { CHECK_THROWS(fit(reg)); }

  SUBCASE("Fitting on one point throws") {
    reg.add(0., 0.);
    CHECK_THROWS(reg.fit());
  }

  SUBCASE("Fitting on two, vertically aligned, points throws") {
    reg.add(1., 0.);
    reg.add(1., 2.);
    CHECK_THROWS(reg.fit());
  }

  SUBCASE("Fitting on two points") {
    reg.add(0., 0.);
    reg.add(1., 1.);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(0));
    CHECK(result.B == doctest::Approx(1));
  }

  SUBCASE("Fitting on two points, negative slope") {
    reg.add(0., 1.);
    reg.add(1., 0.);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(1));
    CHECK(result.B == doctest::Approx(-1));
  }

  SUBCASE("Fitting on five points") {
    reg.add(2.1, 3.2);
    reg.add(6.9, 7.3);
    reg.add(2.2, 3.0);
    reg.add(0.1, 1.3);
    reg.add(4.7, 5.6);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(1.2).epsilon(0.01));
    CHECK(result.B == doctest::Approx(0.9).epsilon(0.01));
  }
}
