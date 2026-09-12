#include "Piece.hpp"
class Rook : public Piece {
private:
  bool firstMove;
  std::vector<Pos> getPseudoLegalPositions(const Pos &,
                                           const Board &) const override;

public:
  Rook *clone() const override;
  Rook(PieceColor);
  Rook(const Rook &);
  std::string getIcon() const override;
  std::string toString() const override;
  bool isFirstMove() const;

  void move(const Move &, Board &) override;
  std::vector<Pos> getAttackPositions(const Pos &,
                                      const Board &) const override;
};
