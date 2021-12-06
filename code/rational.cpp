// g++ -std=c++17 rational.cpp

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cassert>
#include <numeric>
#include <stdexcept>

class Rational
{
  int n_;
  int d_;

  // i due metodi privati seguenti "normalizzano" la frazione, in modo tale che
  // * numeratore e denominatore siano ridotti ai minimi termini
  // * il segno e' mantenuto dal numeratore
  // e' meglio avere due funzioni separate perche' non servono sempre entrambe
  // (vedi operator/=)

  void reduce()
  {
    auto const g = std::gcd(n_, d_);
    n_ /= g;
    d_ /= g;
  }
  void fix_sign()
  {
    if (d_ < 0) {
      n_ = -n_;
      d_ = -d_;
    }
  }

  // funzione che esprime l'invariante di classe
  bool invariant()
  {
    return std::gcd(n_, d_) == 1 && d_ > 0;
  }

 public:
  Rational(int num = 0, int den = 1) : n_{num}, d_{den}
  {
    // nel costruttore scegliamo di accettare anche un denominatore uguale a zero,
    // nel qual caso solleviamo un'eccezione
    if (d_ == 0) {
      throw std::runtime_error{"denominator is zero"};
    }
    reduce();
    fix_sign();

    assert(invariant());
  }

  int num() const
  {
    return n_;
  }
  int den() const
  {
    return d_;
  }

  Rational& operator*=(int n)
  {
    assert(invariant());

    auto g = std::gcd(n, d_);
    n_ *= n / g;
    d_ /= g;

    assert(invariant());
    return *this;
  }

  Rational& operator/=(int n)
  {
    // pre-condizione
    // e' sotto forma di assert (in alternativa a sollevare un'eccezione) per analogia
    // a cio' che avviene dividendo un int per zero
    assert(n != 0);

    assert(invariant());

    auto g = std::gcd(n, n_);
    n_ /= g;
    d_ *= n / g;
    fix_sign();

    assert(invariant());
    return *this;
  }
};

bool operator==(Rational const& l, Rational const& r)
{
  assert(std::gcd(l.num(), l.den()) == 1 && std::gcd(r.num(), r.den()) == 1);
  return l.num() == r.num() && l.den() == r.den();
}

bool operator!=(Rational const& l, Rational const& r)
{
  return !(l == r);
}

Rational operator*(Rational const& l, int n)
{
  Rational result{l};
  result *= n;
  return result;
}

Rational operator/(Rational const& l, int n)
{
  Rational result{l};
  result /= n;
  return result;
}

Rational operator+(Rational const& r)
{
  return r;
}

Rational operator-(Rational const& r)
{
  return {-r.num(), r.den()};
}

TEST_CASE("Testing Rational")
{
  Rational r0;
  CHECK(r0 == Rational{0});
  CHECK(r0 == Rational{0, 1});
  Rational r1(1, 3);
  Rational r2(4, 6);
  CHECK(r2.num() == 2);
  CHECK(r2.den() == 3);
  CHECK(Rational{-1, 2} == Rational{1, -2});
  CHECK(Rational{-1, -2} == Rational{1, 2});
  CHECK(Rational{1, 18} * 3 == Rational{1, 6});
  CHECK(Rational{-1, 18} * 3 == Rational{-1, 6});
  CHECK(Rational{1, 18} * -3 == Rational{-1, 6});
  CHECK(Rational{-1, 18} * -3 == Rational{1, 6});
  CHECK(Rational{4, 9} / 2 == Rational{2, 9});
  CHECK(Rational{-4, 9} / 2 == Rational{-2, 9});
  CHECK(Rational{4, 9} / -2 == Rational{-2, 9});
  CHECK(Rational{-4, 9} / -2 == Rational{2, 9});
  CHECK_THROWS((Rational{0, 0}));

  // il test seguente non si puo' fare perche' la divisione per zero farebbe
  // scattare l'assert
  // CHECK(r1 / 0 != 0);
}
