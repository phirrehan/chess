#include "Input.hpp"
#include "Bishop.hpp"
#include "Exception.hpp"
#include "Graphics.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Piece.hpp"
#include "Position.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include <iostream>

using namespace std;

char Input::getChar() {
  char c;
  cin >> c;
  cin.ignore();
  return c;
}

string Input::getStr() {
  string str;
  getline(cin, str);
  return str;
}

void Input::validateStr(string str) {
  if (str.size() == 0)
    throw InvalidInput("input must not be empty");
  else if (str.size() == 1) {
    if (tolower(str[0]) == 's')
      throw ReturnToSelection("Returning to Piece Selection");
    else if (tolower(str[0]) == 'q')
      throw Terminate("Terminating program...");
  } else if (str.size() > 2 || str.size() == 0)
    InvalidInput("Please enter exactly two letter coordinate such as: e2");
}

Pos Input::getPos() {
  string input = getStr();
  validateStr(input);

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
  char lowerCaseFile = tolower(input[0]);
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
Piece *Input::getPromotionPiece(PieceColor color) {
  char input;
  const std::string FG_COLOR =
      (color == PieceColor::WHITE) ? FG_WHITE : FG_BLACK;
  cout << "1) " << FG_COLOR << "♛" << FG_WHITE << endl;
  cout << "2) " << FG_COLOR << "♜" << FG_WHITE << endl;
  cout << "3) " << FG_COLOR << "♝" << FG_WHITE << endl;
  cout << "4) " << FG_COLOR << "♞" << FG_WHITE << endl;
  do {
    cout << "Choose a piece to promote pawn: \n";
    input = getChar();
    switch (static_cast<Promotion>(input)) {
    case Promotion::QUEEN:
      return new Queen(color);
    case Promotion::ROOK:
      return new Rook(color);
    case Promotion::BISHOP:
      return new Bishop(color);
    case Promotion::KNIGHT:
      return new Knight(color);
    default:
      cout << "invalid choice. please choose from 1-4" << endl;
    }
  } while (true);
}

void Input::pressEnter() {
  cout << "Press Enter to Continue.\n";
  getStr(); // dump the input string
}
