#include "regression.hpp"

#include <algorithm>
#include <stdexcept>

bool operator==(Point const& l, Point const& r) {
  return l.x == r.x && l.y == r.y;
}

bool operator!=(Point const& l, Point const& r) { return !(l == r); }

std::ostream& operator<<(std::ostream& os, Point const& p) {
  os << '(' << p.x << ',' << p.y << ')';
  return os;
}

int Regression::size() const { return points_.size(); }

void Regression::add(double x, double y) { points_.push_back({x, y}); }

bool Regression::remove(double x, double y) {
  auto const p_rm_it = std::find(points_.begin(), points_.end(), Point{x, y});

  if (p_rm_it != points_.end()) {
    points_.erase(p_rm_it);
    return true;
  }
  return false;
}

Result Regression::fit() const {
  const int N{size()};

  if (N < 2) {
    throw std::runtime_error{"Not enough points to run a fit"};
  }

  double sum_x{};
  double sum_y{};
  double sum_x2{};
  double sum_xy{};

  std::for_each(points_.begin(), points_.end(), [&](Point p) {
    sum_x += p.x;
    sum_y += p.y;
    sum_x2 += p.x * p.x;
    sum_xy += p.x * p.y;
  });

  double const d = N * sum_x2 - sum_x * sum_x;
  if (d == 0.) {
    throw std::runtime_error{"Trying to fit a vertical line"};
  }

  double const a = (sum_y * sum_x2 - sum_x * sum_xy) / d;
  double const b = (N * sum_xy - sum_x * sum_y) / d;

  return {a, b};
}

Result fit(Regression const& reg) {
  // the following call would fail compilation if the fit method weren't const
  return reg.fit();
}
