#include <iostream>
#include <string>

class Complex
{
  double r_;
  double i_;

 public:
  Complex(double r = 0., double i = 0.) : r_{r}, i_{i}
  {
  }
  double real() const
  {
    return r_;
  }
  double imag() const
  {
    return i_;
  }
  Complex& operator+=(Complex const& o)
  {
    r_ += o.r_;
    i_ += o.i_;
    return *this;
  }
  Complex& operator*=(Complex const& o)
  {
    auto t = r_ * o.r_ - i_ * o.i_;
    i_ = r_ * o.i_ + i_ * o.r_;
    r_ = t;
    return *this;
  }
};

Complex operator-(Complex const& c)
{
  return {-c.real(), -c.imag()};
}

Complex operator+(Complex const& left, Complex const& right)
{
  auto result = left;
  return result += right;
}

Complex operator-(Complex const& left, Complex const& right)
{
  return left + (-right);
}

Complex operator*(Complex const& left, Complex const& right)
{
  auto result = left;
  return result *= right;
}

double norm2(Complex const& c)
{
  return c.real() * c.real() + c.imag() * c.imag();
}

int mandelbrot(Complex const& c)
{
  int i = 0;
  auto z = c;
  for (; i != 256 && norm2(z) < 4.; ++i) {
    z = z * z + c;
  }
  return i;
}

auto to_symbol(int k)
{
  return k < 256 ? ' ' : '*';
}

int main()
{
  int const display_width = 100;
  int const display_height = 48;

  Complex const top_left{-2.3, 1.};
  Complex const lower_right{0.8, -1.};
  auto const diff = lower_right - top_left;

  auto const delta_x = diff.real() / display_width;
  auto const delta_y = diff.imag() / display_height;

  for (int row{0}; row != display_height; ++row) {
    std::string line;
    for (int column{0}; column != display_width; ++column) {
      auto k = mandelbrot(top_left + Complex{delta_x * column, delta_y * row});
      line.push_back(to_symbol(k));
    }
    std::cout << line << '\n';
  }
}
