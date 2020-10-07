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

int is_varidecl(int a ){
    if(a == Id|| a==',')return 1;
    return 0;
}

int in_field(int a){
    if(a>= Assign && a<= Mod  ||  a=='['  || a==']'
       ||  a=='~'|| a==',' ||  a=='('  || a==')' )return 1;
    else return 0;
}


AST* parse(Token * tp)
{
    AST* p = makempty();
    p->type = Program;
    while(tp->type){
        tp = glo_decl(p,tp);
        tp++;
    }
    return p ;
}


Token * glo_decl(AST* p,Token* tp)
{
    p = insert(p,global_decl,0,1);
    if(is_type(tp->type)){
        if((tp+1)->type == '(')
        {
            p = insert(p,function_defined,0,1);
            tp = func_decl(p,tp);
        }
        else {
            p  = insert(p,variable_decl,0,1);
            tp = vari_decl(p,tp);
        }
    }
    else {
        printf("error! 'type' needed!");
        return 1;
    }
    return tp;
}
/*variable_decl ::= type  id { ',' id } ';'                             no initialize no decorate
function_decl ::= type id '(' parameter_decl ')' '{' body_decl '}'      to be added
 */
Token * func_decl(AST * p, Token * tp)
{
    p = insert(p,tp->type,tp->value,1);//insert type
    tp++;
    p = insert(p,tp->type,tp->value,0);//insert id
    tp++;
    if(tp->type == '('){
        p = insert(p,parameter_decl,0,0);//insert parameter-list
        tp = para_decl(p,tp); //ignore )
        if(tp->type == '{'){
            p = insert(p,body_decl,0,0);
            tp = bd_st(p,tp);
        }
        else printf("function body part needs '{}'");
    }
    return  tp;
}

Token * para_decl(AST* p,Token* tp)
{
        p = insert(p,tp->type,tp->value,1);//type
        tp++;
        p = insert(p,tp->type,tp->value,0);//id
        tp++;
        while(tp->type != ','){
            p = insert(p,tp->type,tp->value,0);//type
            tp++;
            p = insert(p,tp->type,tp->value,0);//id
            tp++;
        }
    return ++tp;
}

Token * bd_st(AST* p,Token* tp )
{
    if (is_type(tp->type)){
        p = insert(p,variable_decl,0,1);
        tp = vari_decl(p,tp);
        while(is_type(tp->type)){
            p = insert(p,variable_decl,0,0);
            tp = vari_decl(p,tp);
        }
    }
    if(tp->type == '{'){
        p = insert(p,stmt_st,0,0);
        tp = stmt(p,tp);
    }
    else printf("statement needs '{}'");
    return tp;
}

Token * stmt(AST*p ,Token* tp)
{//block statement

    //continue
    //emtpy_exp
    //break
    char flag = 1;
    while( (++tp)->type != '}'){
        if (tp->type == If){
            p = insert(p,ifst,0,flag);
            tp = if_st(p,tp);
            if(flag)flag--;
        }

        else if (tp->type == While) {
            p = insert(p,whilest,0,flag);
            tp = while_st(p,tp);
            if(flag)flag--;
        }

        else if (tp->type == For) {
            p = insert(p,forst,0,flag);
            tp = for_st(p,tp);
            if(flag)flag--;
        }

        else if (tp->type == Return) {
            p = insert(p,retexp,0,flag);
            tp = ret_exp(p,tp);
            if(flag)flag--;
        }

        else//exp
        {
            p = insert(p,exp,0,flag);
            tp = exp_st(p,tp);
            if(flag)flag--;
        }
    }
    return ++tp;//ignore }
}


/*
 * if_st -> '(' exp_st ')' [ '{' stmt '}' | exp_st ]
 */
Token * if_st(AST* p,Token * tp)
{
    tp+=2;
    p = insert(p,condition,0,1);
    tp = exp_st(p,tp);//condition
    if( (++tp)->type =='{'){
        p = insert(p,stmt_st, 0,0);
        tp= stmt(p,tp);
    }
    else {
        p = insert(p,exp,0,0);
        tp = exp_st(p,tp);
    }
    if(tp->type == Else){
        if((++tp)->type=='{'){
            p = insert(p,stmt_st,0,0);
            tp = stmt(p,tp);
        }
        else {
            p = insert(p,exp,0,0);
            tp = exp_st(p,tp);
        }
    }
    return tp;
}


Token * while_st(AST *p, Token* tp)
{
    tp+= 2;
    p = insert(p,condition,0,1);
    tp = exp_st(p,tp);
    if( (++tp)->type =='{'){
        p = insert(p,stmt_st, 0,0);
        tp= stmt(p,tp);
    }
    else {
        p = insert(p,exp,0,0);
        tp = exp_st(p,tp);
    }
    return tp;
}


Token * for_st(AST*p, Token * tp)
{
    tp+=2;
    p = insert(p,forfdo,0,1);
    tp = exp_st(p,tp);//please ignore ;
    p = insert(p,condition,0,0);
    tp = exp_st(p,tp);
    p = insert(p,fordo,0,0);
    tp = exp_st(p,tp);
    if(tp->type == '{'){
        p = insert(p,stmt_st,0,0);
        tp = stmt(p,tp);
    }
    else{
        p = insert(p,exp,0,0);
        tp = exp_st(p,tp);
    }
    return tp;
}


Token* ret_exp(AST *p, Token* tp)
{
    p = insert(p,exp,0,1);
    tp = exp_st(p,tp);  //ignore ;
    return tp;
}



Token* exp_st(AST*p,Token*tp)
{
    p = insert(p,tp->type,tp->value,1);
    tp++;
    while(tp->type != Id && in_field(tp->type)){
        p =insert(p,tp->type,tp->value,0);
        tp++;
    }

    return tp;
}



Token* vari_decl(AST*p, Token* tp){
    p = insert(p,p->type,p->value,1);
    while(is_varidecl(tp->type)){
        p = insert(p,p->type,p->value,0);
        tp++;
    }
    return tp;
}


