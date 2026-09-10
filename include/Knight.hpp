#include "Piece.hpp"
#include <ostream>
class Knight : public Piece {
private:
  virtual std::vector<Pos> getPlausiblePosList(const Square &,
                                               const Board &) const override;

public:
  Knight(PieceColor);
  Knight(const Knight &);
  Knight *clone() const override;
  std::string getIcon() const override;
  void move(const Move &, Board &) override;

  // overload << operator
  friend std::ostream &operator<<(std::ostream &, const Knight &);
};
