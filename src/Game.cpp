#include "Game.hpp"
#include <chrono>
#include <iostream>
#include <thread>

Game::Game() : board(), move(nullptr) {}
void Game::renderBoard() const {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  Graphics::clrscr();
  std::cout << "Player " << (board.isWhiteToMove() ? 2 : 1) << std::endl;
  Graphics::printBoard(board);
  std::cout << "*Player " << (board.isWhiteToMove() ? 1 : 2) << "*"
            << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
void Game::gameEnd() const {
  renderBoard();
  std::cout << "\nGame Ended" << "\n";
  switch (board.getStatus()) {
  case Status::WHITE_WON:
    std::cout << "White Won";
    break;
  case Status::BLACK_WON:
    std::cout << "Black Won";
    break;
  case Status::STALEMATE:
    std::cout << "Game Ended in Stalemate";
    break;
  case Status::IN_PROGRESS:
    std::cout << "Program Terminated" << std::endl;
    break;
  }
  std::cout << std::endl;

  Input::pressEnter();
  Graphics::exitBuffer();
}

void Game::catchExpt(std::ostream &os, Exception e) {
  os << e.what() << std::endl;
  Input::pressEnter();
}
void Game::start() {
  {
    // move from and move to positions respectively
    Pos fromPos, toPos;

    Graphics::init();
    while (board.getStatus() == Status::IN_PROGRESS) {
      if (board.isSelected())
        board.unselect();
      renderBoard();
      try {

        std::cout << "Enter '" << QUIT_KEY << "' to quit anytime." << std::endl;
        std::cout << "Enter coordinates of piece to select(e.g. e2):"
                  << std::endl;
        fromPos = Input::getPos();
        board.selectPos(fromPos);
        renderBoard();
        std::cout << "Enter '" << SELECTION_KEY
                  << "' to return back to selection." << std::endl;
        std::cout << "Enter coordinates of your move:" << std::endl;
        toPos = Input::getPos();

        if (move)
          delete move;
        move = new Move(fromPos, toPos, board);
        board.move(*move);

      } catch (ReturnToSelection e) {
        continue;
      } catch (Terminate e) {
        break;
      } catch (InvalidInput e) {
        catchExpt(std::cerr, e);
      } catch (InvalidPos e) {
        catchExpt(std::cerr, e);
      } catch (InvalidMove e) {
        catchExpt(std::cerr, e);
      }
    }
    board.unselect();
    gameEnd();
  }
}

Game::~Game() {}
