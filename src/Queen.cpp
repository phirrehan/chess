#include "Queen.hpp"
#include "Board.hpp"

Queen::Queen(PieceColor c) : Piece(c) {}
Queen::Queen(const Queen &other) : Piece(other.color) {}

Queen *Queen::clone() const { return new Queen(*this); }
std::vector<Pos> Queen::getAttackPositions(const Pos &p,
                                           const Board &board) const {
  std::vector<Pos> list;
  this->addCardinalPos(list, board.getSquareAt(p), board, true);
  this->addDiagPos(list, board.getSquareAt(p), board, true);
  return list;
}
std::vector<Pos> Queen::getPseudoLegalPositions(const Pos &p,
                                                const Board &board) const {
  std::vector<Pos> list;
  this->addCardinalPos(list, board.getSquareAt(p), board, false);
  this->addDiagPos(list, board.getSquareAt(p), board, false);
  return list;
}

std::string Queen::getIcon() const { return "♛"; }
std::string Queen::toString() const { return "Q"; }
