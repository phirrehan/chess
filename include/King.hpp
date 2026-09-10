#include "Piece.hpp"
#include <ostream>
struct Move;
class King : public Piece {
private:
  bool firstMove;
  bool check;
  std::vector<Pos> getPlausiblePosList(const Square &,
                                       const Board &) const override;

public:
  King(PieceColor);
  King(const King &);
  King *clone() const override;

  void updateCheckStatus(const Square &, const Board &);
  void move(const Move &, Board &) override;

  bool isCheck() const;
  std::string getIcon() const override;
  std::string isFirstMove() const;

  std::string setFirstMove(bool);

  // overload << operator
  friend std::ostream &operator<<(std::ostream &, const King &);
};
