#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>

/* 
ERROR return codes:
-1 - Internal error.
-2 - Compiling error.
*/

void error(int status, char error[1024]) {
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

#endif
