#include "Piece.hpp"
#include <ostream>
#include <vector>
class Pawn : public Piece {
private:
  bool firstMove;
  bool enPassant;
  std::vector<Pos> getPlausiblePosList(const Square &,
                                       const Board &) const override;

public:
  Pawn *clone() const override;
  Pawn(PieceColor);
  Pawn(const Pawn &);
  std::string getIcon() const override;
  bool isFirstMove() const;
  bool isEnPassant() const;

  void move(const Move &, Board &) override;
  void setEnPassant(bool);

  // overload << operator
  friend std::ostream &operator<<(std::ostream &, const Pawn &);
};
