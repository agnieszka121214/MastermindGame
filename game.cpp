#include "game.h"

void Game::menu() {
  std::cout << "Welcome to the Mastermind Game" << std::endl;
  std::cout << "Enter the numbers in the following sequence 1234" << std::endl;
  std::cout << "OK - correct number on correct position" << std::endl;
  std::cout << "X - correct number on wrong position" << std::endl;
  std::cout << "NOK - number does not exist in secret code" << std::endl;
}

std::vector<int> Game::generateCode() {
  auto randomNumber = 0;
  for (int i = 0; i < size; i++) {
    randomNumber = random();
    randomCode.push_back(randomNumber);
    std::cout << randomNumber << "   ";
  }
  std::cout << std::endl;
  return randomCode;
}

int Game::random() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 6);
  return dist(gen);
}

std::string Game::enterNumberCode() {
  std::string numbers{};
  std::getline(std::cin, numbers);
  return numbers;
}

void Game::validateNumberCode(std::string numberCode) {
  if (numberCode.size() != 4) {
    std::cout << "std::range_error ";
    throw std::range_error("Error, Incorrect size of code.");
  } else if (numberCode.find_first_not_of("123456") != std::string::npos) {
    throw std::runtime_error(
        "Error, Incorect code sequence, enter four numbers between 1 and 6.");
  }
}

std::vector<int>
Game::convertNumberCodeFromSringToIntVector(std::string numberCode) {
  for (size_t i = 0; i < numberCode.length(); ++i) {
    int num = numberCode[i] - '0';
    checkCode.push_back(num);
    matchingNumbers.insert({std::make_pair(i, num), " "});
  }
  return checkCode;
}

bool Game::checkAndPrepareNumberCode() {
  bool isValidated;
  std::string codeFromUser = enterNumberCode();
  try {
    validateNumberCode(codeFromUser);
    convertNumberCodeFromSringToIntVector(codeFromUser);
    isValidated = true;
  } catch (std::runtime_error const &e) {
    std::cout << e.what() << std::endl;
    isValidated = false;
  } catch (std::range_error const &e) {
    std::cout << e.what() << std::endl;
    isValidated = false;
  }
  return isValidated;
}

void Game::play() {
  generateCode();
  for (int i = 0; i < 10; i++) {
    clearMatchingNumbersMap();
    resetCountMatches();
    if (round()) {
      std::cout << " You win!!! " << std::endl;
      break;
    }
  }
}

bool Game::round() {
  bool checkedCode = false;
  while (checkedCode != true) {
    checkedCode = checkAndPrepareNumberCode();
  }
  bool checkedCodeMatches = checkCodeMatches();
  printMatchingNumbersMap();
  return checkedCodeMatches;
}

bool Game::checkCodeMatches() {
  std::vector<int> randomCodeC = randomCode;
  std::vector<int>::iterator itv = randomCodeC.begin();

  for (std::map<std::pair<int, int>, std::string>::iterator itm =
           matchingNumbers.begin();
       itm != matchingNumbers.end(); ++itm) {
    if (*itv == itm->first.second) {
      itm->second = "OK";
      itv = randomCodeC.erase(itv);
      countMatches++;
    } else {
      ++itv;
    }
  }

  if (checkWin()) {
    return true;
  }

  for (std::map<std::pair<int, int>, std::string>::iterator itm =
           matchingNumbers.begin();
       itm != matchingNumbers.end(); ++itm) {
    auto foundKeyNumberInCode =
        std::find(randomCodeC.begin(), randomCodeC.end(), itm->first.second);
    if (itm->second == " " && foundKeyNumberInCode != randomCodeC.end()) {
      itm->second = "X";
      randomCodeC.erase(foundKeyNumberInCode);

    } else if (itm->second == " ") {
      itm->second = "NOK";
    }
  }
  return false;
}

void Game::resetCountMatches() { countMatches = 0; }

bool Game::checkWin() { return (countMatches == 4) ? true : false; }

void Game::clearMatchingNumbersMap() { matchingNumbers.clear(); }

void Game::printMatchingNumbersMap() {
  for (std::map<std::pair<int, int>, std::string>::const_iterator it =
           matchingNumbers.begin();
       it != matchingNumbers.end(); ++it) {
    std::cout << it->first.second << "-" << it->second << "  ";
  }
  std::cout << std::endl;
}
