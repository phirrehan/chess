#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

class Square;
class Board;
class Graphics {
private:
  static void printSquare(const Square &sq, bool, bool, bool);

public:
  static void clrscr();
  static void init();
  static void printBoard(const Board &);
  static void exitBuffer();
};
#endif
