// This will be the main file.

#include <iostream>

/* Example command: 
aur hello.aur hello
*/

int main(int argc, char* argv[]) {
  char *filename = argv[1]; // First argument is always filename..
  char *outfile = argv[2]; // Second argument is always out file.

  std::cout << "Compiling " << filename << " to " << outfile << "..."; // Just print a message for now.
  return 0;
}
