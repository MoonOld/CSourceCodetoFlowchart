//
// Created by 网安 胡洋 on 2020/10/4.
//

#ifndef COMPLIER_ASTBULIDER_H
#define COMPLIER_ASTBULIDER_H




//tokens and classes defined here
enum{
    Num = 128, Fun, Sys, Glo, Loc, Id,// Glo for global, Loc for local, sys for
    Else, If, Char,Int,Float, Return, While,For,
    Assign, Lor, Lan, Or, Xor,And, Eq, Ne, Lt,Gt, Le, Ge, Shl, Shr,//Lt <  Le <=
    Add,Sub,Mul,Div, Mod,
    ary,Str,Brk
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
    int value;//id,string for index,num and char for value
};

typedef struct TOKENSTR stream;
struct TOKENSTR{
    Token * tp;
    id * ip;
    char * str[20][100];
};




typedef struct ast AST;
struct ast{
    int type; //token
    int value;
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
    Program,
    global_decl,
    function_defined,decl,
    parameter_decl,body_decl,variable_decl,stmt_st,
    stnoempty,stempty,ifst,whilest,forst,forfdo,fordo,retexp,exp,stop,
    condition,
    arry
};

AST* insert(AST* node,int type,int value,int mode);
int output();
AST* makempty();
int is_type(int tocheck);

void load(FILE * _fileI,char* file);
int stringcmp(char* a,char*b,int length);
int lex(char * src ,Token * tp, id * ip,char str[100]);
int lextest(Token * tp, id* ip,char str[20][100]);
#endif //COMPLIER_ASTBULIDER_H
/*先把主体的部分输出
 * 变量声明、表达式直接输出到分号
 * 函数、宏定义直接输出
 * 从int main开始（圆角矩形）顺序执行（矩形）
 * 遇到if、while、for（菱形）、else（if接的no）先输出复合语句块，continue回到循环、break执行语句块下一块、while、for的no接语句块下一块
 * 没有else 则no接到语句块下一个语句
 * */

