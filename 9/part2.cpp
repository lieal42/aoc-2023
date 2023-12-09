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

std::vector<std::vector<long long int>> build_prediction_map(std::vector<long long int> vec) {
  bool all_zeroes;
  std::vector<std::vector<long long int>> pred_map;
  pred_map.push_back(vec);
  do {
    std::vector<long long int> numbers;
    for (size_t i = 1; i < pred_map.back().size(); ++i) {
      numbers.push_back(pred_map.back()[i] - pred_map.back()[i - 1]);
    }
    pred_map.push_back(numbers);
    all_zeroes = true;
    for (auto element : pred_map.back()) {
      if (element != 0) {
        all_zeroes = false;
      }
    }
  } while (!all_zeroes);
  return pred_map;
}

int main() {
  std::string line;
  std::ifstream content;
  long long int result = 0;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, line)) {
    std::vector<long long int> report_line;
    for (auto step : tokenize(line)) {
      report_line.push_back(std::stoll(step));
    }
    std::vector<std::vector<long long int>> prediction_map = build_prediction_map(report_line);

    for (auto &element : prediction_map) {
      std::reverse(element.begin(), element.end());
    }

    for (int i = prediction_map.size() - 2; i >= 0; --i) {
      prediction_map[i].push_back(prediction_map[i].back() - prediction_map[i + 1].back());
    }
    result += prediction_map.front().back();
  }

  std::cout << "result: " << result << std::endl;
  content.close();
  return EXIT_SUCCESS;
}
