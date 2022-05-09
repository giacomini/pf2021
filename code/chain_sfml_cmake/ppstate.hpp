#ifndef PPSTATE_HPP
#define PPSTATE_HPP

#include <iosfwd>

struct PPState {
  double m{};
  double x{};
  double v{};
};

std::ostream& operator<<(std::ostream& os, PPState const& p);

#endif
