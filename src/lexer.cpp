#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include <iostream>

// ------------------------------------------
//                 HELPERS 
// ------------------------------------------
const char* fname;

Token getNextToken(Lexer *lexer) {
    if (!lexer->ifile) {
        std::cout << "Error: Lexer file pointer is NULL... Starting backup..." << std::endl;

        /* Backup attempt, something goes wrong in lexer open the file in here instead */
        FILE* ifile = fopen(fname, "r");
        if (ifile == NULL) {
            aurerror(1, "Error opening file...");
        }
        lexer->ifile = ifile;

        if (!lexer->ifile) {
            std::cerr << "Error: Backup attempt failed..." << std::endl;
            exit(-1);
        }
    }

    printf("(DEBUG) File pointer initialized: %p\n", (void*)lexer->ifile);
    printf("(DEBUG) Current file position: %ld\n", ftell(lexer->ifile));
    
    lexer->cchar = fgetc(lexer->ifile); // Read from the file to get the next token.
    std::cout << "(DEBUG) Read character: " << (char)lexer->cchar << std::endl;
    if (lexer->cchar == EOF) {
        Token token;
        printf("Reached EOF!");
        token.type = TOKEN_EOF;
        return token;
    }
    return getToken(lexer, (char)lexer->cchar);
}

// ------------------------------------------
//             MAIN FUNCTIONS
// ------------------------------------------


Token getToken(Lexer *lexer, const char c) {
    Token token;
    std::string identifier;
    char nextChar;

    if (c == EOF) {
        token.type = TOKEN_EOF;
    }
    
    switch(c) {
        case '0' ... '9': {
            int number = c - '0'; 
            char nextChar;
            while (isdigit((nextChar = fgetc(lexer->ifile)))) {
                number = number * 10 + (nextChar - '0'); 
            }
            ungetc(nextChar, lexer->ifile);
            token.type = TOKEN_INT;
            token.value = number;
            printf("Debug: (Found) %d TYPE=INT\n", number);
            break;
        }
        case 'a' ... 'z':  
        case 'A' ... 'Z':
            identifier += c;
            while (isalnum(nextChar = fgetc(lexer->ifile))) {  // Include numbers in identifiers
                identifier += nextChar;
            }
            ungetc(nextChar, lexer->ifile); // Push back all non identifiers.

            if (identifier == "if") {
                token.type = TOKEN_IF;
            } else if (identifier == "elif") {
                token.type = TOKEN_ELIF;
            } else if (identifier == "else") {
                token.type = TOKEN_ELSE;
            } else if (identifier == "while") {
                token.type = TOKEN_WHILE;
            } else if (identifier == "return") {
                token.type = TOKEN_RETURN;
            } else if (identifier == "const") {
                token.type = TOKEN_CONST;
            } else if (identifier == "local") {
                token.type = TOKEN_LOCAL;
            } else if (identifier == "global") {
                token.type = TOKEN_GLOBAL;
            } else if (identifier == "fn") {
                token.type = TOKEN_FUNC;
            } else {
                token.type = TOKEN_IDENTIFIER;
                token.identifier = identifier.c_str();
            }
            
            printf("Debug: (Found) %s\n", identifier.c_str());
            break;
        case '+':
            token.type = TOKEN_PLUS;
            printf("Debug: (Found) +\n");
            break;
        case '-':
            token.type = TOKEN_MINUS;
            printf("Debug: (Found) -\n");
            break;
        case '/':
            token.type = TOKEN_DIVIDE;
            printf("Debug: (Found) /\n");
            break;
        case ' ':
            token.type = TOKEN_SPACE;
            printf("Debug: (Found) SPACE\n");
            break;
        case '=':
            printf("Debug: (Found) =\n");
            token.type = TOKEN_ASSIGN;
            break;
        case '{':
            printf("Debug: (Found) {\n");
            token.type = TOKEN_RBRACE;
            break;
        case '}':
            token.type = TOKEN_LBRACE;
            printf("Debug: (Found) }\n");
            break;
        case ',':
            token.type = TOKEN_COMMA;
            printf("Debug: (Found) ,\n");
            break;
        case '(':
            token.type = TOKEN_RPARAN;
            printf("Debug: (Found) (\n");
            break;
        case ')':
            printf("Debug: (Found) )\n");
            token.type = TOKEN_LPARAN;
            break;
        case ';':
            token.type = TOKEN_SEMICOL;
            printf("Debug: (Found) ;\n");
            break;
        case '"': { // Start of a string
            std::string strValue;
            char nextChar;
            while ((nextChar = fgetc(lexer->ifile)) != '"' && nextChar != EOF) {
                strValue += nextChar;
            }
            if (nextChar == EOF) {
                std::cerr << "Error: Unterminated string literal." << std::endl;
                std::exit(EXIT_FAILURE);
            }
            token.type = TOKEN_STRING;
            token.strValue = strValue.c_str();
            printf("Debug: (Found) %s TYPE=STR\n", strValue.c_str());
            break;
        }
        case '\n':
            token.type = TOKEN_NEWLINE;
            printf("Debug: (Found) NEWLINE\n");
            break;

        
        default:
            printf("Warning: Found unreqonised characters.. Continuing..\n");
            break;
    }
    return token;
}

// mv 1 step forwards
void lforwards(Lexer *lexer) {
    lexer->pos++;
}


// lex fn: reads from file and tokenizes it. ( how tf do u spell tokenize or smth)
int lex(Lexer* lexer, const char* filename) {
    if (!filename) {
        aurerror(2, "No file given to lexer.");
    }
    fname = filename;
    
    FILE* ifile = fopen(filename, "r");
    if (ifile == NULL) {
        aurerror(1, "Error opening file...");
    }

    if (ferror(lexer->ifile)) {
        perror("(DEBUG) Error in file stream");
    }

    lexer->ifile = ifile;
    lexer->pos = 0;

    printf("------------------------------\n");
    printf("           LEXER - DEBUG      \n");
    printf("------------------------------\n\n");
    while ((lexer->cchar = fgetc(ifile)) != EOF) {
        Token token = getToken(lexer, (char)lexer->cchar);

        lforwards(lexer);
    }

    fclose(ifile);
    printf("\n\n");
    
    return 0;
}
