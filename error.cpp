#include <iostream>
#include <cstdlib>
#include "error.h"

void aurerror(int status, char* error) {
  if (!error || !status) {
    std::cerr << "Internal error, no error or status provided.." << std::endl;
    exit(-1);
  }

  switch (status) {
    case 0: // Warning
      std::cerr << "WARNING: " << error << std::endl;
      break;

    case 1: // Error
      std::cerr << "ERROR: %s" << error << std::endl;
      exit(-2);
  }
}
