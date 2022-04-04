#include <SFML/Graphics.hpp>
#include <cassert>
#include <complex>
#include <iostream>
#include <string>
#include <thread>

using Complex = std::complex<double>;

int mandelbrot(Complex const& c)
{
  int i = 0;
  auto z = c;
  for (; i != 256 && norm(z) < 4.; ++i) {
    z = z * z + c;
  }
  return i;
}

auto to_color(int k)
{
  return k < 256 ? sf::Color{static_cast<sf::Uint8>(10 * k), 0, 0}
                 : sf::Color::Black;
}

class Rendering
{
  int m_w;
  int m_h;
  std::vector<sf::Color> m_colors;

 public:
  Rendering(int w, int h) : m_w{w}, m_h{h}, m_colors(w * h)
  {
  }
  sf::Color const& at(int r, int c) const
  {
    assert(r >= 0 && r < m_h);
    assert(c >= 0 && c < m_w);
    return m_colors[r * m_w + c];
  }
  sf::Color& at(int r, int c)
  {
    assert(r >= 0 && r < m_h);
    assert(c >= 0 && c < m_w);
    return m_colors[r * m_w + c];
  }
};

int main()
{
  int const display_width{600};
  int const display_height{600};

  Complex const top_left{-2.3, 1.5};
  Complex const lower_right{0.8, -1.5};
  auto const diff = lower_right - top_left;

  auto const delta_x = diff.real() / display_width;
  auto const delta_y = diff.imag() / display_height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Mandelbrot Set");

  Rendering rendering(display_width, display_height);

  sf::RectangleShape point{sf::Vector2f{1.f, 1.f}};

  for (int row = 0; row != display_height; ++row) {
    for (int column = 0; column != display_width; ++column) {
      auto k = mandelbrot(top_left + Complex{delta_x * column, delta_y * row});
      rendering.at(row, column) = to_color(k);
    }
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();

    for (int row = 0; row != display_height; ++row) {
      for (int column = 0; column != display_width; ++column) {
        point.setPosition(column, row);
        point.setFillColor(rendering.at(row, column));
        window.draw(point);
      }
    }

    window.display();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
  }
}
