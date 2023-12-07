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
  size_t result = 1;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, line)) {
    data.push_back(line.erase(0, line.find(": ") + 1));
  }

  std::vector<std::string> str_times = tokenize(data[0]), str_distances = tokenize(data[1]);
  std::vector<size_t> times, distances;

  for (size_t i = 0; i < str_times.size(); ++i) {
    times.push_back(std::stoull(str_times[i]));
    distances.push_back(std::stoull(str_distances[i]));
  }

  for (size_t i = 0; i < times.size(); ++i) {
    size_t total = times[i];
    size_t record = distances[i];
    size_t winning = 0;
    for (size_t j = 0; j < total; ++j) {
      winning += (j * (total - j) > record) ? 1 : 0;
    }
    result *= winning;
  }

  std::cout << "result: " << result << std::endl;

  content.close();
  return EXIT_SUCCESS;
}
