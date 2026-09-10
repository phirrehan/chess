#include "Piece.hpp"
#include <ostream>
#include <vector>
class Queen : public Piece {
private:
  std::vector<Pos> getPlausiblePosList(const Square &,
                                       const Board &) const override;

public:
  Queen *clone() const override;
  Queen(PieceColor);
  Queen(const Queen &);
  std::string getIcon() const override;

  void move(const Move &, Board &) override;

  // overload << operator
  friend std::ostream &operator<<(std::ostream &, const Queen &);
};
