#include "Pawn.hpp"
#include "Board.hpp"
#include "Input.hpp"
#include "Piece.hpp"
#include "Square.hpp"

Pawn::Pawn(PieceColor c) : Piece(c), firstMove(true) {}
Pawn::Pawn(const Pawn &other)
    : Piece(other.color, other.pin), firstMove(other.firstMove),
      enPassant(false) {}
Pawn *Pawn::clone() const { return new Pawn(*this); }

std::vector<Pos> Pawn::getAttackPositions(const Pos &p,
                                          const Board &board) const {
  int rowDir = (isWhite()) ? -1 : 1;

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

  return list;
}
std::vector<Pos> Pawn::getPseudoLegalPositions(const Pos &p,
                                               const Board &board) const {
  int rowDir = (isWhite()) ? -1 : +1;
  int enPassantRow = (isWhite()) ? 3 : 4;
  std::vector<Pos> list = getAttackPositions(p, board);
  for (int i = 0; i < list.size(); i++) {
    const Square &attackSq(board.getSquareAt(list[i]));
    if (attackSq.isEmpty() || attackSq.getPiece().getColor() == color) {
      std::swap(list[i--], list[list.size() - 1]);
      list.pop_back();
    }
  }

  // add enpassant capture positions
  if (p.row == enPassantRow) {
    Pos leftSqPos(p + Pos(0, -1));
    Pos rightSqPos(p + Pos(0, 1));
    if (!Board::isPosOutOfBounds(leftSqPos)) {
      const Square &leftSq(board.getSquareAt(p + Pos(0, -1)));
      if (auto pawn = dynamic_cast<const Pawn *>(leftSq.getPiecePtr())) {
        if (pawn->getColor() != color && pawn->isEnPassant())
          list.push_back(leftSq.getPos() + Pos(1 * rowDir, 0));
      }
    }
    if (!Board::isPosOutOfBounds(rightSqPos)) {
      const Square &rightSq(board.getSquareAt(p + Pos(0, 1)));
      if (auto pawn = dynamic_cast<const Pawn *>(rightSq.getPiecePtr())) {
        if (pawn->getColor() != color && pawn->isEnPassant())
          list.push_back(rightSq.getPos() + Pos(1 * rowDir, 0));
      }
    }
  }

  Pos oneAhead(p + Pos(1 * rowDir, 0));
  Pos twoAhead(p + Pos(2 * rowDir, 0));
  if (!Board::isPosOutOfBounds(oneAhead) &&
      board.getSquareAt(oneAhead).isEmpty())
    list.push_back(oneAhead);
  if (firstMove && !Board::isPosOutOfBounds(twoAhead) &&
      board.getSquareAt(twoAhead).isEmpty())
    list.push_back(twoAhead);

  return list;
}

bool Pawn::isFirstMove() const { return firstMove; }
bool Pawn::isEnPassant() const { return enPassant; }

void Pawn::move(const Move &move, Board &board) {
  int promotionRow = (isWhite()) ? 0 : 7;
  int rowDir = (isWhite()) ? -1 : 1;

  Piece::move(move, board);
  if (firstMove && Board::distance(move) == 2)
    enPassant = true;
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
    Square &pawnSq(board.getSquareAt(move.to.getPos()));
    Piece *pawnPtr = pawnSq.getPiecePtr();
    Piece *newPiece = Input::getPromotionPiece(color);

    delete pawnPtr;
    pawnSq.setPiece(newPiece);

    board.updateBoard();
  }
}

void Pawn::setEnPassant(bool enPas) { enPassant = enPas; }

std::string Pawn::getIcon() const { return "♟"; }
std::string Pawn::toString() const { return ""; }
