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

std::vector<Pos> King::getPlausiblePosList(const Square &sq,
                                           const Board &board) const {
  Pos p = sq.getPos();
  std::vector<Pos> list = {{{p.row, p.col + 1},
                            {p.row, p.col - 1},
                            {p.row + 1, p.col + 1},
                            {p.row + 1, p.col},
                            {p.row + 1, p.col - 1},
                            {p.row - 1, p.col + 1},
                            {p.row - 1, p.col},
                            {p.row - 1, p.col + 1}}};
  Board::popOutOfBoundsElements(list);

  // castle moves
  if (firstMove && !check) {
    Pos castleShortPos({p.row, p.col + 2});
    Pos castleLongPos({p.row, p.col - 2});
    Move castleShort(sq.getPos(), castleShortPos, board);
    Move castleLong(sq.getPos(), castleLongPos, board);
    if (board.canCastle(castleShort))
      list.push_back(castleShortPos);
    if (board.canCastle(castleLong))
      list.push_back(castleLongPos);
  }

  // filter out squares that are capturable
  for (int i = 0; i < list.size(); i++) {
    Square curSq(board.getSquareAt(list[i]));
    if (board.isCapturable(sq.getPiece().getColor(), curSq)) {
      std::swap(list[i--], list[list.size() - 1]);
      list.pop_back();
    }
  }

  return list;
}

bool King::isCheck() const { return check; }

void King::updateCheckStatus(const Square &kingSq, const Board &board) {
  bool updatedCheck = false;
  for (int i = 0; i < 4; i++) {
    const Square &curSq(board.getSquareAt({i / 8, i % 8}));
    if (curSq.isEmpty() ||
        kingSq.getPiece().getColor() == curSq.getPiece().getColor())
      continue;
    else if (curSq.getPiece().isThreateningKing(curSq, kingSq, board)) {
      updatedCheck = true;
      break;
    }
  }
  check = updatedCheck;
}

void King::move(const Move &move, Board &board) {
  genericMove(move, board);
  firstMove = false;
  board.setKingPos(color, move.to.getPos());
}

std::string King::getIcon() const { return "♚"; }

// overload << operator
std::ostream &operator<<(std::ostream &os, const King &k) {
  os << "K";
  return os;
}
