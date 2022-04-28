#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <cmath>
#include <ostream>
#include <stdexcept>

// Point Particle State (ad un dato istante di tempo t):
// massa, posizione e velocità (lungo x)
struct PPState {
  double m{};
  double x{};
  double v{};
};

std::ostream& operator<<(std::ostream& os, PPState const& p) {
  os << "pps ( m: " << p.m << ", x: " << p.x << ", v: " << p.v << ')';
  return os;
}

// Oggetto funzione che implementa la legge di Hooke
class Hooke {
  double m_k;
  double m_l;

 public:
  Hooke(double k, double l) : m_k(k), m_l(l) {
    if (m_k <= 0.) {
      throw std::runtime_error{"Hooke's parameter k must be > 0"};
    }
    if (m_l < 0.) {
      throw std::runtime_error{"Hooke's parameter l must be >= 0"};
    }
  }

  // Il segno del risultato di `operator()` è calcolato
  // secondo la convenzione suggerita in lab5.md
  double operator()(PPState const& p1, PPState const& p2) const {
    return m_k * (std::abs(p2.x - p1.x) - m_l);
  }
};

#endif
