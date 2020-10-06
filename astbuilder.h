//
// Created by 网安 胡洋 on 2020/10/4.
//

#ifndef COMPLIER_ASTBULIDER_H
#define COMPLIER_ASTBULIDER_H




//tokens and classes defined here
enum{
    Num = 128, Fun, Sys, Glo, Loc, Id,// Glo for global, Loc for local, sys for
    Char, Else, Enum, If, Int, Return, Sizeof, While,
    Assign, Cond, Lor, Lan, Or, Xor,And, Eq, Ne, Lt,Gt, Le, Ge, Shl, Shr,
    Add,Sub,Mul,Div, Mod, Inc, Dec,
    Brk,Str
};

typedef struct  ident id;
struct ident{
    int token;
    int hash;
    char  name[11];
};

typedef struct token Token;
struct token{
    int type;
    int value;//id for index,num and char for value
};


int astbuilder();
int insert();
int output();
int makempty();
void load(FILE * _fileI,char* file);
int stringcmp(char* a,char*b,int length);
int lex(char * src ,Token * tp, id * ip,char str[100]);
int lextest(Token * tp, id* ip,char str[20][100]);

typedef struct ast AST;
struct ast{
    int type;
    int value;
    int string_end;
    AST* firstson;
    AST* fellow;
};
/*  EBNFlist
program ::= {global_declaration}+
global_declaration ::= enum_decl | variable_decl | function_decl
enum_decl ::= 'enum' [id] '{' id ['=' 'num'] {',' id ['=' 'num'] '}'
variable_decl ::= type id { ',' id } ';'
function_decl ::= type id '(' parameter_decl ')' '{' body_decl '}'
parameter_decl ::= type id {',' type id}
body_decl ::= {variable_decl}, {statement}
statement ::= non_empty_statement | empty_statement
non_empty_statement ::= if_statement | while_statement|for_statement | '{' statement '}'
| 'return' expression | expression ';'
if_statement ::= 'if' '(' expression ')' statement ['else' non_empty_statement]
while_statement ::= 'while' '(' expression ')' non_empty_statement
for_statement ::= 'for' '(' {expression} ';' {expression} ';' ')' non_empty_statement

AST nodetype defined here */
enum {
    function_defined,decl,
    parameter_decl,body_decl,variable_decl,stmt,
    stnoempty,stempty,ifst,whilest,forst,retexp,exp,stop
};

#endif //COMPLIER_ASTBULIDER_H


