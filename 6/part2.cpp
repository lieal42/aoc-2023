#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define MY_FILE "data.txt"

std::vector<std::string> tokenize(std::string str, std::string del = " ") {
  int start, end = -1 * del.length();
  std::vector<std::string> tokens;
  do {
    start = end + del.length();
    end = str.find(del, start);
    std::string new_string = str.substr(start, end - start);
    if (new_string != "") {
      tokens.push_back(str.substr(start, end - start));
    }
  } while (end != -1);
  return tokens;
}

int main() {
  std::string line;
  std::ifstream content;
  std::vector<std::string> data;
  size_t result = 0;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, line)) {
    data.push_back(line.erase(0, line.find(": ") + 1));
  }

  data[0].erase(std::remove(data[0].begin(), data[0].end(), ' '), data[0].end());
  data[1].erase(std::remove(data[1].begin(), data[1].end(), ' '), data[1].end());

  size_t times = std ::stoull(data[0]), distances = std::stoull(data[1]);
  for (size_t i = 1; i < times; ++i) {
    result += (i * (times - i) > distances) ? 1 : 0;
  }

  std::cout << "result: " << result << std::endl;

  content.close();
  return EXIT_SUCCESS;
}
