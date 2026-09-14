#ifndef BOARD_HPP
#define BOARD_HPP
#include "Piece.hpp"
#include "Position.hpp"

enum class Status { IN_PROGRESS, WHITE_WON, BLACK_WON, STALEMATE };

class Board {
private:
  Square *arr[64];
  Pos whiteKingPos;
  Pos blackKingPos;
  Pos selectedPos;
  int moveCount;
  bool whiteToMove;
  bool selected;
  Status status;

  // helper function
  bool hasPinUpdated(Pos, Square &, Pin);

public:
  Board();
  Board(const Board &);
  Square &getSquareAt(Pos);
  const Square &getSquareAt(Pos) const;
  const Board &getBoard();
  Pos getKingPos(PieceColor) const;
  Pos getSelectedPos() const;
  int getMoveCount() const;
  Status getStatus() const;

  bool isSelected() const;
  bool isWhiteToMove() const;
  bool isAlignedWithKing(const Square &, PieceColor, Pin) const;
  bool isMoveAvailable() const;
  static bool isPosOutOfBounds(Pos);
  bool isCapturable(PieceColor, const Square &) const;
  bool canCastle(const Move &) const;
  bool isCheckMate(PieceColor) const;
  bool isStaleMate() const;
  bool canMoveRemoveCheck(const Move &) const;
  bool hasObstructions(const Pos &, const Pos &, Pin) const;

  void setKingPos(PieceColor, Pos);
  void toggleWhiteToMove();
  void incrementMoveCount();
  void setSelected(bool);
  void setSelectedPos(Pos);
  void setStatus(Status);

  static void popOutOfBoundsElements(std::vector<Pos> &);
  static int distance(const Move &);
  void markAvailableMoves(const Square &);
  void selectPos(Pos);
  void unselect();
  void updateStatus();
  void updatePin();
  void updateBoard();
  void move(const Move &);

  ~Board();
};
#endif
