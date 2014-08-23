#ifndef __AST_H__
#define __AST_H__
typedef struct _Node Node;
#include "help.tab.h"
union YYSTYPE;
typedef enum {
    TYPE_Invalid,
    TYPE_String,
    TYPE_Italic,
    TYPE_Inline,
    TYPE_Line,
    TYPE_H1,
    TYPE_H2,
    TYPE_H3,
    TYPE_H4,
    TYPE_H5,
    TYPE_H6,
    TYPE_Quote,
    TYPE_List,
    TYPE_Code,
    TYPE_Block,
}Type;

#define tS(type)    ((const char *const []){\
        "Invalid","String","Italic","Inline","Line",\
        "H1","H2","H3","H4","H5","H6",\
        "Quote","List","Code","Block"})[type]

struct _Node{
    Type type;
    int cnt;
    YYSTYPE nodes[0];
};
Node *newNode(Type type,int cnt,...);
Node *insertNode(Node *dest,int cnt,...);
void forNode(Node *node);
#endif
