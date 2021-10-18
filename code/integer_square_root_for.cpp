#include <iostream>

int main()
{
  int n;
  std::cin >> n;
  int i = 1;
  for ( ; i * i < n; ++i) ;
  if (i * i > n) {
    --i;
  }
  std::cout << i << '\n';
}
