#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;            // current token
char *src, *old_src;  // pointer to source code string;
int poolsize;         // default size of text/data/stack
int line;             // line number



//tokens and classes defined here
enum{
    Num = 128, Fun, Sys, Glo, Loc, Id,
    Char, Else, Enum, If, Int, Return, Sizeof, While,
    Assign, Cond, Lor, Lan, Or, Xor,And, Eq, Ne, Lt,Gt, Le, Ge, Shl, Shr,
    Add,Sub,Mul,Div, Mod, Inc, Dec,
    Brk
};


void next(){
    char *last_pos;
    int hash;

    //while(token = *src++){

    //}
    return;
}


int main() {
    printf("Hello, World!\n");
    return 0;
}