#include <iostream>

int main()
{
  int a;
  int b;
  int c;
  std::cin >> a >> b >> c;
  int min = a;
  if (b < min) {
    min = b;
  }
  if (c < min) {
    min = c;
  }
  std::cout << min << '\n';
}
