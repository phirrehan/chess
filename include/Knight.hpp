#include "Piece.hpp"
class Knight : public Piece {
public:
  Knight(PieceColor);
  Knight(const Knight &);
  Knight *clone() const override;
  std::string getIcon() const override;
  std::string toString() const override;
  std::vector<Pos> getAttackPositions(const Pos &,
                                      const Board &) const override;
};
