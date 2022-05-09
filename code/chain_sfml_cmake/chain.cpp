#include "chain.hpp"

#include <iterator>
#include <stdexcept>

void Chain::push_back(PPState const& pps)
{
  if (size() > 0 && pps.x <= m_ppses.back().x) {
    throw std::runtime_error{
        "PPState x must be larger than x of rightmost chain's PPState"};
  }
  m_ppses.push_back(pps);
}

namespace {

PPState solve(PPState const& pps, double f, double delta_t)
{
  auto const a = f / pps.m;
  auto const v = pps.v + a * delta_t;
  auto const x = pps.x + (pps.v + 0.5 * a * delta_t) * delta_t;

  return PPState{pps.m, x, v};
}

} // namespace

void Chain::evolve(double delta_t)
{
  auto pps_it      = m_ppses.begin();
  auto pps_it_next = std::next(pps_it);
  auto pps_last    = std::prev(m_ppses.end());

  double f_prev{0.0};

  for (; pps_it != pps_last; ++pps_it, ++pps_it_next) {
    double f = m_inter(*pps_it, *pps_it_next);
    *pps_it  = solve(*pps_it, f - f_prev, delta_t);
    f_prev   = f;
  }

  *pps_last = solve(*pps_last, -f_prev, delta_t);
}
