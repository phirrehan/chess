#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Board.hpp"
#include "Knight.hpp"
#include "Piece.hpp"
#include "Position.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Square.hpp"
#include <iostream>
#include <vector>

Pawn::Pawn(PieceColor c) : Piece(c), firstMove(true) {}
Pawn::Pawn(const Pawn &other)
    : Piece(other.color, other.pin), firstMove(other.firstMove),
      enPassant(false) {}
Pawn *Pawn::clone() const { return new Pawn(*this); }

std::vector<Pos> Pawn::getAttackPositions(const Pos &p,
                                          const Board &board) const {
  int rowDir = (isWhite()) ? -1 : 1;
  int enPassantRow = (isWhite()) ? 3 : 4;

  std::vector<Pos> list;
  // add capture positions
  // note that left and right are relative to white
  Pos leftDiagPos(p + Pos(1 * rowDir, -1));
  Pos rightDiagPos(p + Pos(1 * rowDir, 1));

  if (!Board::isPosOutOfBounds(leftDiagPos)) {
    list.push_back(leftDiagPos);
  }
  if (!Board::isPosOutOfBounds(rightDiagPos)) {
    list.push_back(rightDiagPos);
  }

  // add enpassant capture positions
  if (p.row == enPassantRow) {
    const Square &leftSq(board.getSquareAt(p + Pos(0, -1)));
    const Square &rightSq(board.getSquareAt(p + Pos(0, 1)));
    if (auto pawn = dynamic_cast<const Pawn *>(leftSq.getPiecePtr())) {
      if (pawn->getColor() != color && pawn->isEnPassant())
        list.push_back(leftSq.getPos() + Pos(1 * rowDir, 0));
    } else if (auto pawn = dynamic_cast<const Pawn *>(rightSq.getPiecePtr())) {
      if (pawn->getColor() != color && pawn->isEnPassant())
        list.push_back(rightSq.getPos() + Pos(1 * rowDir, 0));
    }
  }
  return list;
}
std::vector<Pos> Pawn::getPseudoLegalPositions(const Pos &p,
                                               const Board &board) const {
  int rowDir = (isWhite()) ? -1 : +1;
  std::vector<Pos> list = getAttackPositions(p, board);
  for (int i = 0; i < list.size(); i++) {
    const Square &attackSq(board.getSquareAt(list[i]));
    if (attackSq.isEmpty() || attackSq.getPiece().getColor() == color) {
      std::swap(list[i--], list[list.size() - 1]);
      list.pop_back();
    }
  }

  // add standard 1 square ahead move
  if (board.getSquareAt(p + Pos(1 * rowDir, 0)).isEmpty())
    list.push_back(p + Pos(1 * rowDir, 0));
  // add initial 2 squares ahead move
  if (firstMove && board.getSquareAt(p + Pos(2 * rowDir, 0)).isEmpty())
    list.push_back(p + Pos(2 * rowDir, 0));

  return list;
}

bool Pawn::isFirstMove() const { return firstMove; }
bool Pawn::isEnPassant() const { return enPassant; }

void Pawn::move(const Move &move, Board &board) {
  int promotionRow = (this->isWhite()) ? 0 : 7;
  int rowDir = (this->isWhite()) ? -1 : 1;

  Piece::move(move, board);
  if (firstMove && Board::distance(move) == 2) {
    enPassant = true;
    firstMove = false;
  } else if (firstMove)
    firstMove = false;

  // handle enpassant capture
  if (move.to.isEmpty() && move.capture) {
    Square &captureSq(
        board.getSquareAt(move.to.getPos() + Pos(-1 * rowDir, 0)));
    delete captureSq.getPiecePtr();
    captureSq.setPiece(nullptr);
  }

  // handle promotion
  if (move.to.getPos().row == promotionRow) {
    //  get input from user to select a piece to promote to
    PieceColor color = move.to.getPiece().getColor();
    delete move.to.getPiecePtr();
    board.getSquareAt(move.to.getPos()).setPiece(new Queen(color));
  }
}

void Pawn::setEnPassant(bool enPas) { enPassant = enPas; }

std::string Pawn::getIcon() const { return "♟"; }
std::string Pawn::toString() const { return "P"; }

// overload << operator
std::ostream &operator<<(std::ostream &os, const Pawn &k) {
  os << "";
  return os;
}
