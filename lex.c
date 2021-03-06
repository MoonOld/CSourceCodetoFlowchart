//
// Created by 网安 胡洋 on 2020/10/8.
//

#include "header.h"
#include "stdio.h"

void load(FILE * _fileI,char* file){
    while( ( *file++ = fgetc(_fileI) ) != EOF);
}
int stringcmp(char* a,char*b,int length){
    while(*a++ == *b++ && (length--));
    if(length)
        return 0;
    else return 1;
}

int lex(char * src ,Token * tp, id * ip,char stro[20][100]){
    char *last_pos,*str=stro[0];
    int Hash,current_id,idnum,current_cpyid,current_cpystr,current_str=0;
    unsigned char buffer,strbuffer;

    while((buffer = *src++)){
        if ( buffer == '#')
        {
            while(*src != 0 && *src!='\n' )
                src++;
        }//macro and more to be updated

        else if((buffer >='a'&&buffer<='z') || (buffer>='A'&& buffer <= 'Z')
                ||buffer == '_'){
            last_pos = src-1;

            while((*src >='a'&& *src <= 'z') || (*src>='A'&&*src <= 'Z')||
                  *src == '_'||(*src >='0'&& *src<='9'))
                src++;//find this id

            current_id = 0;
            while((ip+current_id)->token){
                if(stringcmp( (ip +current_id)->name,last_pos,src-last_pos))
                {
                    tp->type=Id;
                    tp++->value = current_id;
                    break;
                }
                current_id++;
            }


            if((ip+current_id)->token == 0)
            {
                current_cpyid = 0;
                while (last_pos < src)
                    (ip + current_id)->name[current_cpyid++] = *last_pos++;
                (ip+current_id)->name[current_cpyid] = '\0';
                (ip+current_id)->token = Id;
                tp->type = Id;
                tp++->value = current_id;
            }
        }

        else if (buffer>='0' && buffer <='9'){
            buffer = buffer - '0';
            while(*src>='0' && *src <='9')
                buffer = buffer*10 + *src++ -'0';
            tp->value = buffer;
            tp++->type = Num;
        }

        else if(buffer == '"'||buffer == '\'' ){
            current_cpystr = 0;
            while(*src != 0 && *src != buffer ) //
            {
                strbuffer = *src++;
                if(strbuffer == '\\' ){
                    strbuffer = *src++;
                    if(strbuffer == 'n')
                        strbuffer = '\n';
                }//escape sequence(to be updated
                if(buffer =='"')//copy string
                    str[current_cpystr++] = strbuffer;
            }
            src++;
            if(buffer == '\'')//if its just a character
            {
                tp -> type = Num;
                tp++ -> value = strbuffer;
            }
            else
            {
                tp ->type =Str;
                tp++ -> value = current_str ;
                (str+current_str++)[current_cpystr] = '\0';
            }
        }

        else if(buffer =='/'){
            if(*src=='/')
                while(*src !=0 && *src !='\n')
                    src++;
            else if(*src =='*') {
                do{src++;}
                while(*src!= 0 && (*(src) == '*' && *(src+1) != '/'));
                src+=2;//jump over
            }
            else
                tp++ ->type = Div;
        }//annototaion

        else if (buffer == '=') {
            // parse '==' and '='
            if (*src == '=') {
                src ++;
                tp++ ->type = Eq;
            }
            else
                tp++ -> type =  Assign;
        }

        else if (buffer == '+'){
            // parse '+' and '++'
            if (*src == '+') {
                src++;
                tp++->type = Inc;
            }
            else
                tp++->type = Add;
        }

        else if (buffer == '-') {
            // parse '-' and '--'
            if (*src == '-') {
                src ++;
                tp++->type= Dec;
            }
            else
                tp++->type= Sub;
        }

        else if (buffer == '!') {
            // parse '!='
            if (*src == '=') {
                src++;
                tp++->type = Ne;
            }
        }

        else if (buffer == '<') {
            // parse '<=', '<<' or '<'
            if (*src == '=') {
                src ++;
                tp++->type = Le;
            }
            else if (*src == '<') {
                src ++;
                tp++->type = Shl;
            }
            else
                tp++->type = Lt;
        }

        else if (buffer == '>')
        {
            if (*src == '=') {
                src ++;
                tp++->type = Ge;//>=
            }
            else if (*src == '>') {
                src ++;
                tp++->type = Shr;//>>
            }
            else
                tp++->type = Gt;//>
        }

        else if (buffer == '|') {
            if (*src == '|') {
                src ++;
                tp++->type = Lor;
            }
            else
                tp++->type = Or;
        }

        else if (buffer == '&') {
            // parse '&' and '&&'
            if (*src == '&') {
                src ++;
                tp++->type = Lan;
            }
            else
                tp++->type = And;
        }

        else if (buffer == '^') {
            tp++->type = Xor;
        }

        else if (buffer == '%') {
            tp++->type = Mod;
        }

        else if (buffer == '*') {
            tp++->type = Mul;
        }

        else if (buffer == '[') {
            tp++->type = Brk;
        }

        else if (buffer == '~' || buffer == ';' || buffer == '{' || buffer == '}' || buffer == '('
                 || buffer == ')' || buffer == ']' || buffer == ',' || buffer == ':') {
            // directly return the character as token;
            tp++->type = buffer;
        }
    }
    return 0;
}


int lextest(Token * tp, id* ip,char str[20][100])
{
    while(tp->type)
    {
        if(tp->type == Num)
            printf("<Num, %d>", tp->type, tp->value);
        else if (tp->type == Id)
            printf("<Id,%s>",ip[tp->value].name);
        else if (tp->type == Str)
            printf("<Str,%s>",str[tp->value]);
        else
            printf("<%d>",tp->type);
        tp++;
    }
    return 0;
}
