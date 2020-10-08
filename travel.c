//
// Created by 网安 胡洋 on 2020/10/8.
//


#include "header.h"
#include "stdio.h"

int travel(AST* p,FILE* file)
{
    vari(); //print glo vari
    mainfunc();
    return 0;
}


int find(AST *p,int token){
    if((p = p->firstson)->type == token){
        p->type = 0;                    //find only once
        return 1;
    }
    else{
        while(p){
            if(p->type == token){
                p ->type = 0;
                return 1;
            }
            p = p->fellow;
        }
        return 0;
    }
}

int putexp(AST*p, FILE* file){



    return 0;
}
