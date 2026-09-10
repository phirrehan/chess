#include "Piece.hpp"
#include "Board.hpp"
#include "Exception.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include "Square.hpp"
#include <vector>

Piece::Piece(PieceColor c) : color(c), pin(Pin::NONE) {}
Piece::Piece(PieceColor c, Pin p) : color(c), pin(p) {}
PieceColor Piece::getColor() const { return color; }
PieceColor Piece::getEnemyColor() const {
  return (isWhite()) ? PieceColor::BLACK : PieceColor::WHITE;
}
Pin Piece::getPin() const { return pin; }
bool Piece::isWhite() const { return color == PieceColor::WHITE; }

// helper functions

bool Piece::isNextSquarePlausible(std::vector<Pos> &list, const Square &sq,
                                  const Board &board) const {
  if (sq.isEmpty()) {
    list.push_back(sq.getPos());
    return true;
  } else if (sq.getPiece().getColor() != color) {
    list.push_back(sq.getPos());
    return false;
  } else
    return false;
}
void Piece::addCardinalPos(std::vector<Pos> &list, const Square &sq,
                           const Board &board) const {
  Pos p = sq.getPos();
  int r, c;
  // traverse upwards
  for (r = p.row - 1; r >= 0; r--) {
    Square curSq(board.getSquareAt({r, p.col}));
    if (!sq.getPiece().isNextSquarePlausible(list, curSq, board))
      break;
  }
  // traverse downwards
  for (r = p.row + 1; r < 8; r++) {
    Square curSq(board.getSquareAt({r, p.col}));
    if (!sq.getPiece().isNextSquarePlausible(list, curSq, board))
      break;
  }
  // traverse leftwards
  for (c = p.col - 1; c >= 0; c--) {
    Square curSq(board.getSquareAt({p.row, c}));
    if (!sq.getPiece().isNextSquarePlausible(list, curSq, board))
      break;
  }
  // traverse rightwards
  for (c = p.col + 1; c < 8; c++) {
    Square curSq(board.getSquareAt({p.row, c}));
    if (!sq.getPiece().isNextSquarePlausible(list, curSq, board))
      break;
  }
}
void Piece::addDiagonalPos(std::vector<Pos> &list, const Square &sq,
                           const Board &board) const {
  Pos p = sq.getPos();
  int r, c;
  // traverse top-left along main diagonal
  for (r = p.row - 1, c = p.col - 1; r >= 0 && c >= 0; r--, c--) {
    Square curSq(board.getSquareAt({r, c}));
    if (!isNextSquarePlausible(list, curSq, board))
      break;
  }
  // traverse top-left along main diagonal
  for (r = p.row + 1, c = p.col + 1; r < 8 && c < 8; r++, c++) {
    Square curSq(board.getSquareAt({r, c}));
    if (!isNextSquarePlausible(list, curSq, board))
      break;
  }
  // traverse top-right along anti diagonal
  for (r = p.row - 1, c = p.col + 1; r >= 0 && c < 8; r--, c++) {
    Square curSq(board.getSquareAt({r, c}));
    if (!isNextSquarePlausible(list, curSq, board))
      break;
  }
  // traverse top-left along anti diagonal
  for (r = p.row + 1, c = p.col - 1; r < 8 && c >= 0; r++, c--) {
    Square curSq(board.getSquareAt({r, c}));
    if (!isNextSquarePlausible(list, curSq, board))
      break;
  }
}

std::vector<Move> Piece::getValidMovesList(const Square &sq,
                                           const Board &board) const {
  std::vector<Pos> moves = sq.getPiece().getPlausiblePosList(sq, board);
  for (int i = 0; i < moves.size(); i++) {
  }
  Square kingSq(board.getSquareAt(board.getKingPos(sq.getPiece().getColor())));
  auto king = dynamic_cast<const King *>(kingSq.getPiecePtr());

  for (int i = 0; i < moves.size(); i++) {
    Square curSq(board.getSquareAt(moves[i]));
    bool valid =
        (curSq.isEmpty() || color != curSq.getPiece().getColor()) &&
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

bool Piece::isMoveValid(const Move &move, const Board &board) const {
  std::vector<Move> list =
      move.from.getPiecePtr()->getValidMovesList(move.from, board);
  for (int i = 0; i < list.size(); i++) {
    if (move == list[i])
      return true;
  }
  return false;
}

bool Piece::hasMoveAvailable(const Square &curSq, const Board &board) const {
  std::vector<Move> list = curSq.getPiece().getValidMovesList(curSq, board);
  return (list.size() != 0);
}

void Piece::genericMove(const Move &move, Board &board) {
  Square &moveFromSq(board.getSquareAt(move.from.getPos()));
  Square &moveToSq(board.getSquareAt(move.to.getPos()));
  if (!isMoveValid(move, board))
    throw InvalidMove("move is invalid. try again");
  // check if move is capturing
  if (auto ptr = move.to.getPiecePtr())
    delete ptr;
  moveToSq.setPiece(moveFromSq.getPiecePtr());
  moveFromSq.setPiece(nullptr);

  // update board
  // update board variables
  if (!board.isWhiteToMove())
    board.incrementMoveCount();

  // update king position if the king moved
  if (dynamic_cast<King *>(moveToSq.getPiecePtr())) {
    board.setKingPos(color, move.to.getPos());
  }

  // update game status
  board.updateStatus();
  board.toggleWhiteToMove();

  // update loop
  for (int i = 0; i < 64; i++) {
    Square curSq(board.getSquareAt({i / 8, i % 8}));
    // update pin
    if (!curSq.isEmpty())
      board.updatePin();
    // update pawn's enPassant variable
    if (auto pawn = dynamic_cast<Pawn *>(curSq.getPiecePtr())) {
      if (pawn->isEnPassant() && curSq.getPos() != move.to.getPos())
        pawn->setEnPassant(false);
    }
  }
}

bool Piece::isThreateningKing(const Square &curSq, const Square &kingSq,
                              const Board &board) const {
  if (color == kingSq.getPiece().getColor())
    return false;
  else if (auto king = dynamic_cast<const King *>(curSq.getPiecePtr()))
    return false;

  std::vector<Move> list = getValidMovesList(curSq, board);
  for (int i = 0; i < list.size(); i++) {
    if (list[i].to == kingSq)
      return true;
  }
  return false;
}

void Piece::setPin(Pin p) { pin = p; }
