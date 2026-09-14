#include "Queen.hpp"
#include "Board.hpp"

Queen::Queen(PieceColor c) : Piece(c) {}
Queen::Queen(const Queen &other) : Piece(other.color) {}

Queen *Queen::clone() const { return new Queen(*this); }
std::vector<Pos> Queen::getAttackPositions(const Pos &p,
                                           const Board &board) const {
  std::vector<Pos> list;
  addSlidingPositions(list, board.getSquareAt(p), board, false, true);
  addSlidingPositions(list, board.getSquareAt(p), board, true, true);
  return list;
}
std::vector<Pos> Queen::getPseudoLegalPositions(const Pos &p,
                                                const Board &board) const {
  std::vector<Pos> list;
  addSlidingPositions(list, board.getSquareAt(p), board, false, true);
  addSlidingPositions(list, board.getSquareAt(p), board, true, true);
  return list;
}

std::string Queen::getIcon() const { return "♛"; }
std::string Queen::toString() const { return "Q"; }
