#include <iostream>

int main() {
  int n;
  std::cout
      << "Inserisci il numero di sotto-intervalli per il calcolo di pi greco: ";
  std::cin >> n;

  const double x_min = 0.0;
  const double x_max = 1.0;

  const double delta_x = (x_max - x_min) / n;
  double area = 0.0;

  for (int i = 0; i != n; ++i) {
    const double x_i = delta_x * i;
    const double y_i = 4.0 / (1.0 + x_i * x_i);
    area += y_i * delta_x;
  }

  std::cout << "Integrale: " << area << '\n';
}