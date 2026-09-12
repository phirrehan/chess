#include "King.hpp"
#include "Board.hpp"
#include "Exception.hpp"
#include "Piece.hpp"
#include "Position.hpp"
#include "Square.hpp"
#include <iostream>

King::King(PieceColor c) : Piece(c), firstMove(true), check(false) {}
King::King(const King &other)
    : Piece(other.color, other.pin), firstMove(other.firstMove),
      check(other.check) {}
King *King::clone() const { return new King(*this); }

std::vector<Pos> King::getAttackPositions(const Pos &p,
                                          const Board &board) const {
  std::vector<Pos> list = {{{p.row, p.col + 1},
                            {p.row, p.col - 1},
                            {p.row + 1, p.col + 1},
                            {p.row + 1, p.col},
                            {p.row + 1, p.col - 1},
                            {p.row - 1, p.col + 1},
                            {p.row - 1, p.col},
                            {p.row - 1, p.col - 1}}};
  Board::popOutOfBoundsElements(list);
  return list;
}

std::vector<Pos> King::getPseudoLegalPositions(const Pos &p,
                                               const Board &board) const {
  std::vector<Pos> list = getAttackPositions(p, board);
  // castle moves
  if (firstMove && !check) {
    Pos castleShortPos({p.row, p.col + 2});
    Pos castleLongPos({p.row, p.col - 2});
    Move castleShort(p, castleShortPos, board);
    Move castleLong(p, castleLongPos, board);
    if (board.canCastle(castleShort))
      list.push_back(castleShortPos);
    if (board.canCastle(castleLong))
      list.push_back(castleLongPos);
  }

  for (int i = 0; i < list.size(); i++) {
    const Square &curSq(board.getSquareAt(list[i]));
    if ((!curSq.isEmpty() && curSq.getPiece().getColor() == color) ||
        (board.isCapturable(getEnemyColor(), curSq))) {
      std::swap(list[i--], list[list.size() - 1]);
      list.pop_back();
    }
    // filter out squares that are capturable
  }
  return list;
}

bool King::isCheck() const { return check; }

void King::updateCheckStatus(const Square &kingSq, const Board &board) {
  bool updatedCheck = false;
  for (int i = 0; i < 64; i++) {
    const Square &curSq(board.getSquareAt({i / 8, i % 8}));
    if (curSq.isEmpty() || color == curSq.getPiece().getColor())
      continue;
    else if (isThreateningKing(curSq, kingSq, board)) {
      updatedCheck = true;
      break;
    }
  }
  check = updatedCheck;
}

void King::move(const Move &move, Board &board) {
  Piece::move(move, board);
  firstMove = false;
  board.setKingPos(color, move.to.getPos());

  // change rook's position for castles
  if (Board::distance(move) == 2) {
    bool isCastleShort = move.to.getPos().col == 6;
    int rookCastleRow = (isWhite()) ? 7 : 0;
    int rookCastleCol = (isCastleShort) ? 5 : 3;
    int rookRow = rookCastleRow;
    int rookCol = (isCastleShort) ? 7 : 0;
    Square &rookSq(board.getSquareAt({rookRow, rookCol}));
    Square &rookCastleSq(board.getSquareAt({rookCastleRow, rookCastleCol}));
    rookCastleSq.setPiece(rookSq.getPiecePtr());
    rookSq.setPiece(nullptr);
  }
}

std::string King::getIcon() const { return "♚"; }
std::string King::toString() const { return "K"; }
