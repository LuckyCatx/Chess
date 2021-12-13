#include "Reader.h"

Reader::~Reader() {
  file_.close();
}
void Reader::Read(std::string file_name) {
  file_.open(file_name);
  if (file_) {
    is_read_ = true;
    char read_char;
    while (file_.get(read_char))
      read_.push_back(read_char);
  } else {
    is_read_ = false;
    std::cout << "Error reading file.";
  }
}
std::string Reader::toString() {
  //Return the content of file
  return read_;
}
Board* FENReader::Construct() {
  if (is_read_) {
    //Check the format of FEN file is correct or not
    if (checkFEN()) {
      return new Board(toString());
    } else {
      std::cout << "Incorrect file format, create an empty board.\n";
      return new Board;
    }
  } else {
    //Error reading, board not created
    return nullptr;
  }
}
bool FENReader::checkFEN(){
  //Temporary pointer for checking
  Board *p_check = nullptr;
  int piece_number = 0, piece_number_row = 0;
  for (int i = 0; i < read_.size(); ++i) {
    if (static_cast<int>(read_[i]) - '0' > 0 &&
        static_cast<int>(read_[i]) - '0' <= kRow) {
      for (int j = 0; j < static_cast<int>(read_[i]) - '0'; ++j) {
        ++piece_number;
        ++piece_number_row;
      }
      if (piece_number_row > kCol) return false;
    } else if (p_check->checkPiece(read_[i])) {
      ++piece_number;
      ++piece_number_row;
      if (piece_number_row > kCol) return false;
    } else if (read_[i] == '/') {
      if (piece_number_row < kCol) return false;
      else piece_number_row = 0;
    } else {
      return false;
    }
    if (piece_number == kRow * kCol) {
      if (!read_[i+1]) return true;
      else return false;
    }
  }
}
