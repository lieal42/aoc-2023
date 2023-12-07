#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
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
  std::unordered_map<char, int> cards = {
      {'A', 12},
      {'K', 11},
      {'Q', 10},
      {'J', 9},
      {'T', 8},
      {'9', 7},
      {'8', 6},
      {'7', 5},
      {'6', 4},
      {'5', 3},
      {'4', 2},
      {'3', 1},
      {'2', 0},
  };
  std::unordered_map<std::string, int> points = {
      {"FI", 6},
      {"FO", 5},
      {"FH", 4},
      {"TH", 3},
      {"TP", 2},
      {"OP", 1},
      {"HC", 0},
  };
  std::map<size_t, size_t> values;
  size_t result = 0;
  content.open(MY_FILE);
  if (!content.is_open()) {
    std::cout << "Error: no such file!" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<size_t> bets;
  size_t counter = 0;

  while (getline(content, line)) {
    std::string hand = tokenize(line)[0];
    bets.push_back(std::stoull(tokenize(line)[1]));

    std::unordered_map<char, int> cards_in_hand;

    size_t value;

    for (auto card : hand) {
      if (cards_in_hand.find(card) != cards_in_hand.end()) {
        ++cards_in_hand[card];
      } else {
        cards_in_hand.insert({card, 1});
      }
    }
    std::string kind;

    bool check = true;
    switch (cards_in_hand.size()) {
    case 1:
      kind = "FI";
      break;
    case 2:
      for (auto it : cards_in_hand) {
        if (it.second == 4) {
          kind = "FO";
          check = false;
          break;
        }
      }
      if (check) {
        kind = "FH";
      }
      break;
    case 3:
      for (auto it : cards_in_hand) {
        if (it.second == 3) {
          kind = "TH";
          check = false;
          break;
        }
      }
      if (check) {
        kind = "TP";
      }
      break;
    case 4:
      kind = "OP";
      break;
    case 5:
      kind = "HC";
      break;
    }
    value = points[kind] << 20;

    for (size_t i = 0; i < hand.length(); ++i) {
      value += (cards[hand[i]] << (4 * (4 - i)));
    }
    values.insert({value, counter});

    ++counter;
  }

  size_t rank = 1;

  for (auto i : values) {
    result += rank * bets[i.second];
    ++rank;
  }

  std::cout << "result: " << result << std::endl;
  content.close();
  return EXIT_SUCCESS;
}
