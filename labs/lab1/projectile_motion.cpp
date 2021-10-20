#include <cmath>
#include <iostream>

int main() {
  double v;
  std::cout << "Inserisci modulo della velocità (in m/s): ";
  std::cin >> v;

  double alpha;
  std::cout << "Inserisci angolo di alzata (in gradi): ";
  std::cin >> alpha;

  const double pi = std::acos(-1.0);

  double v_x = std::cos(alpha / 180.0 * pi) * v;
  double v_y = std::sin(alpha / 180.0 * pi) * v;

  std::cout << "Componenti della velocità iniziale del proiettile: v_x = "
            << v_x << " m/s - v_y = " << v_y << " m/s\n";

  const double delta_t = 0.001;
  const double g = -9.80419;

  double y = 0.0;
  double t = 0.0;
  double y_max = 0.0;

  while (y >= 0.0) {
    t += delta_t;
    y = v_y * t + 0.5 * g * t * t;
    if (y > y_max) {
      y_max = y;
    }
  }

  const double t_max = t - delta_t;  // t_max e x_max "subito prima" di y < 0
  const double x_max = v_x * t_max;

  std::cout << "Gittata: " << x_max << " m\n"
            << "Altezza massima: " << y_max << " m\n"
            << "Tempo di volo: " << t_max << " s\n";
}