#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
#include "Content.h"

static const int kType = 3;
class UserInterface {
 public:
  UserInterface();
  ~UserInterface();
  void handleInput();
  void showMsg(std::string);
  void refresh();
  bool isQuit(std::string);
  Content* checkContentType(std::string);
 private:
   //Using pointer to pointer to save different types of Contents
   Content **p_content_;
   //The current pointer which point to current Content
   Content *p_current_;
};

#endif
