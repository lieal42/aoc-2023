#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#define MY_FILE "data1.txt"
#define CONVERSION 48

int main() {
  std::string line;
  std::ifstream content;
  int sum = 0;
  std::string lit_num;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, line)) {

    lit_num = "";

    for (char c : line) {
      if (std::isdigit(c)) {
        lit_num += c;
      }
    }

    //    std::cout << "literal number: " << lit_num << std::endl;

    //    char number[2];
    //    number[0] = lit_num.front();
    //    number[1] = lit_num.back();

    //  std::string number = std::to_string(lit_num.front()) + std::to_string(lit_num.back());

    int number = (lit_num.front() - CONVERSION) * 10 + (lit_num.back() - CONVERSION);

    //    std::cout << "integer number: " << (number) << std::endl;

    //    std::cout << "line: " << line << "\n";

    sum += (number);

    //    std::cout << "sum so far: " << sum << std::endl;
  }

  std::cout << "sum: " << sum << std::endl;

  content.close();
  return EXIT_SUCCESS;
}
