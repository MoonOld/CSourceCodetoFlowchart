#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;            // current token
char *src, *old_src;  // pointer to source code string;
int poolsize;         // default size of text/data/stack
int line;             // line number
int token_val;         // value of current token(
int current_id=0;         //current parsed identifiers
int current_str=0;      //current parsed str

//tokens and classes defined here
enum{
    Num = 128, Fun, Sys, Glo, Loc, Id,
    Char, Else, Enum, If, Int, Return, Sizeof, While,
    Assign, Cond, Lor, Lan, Or, Xor,And, Eq, Ne, Lt,Gt, Le, Ge, Shl, Shr,
    Add,Sub,Mul,Div, Mod, Inc, Dec,
    Brk
};

struct identifier{
    int token;
    int hash;
    char  name[11];
    int class,type,value,
    Bclass,Btype,Bvalue; //BX for extern
};

char str[20][100];

struct identifier array[130];//max identifier


void next(){
    char *last_pos;
    int hash;

    while(token = *src++){
//        if(token == '\n'){
//            line++;
//        }
//

        else if (token == '#'){
            while(*src != 0 && *src!='\n' )
                src++;
        }//macro and more
//
//        else if((token >='a'&&token<='z') || (token>='A'&&token <= 'Z')||token == '_'){
//            last_pos = src-1;
//            hash = token;
//
//            while((token >='a'&&token<='z') || (token>='A'&&token <= 'Z')||
//            token == '_'||(token>='0'&&token<='9'))
//                hash = hash*147 + *src++;//hash this id
//            idcpy(array[current_id].name,);
//            array[current_id].hash = hash;
//        }
//
//        else if (token>='0' && token <='9'){
//            token_val = token - '0';
//            while(*src>='0' && *src <='9')
//                token_val = token_val*10 + *src++ -'0';
//            token = Num;
//            return;
//        }
//
//        else if(token == '"'||token == '\'' ){
//            last_pos = str[current_str];
//            while(*src != 0 && *src != token ){
//                token_val = *src++;
//                if(token_val =='\\'){
//                    token_val = *src++;
//                    if(token =='n')
//                        token_val = '\n';
//                }//escape sequence(to be updated
//                if(token =='"')
//                    *str[current_str] = token_val;
//            }
//            src++;
//            if(token == '"')
//                token_val = (int)last_pos;
//            else
//                token = Num;
//            return ;
//        }

        else if(token =='/'){
            if(*src=='/')
                while(*src !=0 && *src !='\n')
                    src++;
            else{
                token = Div;
                return;
            }
        }//only '//' supported

        else if (token == '=') {
            // parse '==' and '='
            if (*src == '=') {
                src ++;
                token = Eq;
            }
            else
                token = Assign;
            return;
        }

        else if (token == '+') {
            // parse '+' and '++'
            if (*src == '+') {
                src ++;
                token = Inc;
            }
            else
                token = Add;
            return;
        }

        else if (token == '-') {
            // parse '-' and '--'
            if (*src == '-') {
                src ++;
                token = Dec;
            }
            else
                token = Sub;
            return;
        }

        else if (token == '!') {
            // parse '!='
            if (*src == '=') {
                src++;
                token = Ne;
            }
            return;
        }

        else if (token == '<') {
            // parse '<=', '<<' or '<'
            if (*src == '=') {
                src ++;
                token = Le;
            }
            else if (*src == '<') {
                src ++;
                token = Shl;
            }
            else
                token = Lt;
            return;
        }

        else if (token == '>') {
            // parse '>=', '>>' or '>'
            if (*src == '=') {
                src ++;
                token = Ge;
            }
            else if (*src == '>') {
                src ++;
                token = Shr;
            }
            else
                token = Gt;
            return;
        }

        else if (token == '|') {
            // parse '|' or '||'
            if (*src == '|') {
                src ++;
                token = Lor;
            }
            else
                token = Or;
            return;
        }

        else if (token == '&') {
            // parse '&' and '&&'
            if (*src == '&') {
                src ++;
                token = Lan;
            }
            else
                token = And;
            return;
        }

        else if (token == '^') {
            token = Xor;
            return;
        }

        else if (token == '%') {
            token = Mod;
            return;
        }

        else if (token == '*') {
            token = Mul;
            return;
        }

        else if (token == '[') {
            token = Brak;
            return;
        }

        else if (token == '?') {
            token = Cond;
            return;
        }

        else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':') {
            // directly return the character as token;
            return;
        }
    }
    return;
}


int main() {
    printf("Hello, World!\n");
    return 0;
}