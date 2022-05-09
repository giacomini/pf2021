#ifndef HOOKE_HPP
#define HOOKE_HPP

#include "ppstate.hpp"

#include <cmath>
#include <stdexcept>

class Hooke
{
  double m_k;
  double m_l;

 public:
  Hooke(double k, double l) : m_k(k), m_l(l)
  {
    if (m_k <= 0.) {
      throw std::runtime_error{"Hooke's parameter k must be > 0"};
    }
    if (m_l < 0.) {
      throw std::runtime_error{"Hooke's parameter l must be >= 0"};
    }
  }

  double operator()(PPState const& p1, PPState const& p2) const
  {
    return m_k * (std::abs(p2.x - p1.x) - m_l);
  }
};

#endif
