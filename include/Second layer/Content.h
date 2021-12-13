#ifndef CONTENT_H
#define CONTENT_H

#include <iostream>
#include <string>
#include "Reader.h"

static const std::string kLine = "================================================================================";
class Content {
 public:
  virtual ~Content();
  virtual void read(std::string);
  virtual std::string getContent();
  virtual std::string command(std::string);
};
class TextContent : public Content {
 public:
  void read(std::string);
  std::string getContent();
  std::string command(std::string);
 private:
  Reader reader_;
};
class BoardContent : public Content {
 public:
  BoardContent();
  ~BoardContent();
  void read(std::string);
  std::string getContent();
  std::string command(std::string);
  bool checkPiece(char);
  bool checkSquare(std::string);
 private:
  Board *p_board_;
  FENReader FEN_reader_;
};

#endif
