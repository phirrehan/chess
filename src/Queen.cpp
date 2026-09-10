#include "Queen.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Square.hpp"

Queen::Queen(PieceColor c) : Piece(c) {}
Queen::Queen(const Queen &other) : Piece(other.color) {}

Queen *Queen::clone() const { return new Queen(*this); }
std::vector<Pos> Queen::getPlausiblePosList(const Square &sq,
                                            const Board &board) const {
  std::vector<Pos> list;
  this->addCardinalPos(list, sq, board);
  this->addDiagonalPos(list, sq, board);
  return list;
}

std::string Queen::getIcon() const { return "♛"; }

void Queen::move(const Move &move, Board &board) { genericMove(move, board); }

// overload << operator
std::ostream &operator<<(std::ostream &os, const Queen &k) {
  os << "Q";
  return os;
}
