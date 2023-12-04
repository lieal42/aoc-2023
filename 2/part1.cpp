#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define MY_FILE "data.txt"
#define RED 12
#define GREEN 13
#define BLUE 14

std::vector<std::string> tokenize(std::string str, std::string del = " ") {
  int start, end = -1 * del.length();
  std::vector<std::string> tokens;
  do {
    start = end + del.length();
    end = str.find(del, start);
    tokens.push_back(str.substr(start, end - start));
  } while (end != -1);
  return tokens;
}

int main() {
  std::string game;
  std::map<std::string, int> rgb{
      {"red", -1},
      {"green", -1},
      {"blue", -1},
  };
  std::ifstream content;
  size_t sum = 0, game_counter = 0;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (getline(content, game)) {
    game_counter++;
    rgb["red"] = rgb["green"] = rgb["blue"] = -1;
    game.erase(0, game.find(":") + 2);

    std::vector<std::string> rounds = tokenize(game, "; ");
    for (auto rnd : rounds) {
      std::vector<std::string> colors = tokenize(rnd, ", ");
      for (auto clr : colors) {
        std::vector<std::string> single = tokenize(clr);
        rgb[single[1]] = std::max(rgb[single[1]], std::stoi(single[0]));
      }
    }

    if (rgb["red"] <= RED && rgb["green"] <= GREEN && rgb["blue"] <= BLUE) {
      sum += game_counter;
    }
  }

  std::cout << "sum: " << sum << std::endl;

  content.close();
  return EXIT_SUCCESS;
}
