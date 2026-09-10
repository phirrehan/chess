#ifndef PIECE_HPP
#define PIECE_HPP
#include <string>
#include <vector>

enum class PieceColor { WHITE, BLACK };
enum class Pin { NONE, HORIZONTAL, VERTICAL, DIAGONAL_MAIN, DIAGONAL_ANTI };

struct Pos;
struct Move;
class Square;
class Board;
class Piece {

protected:
  const PieceColor color;
  Pin pin;

  // the following functions are used as helper function for
  // getPlausiblePosList() across various classes
  bool isNextSquarePlausible(std::vector<Pos> &, const Square &,
                             const Board &) const;
  void addCardinalPos(std::vector<Pos> &, const Square &, const Board &) const;
  void addDiagonalPos(std::vector<Pos> &, const Square &, const Board &) const;

  virtual std::vector<Pos> getPlausiblePosList(const Square &,
                                               const Board &) const = 0;

public:
  virtual Piece *clone() const = 0;
  virtual std::string getIcon() const = 0;
  virtual void move(const Move &, Board &) = 0;

  Piece(PieceColor);
  Piece(PieceColor, Pin);
  bool isMoveValid(const Move &, const Board &) const;
  bool hasMoveAvailable(const Square &, const Board &) const;
  bool isThreateningKing(const Square &, const Square &, const Board &) const;
  PieceColor getColor() const;
  PieceColor getEnemyColor() const;
  Pin getPin() const;

  bool isWhite() const;
  void setPin(Pin);

  std::vector<Move> getValidMovesList(const Square &, const Board &) const;
  void genericMove(const Move &, Board &);
  virtual ~Piece() = default;
};
#endif
