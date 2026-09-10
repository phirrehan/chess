#include "Piece.hpp"
#include <ostream>
#include <vector>
class Bishop : public Piece {
private:
  std::vector<Pos> getPlausiblePosList(const Square &,
                                       const Board &) const override;

public:
  Bishop *clone() const override;
  Bishop(PieceColor);
  Bishop(const Bishop &);
  std::string getIcon() const override;

  void move(const Move &, Board &) override;

  // overload << operator
  friend std::ostream &operator<<(std::ostream &, const Bishop &);
};
