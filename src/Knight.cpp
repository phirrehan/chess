#include "Knight.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Position.hpp"

Knight::Knight(PieceColor c) : Piece(c) {}
Knight::Knight(const Knight &other) : Piece(other.color, other.pin) {}

Knight *Knight::clone() const { return new Knight(*this); }

std::vector<Pos> Knight::getAttackPositions(const Pos &p,
                                            const Board &board) const {
  std::vector<Pos> list = {
      {p.row + 2, p.col + 1}, {p.row + 2, p.col - 1}, {p.row - 2, p.col + 1},
      {p.row - 2, p.col - 1}, {p.row + 1, p.col + 2}, {p.row - 1, p.col + 2},
      {p.row + 1, p.col - 2}, {p.row - 1, p.col - 2},
  };
  Board::popOutOfBoundsElements(list);
  return list;
}

std::string Knight::getIcon() const { return "♞"; }
std::string Knight::toString() const { return "N"; }
