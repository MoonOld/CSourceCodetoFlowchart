//
// Created by 网安 胡洋 on 2020/10/4.
//

#ifndef COMPLIER_ASTBULIDER_H
#define COMPLIER_ASTBULIDER_H
int astbuilder();
int insert();
int output();
int makempty();


typedef struct ast AST;
struct ast{
    int type;
    int value;
    int string_end;
    AST* firstson;
    AST* fellow;
};
#endif //COMPLIER_ASTBULIDER_H
