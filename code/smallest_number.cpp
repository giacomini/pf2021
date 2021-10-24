#include <iostream>

int main()
{
  int smallest;
  std::cin >> smallest;

  if (std::cin) {
    for (int n; std::cin >> n; ) {
      if (n < smallest) {
        smallest = n;
      }
    }
    std::cout << smallest << '\n';
  } else {
    std::cerr << "No numbers\n";
  }
}
