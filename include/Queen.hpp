#include "Piece.hpp"
class Queen : public Piece {
private:
  std::vector<Pos> getPseudoLegalPositions(const Pos &,
                                           const Board &) const override;

public:
  Queen *clone() const override;
  Queen(PieceColor);
  Queen(const Queen &);
  std::string getIcon() const override;
  std::string toString() const override;
  std::vector<Pos> getAttackPositions(const Pos &,
                                      const Board &) const override;
};
