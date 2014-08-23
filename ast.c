#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "ast.h"
#include "render.h"

#define node_size(n)    (sizeof(Node) + (n) * sizeof(YYSTYPE))

Node *newNode(Type type,int cnt,...){
    Node *node = NULL;
    va_list args;
    node = calloc(1,node_size(cnt));
    if(node){
        node->type = type;
        node->cnt = cnt;
        va_start(args,cnt);
        for(int i = 0;i < cnt;i++){
            node->nodes[i] = va_arg(args,YYSTYPE);
        }
        va_end(args);
    }
    return node;
}

Node *insertNode(Node *dest,int cnt,...){
    Node *node = NULL;
    va_list args;
    if(!dest)
        return NULL;
    node = realloc(dest,node_size(dest->cnt + cnt));
    if(node){
        va_start(args,cnt);
        for(int i = 0;i < cnt;i++){
            node->nodes[node->cnt + i].node = va_arg(args,Node *);
        }
        va_end(args);
        node->cnt += cnt;
    }
    return node;
}

static void forNodeDrv(Node *node,Render *render){
    if(node){
        render->push(render);
        if(render->rndr(render,node)){
            for(int i = 0;i < node->cnt;i++){
                forNodeDrv(node->nodes[i].node,render);
            }
        }
        render->pop(render);
    }
}

void forNode(Node *node){
    Render *render = newRender();
    if(render){
        forNodeDrv(node,render);
        render->destroy(render);
    }
}
