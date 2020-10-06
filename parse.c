//
// Created by 网安 胡洋 on 2020/10/6.
//
#include "astbuilder.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

AST* makempty(){
    AST* p;
    if(p = malloc(sizeof(AST))){
        p->type = 0;
        p->value = 0;
        p->fellow = 0;
        p->firstson = 0;
        return p;
    }
    else {
        printf("cant make empty ast");
        return 0;
    }
}


AST* insert(AST* p, int type, int value,int mode){// mode 0 for fellow, 1 for son
    AST* p1;
    if(p1 = malloc(sizeof(AST))){
        p1 ->type = type;
        p1->value = value;
        p1-> fellow = 0;
        p1-> firstson = 0;
        if(mode)p->firstson = p1;
        else p->fellow = p1;
    }
    else {
        printf("cant insert");
        return 0;
    }
}

int is_type(int tocheck){
    if(tocheck >=Char && tocheck<= Float)return 1;
    else return 0;
}
/*   EBNF in c
program ::= {global_declaration}+
*/
AST* parse(Token * tp,id* ip, char str[20][100]){
    AST* p = makempty();
    p->type = Program;
    while(tp->type){
        int();
        tp++;
    }
    return 0 ;
}

/*
global_declaration ::=  variable_decl | function_decl
 */
int glo_decl(Token* tp, id* ip, char str[20][100]){
    if(is_type(tp->type)){
        if((tp+2)->type == '(')
            func_decl();
        else vari_decl();
    }
    else {
        printf("error! 'type' needed!");
        return 1;
    }
}
/*variable_decl ::= type  id { ',' id } ';'                             no initialize no decorate
function_decl ::= type id '(' parameter_decl ')' '{' body_decl '}'      to be added
parameter_decl ::= type id {',' type id}
body_decl ::= {variable_decl}, {statement}
statement ::= non_empty_statement | empty_statement
non_empty_statement ::= if_statement | while_statement | '{' statement '}'
                     | 'return' expression | expression ';'
if_statement ::= 'if' '(' expression ')' statement ['else' non_empty_statement]
while_statement ::= 'while' '(' expression ')' non_empty_statement
 */
int func_decl(AST * p, Token * tp,char str[20][100]){
    p = insert(p,tp->type,tp->value,1);//insert type
    tp++;
    p = insert(p,tp->type,tp->value,0);//insert id
    tp++;
    if(tp->type == '('){
        p = insert(p,parameter_decl,0,0);//insert parameter-list
        tp = para_decl(p,tp);
        if(tp->type == '{')p = insert(p,body_decl, 0, 0);
    bd_decl();}
    return 0;
}

Token * para_decl(AST* p,Token* tp){
    do{
        p = insert(p,tp->type,tp->value,1);//type
        tp++;
        p = insert(p,tp->type,tp->value,0);//id
        tp++;
    }while(tp++ -> type == ',');
    return tp;
}

