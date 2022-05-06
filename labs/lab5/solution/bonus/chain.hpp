#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <algorithm>
#include <cmath>
#include <functional>
#include <ostream>
#include <stdexcept>
#include <vector>

struct PPState {
  double m{};
  double x{};
  double v{};
};

std::ostream& operator<<(std::ostream& os, PPState const& p) {
  os << "(m: " << p.m << ", x: " << p.x << ", v: " << p.v << ')';
  return os;
}

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

  double operator()(PPState const& p1, PPState const& p2) const {
    return m_k * (std::abs(p2.x - p1.x) - m_l);
  }
};

template <class F>
class Chain {
 private:
  F m_inter;
  std::vector<PPState> m_ppses;

  PPState solve(PPState const& pps, double f, double const delta_t) const {
    auto const a = f / pps.m;
    auto const v = pps.v + a * delta_t;
    auto const x = pps.x + (pps.v + 0.5 * a * delta_t) * delta_t;

    return PPState{pps.m, x, v};
  }

 public:
  // Necessario per usare back_inserter in std::generate_n
  using value_type = PPState;

  Chain(F const& inter) : m_inter(inter) {}

  bool empty() { return m_ppses.empty(); }

  std::size_t size() const { return m_ppses.size(); }

  void push_back(PPState const& pps) {
    if (!empty() && pps.x <= m_ppses.back().x) {
      throw std::runtime_error{
          "Added PPState x must be larger than x of rightmost chain's PPState"};
    }
    m_ppses.push_back(pps);
  }

  std::vector<PPState> const& state() const { return m_ppses; }

  void evolve(double const delta_t) {
    auto first = m_ppses.begin();
    auto last = std::prev(m_ppses.end());

    auto f{0.0};

    std::transform(first, last, std::next(first), first,
                   [&](PPState const& l, PPState const& r) {
                     auto f_prev{f};
                     f = m_inter(l, r);
                     return solve(l, f - f_prev, delta_t);
                   });

    *last = solve(*last, -f, delta_t);
  }
};

#endif
