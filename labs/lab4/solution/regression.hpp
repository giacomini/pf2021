#ifndef REGRESSION_HPP
#define REGRESSION_HPP

#include <iostream>
#include <vector>

struct Result {
  double A;
  double B;
};

struct Point {
  double x;
  double y;
};

bool operator==(Point const& l, Point const& r);
bool operator!=(Point const& l, Point const& r);
std::ostream& operator<<(std::ostream& os, Point const& p);

class Regression {
  std::vector<Point> points_{};

 public:
  int size() const;

  void add(double x, double y);
  bool remove(double x, double y);

  Result fit() const;
};

Result fit(Regression const& reg);

#endif
