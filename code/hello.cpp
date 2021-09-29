#include <iostream>
#include <string>

int main()
{
  std::cout << "What's your name? ";
  std::string name;
  std::cin >> name;
  std::cout << "Hello, " << name << '\n';
}
