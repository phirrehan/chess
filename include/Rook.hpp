#include "Piece.hpp"
#include <ostream>
#include <vector>
class Rook : public Piece {
private:
  bool firstMove;
  std::vector<Pos> getPlausiblePosList(const Square &,
                                       const Board &) const override;

public:
  Rook *clone() const override;
  Rook(PieceColor);
  Rook(const Rook &);
  std::string getIcon() const override;
  bool isFirstMove() const;

  void move(const Move &, Board &) override;

  // overload << operator
  friend std::ostream &operator<<(std::ostream &, const Rook &);
};
