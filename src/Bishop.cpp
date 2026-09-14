#include "Bishop.hpp"
#include "Board.hpp"

Bishop::Bishop(PieceColor c) : Piece(c) {}
Bishop::Bishop(const Bishop &other) : Piece(other.color) {}

Bishop *Bishop::clone() const { return new Bishop(*this); }
std::vector<Pos> Bishop::getAttackPositions(const Pos &p,
                                            const Board &board) const {
  std::vector<Pos> list;
  addSlidingPositions(list, board.getSquareAt(p), board, true, true);
  return list;
}
std::vector<Pos> Bishop::getPseudoLegalPositions(const Pos &p,
                                                 const Board &board) const {
  std::vector<Pos> list;
  addSlidingPositions(list, board.getSquareAt(p), board, true, false);
  return list;
}
std::string Bishop::getIcon() const { return "♝"; }
std::string Bishop::toString() const { return "B"; }
