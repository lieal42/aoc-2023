#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#define MY_FILE "data1.txt"
#define CONVERSION 48

int main() {
  std::string line;
  std::ifstream content;
  int sum = 0;
  std::string lit_num;
  const size_t max_length = 5;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::unordered_map<std::string, std::string> dict{
      {"one", "1"},
      {"two", "2"},
      {"three", "3"},
      {"four", "4"},
      {"five", "5"},
      {"six", "6"},
      {"seven", "7"},
      {"eight", "8"},
      {"nine", "9"},
  };

  while (getline(content, line)) {

    lit_num = "";

    for (size_t pos = 0; pos < line.length(); pos++) {
      if (std::isdigit(line[pos])) {
        lit_num += line[pos];
      } else {
        for (size_t len = 3; len < std::min(max_length, line.length() - pos) + 1; len++) {
          if (dict.contains(line.substr(pos, len))) {
            lit_num += dict[line.substr(pos, len)];
          }
        }
      }
    }

    int number = (lit_num.front() - CONVERSION) * 10 + (lit_num.back() - CONVERSION);

    sum += number;
  }

  std::cout << "sum: " << sum << std::endl;

  content.close();
  return EXIT_SUCCESS;
}
