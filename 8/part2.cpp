#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
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

size_t vec_lcm(std::vector<size_t> numbers) {
  if (numbers.size() == 2) {
    return std::lcm(numbers[0], numbers[1]);
  }
  return std::lcm(numbers[0], vec_lcm(std::vector<size_t>(numbers.begin() + 1, numbers.end())));
}

int main() {
  std::string line;
  std::ifstream content;
  std::unordered_map<std::string, const std::pair<const std::string, const std::string>> network;
  size_t result = 0;
  std::vector<size_t> iterations_vector;
  const char end_position_char = 'Z', start_position_char = 'A';
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

  std::vector<std::string> current_positions;

  for (auto instruction : network) {
    if (instruction.first.back() == start_position_char) {
      current_positions.push_back(instruction.first);
    }
  }
  for (auto current_position : current_positions) {
    size_t iterations = 0;
    while (current_position.back() != end_position_char) {
      ++iterations;
      for (auto order : navigation_orders) {
        if (order == 'L') {
          current_position = network[current_position].first;
        } else {
          current_position = network[current_position].second;
        }
      }
    }
    iterations_vector.push_back(iterations);
  }

  result = vec_lcm(iterations_vector) * navigation_orders.length();

  std::cout << "result: " << result << std::endl;
  content.close();
  return EXIT_SUCCESS;
}
