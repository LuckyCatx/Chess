#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <cmath>

static const int kRow = 8, kCol = 8;
class Board {
 public:
   //Two types of constructor: FEN file or empty
  Board(std::string = "");
  ~Board();
  std::string toString();
  std::string toFEN();
  void flip();
  bool putPiece(char, std::string);
  //Two types of move: move or remove
  bool movePiece(std::string, std::string = "");
  bool checkPiece(char);
  bool checkSquare(std::string);
  bool is_flipped_;
 private:
  //Simulate a chessboard using a 2-dimensional array
  char chess_[kRow][kCol];
  std::string *chess_str_;
  std::string *chess_FEN_;
};

#endif
