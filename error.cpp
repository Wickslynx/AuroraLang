
#include "error.h"

void aurerror(int status, char* error) {
  if (!error || !status) {
    printf("Internal error, no error or status provided..");
    exit(-1);
  }

  switch (status) {
    case 0: // Warning
      printf("WARNING: %s", error);

    case 1: // Error
      printf("ERROR: %s", error)
      exit(-2);
  }
}
