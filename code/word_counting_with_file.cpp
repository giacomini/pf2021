// compile with: g++ -Wall -Wextra -g -fsanitize=address -std=c++17 word_counting_with_file.cpp
// run with: ./a.out < divina_commedia.txt
//       or: ./a.out divina_commedia.txt

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>

int main(int argc, char* argv[])
{
  std::ifstream fis;

  if (argc > 1) {
    std::string const& filename{argv[1]};

    fis.open(filename);

    if (!fis) {
      std::cerr << "Cannot open file " << filename << '\n';
      return EXIT_FAILURE;
    }
  }

  std::istream& is = fis.is_open() ? fis : std::cin;

  std::map<std::string, int> words;

  std::string word;
  while (is >> word) {
    ++words[word];
  }

  auto const width = 12;
  for (auto const& [w, c] : words) {
    std::cout << std::setw(width) << std::left << w << ": " << std::setw(6)
              << std::right << c << '\n';
  }
}
