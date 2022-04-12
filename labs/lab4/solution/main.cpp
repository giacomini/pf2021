#include "regression.hpp"

#include <iostream>
#include <limits>

int main() {
  try {
    Regression reg;
    char cmd;

    std::cout << "Valid commands: a (add), r (remove), f (fit)\n";

    while (std::cin >> cmd) {
      if (cmd == 'a') {
        double x, y;
        if (std::cin >> x >> y) {
          reg.add(x, y);
          Point p{x, y};
          std::cout << "Successfully added: " << p << '\n';
        }
      } else if (cmd == 'r') {
        double x, y;
        if (std::cin >> x >> y) {
          Point p{x, y};
          if (reg.remove(x, y)) {
            std::cout << "Successfully removed: " << p << '\n';
          } else {
            std::cout << p << " not found\n";
          }
        }
      } else if (cmd == 'f') {
        break;
      } else if (std::cin.good()) {
        std::cerr << "Invalid command '" << cmd << "'\n";
      }

      if (std::cin.fail()) {
        std::cerr << "Bad format, insert a new command\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }

    std::cout << "Regression object size: " << reg.size() << '\n';
    if (reg.size() > 1) {
      const auto r = reg.fit();
      std::cout << "Regression line: y = " << r.B << " * x + " << r.A << '\n';
    }

  } catch (std::exception const& e) {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
