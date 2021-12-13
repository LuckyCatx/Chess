#include "Content.h"

/*---------------------------------------------------------------------------*/
/*--------------------------Content implementation---------------------------*/
/*---------------------------------------------------------------------------*/
Content::~Content() = default;
void Content::read(std::string) {return;}
std::string Content::getContent() {
  //Default title content
  return "Semester 09/2021, C++ Project, by group Natus Vincere\n"
         "Type \"help\" or \"credits\" for more information";
}
std::string Content::command(std::string input) {
  //Error command
  //Send "Unknown command" to UserInterface
  return "Unknown command\n" + kLine;
}
/*---------------------------------------------------------------------------*/
/*------------------------TextContent implementation-------------------------*/
/*---------------------------------------------------------------------------*/
void TextContent::read(std::string file_name) {
  reader_.Read(file_name);
}
std::string TextContent::getContent() {
  return reader_.toString();
}
std::string TextContent::command(std::string input) {
  //Command error
  return "Unknown command\n" + kLine;
}
/*---------------------------------------------------------------------------*/
/*------------------------BoardContent implementation------------------------*/
/*---------------------------------------------------------------------------*/
BoardContent::BoardContent() : p_board_(nullptr) {
  if (p_board_ != nullptr)
    delete p_board_;
  p_board_ = new Board;
}
BoardContent::~BoardContent() {
  if (p_board_ != nullptr) {
    delete p_board_;
    p_board_ = nullptr;
  }
}
void BoardContent::read(std::string file_name) {
  FEN_reader_.Read(file_name);
  if (p_board_ != nullptr)
    delete p_board_;
  p_board_ = FEN_reader_.Construct();
}
std::string BoardContent::getContent() {
  //A board does not exists
  if (p_board_ == nullptr) return "";
  //A board exists
  std::string board_content;
  std::string arr = p_board_->toString();
  std::string title = "[Interact-able board]\n";
  std::string line = "  +---+---+---+---+---+---+---+---+\n";
  board_content.append(title).append(" ");
  //Check the board is flipped or not
  //and draw the chess position with the perspective
  if (p_board_->is_flipped_) {
    for (int i = 0; i < arr.size() / 2; ++i)
      std::swap(arr[i], arr[arr.size() - i - 1]);
    for (int i = 0, k = 0; i < kRow; ++i) {
      if (i == 0) {
        for (int x = 0; x < kRow; ++x)
          board_content.append("   ").push_back('h' - x);
        board_content.append("\n");
      }
      board_content.append(line).append(std::to_string(i + 1));
      for (int j = 0; j < kCol; ++j) {
        board_content.append(" | ").push_back(arr[k]);
        ++k;
      }
      board_content.append(" | ").append(std::to_string(i + 1)).append("\n");
      if (i == kRow - 1) {
        board_content.append(line).append(" ");
        for (int y = 0; y < kRow; ++y)
          board_content.append("   ").push_back('h' - y);
      }
    }
  } else {
    for (int i = 0, k = 0; i < kRow; ++i) {
      if (i == 0) {
        for (int x = 0; x < kRow; ++x)
          board_content.append("   ").push_back('a' + x);
        board_content.append("\n");
      }
      board_content.append(line).append(std::to_string(kRow - i));
      for (int j = 0; j < kCol; ++j) {
        board_content.append(" | ").push_back(arr[k]);
        ++k;
      }
      board_content.append(" | ").append(std::to_string(kRow - i)).append("\n");
      if (i == kRow - 1) {
        board_content.append(line).append(" ");
        for (int y = 0; y < kRow; ++y)
          board_content.append("   ").push_back('a' + y);
      }
    }
  }
  return board_content;
}
std::string BoardContent::command(std::string input) {
  if (input == "flip") {
    p_board_->flip();
  } else if (input == "put") {
    char piece;
    std::string square;
    std::cin >> piece;
    std::cin >> square;
    //Validate the name of piece and name of square
    if (p_board_->checkPiece(piece) && p_board_->checkSquare(square)) {
      //Put the piece and check if the put was successful
      if(!p_board_->putPiece(piece, square))
        //Put fail
        return "Put failed, there's already a piece exists\n" + kLine;
    } else {
      //Invalid name
      return "Invalid name of piece or square\n" + kLine;
    }
  } else if (input == "remove") {
    std::string square;
    std::cin >> square;
    //Validate the name of square
    if (p_board_->checkSquare(square)) {
      //Remove the piece and check if the remove was successful
      if(!p_board_->movePiece(square))
        //Remove fail
        return "There's no piece that exists\n" + kLine;
    } else {
      //Invalid name
      return "Invalid name of square\n" + kLine;
    }
  } else if (input == "move") {
    std::string square1, square2;
    std::cin >> square1 >> square2;
    //Validate the name of both squares
    if (p_board_->checkSquare(square1) && p_board_->checkSquare(square2)) {
      //Move the piece and check if the move was successful
      if(!p_board_->movePiece(square1, square2))
        //Move fail
        return "There's no piece that exists\n" + kLine;
    } else {
      //Invalid name
      return "Invalid name of square\n" + kLine;
    }
  } else {
    //Command error
    return "Unknown command\n" + kLine;
  }
  return "Correct";
}
