#ifndef CHAIN_HPP
#define CHAIN_HPP

#include "hooke.hpp"
#include "ppstate.hpp"

#include <vector>

class Chain
{
  std::vector<PPState> m_ppses;

  Hooke m_inter;

 public:
  Chain(Hooke const& inter) : m_inter(inter)
  {
  }

  void push_back(PPState const& pps);

  std::size_t size() const
  {
    return m_ppses.size();
  }

  bool empty() const { return m_ppses.empty(); }

  std::vector<PPState> const& state() const
  {
    return m_ppses;
  }

  void evolve(double delta_t);
};

#endif
