#include "Position.hpp"

Pos::Pos() {}
Pos::Pos(int r, int c) : row(r), col(c) {}
Pos::Pos(char rank, char file)
    : row(7 - static_cast<int>(rank - '1')), col(static_cast<int>(file - 'a')) {
}
Pos Pos::operator+(const Pos &other) const {
  return Pos(row + other.row, col + other.col);
}
Pos &Pos::operator=(const Pos &other) {
  this->row = other.row;
  this->col = other.col;
  return *this;
}
Pos Pos::operator-(const Pos &other) const {
  return Pos(row - other.row, col - other.col);
}
bool Pos::operator!=(const Pos &other) const {
  return row != other.row && col != other.col;
}
bool Pos::operator==(const Pos &other) const {
  return row == other.row && col == other.col;
}
