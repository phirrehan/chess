#include "Piece.hpp"
class Bishop : public Piece {
private:
  std::vector<Pos> getPseudoLegalPositions(const Pos &,
                                           const Board &) const override;

public:
  Bishop *clone() const override;
  Bishop(PieceColor);
  Bishop(const Bishop &);
  std::string getIcon() const override;
  std::string toString() const override;
  std::vector<Pos> getAttackPositions(const Pos &,
                                      const Board &) const override;
};
