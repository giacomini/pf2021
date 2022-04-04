// compile with: g++ -Wall -Wextra -g -fsanitize=address -std=c++17 better_word_counting.cpp
// run with: ./a.out < divina_commedia.txt

#include <algorithm>
#include <cassert>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

using Words = std::map<std::string, int>;

// all lowercase, no punctuation characters
void normalize(std::string& s);

// return the width of the longest word
int max_width(Words const& words);

int main()
{
  Words words;

  std::string line;
  while (std::getline(std::cin, line)) {
    normalize(line);
    std::istringstream is{line};
    std::string word;
    while (is >> word) {
      ++words[word];
    }
  }

  auto const width{max_width(words)};

  for (auto const& [w, c] : words) {
    std::cout << std::setw(width) << std::left << w << ": " << std::setw(6)
              << std::right << c << '\n';
  }
}

void normalize(std::string& s)
{
  // clang-format off
    std::transform(
      s.begin(),
      s.end(),
      s.begin(),
      [](unsigned char c) -> char {
        if (std::isalpha(c)) {
          return std::tolower(c);
        } else {
          return ' ';
        }
      }
    );
  // clang-format on
}

int max_width(Words const& words)
{
  // clang-format off
  return
    words.empty()
    ? 0
    : std::max_element(
         words.begin(), words.end(), [](auto const& l, auto const& r) {
             return l.first.size() < r.first.size();
         }
      )->first.size();
  // clang-format on
}