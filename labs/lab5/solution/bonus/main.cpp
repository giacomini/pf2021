#include "chain.hpp"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <numeric>

// Esegue la simulazione della catena, suddividendo "duration" in "steps"
// e registrando lo stato ogni volta che si compie un numero di step pari
// a "prescale"
auto simulate(Chain<Hooke>& chain, double duration, int steps, int prescale) {
  std::vector<std::vector<PPState>> v_states;

  double delta_t{duration / steps};

  for (int step = 0; step != steps; ++step) {
    if (step % prescale == 0) {
      v_states.push_back(chain.state());
    }
    chain.evolve(delta_t);
  }

  return v_states;
}

struct Acc {
  double m{};
  double mx{};
  double mv{};

  auto centre_of_mass() { return mx / m; }
  auto centre_of_mass_v() { return mv / m; }
};

void print_state(std::vector<PPState> const& state) {
  auto length = state.back().x - state.front().x;

  auto sums = std::accumulate(state.begin(), state.end(), Acc{},
                              [](Acc sums, PPState const& pps) {
                                sums.m += pps.m;
                                sums.mx += pps.m * pps.x;
                                sums.mv += pps.m * pps.v;
                                return sums;
                              });

  std::cout << std::setprecision(4) << std::fixed << std::setw(8) << length
            << "  : " << std::setw(14) << sums.centre_of_mass() << "   : "
            << std::setw(14) << sums.centre_of_mass_v() << '\n';
}

void print_summary(std::vector<std::vector<PPState>> const& v_states) {
  auto sum_length =
      std::accumulate(v_states.begin(), v_states.end(), 0.0,
                      [](double length, std::vector<PPState> const& state) {
                        return length + state.back().x - state.front().x;
                      });

  std::cout << "Average length: " << (sum_length / v_states.size()) << '\n';
}

int main() {
  Hooke const hooke{1.0, 0.01};

  // Catena con 10 punti materiali:
  // m: 50 g per ogni punto
  // x: un punto ogni 1.1 cm (partendo da 0.0)
  // v: tutti i punti hanno v = 0 m/s
  Chain chain{hooke};

  int const n_points{10};
  double const p_m{0.05};
  double const p_v{0.0};

  double delta_x{0.011};

  std::generate_n(std::back_inserter(chain), n_points,
                  [=, p_x = 0.0]() mutable {
                    auto x = p_x;
                    p_x += delta_x;
                    return PPState{p_m, x, p_v};
                  });

  // Esegue una simulazione:
  // - per una durata di 20 s
  // - suddividendola in 20000 intervalli di tempo
  // - registrando lo stato della catena ogni 100 intervalli di tempo
  double const duration{20.0};
  int const steps{20000};
  int const prescale{100};

  const auto v_states = simulate(chain, duration, steps, prescale);

  std::cout << "Report for each fo the stored states:\n";
  std::cout << " length : center of mass x : center of mass v\n";
  std::for_each(v_states.begin(), v_states.end(), print_state);

  std::cout << "\nSummary:\n";
  print_summary(v_states);
}
