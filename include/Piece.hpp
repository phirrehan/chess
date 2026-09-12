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
  bool isNextPosPlausible(std::vector<Pos> &, const Square &, const Board &,
                          bool) const;
  void addCardinalPos(std::vector<Pos> &, const Square &, const Board &,
                      bool) const;
  void addDiagPos(std::vector<Pos> &, const Square &, const Board &,
                  bool) const;
  virtual std::vector<Pos> getPseudoLegalPositions(const Pos &,
                                                   const Board &) const;

public:
  virtual Piece *clone() const = 0;
  virtual std::string getIcon() const = 0;
  virtual std::string toString() const = 0;
  virtual std::vector<Pos> getAttackPositions(const Pos &,
                                              const Board &) const = 0;
  void makeMove(const Move &, Board &);
  virtual void move(const Move &, Board &);

  Piece(PieceColor);
  Piece(PieceColor, Pin);
  PieceColor getColor() const;
  PieceColor getEnemyColor() const;
  Pin getPin() const;

  bool isMoveLegal(const Move &, const Board &) const;
  bool hasMoveAvailable(const Square &, const Board &) const;
  bool isThreateningKing(const Square &, const Square &, const Board &) const;
  bool isWhite() const;

  void setPin(Pin);

  std::vector<Move> getLegalMoves(const Square &, const Board &) const;
  virtual ~Piece() = default;
};
#endif
