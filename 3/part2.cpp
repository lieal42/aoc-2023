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
      if (schematics[row][col] == '*') {
        int nNum = 0;
        std::vector<int> gears;
        for (auto &number : numbers) {
          bool control = true;
          if (row - 1 == number.row) {
            for (auto c : number.cols) {
              if ((c == col - 1 || c == col || c == col + 1) && control) {
                number.to_use = true;
                control = false;
                nNum++;
                gears.push_back(number.value);
              }
            }
          }
          if (row == number.row) {
            for (auto c : number.cols) {
              if ((c == col - 1 || c == col || c == col + 1) && control) {
                number.to_use = true;
                control = false;
                nNum++;
                gears.push_back(number.value);
              }
            }
          }
          if (row + 1 == number.row) {
            for (auto c : number.cols) {
              if ((c == col - 1 || c == col || c == col + 1) && control) {
                number.to_use = true;
                control = false;
                nNum++;
                gears.push_back(number.value);
              }
            }
          }
          // qui finisce il ciclo esterno del vector
        }
        if (nNum == 2) {
          sum += gears[1] * gears[0];
        }
      }
    }
  }

  std::cout << "sum: " << sum << std::endl;
  content.close();
  return EXIT_SUCCESS;
}
