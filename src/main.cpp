#include <iostream>
#include <UserInterface.h>

using namespace std;

int main() {
  //Instantiate a UserInterface object and invoke the interface
  UserInterface interface;
  interface.handleInput();
  cout << endl;
  system("pause");
  return 0;
}
