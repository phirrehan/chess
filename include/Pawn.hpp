#include "Piece.hpp"
class Pawn : public Piece {
private:
  bool firstMove;
  bool enPassant;
  std::vector<Pos> getPseudoLegalPositions(const Pos &,
                                           const Board &) const override;

public:
  Pawn *clone() const override;
  Pawn(PieceColor);
  Pawn(const Pawn &);
  std::string getIcon() const override;
  std::string toString() const override;
  bool isFirstMove() const;
  bool isEnPassant() const;

  void move(const Move &, Board &) override;
  void setEnPassant(bool);

  std::vector<Pos> getAttackPositions(const Pos &,
                                      const Board &) const override;
};
