#include <iostream>

int main()
{
  int a;
  int b;
  std::cin >> a >> b;
  int result;
  if (a < b) {
    result = a;
  } else {
    result = b; 
  }
  std::cout << result << '\n';
}
