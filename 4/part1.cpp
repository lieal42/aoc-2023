#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
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

std::unordered_set<std::string> intersection(std::unordered_set<std::string> a, std::unordered_set<std::string> b) {
  std::unordered_set<std::string> c;
  for (auto element : a) {
    if (b.contains(element)) {
      c.insert(element);
    }
  }
  return c;
}

int main() {
  std::string line;
  std::ifstream content;
  size_t sum = 0;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, line)) {
    line.erase(0, line.find(":") + 2);

    std::vector<std::string> scratchcard = tokenize(line, " | ");
    std::vector<std::vector<std::string>> computation;
    for (auto section : scratchcard) {
      computation.push_back(tokenize(section));
    }
    std::unordered_set<std::string> winning, ours, matching;
    for (auto number : computation.front()) {
      winning.insert(number);
    }
    for (auto number : computation.back()) {
      ours.insert(number);
    }
    matching = intersection(winning, ours);
    if (matching.size() > 0) {
      sum += 1 << (matching.size() - 1);
    }
  }

  std::cout << "sum: " << sum << std::endl;

  content.close();
  return EXIT_SUCCESS;
}
