#include "UserInterface.h"

UserInterface::UserInterface() : p_current_(nullptr) {
  //Allocate three memory spaces to three types of Contents
  //Index 0 refers to Content, index 1 refers to TextContent, index 2 refers to BoardContent
  p_content_ = new Content*[kType] {nullptr, nullptr, nullptr};
  p_content_[0] = new Content;
  //Default current pointer point Content
  p_current_ = p_content_[0];
  //Print title
  refresh();
  showMsg(kLine);
}
UserInterface::~UserInterface() {
  //Release the allocated spaces of Content if exist
  for (int i = 0; i < kType; ++i) {
    if (p_content_[i] != nullptr) {
      delete p_content_[i];
      p_content_[i] = nullptr;
    }
  }
  //Release the allocated spaces of pointer array
  delete[] p_content_;
  p_current_ = nullptr;
}
void UserInterface::handleInput() {
  std::string input;
  std::string message;
  while (!isQuit(input)) {
    //Clear redundant input
    std::cin.clear();
    std::cin.sync();
    std::cout << ">> ";
    std::cin >> input;
/*---------------------------------------------------------------------------*/
/*-------------First layer command | Implement in UserInterface--------------*/
/*---------------------------------------------------------------------------*/
    if (input == "quit") {
      //Do nothing and continue
      continue;
    } else if (input == "new") {
      if (p_content_[2] != nullptr)
        delete p_content_[2];
      p_content_[2] = new BoardContent;
      p_current_ = p_content_[2];
    } else if (input == "help") {
      if (p_content_[1] == nullptr)
        p_content_[1] = new TextContent;
      p_current_ = p_content_[1];
      p_current_->read("help.txt");
    } else if (input == "credits") {
      if (p_content_[1] == nullptr)
        p_content_[1] = new TextContent;
      p_current_ = p_content_[1];
      p_current_->read("credits.txt");
    } else if (input == "open") {
      std::string file_name;
      std::cin >> file_name;
      Content *p_check_type = checkContentType(file_name);
      //Check file extension
      if (p_check_type != nullptr) {
        //Check Content type
        if (dynamic_cast<TextContent*>(p_check_type) != nullptr) {
          //TextContent
          p_content_[1] = p_check_type;
          p_current_ = p_content_[1];
        } else {
          //BoardContent type
          if (p_content_[2] != nullptr)
            delete p_content_[2];
          p_content_[2] = p_check_type;
          p_current_ = p_content_[2];
        }
        //Read file
        p_current_->read(file_name);
      } else {
        //File extension error
        showMsg(kLine);
        continue;
      }
/*---------------------------------------------------------------------------*/
/*----------------Second layer command | Implement in Content----------------*/
/*---------------------------------------------------------------------------*/
    } else {
      //Avoid being unable to manipulate existing board
      //while TextContent is being displayed
      if (dynamic_cast<TextContent*>(p_current_) != nullptr &&
          p_content_[2] != nullptr) p_current_ = p_content_[2];
      //Pass the command to current Content and receive message
      message = p_current_->command(input);
      //Invalid command, display the return message
      if (message != "Correct") {
        showMsg(message);
        continue;
      }
    }
/*---------------------------------------------------------------------------*/
/*-------------------------------Normal output-------------------------------*/
/*---------------------------------------------------------------------------*/
    refresh();
    showMsg(kLine);
  }
//After any valid command,
//the current pointer will not point to Content anymore
}
void UserInterface::showMsg(std::string msg) {
  std::cout << msg << std::endl;
}
void UserInterface::refresh() {
    std::cout << p_current_->getContent() << std::endl;
}
bool UserInterface::isQuit(std::string input) {
  if (input == "quit") return true;
  else return false;
}
Content* UserInterface::checkContentType(std::string file_name) {
  std::string text_ext = ".txt";
  std::string FEN_ext = ".FEN";
  //File extension existence checking
  if (file_name.size() <= text_ext.size() || file_name.size() <= FEN_ext.size()) {
    std::cout << "A file extension is required.\n";
    return nullptr;
  } else {
    //File extension .txt checking
    if (!file_name.compare(file_name.size() - text_ext.size(), text_ext.size(), text_ext)) {
      //Check if there's an existing TextContent
      return p_content_[1] == nullptr ? new TextContent : p_content_[1];
      //File extension .FEN checking
    } else if (!file_name.compare(file_name.size() - FEN_ext.size(), FEN_ext.size(), FEN_ext)) {
      //Create new BoardContent
      return new BoardContent;
    } else {
      //File extension error or not exist
      std::cout << "File extension error.\n";
      return nullptr;
    }
  }
}
