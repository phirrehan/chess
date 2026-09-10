#include "Board.hpp"
#include "Bishop.hpp"
#include "Exception.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Piece.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Square.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>

Board::Board()
    : whiteKingPos({7, 4}), blackKingPos({0, 4}), whiteToMove(true),
      selected(false), selectedPos({-1, -1}), moveCount(0) {
  // rank 1 black pieces
  int row = 0;
  arr[0] = new Square(new Rook(PieceColor::BLACK), {row, 0});
  arr[1] = new Square(new Knight(PieceColor::BLACK), {row, 1});
  arr[2] = new Square(new Bishop(PieceColor::BLACK), {row, 2});
  arr[3] = new Square(new Queen(PieceColor::BLACK), {row, 3});
  arr[4] = new Square(new King(PieceColor::BLACK), {row, 4});
  arr[5] = new Square(new Bishop(PieceColor::BLACK), {row, 5});
  arr[6] = new Square(new Knight(PieceColor::BLACK), {row, 6});
  arr[7] = new Square(new Rook(PieceColor::BLACK), {row, 7});

  // rank 2 black pawns
  row = 1;
  for (int col = 0; col < 8; col++) {
    arr[row * 8 + col] = new Square(new Pawn(PieceColor::BLACK), {row, col});
  }

  // rank 3-6 empty spaces
  for (row = 2; row < 6; row++)
    for (int col = 0; col < 8; col++)
      arr[row * 8 + col] = new Square(nullptr, {row, col});

  // rank 7 white pawns
  row = 6;
  for (int col = 0; col < 8; col++) {
    arr[row * 8 + col] = new Square(new Pawn(PieceColor::WHITE), {row, col});
  }

  // rank 8 white pieces
  row = 7;
  arr[row * 8 + 0] = new Square(new Rook(PieceColor::WHITE), {row, 0});
  arr[row * 8 + 1] = new Square(new Knight(PieceColor::WHITE), {row, 1});
  arr[row * 8 + 2] = new Square(new Bishop(PieceColor::WHITE), {row, 2});
  arr[row * 8 + 3] = new Square(new Queen(PieceColor::WHITE), {row, 3});
  arr[row * 8 + 4] = new Square(new King(PieceColor::WHITE), {row, 4});
  arr[row * 8 + 5] = new Square(new Bishop(PieceColor::WHITE), {row, 5});
  arr[row * 8 + 6] = new Square(new Knight(PieceColor::WHITE), {row, 6});
  arr[row * 8 + 7] = new Square(new Rook(PieceColor::WHITE), {row, 7});
}
Board::Board(const Board &other)
    : whiteKingPos(other.whiteKingPos), blackKingPos(other.blackKingPos),
      whiteToMove(other.whiteToMove), selected(other.selected),
      selectedPos(other.selectedPos), moveCount(0) {
  for (int i = 0; i < 64; i++) {
    arr[i] = other.getSquareAt({i / 8, i % 8}).clone();
  }
}

int Board::distance(const Move &move) {
  Pos diff = move.from.getPos() - move.to.getPos();
  return static_cast<int>(
      std::sqrt(std::pow(diff.row, 2) + std::pow(diff.col, 2)));
}
bool Board::isPosOutOfBounds(Pos p) {
  return (p.row < 0 || p.row >= 8 || p.col < 0 || p.col >= 8);
}
void Board::popOutOfBoundsElements(std::vector<Pos> &list) {

  for (int i = 0; i < list.size(); i++) {
    if (isPosOutOfBounds(list[i])) {
      std::swap(list[i--], list[list.size() - 1]);
      list.pop_back();
    }
  }
}

Square &Board::getSquareAt(Pos p) {
  if (isPosOutOfBounds(p))
    throw InvalidPos("access to square denied. pos is out of bounds");
  return *arr[p.row * 8 + p.col];
}

const Square &Board::getSquareAt(Pos p) const {
  if (isPosOutOfBounds(p)) {
    throw InvalidPos("access to square denied. pos is out of bounds");
  }
  return *arr[p.row * 8 + p.col];
}
Pos Board::getKingPos(PieceColor color) const {
  return (color == PieceColor::WHITE) ? whiteKingPos : blackKingPos;
}
Pos Board::getSelectedPos() const { return selectedPos; }
int Board::getMoveCount() const { return moveCount; }
Status Board::getStatus() const { return status; }
bool Board::isWhiteToMove() const { return whiteToMove; }
bool Board::isSelected() const { return selected; }
bool Board::hasObstructions(const Pos &p1, const Pos &p2, Pin pin) const {
  Pos diff = p2 - p1;
  int r, c;
  int minR = std::min(p1.row, p2.row);
  int minC = std::min(p1.col, p2.col);
  int maxR = std::max(p1.row, p2.col);
  int maxC = std::max(p1.col, p2.col);

  switch (pin) {
  case Pin::HORIZONTAL:
    for (c = minC + 1; c < maxC; c++) {
      if (!getSquareAt({p1.row, c}).isEmpty()) {
        return true;
      }
    }
    break;
  case Pin::VERTICAL:
    for (r = minR + 1; r < maxR; r++) {
      if (!getSquareAt({r, p1.col}).isEmpty()) {
        return true;
      }
    }
    break;
  case Pin::DIAGONAL_MAIN:
    for (r = minR + 1, c = minC + 1; r < maxR && c < maxC; r++, c++)
      if (!getSquareAt({r, c}).isEmpty()) {
        return true;
      }
    break;
  case Pin::DIAGONAL_ANTI:
    for (r = minR + 1, c = maxC - 1; r < maxR && c > minC; r++, c--)
      if (!getSquareAt({r, c}).isEmpty()) {
        return true;
      default:
        throw std::invalid_argument("expected pin to not be NONE");
      }
  }
  return false;
}

void Board::setKingPos(PieceColor color, Pos p) {
  if (color == PieceColor::WHITE)
    whiteKingPos = p;
  else
    blackKingPos = p;
}
void Board::setSelectedPos(Pos p) { selectedPos = p; }
void Board::toggleWhiteToMove() { whiteToMove = (whiteToMove) ? false : true; }
void Board::setSelected(bool s) { selected = s; }
void Board::incrementMoveCount() { moveCount++; }
void Board::setStatus(Status st) { status = st; }

bool Board::isAlignedWithKing(const Square &sq, PieceColor color,
                              Pin pin) const {
  Pos kingPos = getKingPos(color);
  Pos sqPos = sq.getPos();
  int dx = kingPos.row - sqPos.row;
  int dy = kingPos.col - sqPos.col;

  switch (pin) {
  case Pin::HORIZONTAL:
    return dx == 0;
    break;
  case Pin::VERTICAL:
    return dy == 0;
    break;
  case Pin::DIAGONAL_MAIN:
    return dx == dy;
    break;
  case Pin::DIAGONAL_ANTI:
    return dx == dy;
    break;
  default:
    throw std::invalid_argument("expected pin to be not NONE.");
  }
}

bool Board::isMoveAvailable() const {
  PieceColor enemyColor = (whiteToMove) ? PieceColor::BLACK : PieceColor::WHITE;
  for (int i = 0; i < 64; i++) {
    const Square &curSq(getSquareAt({i / 8, i % 8}));
    if (curSq.isEmpty() || curSq.getPiece().getColor() != enemyColor)
      continue;
    else if (curSq.getPiece().hasMoveAvailable(curSq, *this))
      return true;
  }
  return false;
}

bool Board::isCapturable(PieceColor color, const Square &sq) const {
  for (int i = 0; i < 64; i++) {
    Square curSq(getSquareAt({i / 8, i % 8}));
    if (curSq.isEmpty())
      continue;
    else if (curSq.getPiece().getColor() != color)
      continue;
    else if (auto king = dynamic_cast<const King *>(curSq.getPiecePtr()))
      continue;

    std::vector<Move> list = curSq.getPiece().getValidMovesList(curSq, *this);
    for (int j = 0; j < list.size(); j++) {
      if (!list[i].capture)
        continue;
      else if (list[i].to == sq)
        return true;
    }
  }
  return false;
}

bool Board::canCastle(const Move &move) const {
  PieceColor kingColor = move.from.getPiece().getColor();

  int castleRow, castleCol;
  const Rook *rook;
  castleRow = (kingColor == PieceColor::WHITE) ? 7 : 0;
  // castle short
  if (move.to.getPos().col == 6) {
    for (int c = 6; c > 4; c--) {
      if (!getSquareAt({castleRow, c}).isEmpty())
        return false;
    }
    rook =
        dynamic_cast<const Rook *>(getSquareAt({castleRow, 7}).getPiecePtr());
  }
  // castle long
  else {
    for (int c = 1; c < 4; c++) {
      if (!(*this).getSquareAt({castleRow, c}).isEmpty())
        return false;
    }
    rook =
        dynamic_cast<const Rook *>(getSquareAt({castleRow, 0}).getPiecePtr());
  }

  if (rook == nullptr || !rook->isFirstMove())
    return false;
  else
    return true;
}

bool Board::canMoveRemoveCheck(const Move &move) const {
  PieceColor kingColor = move.from.getPiece().getColor();

  // copy board and move
  Board boardCopy(*this);
  Pos posFrom(move.from.getPos());
  Pos posTo(move.to.getPos());
  Move moveCopy(posFrom, posTo, boardCopy);

  // simulate the move in the copy
  try {
    moveCopy.from.getPiece().move(moveCopy, boardCopy);
  } catch (InvalidMove e) {
    return false;
  }
  Square kingSqCopy(boardCopy.getSquareAt(boardCopy.getKingPos(kingColor)));
  if (auto king = dynamic_cast<King *>(kingSqCopy.getPiecePtr())) {
    return !king->isCheck();
  } else
    throw std::invalid_argument(
        "invalid kingSq provided. king not found on this square");
}

bool Board::isCheckMate(PieceColor color) const {
  Pos kingPos = getKingPos(color);
  Square kingSq = getSquareAt(kingPos);
  auto king = dynamic_cast<const King *>(kingSq.getPiecePtr());
  if (!king->isCheck())
    return false;
  for (int i = 0; i < 64; i++) {
    Square curSq(getSquareAt({i / 8, i % 8}));
    if (curSq.isEmpty() ||
        curSq.getPiece().getColor() != kingSq.getPiece().getColor())
      continue;
    std::vector<Move> list =
        curSq.getPiecePtr()->getValidMovesList(curSq, *this);
    for (int j = 0; j < list.size(); j++) {
      if (canMoveRemoveCheck(list[j]))
        return false;
    }
  }
  return true;
}

void Board::markAvailableMoves(const Square &sq) {
  std::vector<Move> moves = sq.getPiece().getValidMovesList(sq, *this);
  for (auto move : moves) {
    Square &markSq(getSquareAt(move.to.getPos()));
    markSq.setLabel((markSq.isEmpty()) ? CAN_MOVE : CAN_CAPTURE);
  }
}

void Board::selectPos(Pos p) {
  if (getSquareAt(p).isEmpty())
    throw InvalidPos("selection failed. cannot select an empty square");
  selected = true;
  selectedPos = p;
  markAvailableMoves(getSquareAt(p));
}

void Board::unselect() {
  selected = false;
  selectedPos = {-1, -1};
  for (int i = 0; i < 64; i++) {
    Square &curSq(getSquareAt({i / 8, i % 8}));
    if (curSq.isEmpty() && !curSq.isLabelEmpty())
      curSq.setLabel(EMPTY);
  }
}

void Board::updateStatus() {

  // update check statuses of both kings
  Square enemyKingSq(getSquareAt((whiteToMove) ? blackKingPos : whiteKingPos));
  auto enemyKing = dynamic_cast<King *>(enemyKingSq.getPiecePtr());
  enemyKing->updateCheckStatus(enemyKingSq, *this);

  // update game status
  if (isCheckMate(enemyKingSq.getPiece().getColor()))
    status = (whiteToMove) ? Status::WHITE_WON : Status::BLACK_WON;
  else if (!isMoveAvailable())
    status = Status::STALEMATE;
}

void Board::move(const Move &move) {
  Square &moveSq(getSquareAt(move.from.getPos()));
  moveSq.getPiece().move(move, *this);
}

bool Board::hasPinUpdated(Pos p, Square &sq, Pin pin) {
  if (isPosOutOfBounds(p))
    return true;
  else if (getSquareAt(p).isEmpty())
    return false;
  else if (getSquareAt(p).getPiece().getColor() == sq.getPiece().getColor())
    return true;
  else {
    sq.getPiece().setPin(pin);
    return true;
  }
}

int moveDir(int num) {
  if (num > 0)
    return 1;
  else if (num < 0)
    return -1;
  else
    return 0;
}

void Board::updatePin() {

  for (int i = 0; i < 64; i++) {
    Square &sq(getSquareAt({i / 8, i % 8}));
    if (sq.isEmpty() || dynamic_cast<King *>(sq.getPiecePtr()) != nullptr)
      continue;

    PieceColor color = sq.getPiece().getColor();
    Pos sqPos = sq.getPos();
    Pos kingPos = getKingPos(color);
    Pos diff = sqPos - kingPos;
    int rowDir = moveDir(diff.row);
    int colDir = moveDir(diff.col);
    int startRow = sqPos.row + 1 * rowDir;
    int startCol = sqPos.col + 1 * colDir;
    int r = startRow, c = startCol;

    sq.getPiece().setPin(Pin::NONE);
    Pin pinList[4] = {Pin::HORIZONTAL, Pin::VERTICAL, Pin::DIAGONAL_MAIN,
                      Pin::DIAGONAL_ANTI};
    for (int i = 0; i < 4; i++) {
      if (isAlignedWithKing(sq, color, pinList[i]) &&
          !hasObstructions(sqPos, kingPos, pinList[i])) {

        if (pinList[i] == Pin::HORIZONTAL)
          r = sqPos.row;
        else if (pinList[i] == Pin::VERTICAL)
          c = sqPos.col;

        while ((r >= 0 && r < 8) && (c >= 0 && c < 8)) {
          if (hasPinUpdated({r, c}, sq, pinList[i]))
            break;
          r += 1 * rowDir;
          c += 1 * colDir;
        }
      }
    }
  }
}

Board::~Board() {
  for (int i = 0; i < 64; i++) {
    if (auto piecePtr = arr[i]->getPiecePtr())
      delete piecePtr;
    delete arr[i];
  }
}
