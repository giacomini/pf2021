#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "chain.hpp"

// Semplifica la comparazione tra PPStates
// facendo uso di doctest::Approx
bool approx_eq(PPState const& l, PPState const& r)
{
  return l.m == doctest::Approx(r.m) && l.x == doctest::Approx(r.x)
      && l.v == doctest::Approx(r.v);
}

TEST_CASE("Hooke's law")
{
  SUBCASE("Negative k throws")
  {
    CHECK_THROWS(Hooke{-1.0, 1.0});
  }
  SUBCASE("Negative l0 throws")
  {
    CHECK_THROWS(Hooke{1.0, -1.0});
  }

  SUBCASE("k=0 throws")
  {
    CHECK_THROWS(Hooke{0.0, 1.0});
  }

  Hooke const hooke{2.0, 10.0};

  SUBCASE("Nominal use, zero F")
  {
    PPState p1{1.0, 0.0, 0.0};
    PPState p2{1.0, 10.0, 0.0};
    CHECK(hooke(p1, p2) == doctest::Approx(0.0));
  }

  SUBCASE("Nominal use, F > 0")
  {
    PPState p1{1.0, 0.0, 0.0};
    PPState p2{1.0, 12.0, 0.0};
    CHECK(hooke(p1, p2) == doctest::Approx(4.0));
  }

  SUBCASE("Nominal use, F < 0")
  {
    PPState p1{1.0, 0.0, 0.0};
    PPState p2{1.0, 8.0, 0.0};
    CHECK(hooke(p2, p1) == doctest::Approx(-4.0));
  }
}

TEST_CASE("Chain basics")
{
  Chain c{Hooke{0.1, 2.0}};
  REQUIRE(c.empty());

  SUBCASE("Out-of-order PPStates throws")
  {
    c.push_back({0.5, 1.0, 0.0});
    CHECK_THROWS(c.push_back({0.5, 0.0, 0.0}));
  }

  SUBCASE("PPStates with same x throws")
  {
    c.push_back({0.5, 1.0, 0.0});
    CHECK_THROWS(c.push_back({0.5, 1.0, 0.0}));
  }

  SUBCASE("Nominal use, F = 0, 1 step")
  {
    c.push_back({0.5, 0.0, 0.0});
    c.push_back({0.5, 2.0, 0.0});

    c.evolve(1.0);
    const auto state = c.state();

    CHECK(approx_eq(state[0], {0.5, 0.0, 0.0}));
    CHECK(approx_eq(state[1], {0.5, 2.0, 0.0}));
  }

  SUBCASE("Nominal use, F != 0, 1 step")
  {
    c.push_back({0.5, 0.0, 0.0});
    c.push_back({0.5, 4.0, 0.0});

    c.evolve(1.0);
    const auto state = c.state();

    CHECK(approx_eq(state[0], {0.5, 0.2, 0.4}));
    CHECK(approx_eq(state[1], {0.5, 3.8, -0.4}));
  }

  SUBCASE("Nominal use, F != 0, 2 steps forward")
  {
    c.push_back({1.0, 0.0, 0.2});
    c.push_back({1.0, 2.0, 0.0});
    c.push_back({1.0, 4.0, 0.0});

    c.evolve(1.0);
    c.evolve(1.0);
    const auto state = c.state();

    CHECK(approx_eq(state[0], {1.0, 0.39, 0.18}));
    CHECK(approx_eq(state[1], {1.0, 2.01, 0.02}));
    CHECK(approx_eq(state[2], {1.0, 4.0, 0.0}));
  }

  SUBCASE("Nominal use, F != 0, 2 steps backward")
  {
    c.push_back({1.0, 0.0, 0.0});
    c.push_back({1.0, 2.0, 0.0});
    c.push_back({1.0, 4.0, -0.2});

    c.evolve(1.0);
    c.evolve(1.0);
    const auto state = c.state();

    CHECK(approx_eq(state[0], {1.0, 0.0, 0.0}));
    CHECK(approx_eq(state[1], {1.0, 1.99, -0.02}));
    CHECK(approx_eq(state[2], {1.0, 3.61, -0.18}));
  }
}

TEST_CASE("Chain stability")
{
  Chain c{Hooke{0.1, 0.1}};
  REQUIRE(c.empty());

  const auto n_steps{100000};
  const auto delta_t{0.001};

  SUBCASE("Nominal use, zero F, n_steps")
  {
    c.push_back({0.05, 0.0, 0.0});
    c.push_back({0.05, 0.1, 0.0});
    const auto state_i = c.state();
    for (int i = 0; i != n_steps; ++i) {
      c.evolve(delta_t);
    }
    const auto state_f = c.state();

    CHECK(approx_eq(state_i[0], state_f[0]));
    CHECK(approx_eq(state_i[1], state_f[1]));
  }

  SUBCASE("Nominal use, 4 bodies, symmetric, n_steps")
  {
    c.push_back({0.05, -0.165, 0.0});
    c.push_back({0.05, -0.055, 0.0});
    c.push_back({0.05, 0.055, 0.0});
    c.push_back({0.05, 0.165, 0.0});

    for (int i = 0; i != n_steps; ++i) {
      c.evolve(delta_t);
    }

    const auto state = c.state();

    CHECK((state[0].x) == doctest::Approx(-state[3].x));
    CHECK((state[0].v) == doctest::Approx(-state[3].v));
    CHECK((state[1].x) == doctest::Approx(-state[2].x));
    CHECK((state[1].v) == doctest::Approx(-state[2].v));
  }

  SUBCASE("Nominal use, 5 bodies, symmetric, n_steps")
  {
    c.push_back({0.05, 0.0, -0.01});
    c.push_back({0.05, 0.1, 0.0});
    c.push_back({0.05, 0.2, 0.0});
    c.push_back({0.05, 0.3, 0.0});
    c.push_back({0.05, 0.4, 0.01});

    for (int i = 0; i != n_steps; ++i) {
      c.evolve(delta_t);
    }

    const auto state = c.state();

    CHECK((state[0].x + state[4].x) == doctest::Approx(0.4));
    CHECK((state[1].x + state[3].x) == doctest::Approx(0.4));
    CHECK((state[0].v) == doctest::Approx(-state[4].v));
    CHECK((state[1].v) == doctest::Approx(-state[3].v));
  }
}
