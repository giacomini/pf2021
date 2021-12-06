#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

class Complex
{
  double r_;
  double i_;

 public:
  Complex(double x = 0., double y = 0.) : r_{x}, i_{y}
  {
  }
  double real() const
  {
    return r_;
  }
  double imag() const
  {
    return i_;
  }
};

double norm2(Complex const& c)
{
  return c.real() * c.real() + c.imag() * c.imag();
}

Complex operator+(Complex const& c1, Complex const& c2)
{
  return {c1.real() + c2.real(), c1.imag() + c2.imag()};
}

bool operator==(Complex const& c1, Complex const& c2)
{
  return c1.real() == c2.real() && c1.imag() == c2.imag();
}

bool operator!=(Complex const& c1, Complex const& c2)
{
  return !(c1 == c2);
}

TEST_CASE("Testing Complex")
{
  Complex c{};
  CHECK(c.real() == 0.);
  CHECK(c.imag() == 0.);
  CHECK(norm2(c) == 0.);
  CHECK(norm2({1.,2.}) == 5.);
  CHECK((Complex{1.,2.} + Complex{3.,4.} == Complex{4.,6.}));
}
