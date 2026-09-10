#include "Knight.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Position.hpp"
#include "Square.hpp"

Knight::Knight(PieceColor c) : Piece(c) {}
Knight::Knight(const Knight &other) : Piece(other.color, other.pin) {}

Knight *Knight::clone() const { return new Knight(*this); }

std::vector<Pos> Knight::getPlausiblePosList(const Square &sq,
                                             const Board &board) const {
  Pos p = sq.getPos();
  std::vector<Pos> list = {
      {p.row + 2, p.col + 1}, {p.row + 2, p.col - 1}, {p.row - 2, p.col + 1},
      {p.row - 2, p.col - 1}, {p.row + 1, p.col + 2}, {p.row - 1, p.col + 2},
      {p.row + 1, p.col - 2}, {p.row - 1, p.col - 2},
  };
  Board::popOutOfBoundsElements(list);
  return list;
}
std::string Knight::getIcon() const { return "♞"; }

void Knight::move(const Move &move, Board &board) { genericMove(move, board); }

// overload << operator
std::ostream &operator<<(std::ostream &os, const Knight &k) {
  os << "N";
  return os;
}
