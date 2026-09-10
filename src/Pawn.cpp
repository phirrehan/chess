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

std::vector<Pos> Pawn::getPlausiblePosList(const Square &sq,
                                           const Board &board) const {
  int moveDir = (this->isWhite()) ? -1 : +1;
  int enPassantRow = (this->isWhite()) ? 4 : 3;

  // add 1 square ahead
  std::vector<Pos> list = {sq.getPos() + Pos(1 * moveDir, 0)};
  // add first move 2 squares ahead
  if (firstMove &&
      board.getSquareAt(sq.getPos() + Pos(2 * moveDir, 0)).isEmpty())
    list.push_back(sq.getPos() + Pos(2 * moveDir, 0));

  // add capture positions
  // note that left and right are relative to white
  Pos leftDiagPos(sq.getPos() + Pos(1 * moveDir, -1));
  Pos rightDiagPos(sq.getPos() + Pos(1 * moveDir, 1));

  if (!Board::isPosOutOfBounds(leftDiagPos)) {
    Square leftDiagSq(board.getSquareAt(leftDiagPos));
    if (!leftDiagSq.isEmpty() && leftDiagSq.getPiece().getColor() != color)
      list.push_back(leftDiagSq.getPos());
  }
  if (!Board::isPosOutOfBounds(rightDiagPos)) {
    Square rightDiagSq(board.getSquareAt(rightDiagPos));
    if (!rightDiagSq.isEmpty() && rightDiagSq.getPiece().getColor() != color)
      list.push_back(rightDiagSq.getPos());
  }

  // add enpassant capture positions
  if (sq.getPos().row == enPassantRow) {
    Square leftSq = board.getSquareAt(sq.getPos() + Pos(0, -1));
    Square rightSq = board.getSquareAt(sq.getPos() + Pos(0, 1));
    if (auto pawn = dynamic_cast<const Pawn *>(leftSq.getPiecePtr())) {
      if (pawn->isEnPassant())
        list.push_back(leftSq.getPos());
    } else if (auto pawn = dynamic_cast<const Pawn *>(rightSq.getPiecePtr())) {
      if (pawn->isEnPassant())
        list.push_back(rightSq.getPos());
    }
  }
  return list;
}

bool Pawn::isFirstMove() const { return firstMove; }
bool Pawn::isEnPassant() const { return enPassant; }

void Pawn::move(const Move &move, Board &board) {
  int promotionRow = (this->isWhite()) ? 0 : 7;
  int enPassantRow = (this->isWhite()) ? 4 : 3;
  genericMove(move, board);
  // if move is invalid, an exception is thrown
  // meaning the rest of the code below this will not get executed

  // handle enpassant capture
  int moveDir = (this->isWhite()) ? -1 : 1;

  Pos leftSqPos(move.from.getPos() + Pos(0, -1));
  Pos rightSqPos(move.from.getPos() + Pos(0, +1));

  if (move.from.getPos().row == enPassantRow) {
    if (!Board::isPosOutOfBounds(leftSqPos)) {
      Square &leftSq(board.getSquareAt(leftSqPos));
      if (auto pawn = dynamic_cast<const Pawn *>(leftSq.getPiecePtr())) {
        if (pawn->isEnPassant() &&
            (leftSqPos + Pos(1 * moveDir, 0)) == move.to.getPos()) {
          delete leftSq.getPiecePtr();
          leftSq.setPiece(nullptr);
        }
      }
    } else if (!Board::isPosOutOfBounds(rightSqPos)) {
      Square &rightSq(board.getSquareAt(rightSqPos));
      if (auto pawn = dynamic_cast<const Pawn *>(rightSq.getPiecePtr())) {
        if (pawn->isEnPassant() &&
            (rightSqPos + Pos(1 * moveDir, 0)) == move.to.getPos()) {
          delete rightSq.getPiecePtr();
          rightSq.setPiece(nullptr);
        }
      }
    }
  }

  // handle promotion
  if (move.to.getPos().row == promotionRow) {
    //  get input from user to select a piece to promote to
    PieceColor color = move.to.getPiece().getColor();
    delete move.to.getPiecePtr();
    board.getSquareAt(move.to.getPos()).setPiece(new Queen(color));
  }

  // post move actions
  if (firstMove) {
    firstMove = false;
    enPassant = true;
  } else
    enPassant = false;
}

void Pawn::setEnPassant(bool enPas) { enPassant = enPas; }

std::string Pawn::getIcon() const { return "♟"; }

// overload << operator
std::ostream &operator<<(std::ostream &os, const Pawn &k) {
  os << "";
  return os;
}
