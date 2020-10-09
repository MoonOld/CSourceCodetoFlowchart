//
// Created by 网安 胡洋 on 2020/10/8.
//


#include "header.h"
#include "stdio.h"
#include "string.h"
//put expression in the end
//just need to find exp order and note that how flow jumps


/*
 * the json object designed like below
 * {
 *      "shape": "diamond"/"rect"/oval
 *      "label": "if/while/for/else"+"exp"
 * }
 */



int travel(AST* p,FILE* file,id* ip,char str[20][100])
{
    p = p->firstson;
    while(p){
        if(p->type == variable_decl)
            putvari(p,file,ip,str);
        else if(p->type == function_defined)
            putmain(p,file,ip,str);
        p = p->fellow;
    }
    return 0;
}


int putmain(AST*p, FILE *file , id *ip, char str[20][100]){
    if(strcmp((ip+  (   (p->firstson )->fellow  )  ->value )->name,"main")){
        p = p->firstson;
        while(p){
            putexp(p,file,ip,str);//type
            p = p->fellow;
        }
    }
    return 0;
}


int putvari(AST* p, FILE *file, id*ip, char str[20][100]){
    p = p->firstson;
    putexp(p,file,ip,str);
    return 0;
}


int putstmt(AST*p){
    p = p->firstson;
    while(p){
        if(p->type == whilest)putwhile(p);
        else if(p->type == ifst){
            putif();
        }
        else if(p->type ==forst ){
            putfor();
        }
        else if(p->type == retexp){
            putret();
        }
        else if(p->type == brk){
            putbrk();
        }
        else if(p->type == ctn ){
            putctn();
        }
        else//p->type == exp
        {
            putexp();
        }
        p = p->fellow;
    }
}


int putwhile(AST *p){
    put(while,condition);


}


int putfor(){

}


int putif(){

}


int putelse(){

}


int putexp(AST *p, FILE* file,id*ip, char str[20][100]){
    p = p->firstson;
    while(p){


        p= p->fellow;
    }

    return 0;
}

