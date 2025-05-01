// This will be the main file.

#include <iostream>
#include <cstring>

/* Example command: 
aur hello.aur hello
*/

int main(int argc, char* argv[]) {

  if (strcmp(argv[1], "--version") == 0) {
    std::cout << "(V) Aur  1.0.0 (BETA) \n  (L) MIT License  \n Build: Stable-release. \n Support: https://github.com/Wickslynx/AuroraLang/issues";
    return -1;
  }
  
  char *filename = argv[1]; // First argument is always filename..
  char *outfile = argv[2]; // Second argument is always out file.

  std::cout << "Compiling " << filename << " to " << outfile << "... \n"; // Just print a message for now.
  return 0;
}
