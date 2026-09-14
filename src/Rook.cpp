#include "Rook.hpp"
#include "Board.hpp"

Rook::Rook(PieceColor c) : Piece(c), firstMove(true) {}
Rook::Rook(const Rook &other)
    : Piece(other.color, other.pin), firstMove(other.firstMove) {}
Rook *Rook::clone() const { return new Rook(*this); }

std::vector<Pos> Rook::getAttackPositions(const Pos &p,
                                          const Board &board) const {
  std::vector<Pos> list;
  addSlidingPositions(list, board.getSquareAt(p), board, false, true);
  return list;
}
std::vector<Pos> Rook::getPseudoLegalPositions(const Pos &p,
                                               const Board &board) const {
  std::vector<Pos> list;
  addSlidingPositions(list, board.getSquareAt(p), board, false, false);
  return list;
}

bool Rook::isFirstMove() const { return firstMove; }
void Rook::move(const Move &move, Board &board) {
  Piece::move(move, board);
  firstMove = false;
}

std::string Rook::getIcon() const { return "♜"; }
std::string Rook::toString() const { return "R"; }
