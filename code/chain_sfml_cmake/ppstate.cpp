#include "ppstate.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& os, PPState const& p) {
  os << "( m: " << p.m << ", x: " << p.x << ", v: " << p.v << ')';
  return os;
}
