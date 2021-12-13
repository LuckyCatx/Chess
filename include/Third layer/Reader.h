#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Board.h"

class Reader {
 public:
  ~Reader();
  void Read(std::string);
  std::string toString();
 protected:
  std::ifstream file_;
  std::string read_;
  bool is_read_;
};
class FENReader : public Reader {
 public:
  Board* Construct();
  bool checkFEN();
};

#endif
