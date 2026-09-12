#include "Board.hpp"
#include "Exception.hpp"
class Game {
private:
  Board board;
  Move *move;

  void renderBoard() const;
  void gameEnd() const;
  // helper function for catching exceptions
  static void catchExpt(Exception);

public:
  Game();
  void start();
  ~Game();
};
