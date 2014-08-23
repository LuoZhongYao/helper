%{
#include <stdio.h>
typedef struct _Node Node;
#include "help.tab.h"
#include "ast.h"
#define p                printf
#define color(c,fmt,...) p("\e[%dm"fmt"\e[0m",c,##__VA_ARGS__)
#define yyerror(msg)     color(31,"\n%s\n",msg)
#define mkyy(f,v) (YYSTYPE){.f = v}
#define mknode(v)   mkyy(node,v)
#define mkstring(v) mkyy(string,v)
#define mkword(v) newNode(TYPE_Word,1,mkyy(string,v))
extern int yylex(void);
/*

    | quote_item                    {$$ = $1;}
    | inline_list                   {$$ = $1;}


inline_list
    : inline_item                   {$$ = newNode(TYPE_Line,1,mknode($1));}
    | inline_list inline_item       {$$ = insertNode($1,1,$2);}
    ;

inline_item
    : italic                        {$$ = $1;}
    | string                        {$$ = $1;}
    ;

italic
    : '*' string '*'                {$$ = newNode(TYPE_Italic,1,mknode($2));}
    ;
    | '>' inline_list               {$$ = newNode(TYPE_Quote,1,mknode($2));}
*/
%}

%union{
    int  c;
    const char *string;
    Node *node;
}

%token <string>STRING H1 H2 H3 H4 H5 H6 LIST CODE
%type <node>block_list block_item code list quote 
%type <node>line inline_list inline_item italic string

%%
block
    :block_list                     {forNode($1);}

block_list
    : block_item                    {$$ = newNode(TYPE_Block,1,mknode($1));}
    | block_list block_item         {$$ = insertNode($1,1,$2);}
    ;

block_item
    : H1                            {$$ = newNode(TYPE_H1,1,mkstring($1));}
    | H2                            {$$ = newNode(TYPE_H2,1,mkstring($1));}
    | H3                            {$$ = newNode(TYPE_H3,1,mkstring($1));}
    | H4                            {$$ = newNode(TYPE_H4,1,mkstring($1));}
    | H5                            {$$ = newNode(TYPE_H5,1,mkstring($1));}
    | H6                            {$$ = newNode(TYPE_H6,1,mkstring($1));}
    | line                          {$$ = $1;}
    | quote                         {$$ = $1;}
    | list                          {$$ = $1;}
    | code                          {$$ = $1;}
    ;

code
    : CODE                          {$$ = newNode(TYPE_Code,1,$1);}
    ;

list
    : LIST line                     {$$ = newNode(TYPE_List,1,$2);}
    | LIST quote                    {$$ = newNode(TYPE_List,1,$2);}
    ;

quote     
    : '>' line                      {$$ = newNode(TYPE_Quote,1,mknode($2));}
    | '>' quote                     {$$ = newNode(TYPE_Quote,1,mknode($2));}
    ;

line
    : inline_list '\n'              {$$ = newNode(TYPE_Line,1,mknode($1));}
    ;

inline_list
    : inline_item                   {$$ = newNode(TYPE_Inline,1,mknode($1));}
    | inline_list inline_item       {$$ = insertNode($1,1,$2);}
    ;

inline_item
    : string                        {$$ = $1;}
    | italic                        {$$ = $1;}
    ;

italic
    : '*' string '*'                {$$ = newNode(TYPE_Italic,1,mknode($2));}
    ;

string 
    : STRING                        {$$ = newNode(TYPE_String,1,mkstring($1));}

%%
int main(void){
    yyparse();
}
