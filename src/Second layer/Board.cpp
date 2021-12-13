#include "Board.h"

Board::Board(std::string FEN)
    : is_flipped_(false), chess_str_(nullptr), chess_FEN_(nullptr) {
  //Create empty board
  if (FEN.empty()) {
    for (int i = 0; i < kRow; ++i)
      for (int j = 0; j < kCol; ++j)
        chess_[i][j] = ' ';
  } else {
    //Create board using FEN as string
    for (int i = 0, j = 0, k = 0; i < FEN.size(); ++i) {
      if (static_cast<int>(FEN[i]) - '0' > 0 &&
          static_cast<int>(FEN[i]) - '0' <= 8) {
        for (int l = 0; l < static_cast<int>(FEN[i]) - '0'; ++l) {
          chess_[j][k] = ' ';
          ++k;
        }
      } else if (FEN[i] != '/') {
        chess_[j][k] = FEN[i];
        ++k;
      } else {
        ++j;
        k = 0;
      }
    }
  }
}
Board::~Board() {
  if (chess_str_ != nullptr) {
    delete chess_str_;
    chess_str_ = nullptr;
  }
  if (chess_FEN_ != nullptr) {
    delete chess_FEN_;
    chess_FEN_ = nullptr;
  }
}
//Save the string that draws the chess position and return
std::string Board::toString() {
  std::string chess_str;
  for (int i = 0; i < kRow; ++i)
    for (int j = 0; j < kCol; ++j)
      chess_str += chess_[i][j];
  if (chess_str_ != nullptr)
    delete chess_str_;
  chess_str_ = new std::string(chess_str);
  return *chess_str_;
}
//Receive the string that draws the chess position
//and change to FEN format that records the chess position
//then save the string and return
std::string Board::toFEN() {
  std::string chess_str = toString();
  std::string chess_FEN;
  for (int i = 0, j = 0, k = 0; i < chess_str.size(); ++i) {
    ++k;
    if (chess_str[i] == ' ') {
      if (!chess_FEN[j]) {
        chess_FEN.push_back('1');
      } else {
        if (static_cast<int>(chess_FEN[j]) - '0' < 0 ||
            static_cast<int>(chess_FEN[j]) - '0' > kRow) {
          chess_FEN.push_back('0');
          ++j;
        }
        ++chess_FEN[j];
      }
    } else {
      chess_FEN.push_back(chess_str[i]);
      ++j;
    }
    if (k == 8 && i != chess_str.size() - 1) {
      chess_FEN.push_back('/');
      ++j;
      k = 0;
    }
  }
  if (chess_FEN_ != nullptr)
    delete chess_FEN_;
  chess_FEN_ = new std::string(chess_FEN);
  return *chess_FEN_;
}
void Board::flip() {
  //Only changes the board state
  //without changing the position of the pieces
  is_flipped_ = is_flipped_ ? false : true;
}
bool Board::putPiece(char piece, std::string square) {
  int x = is_flipped_ ? kCol - (static_cast<int>(square[0]) - 'a') - 1
                      : static_cast<int>(square[0]) - 'a';
  int y = is_flipped_ ? static_cast<int>(square[1]) - '0' - 1
                      : kRow - (static_cast<int>(square[1]) - '0');
  //Check whether a piece already exists
  if (chess_[y][x] == ' ') {
    chess_[y][x] = piece;
    return true;
  }
  return false;
}
bool Board::movePiece(std::string square1, std::string square2) {
  int x1 = static_cast<int>(square1[0]) - 'a';
  int y1 = kRow - (static_cast<int>(square1[1]) - '0');
  //Check whether a piece exists to move or remove
  if (chess_[y1][x1] != ' ') {
    //Check function types
    if (!square2.empty()) {
      //Function move piece
      int x2 = static_cast<int>(square2[0]) - 'a';
      int y2 = kRow - (static_cast<int>(square2[1]) - '0');
      //Check whether there's a piece exists in the target position,if exists, eat it
      if (chess_[y2][x2] != ' ') chess_[y2][x2] = ' ';
      std::swap(chess_[y1][x1], chess_[y2][x2]);
    } else {
      //Function remove piece
      chess_[y1][x1] = ' ';
    }
    return true;
  }
  return false;
}
bool Board::checkPiece(char piece) {
  if (piece == 'k' || piece =='q' || piece == 'r' ||
      piece == 'b' || piece =='n' || piece == 'p' ||
      piece == 'K' || piece =='Q' || piece == 'R' ||
      piece == 'B' || piece =='N' || piece == 'P')
    return true;
  return false;
}
bool Board::checkSquare(std::string square) {
  if (square.size() == 2) {
    if (static_cast<int>(square[0]) - 'a' >= 0 &&
        static_cast<int>(square[0]) - 'a' < kCol &&
        static_cast<int>(square[1]) - '0' > 0 &&
        static_cast<int>(square[1]) - '0' <= kRow)
      return true;
    }
  return false;
}
