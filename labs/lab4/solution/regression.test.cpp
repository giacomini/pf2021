#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "regression.hpp"

#include "doctest.h"

TEST_CASE("Testing Point operators") {
  Point p{0., 1.};
  Point p_same = p;
  Point p_diff{1., 1.};

  SUBCASE("Operator == on identical points") { CHECK(p == p_same); }
  SUBCASE("Operator == on different points") { CHECK_FALSE(p == p_diff); }

  SUBCASE("Operator != on different points") { CHECK(p != p_diff); }
  SUBCASE("Operator != on identical points") { CHECK_FALSE(p != p_same); }

  SUBCASE("Operator <<") {
    std::stringstream out;
    out << p;
    CHECK(out.str() == "(0,1)");
  }
}

TEST_CASE("Testing Regression") {
  Regression reg;

  REQUIRE(reg.size() == 0);

  SUBCASE("Fitting with no points throws") { CHECK_THROWS(fit(reg)); }

  SUBCASE("Fitting on one point throws") {
    reg.add(0., 0.);
    CHECK_THROWS(reg.fit());
  }

  SUBCASE("Removing existing point") {
    reg.add(0., 0.);
    reg.add(1., 1.);
    CHECK(reg.remove(1., 1.) == true);
    CHECK(reg.size() == 1);
  }

  SUBCASE("Removing non existing point") {
    reg.add(0., 0.);
    reg.add(1., 1.);
    CHECK(reg.remove(1., 2.) == false);
    CHECK(reg.size() == 2);
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
