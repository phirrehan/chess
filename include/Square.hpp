#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "Piece.hpp"
#include "Position.hpp"
#include <ostream>

// empty labels
const std::string EMPTY = " ";
const std::string CAN_MOVE = "*";
const std::string CAN_CAPTURE = "X";

class Square {
private:
  Piece *piece;
  const Pos pos;
  std::string label;

public:
  Square(Piece *, Pos);
  Square(const Square &);
  Square &operator=(const Square &) = delete;
  bool operator==(const Square &) const;

  Square *clone() const {
    Square *copy = new Square(*this);
    copy->piece = (piece) ? piece->clone() : nullptr;
    return copy;
  }
  Piece &getPiece();
  const Piece &getPiece() const;
  const Piece *getPiecePtr() const;
  Piece *getPiecePtr();
  const Pos getPos() const;
  char getRank() const;
  char getFile() const;
  std::string getLabel() const;
  bool isDark() const;
  bool isEmpty() const;
  bool isLabelEmpty() const;

  void setPiece(Piece *);
  void setLabel(const std::string);
  std::vector<Move> convertPosToMoveList(const std::vector<Pos> &,
                                         const Board &) const;

  friend std::ostream &operator<<(std::ostream &, const Square &);
};

struct Move {
  int id;
  Square from;
  Square to;
  bool capture;

  Move(const Pos &, const Pos &, const Board &, bool);
  Move(const Pos &, const Pos &, const Board &);
  Move(const Move &);
  bool operator==(const Move &) const;
  friend std::ostream &operator<<(std::ostream &, const Move &);
};
#endif
