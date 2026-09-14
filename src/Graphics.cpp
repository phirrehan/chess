#include "Graphics.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Square.hpp"
#include <iostream>

using namespace std;

void Graphics::printSquare(const Square &sq, bool whiteToMove, bool selected,
                           bool isSelectedSquare) {
  string pieceStr = "";
  // set foreground color
  if (sq.isEmpty() || sq.getLabel() == CAN_CAPTURE) {
    pieceStr += FG_CYAN;
  } else {
    pieceStr += (sq.getPiece().isWhite()) ? FG_WHITE : FG_BLACK;
  }

  // set background color
  if (isSelectedSquare)
    pieceStr += BG_CYAN;
  else if (auto king = dynamic_cast<const King *>(sq.getPiecePtr())) {
    if (king->isCheck())
      pieceStr += BG_RED;
    else
      pieceStr += (sq.isDark()) ? BG_GREEN : BG_YELLOW;
  } else
    pieceStr += (sq.isDark()) ? BG_GREEN : BG_YELLOW;

  // set label
  pieceStr += " " + sq.getLabel() + " ";

  // set colors back for board
  pieceStr += BG_GREY + FG_WHITE + "│";
  cout << pieceStr;
}

void Graphics::clrscr() {
  cout << BG_GREY << CLEAR << MOVE_CURSOR_TO_HOME << FG_WHITE;
}

// Enable alternate buffer and initialize the terminal
void Graphics::init() {
  cout << ENABLE_ALT_BUFFER;
  clrscr();
}

void Graphics::printBoard(const Board &board) {
  bool whiteTurn = board.isWhiteToMove();
  cout << "  ┌───┬───┬───┬───┬───┬───┬───┬───┐\n"; // top border
  for (int r = 0; r < 8; r++) {
    int printRow = (whiteTurn) ? r : 7 - r;
    cout << 8 - (printRow) << " │";
    for (int c = 0; c < 8; c++) {
      int printCol = (whiteTurn) ? c : 7 - c;
      const Square &curSq(board.getSquareAt({printRow, printCol}));
      bool isSelectedSquare =
          board.isSelected() && (curSq.getPos() == board.getSelectedPos());
      printSquare(curSq, whiteTurn, board.isSelected(), isSelectedSquare);
    }
    cout << "\n";
    if (r != 7)
      cout << "  ├───┼───┼───┼───┼───┼───┼───┼───┤\n"; // grid lines
  }
  cout << "  └───┴───┴───┴───┴───┴───┴───┴───┘\n"; // bottom border
  if (whiteTurn)
    cout << "    a   b   c   d   e   f   g   h  \n"; // reference row for
                                                     // white
  else
    cout << "    h   g   f   e   d   c   b   a  " << endl; // reference row
                                                           // for black
}

void Graphics::exitBuffer() { cout << DEFAULT_STYLE << DISABLE_ALT_BUFFER; }
