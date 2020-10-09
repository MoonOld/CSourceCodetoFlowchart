//
// Created by 网安 胡洋 on 2020/10/6.
//
#include "header.h"
#include "stdio.h"
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




AST* parse(Token * tp)
{
    AST* p = makempty();
    if(p){
        p->type = Program;
        while(tp->type)
            p = insert(p,global_decl,0,1);
            tp = glo_decl(p,tp);
    }
    return p ;
}


Token * glo_decl(AST* p,Token* tp)
{
    int flag =1;
    if(is_type(tp->type)){
        if((tp+1)->type == '(')
        {
            p = insert(p,function_defined,0,flag);
            tp = func_def(p,tp);
            if(flag)flag--;
        }
        else {
            p  = insert(p,variable_decl,0,flag);
            tp = vari_decl(p,tp);
            if(flag)flag--;
        }
    }
    else {
        printf("error! 'type' needed!");
        return 0;
    }
    return tp;
}


Token * func_def(AST * p, Token * tp)
{
    p = insert(p,tp->type,tp->value,1);//insert type
    tp++;
    p = insert(p,tp->type,tp->value,0);//insert id
    tp++;
    if(tp->type == '(')
    {
        p = insert(p,parameter_decl,0,0);//insert parameter-list
        tp = para_decl(p,tp);
        if( tp->type == '{' )
        {
            p = insert(p,body_decl,0,0);
            tp = bd_st(p,tp);
        }
        else {
            printf("function body part needs '{}'");
            return 0;
        }
    }
    return  tp;
}


Token * para_decl(AST* p,Token* tp)
{
        p = insert(p,tp->type,tp->value,1);//type
        tp++;
        p = insert(p,tp->type,tp->value,0);//id
        tp++;
        while(tp->type == ','){
            p = insert(p,tp->type,tp->value,0);//type
            tp++;
            p = insert(p,tp->type,tp->value,0);//id
            tp++;
        }
    return ++tp;//ignore )
}

Token * bd_st(AST* p,Token* tp )
{
    tp = stmt(p,tp);
    return tp;
}

Token * stmt(AST*p ,Token* tp)
{

    //emtpy_exp
    //break
    char flag = 1;
    while( tp->type != '}'){
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

        else if (tp->type == For){
            p = insert(p,forst,0,flag);
            tp = for_st(p,tp);
            if(flag)flag--;
        }

        else if (tp->type == Return){
            p = insert(p,retexp,0,flag);
            tp = ret_exp(p,tp);
            if(flag)flag--;
        }

        else if (tp->type == Continue){
            p = insert(p,ctn,0,flag);
            tp+=2; // ignore ;
            if(flag)flag--;
        }


        else if(tp->type == Break){
            p = insert(p,brk, 0, flag);
            tp+=2; //ignore ;
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



Token * if_st(AST* p,Token * tp)
{
    tp+=2;
    p = insert(p,condition,0,1);
    tp = exp_st(p,tp);//condition
    if( tp->type =='{'){
        p = insert(p,stmt_st, 0,0);
        tp= stmt(p,tp);
    }
    else {
        p = insert(p,exp,0,0);
        tp = exp_st(p,tp);
    }
    if(tp->type == Else){
        p = insert(p,elst,0,0);
        tp++;
        if(tp->type=='{'){
            tp = stmt(p,tp);
        }
        else {
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
    if( (tp)->type =='{'){
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
    tp = exp_st(p,tp);
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
    tp++;           //turn to exp part
    tp = exp_st(p,tp);
    return tp;
}



Token* exp_st(AST*p,Token*tp)
{
    int a=0;
    if(tp->type != ';'){
        p = insert(p,tp->type,tp->value,1);
        tp++;
        while(tp->type != Id && in_field(tp->type))
        {
            if(tp->type == '(')a++;
            else if(tp-> type ==')')
            {
                a--;
                if (a<0)
                    break;                              // to recognize paralist
            }
            p =insert(p,tp->type,tp->value,0);
            tp++;
        }
    }
    return ++tp; //ignore ; or )
}

Token* vari_decl(AST*p, Token* tp)
{
    p = insert(p,p->type,p->value,1);
    while(is_varidecl(tp->type))
    {
        p = insert(p,p->type,p->value,0);
        tp++;
    }
    return tp;
}

int is_type(int tocheck)
{
    if(tocheck >=Char && tocheck<= Float)return 1;
    else return 0;
}

int is_varidecl(int a )
{
    if(a == Id|| a==',')return 1;
    return 0;
}

int in_field(int a) //used in exp
{
    if(a>= Assign && a<= Mod  ||  a=='['  || a==']'         // [ ] for array
       ||  a=='~'|| a==',' ||  a=='('  || a==')' )return 1;
    else return 0;
}