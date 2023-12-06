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
  std::string line, all_file;
  std::ifstream content;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, line)) {
    all_file.append(line + "\n");
  }
  all_file.append("\n");

  std::vector<std::string> maps = tokenize(all_file, "\n\n");

  // make seeds integer vector and removing first block from maps
  std::vector<std::string> temp = tokenize(maps.front().substr(maps.front().find(":") + 2));

  std::vector<size_t> seeds;
  for (auto seed : temp) {
    seeds.push_back(std::stoull(seed));
  }

  maps.erase(maps.begin());
  // done
  for (auto &seed : seeds) {
    for (auto block : maps) {
      block.erase(0, block.find("\n") + 1);
      std::vector<std::string> temp = tokenize(block, "\n");
      std::vector<std::vector<size_t>> datamap;
      for (auto line : temp) {
        std::vector<size_t> tempint;
        std::vector<std::string> temp1 = tokenize(line);
        for (auto number : temp1) {
          tempint.push_back(std::stoull(number));
        }
        datamap.push_back(tempint);
      }
      for (auto range : datamap) {
        if (seed >= range[1] && seed < range[1] + range[2]) {
          seed += (range[0] - range[1]);
          break;
        }
      }
    }
  }

  std::cout << "closest location: " << *std::min_element(seeds.begin(), seeds.end()) << std::endl;

  content.close();
  return EXIT_SUCCESS;
}
