#include "Board.hpp"
#include "Exception.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include "Square.hpp"
#include <iostream>
#include <ostream>

class Game {
private:
  Board board;
  Move *move;

  void renderBoard() const;
  void gameEnd() const;
  // helper function for catching exceptions
  static void catchExpt(std::ostream &, Exception);

public:
  Game();
  void start();
  ~Game();
};
