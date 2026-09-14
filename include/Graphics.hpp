#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <string>

const std::string BG_GREEN = "\x1B[48;2;118;150;85m";
const std::string BG_YELLOW = "\x1B[48;2;219;171;87m";
const std::string BG_GREY = "\x1B[48;2;58;59;69m";
const std::string BG_RED = "\x1B[41m";
const std::string BG_CYAN = "\x1B[46m";
const std::string FG_WHITE = "\x1B[37m";
const std::string FG_BLACK = "\x1B[30m";
const std::string FG_CYAN = "\x1B[36m";
const std::string DEFAULT_STYLE = "\x1B[0m";
const std::string CLEAR = "\x1B[2J";
const std::string MOVE_CURSOR_TO_HOME = "\x1B[H";
const std::string ENABLE_ALT_BUFFER = "\x1B[?1049h";
const std::string DISABLE_ALT_BUFFER = "\x1B[?1049l";

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
