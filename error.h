#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>

/* 
ERROR return codes:
-1 - Internal error.
-2 - Compiling error.
-3 Fatal error.
*/

extern Lexer globalLexer;

void aurerror(int status, char* error);

#endif
