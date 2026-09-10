#include "Rook.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Square.hpp"
#include <vector>

Rook::Rook(PieceColor c) : Piece(c), firstMove(true) {}
Rook::Rook(const Rook &other)
    : Piece(other.color, other.pin), firstMove(other.firstMove) {}
Rook *Rook::clone() const { return new Rook(*this); }

std::vector<Pos> Rook::getPlausiblePosList(const Square &sq,
                                           const Board &board) const {
  std::vector<Pos> list;
  this->addCardinalPos(list, sq, board);
  return list;
}

bool Rook::isFirstMove() const { return firstMove; }
void Rook::move(const Move &move, Board &board) {
  genericMove(move, board);
  firstMove = false;
}

std::string Rook::getIcon() const { return "♜"; }

// overload << operator
std::ostream &operator<<(std::ostream &os, const Rook &k) {
  os << "R";
  return os;
}
