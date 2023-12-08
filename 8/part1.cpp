#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
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
      tokens.push_back(new_string);
    }
  } while (end != -1);
  return tokens;
}

int main() {
  std::string line;
  std::ifstream content;
  std::unordered_map<std::string, const std::pair<const std::string, const std::string>> network;
  size_t result = 0, iterations = 0;
  const std::string end_position = "ZZZ";
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  getline(content, line);

  const std::string navigation_orders = line;

  getline(content, line);

  while (getline(content, line)) {
    std::vector<std::string> temp = tokenize(line, " = ");
    const std::string hash_key = temp[0];
    std::vector<std::string> pair_value = tokenize(temp[1].substr(1, temp[1].length() - 2), ", ");
    const std::pair<const std::string, const std::string> hash_value = {pair_value[0], pair_value[1]};

    network.insert({hash_key, hash_value});
  }

  //  for (auto instruction : network) {
  //    std::cout << " mapped " << instruction.first << " into L " << instruction.second.first << " or R " << instruction.second.second << std::endl;
  //  }
  std::string current_position = "AAA";
  while (current_position != end_position) {
    ++iterations;
    for (auto order : navigation_orders) {
      if (order == 'L') {
        current_position = network[current_position].first;
      } else {
        current_position = network[current_position].second;
      }
    }
  }

  result = iterations * navigation_orders.length();

  std::cout << "result: " << result << std::endl;
  content.close();
  return EXIT_SUCCESS;
}
