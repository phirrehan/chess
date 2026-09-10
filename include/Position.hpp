#ifndef POSITION_HPP
#define POSITION_HPP

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
};
#endif
