#include "Piece.hpp"
class King : public Piece {
private:
  bool firstMove;
  bool check;
  std::vector<Pos> getPseudoLegalPositions(const Pos &,
                                           const Board &) const override;

public:
  King(PieceColor);
  King(const King &);
  King *clone() const override;

  void updateCheckStatus(const Square &, const Board &);
  void move(const Move &, Board &) override;

  bool isCheck() const;
  std::string getIcon() const override;
  std::string toString() const override;
  std::string isFirstMove() const;

  std::string setFirstMove(bool);

  std::vector<Pos> getAttackPositions(const Pos &,
                                      const Board &) const override;
};
