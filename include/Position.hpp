#ifndef POSITION_HPP
#define POSITION_HPP
#include <ostream>

struct Pos {
  int row;
  int col;

  Pos();
  Pos(int, int);
  Pos(char, char);
  Pos &operator=(const Pos &);
  Pos operator+(const Pos &) const;
  Pos operator-(const Pos &) const;
  bool operator!=(const Pos &) const;
  bool operator==(const Pos &) const;
  friend std::ostream &operator<<(std::ostream &, const Pos &);
};

const Pos CARD_DIRS[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const Pos DIAG_DIRS[4] = {{-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
#endif
