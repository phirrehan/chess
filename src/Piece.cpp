#include "Piece.hpp"
#include "Board.hpp"
#include "Exception.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include "Square.hpp"
#include <iostream>
#include <ostream>

Piece::Piece(PieceColor c) : color(c), pin(Pin::NONE) {}
Piece::Piece(PieceColor c, Pin p) : color(c), pin(p) {}
PieceColor Piece::getColor() const { return color; }
PieceColor Piece::getEnemyColor() const {
  return (isWhite()) ? PieceColor::BLACK : PieceColor::WHITE;
}
Pin Piece::getPin() const { return pin; }
bool Piece::isWhite() const { return color == PieceColor::WHITE; }

// helper functions
bool Piece::isNextPosPlausible(std::vector<Pos> &list, const Square &sq,
                               const Board &board, bool isAttack) const {
  if (sq.isEmpty()) {
    list.push_back(sq.getPos());
    return true;
  } else if (sq.getPiece().getColor() == color) {
    return false;
  } else {
    list.push_back(sq.getPos());
    if (isAttack && dynamic_cast<const King *>(sq.getPiecePtr())) {
      return true;
    } else {
      return false;
    }
  }
}
void Piece::addSlidingPositions(std::vector<Pos> &list, const Square &sq,
                                const Board &board, bool isDiag,
                                bool isAttack) const {
  const Pos p = sq.getPos();
  const Pos *directions = isDiag ? DIAG_DIRS : CARD_DIRS;

  for (int i = 0; i < 4; i++) {
    const Pos dir = directions[i];
    int r = p.row + dir.row;
    int c = p.col + dir.col;

    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
      const Square &curSq = board.getSquareAt({r, c});
      if (!isNextPosPlausible(list, curSq, board, isAttack))
        break;
      r += dir.row;
      c += dir.col;
    }
  }
}

std::vector<Pos> Piece::getPseudoLegalPositions(const Pos &p,
                                                const Board &board) const {
  std::vector<Pos> list = getAttackPositions(p, board);
  for (int i = 0; i < list.size(); i++) {
    const Square &curSq(board.getSquareAt(list[i]));
    if (!curSq.isEmpty() && color == curSq.getPiece().getColor()) {
      std::swap(list[i--], list[list.size() - 1]);
      list.pop_back();
    }
  }
  return list;
}

std::vector<Move> Piece::getLegalMoves(const Square &sq,
                                       const Board &board) const {
  std::vector<Pos> moves =
      sq.getPiece().getPseudoLegalPositions(sq.getPos(), board);
  const Square &kingSq(
      board.getSquareAt(board.getKingPos(sq.getPiece().getColor())));
  auto king = dynamic_cast<const King *>(kingSq.getPiecePtr());

  for (int i = 0; i < moves.size(); i++) {
    const Square &curSq(board.getSquareAt(moves[i]));
    bool valid =
        (sq.getPiece().getPin() == Pin::NONE ||
         board.isAlignedWithKing(curSq, color, sq.getPiece().getPin())) &&
        (!king->isCheck() ||
         board.canMoveRemoveCheck(Move(sq.getPos(), moves[i], board)));
    if (!valid) {
      std::swap(moves[i--], moves[moves.size() - 1]);
      moves.pop_back();
    }
  }

  return sq.convertPosToMoveList(moves, board);
}

bool Piece::isMoveLegal(const Move &move, const Board &board) const {
  std::vector<Move> list =
      move.from.getPiecePtr()->getLegalMoves(move.from, board);
  for (int i = 0; i < list.size(); i++) {
    if (move == list[i])
      return true;
  }
  return false;
}

bool Piece::hasMoveAvailable(const Square &curSq, const Board &board) const {
  std::vector<Move> list = curSq.getPiece().getLegalMoves(curSq, board);
  return (list.size() != 0);
}

void Piece::makeMove(const Move &move, Board &board) {
  Square &moveFromSq(board.getSquareAt(move.from.getPos()));
  Square &moveToSq(board.getSquareAt(move.to.getPos()));

  if (Piece *ptr = moveToSq.getPiecePtr())
    delete ptr;
  moveToSq.setPiece(moveFromSq.getPiecePtr());
  moveFromSq.setPiece(nullptr);

  // update king position if the king moved
  if (dynamic_cast<King *>(moveToSq.getPiecePtr())) {
    board.setKingPos(color, move.to.getPos());
  }
}

void Piece::move(const Move &move, Board &board) {
  if (!isMoveLegal(move, board))
    throw InvalidMove("move is invalid. try again");

  makeMove(move, board);
  // do not update if the pawn is promoting. the update should happen after
  // promotion in this case
  int promotionRow = (isWhite()) ? 0 : 7;
  const Square &pawnSq(board.getSquareAt(move.to.getPos()));
  if (dynamic_cast<const Pawn *>(pawnSq.getPiecePtr()) == nullptr ||
      pawnSq.getPos().row != promotionRow) {
    board.updateBoard();
  }
}

bool Piece::isThreateningKing(const Square &curSq, const Square &kingSq,
                              const Board &board) const {
  if (auto king = dynamic_cast<const King *>(curSq.getPiecePtr()))
    return false;
  std::vector<Pos> list =
      curSq.getPiece().getAttackPositions(curSq.getPos(), board);
  for (auto attackPos : list) {
    if (attackPos == kingSq.getPos())
      return true;
  }
  return false;
}

void Piece::setPin(Pin p) { pin = p; }

std::ostream &operator<<(std::ostream &os, const Piece &piece) {
  os << piece.toString();
  return os;
}
