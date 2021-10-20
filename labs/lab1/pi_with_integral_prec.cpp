#include <cmath>
#include <iostream>

int main() {
  double min_prec;
  std::cout << "Inserisci la precisione minima richiesta: ";
  std::cin >> min_prec;

  const double x_min = 0.0;
  const double x_max = 1.0;
  const double ref_pi = std::acos(-1.0);

  int n = 0;
  double area = 0.0;

  while (std::abs(ref_pi - area) > min_prec) {
    n += 1;
    const double delta_x = (x_max - x_min) / n;
    double area_n = 0.0;

    for (int i = 0; i != n; ++i) {
      const double x_i = delta_x * i;
      const double y_i = 4.0 / (1.0 + x_i * x_i);
      area_n += y_i * delta_x;
    }

    area = area_n;
  }

  std::cout << "Integrale: " << area << '\n'
            << "Numero di intervalli: " << n << '\n'
            << "Modulo differenza rispetto a pi greco: "
            << std::abs(ref_pi - area) << '\n';
}