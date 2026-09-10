#include "Square.hpp"
#include "Board.hpp"
#include "King.hpp"
#include <stdexcept>
#include <vector>

Square::Square(Piece *P, Pos p) : piece(nullptr), pos(p) { setPiece(P); }
Square::Square(const Square &other)
    : piece(other.piece), pos(other.pos), label(other.label) {}
bool Square::operator==(const Square &other) const {
  return (piece == other.piece && pos == other.pos);
}

Piece &Square::getPiece() {
  if (isEmpty())
    throw std::runtime_error("ptr is null. make sure it is non-empty");
  return *piece;
}
const Piece &Square::getPiece() const {
  if (isEmpty())
    throw std::runtime_error("ptr is null. make sure it is non-empty");
  return *piece;
}
const Piece *Square::getPiecePtr() const { return piece; }
Piece *Square::getPiecePtr() { return piece; }
const Pos Square::getPos() const { return pos; }
char Square::getRank() const { return static_cast<char>(7 - pos.row + '1'); }
char Square::getFile() const { return static_cast<char>(pos.col + 'a'); }
bool Square::isDark() const { return (pos.row + pos.col) % 2; }
bool Square::isEmpty() const { return piece == nullptr; }
bool Square::isLabelEmpty() const { return label == EMPTY; }
std::string Square::getLabel() const { return label; }
// Piece *p must be obtained using new operator
void Square::setPiece(Piece *ptr) {
  if (ptr)
    label = ptr->getIcon();
  else
    setLabel(EMPTY);
  piece = ptr;
}

void Square::setLabel(const std::string str) { label = str; }

std::vector<Move> Square::convertPosToMoveList(const std::vector<Pos> &posList,
                                               const Board &board) const {

  std::vector<Move> moveList;
  for (int i = 0; i < posList.size(); i++) {
    Move move(pos, posList[i], board);
    moveList.push_back(move);
  }

  return moveList;
}

std::ostream &operator<<(std::ostream &os, const Square &p) {
  os << p.getFile() << p.getRank();
  return os;
}

Move::Move(const Pos &fromPos, const Pos &toPos, const Board &board)
    : id(board.getMoveCount()), from(board.getSquareAt(fromPos)),
      to(board.getSquareAt(toPos)) {

  if (to.isEmpty())
    capture = false;
  else {
    PieceColor toColor = to.getPiece().getColor();
    PieceColor fromColor = from.getPiece().getColor();
    capture = fromColor != toColor;
  }
}
Move::Move(const Move &other)
    : id(other.id), from(other.from), to(other.to), capture(other.capture) {}

bool Move::operator==(const Move &other) const {
  return (id == other.id && from == other.from && to == other.to &&
          capture == other.capture);
}
std::ostream &operator<<(std::ostream &os, const Move &move) {
  os << move.from << " " << move.to;
  return os;
}
