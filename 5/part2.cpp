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
  size_t min;
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

  for (size_t index = 0; index < seeds.size(); index += 2) {
    seeds[index + 1] = seeds[index] + seeds[index + 1] - 1;
  }

  maps.erase(maps.begin());
  // done
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
    std::vector<size_t> newseeds;
    while (seeds.size() > 0) {
      bool control = true;
      size_t end = seeds.back() + 1;
      seeds.pop_back();
      size_t start = seeds.back();
      seeds.pop_back();
      for (auto range : datamap) {
        size_t block_start = std::max(start, range[1]);
        size_t block_end = std::min(end, range[1] + range[2]);
        if (block_start < block_end) {
          newseeds.push_back(block_start - range[1] + range[0]);
          newseeds.push_back(block_end - range[1] + range[0] - 1);
          if (block_start > start) {
            seeds.push_back(start);
            seeds.push_back(block_start - 1);
          }
          if (block_end < end) {
            seeds.push_back(block_end);
            seeds.push_back(end - 1);
          }
          control = false;
          break;
        }
      }
      if (control) {
        newseeds.push_back(start);
        newseeds.push_back(end - 1);
      }
    }
    seeds = newseeds;
  }

  min = seeds.front();
  for (size_t index = 0; index < seeds.size(); index += 2) {
    min = (seeds[index] < min) ? seeds[index] : min;
  }

  std::cout << "closest location: " << min << std::endl;
  content.close();
  return EXIT_SUCCESS;
}
