//
// Created by 网安 胡洋 on 2020/10/6.
//
#include "astbuilder.h"
#include "stdio.h"
#include "string.h"
int putforms(Token * tp, id * ip,char str[20][100],FILE *file){
    while(1){
        while(tp->type != Int)tp++;
        if(tp->type)
        if(tp->type == Id && strcmp(ip[tp->value].name,"main")&& (tp+1)->type == '(' ){
            start();
            break;
        }
    }
    while(tp->type){
        if (is_if()){

        }
        else if (is_while()){

        }
        else if (is_for()){

        }
        else if(is_ret()){

        }
        else putline();

    }
    return 1;
}


















/*   EBNF in c
program ::= {global_declaration}+
*/
int parse(Token * tp,id* ip, char str[20][100],ast){
    while(tp->type){
        glo_decl(tp,ip,str);
        tp++;
    }
    return 1 ;
}

/*
global_declaration ::=  variable_decl | function_decl
variable_decl ::= type {'*'} id { ',' {'*'} id } ';'
function_decl ::= type {'*'} id '(' parameter_decl ')' '{' body_decl '}'      to be added
parameter_decl ::= type {'*'} id {',' type {'*'} id}
body_decl ::= {variable_decl}, {statement}
statement ::= non_empty_statement | empty_statement
non_empty_statement ::= if_statement | while_statement | '{' statement '}'
                     | 'return' expression | expression ';'
if_statement ::= 'if' '(' expression ')' statement ['else' non_empty_statement]
while_statement ::= 'while' '(' expression ')' non_empty_statement
 */
int glo_decl(Token* tp, id* ip, char str[20][100]){
    return 1;
}

