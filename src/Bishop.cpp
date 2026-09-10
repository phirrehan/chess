#include "Bishop.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Square.hpp"

Bishop::Bishop(PieceColor c) : Piece(c) {}
Bishop::Bishop(const Bishop &other) : Piece(other.color) {}

Bishop *Bishop::clone() const { return new Bishop(*this); }
std::vector<Pos> Bishop::getPlausiblePosList(const Square &sq,
                                             const Board &board) const {
  std::vector<Pos> list;
  this->addDiagonalPos(list, sq, board);
  return list;
}

std::string Bishop::getIcon() const { return "♝"; }

void Bishop::move(const Move &move, Board &board) { genericMove(move, board); }

// overload << operator
std::ostream &operator<<(std::ostream &os, const Bishop &k) {
  os << "B";
  return os;
}
