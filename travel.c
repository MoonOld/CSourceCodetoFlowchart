//
// Created by 网安 胡洋 on 2020/10/8.
//


#include "header.h"
#include "stdio.h"
//put expression in the end
//just need to find exp order and note that how flow jumps


/*
 * the json object designed like below
 * {
 *      "shape": "diamond"/"rect"/oval
 *      "label": "if/while/for/else"+"exp"
 * }
 */



int travel(AST* p,FILE* file)
{
    if(p =findvari(p))
        putjson(p,file);
    if(p = findmain(p)){
        if(p = findvari(p))putjson(p,file);
        if((p = find(EXP)))putjson(p,file);
    }
    return 0;
}


int findson(AST *p,int token){
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

AST* putmain(){
    return 0;
}

AST * putvari(){

}

AST * putstmt(){

}

AST* putwhile(){

}

AST* putfor(){

}

AST * putif(){

}

AST* putelse(){

}

AST* putexp(){

}

