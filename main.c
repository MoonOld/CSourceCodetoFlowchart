#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "header.h"


char string[20][100];//string to buffer itself
id array[130]={{For,"for"},{While,"while"}, {If,"if"},{Else,"else"},
               {Return,"return"}, {Break,"break"},{Continue,"continue"},
               {Char,"char"}, {Int, "int"}, {Float,"float"}
};//max identifier
Token tokens[20000];
char src[60000];




int main() {
    FILE * _fileI = NULL;

    if(_fileI = fopen("/Users/apple/desktop/programming/complier/test.txt","r")) {
        load(_fileI, src);
        fclose(_fileI);
        lex(src, tokens, array, string);
        lextest(tokens, array, string);
    }
    return 0;
}


