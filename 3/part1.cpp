#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define MY_FILE "data.txt"

struct IntegerInSpace {
  int value;
  int row;
  std::vector<int> cols;
  bool to_use;
};

int main() {
  std::string line;
  std::ifstream content;
  std::vector<std::string> schematics;
  std::vector<IntegerInSpace> numbers;
  size_t sum = 0;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, line)) {
    schematics.push_back(line);
  }

  for (size_t row = 0; row < schematics.size(); row++) {
    for (size_t col = 0; col < schematics[row].size(); col++) {
      if (isdigit(schematics[row][col])) {
        std::string lit_num = "";
        std::vector<int> cols;
        IntegerInSpace number;
        do {
          cols.push_back(col);
          lit_num += schematics[row][col];
          col++;
        } while (col < schematics[row].size() && isdigit(schematics[row][col]));
        number.value = std::stoi(lit_num);
        number.row = row;
        number.cols = cols;
        number.to_use = false;
        numbers.push_back(number);
      }
    }
  }

  for (size_t row = 0; row < schematics.size(); row++) {
    for (size_t col = 0; col < schematics[row].size(); col++) {
      if (!isdigit(schematics[row][col]) && schematics[row][col] != '.') {
        for (auto &number : numbers) {
          if (row - 1 == number.row) {
            for (auto c : number.cols) {
              if (c == col - 1 || c == col || c == col + 1) {
                number.to_use = true;
              }
            }
          }
          if (row == number.row) {
            for (auto c : number.cols) {
              if (c == col - 1 || c == col || c == col + 1) {
                number.to_use = true;
              }
            }
          }
          if (row + 1 == number.row) {
            for (auto c : number.cols) {
              if (c == col - 1 || c == col || c == col + 1) {
                number.to_use = true;
              }
            }
          }
        }
      }
    }
  }
  for (auto number : numbers) {
    if (number.to_use) {
      sum += number.value;
    }
  }
  std::cout << "sum: " << sum << std::endl;
  content.close();
  return EXIT_SUCCESS;
}
