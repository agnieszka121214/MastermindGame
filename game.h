#include <algorithm>
#include <iostream>
// #include <list>
#include <map>
#include <random>
#include <string>
#include <vector>

#ifndef GAME_H
#define GAME_H

class Game {
private:
  std::vector<int> randomCode;
  std::vector<int> checkCode;
  std::map<std::pair<int, int>, std::string> matchingNumbers;
  int countMatches = 0;
  const int size = 4;

public:
  void menu();

  std::vector<int> generateCode();
  int random();

  std::string enterNumberCode();
  void validateNumberCode(std::string numberCode);
  std::vector<int>
  convertNumberCodeFromSringToIntVector(std::string numberCode);

  void play();
  bool round();
  void checkAndPrepareNumberCode();
  bool checkCodeMatches();
  void resetCountMatches();
  bool checkWin();

  void printMatchingNumbersMap();
  void clearMatchingNumbersMap();
};

#endif
