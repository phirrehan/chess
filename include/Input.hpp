#include "Piece.hpp"
#include <string>
class Piece;
struct Pos;

const std::string QUIT_KEY = "q";
const std::string SELECTION_KEY = "s";

enum class Promotion { QUEEN = '1', ROOK = '2', BISHOP = '3', KNIGHT = '4' };
// class for exception handling
class Input {
public:
  static char getChar();
  static std::string getStr();
  static void validateStr(std::string);
  static Pos getPos();
  static Piece *getPromotionPiece(PieceColor);
  static void pressEnter();
};
