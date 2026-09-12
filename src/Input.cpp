#include "Input.hpp"
#include "Exception.hpp"
#include "Position.hpp"
#include <iostream>

std::string Input::getStr() {
  std::string str;
  std::getline(std::cin, str);
  return str;
}

Pos Input::getPos() {
  std::string input = getStr();
  if (input.size() == 0)
    throw InvalidInput("input must not be empty");
  else if (input.size() == 1) {
    if (std::tolower(input[0]) == 's')
      throw ReturnToSelection("Returning to Piece Selection");
    else if (std::tolower(input[0]) == 'q')
      throw Terminate("Terminating program...");
  } else if (input.size() > 2 || input.size() == 0)
    InvalidInput("Please enter exactly two letter coordinate such as: e2");

  // validate rank
  switch (input[1]) {
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
    break;
  default:
    throw InvalidInput("Invalid Rank: rank must be between 1-9");
  }

  // validate file
  char lowerCaseFile = std::tolower(input[0]);
  switch (lowerCaseFile) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
    break;
  default:
    throw InvalidInput("invalid file: file must be between a-h");
  }

  // return pos
  return Pos(input[1], lowerCaseFile);
}

void Input::pressEnter() {
  std::cout << "Press Enter to Continue.\n";
  getStr(); // dump the input string
}
