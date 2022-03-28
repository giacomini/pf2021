// compile with: g++ -Wall -Wextra -g -fsanitize=address -std=c++17 word_counting.cpp
// run with: ./a.out < divina_commedia.txt

#include <iomanip>
#include <iostream>
#include <map>

int main()
{
  std::map<std::string, int> words;

  std::string word;
  while (std::cin >> word) {
    ++words[word];
  }

  auto const width = 12;
  for (auto const& [w, c] : words) {
    std::cout << std::setw(width) << std::left << w << ": " << std::setw(6)
              << std::right << c << '\n';
  }
}
