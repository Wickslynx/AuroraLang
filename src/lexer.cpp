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
    
    lexer->cchar = fgetc(lexer->ifile); // Read from the file to get the next token.
    if (lexer->cchar == EOF) {
        Token token;
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
            break;
        }
        case 'a' ... 'z':  
        case 'A' ... 'Z':
            std::string identifier;
            identifer += c;

            char NextChar;
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
                token.type = TOKEN_GLObAL;
            } else {
                
            }
            
            break;
        case '+':
            token.type = TOKEN_PLUS;
            break;
        case '-':
            token.type = TOKEN_MINUS;
            break;
        case '/':
            token.type = TOKEN_DIVIDE;
            break;
        case ' ':
            token.type = TOKEN_SPACE;
            break;
        case '=':
            token.type = TOKEN_ASSIGN;
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
            break;
        }
        
        default:
            token.type = TOKEN_EOF;
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


    lexer->ifile = ifile;
    lexer->pos = 0;
    

    while ((lexer->cchar = fgetc(ifile)) != EOF) {
        Token token = getToken(lexer, (char)lexer->cchar);

        switch(token.type) {
            case TOKEN_INT:
                printf("Got an INT: %d\n", token.value);
                break;
            case TOKEN_CHAR:
                printf("Got a CHAR: %c\n", token.character);
                break;
            case TOKEN_PLUS:
                printf("Got a PLUS: +\n");
                break;
            case TOKEN_MINUS:
                printf("Got a MINUS: -\n");
                break;
            case TOKEN_DIVIDE:
                printf("Got a DIVIDE: /\n");
                break;
            case TOKEN_EOF:
                printf("Got EOF.\n");
                break;
            default:
                break;
        }

        lforwards(lexer);
    }

    fclose(ifile);
    return 0;
}
