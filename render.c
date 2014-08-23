#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "stack.h"
#include "attribule.h"
#include "render.h"
#define container_of(ptr, type, member) ({                      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})
typedef struct _Render _Render;
struct _Render{
    Render render;
    Stack *stack;
    Attribule attrib;
};

#ifdef __clang__
#define $(...) NULL
#else
#define $(ret,expr) ({ret $$ expr &$$;})
#endif

Render *newRender(void){
    _Render *_render = NULL;
    _render = malloc(sizeof(*_render));
    if(_render){
        _render->stack = newStack(20);
        _render->attrib = (Attribule){0,0,0,0,0,0};
        _render->render.rndr = $(int,(Render *render,Node *node){
            _Render *thiz = container_of(render,_Render,render);
            //printf("| <- %s \n",tS(node->type));
            if(node){
                switch(node->type){
                case TYPE_Block:
                    a_line(thiz->attrib,= 1);
                    break;
                default:
                    a_line(thiz->attrib,= 0);
                    break;
                };
                switch(node->type){
                case TYPE_H1 ... TYPE_H6:
                case TYPE_Code:
                case TYPE_String:
                    atrb(thiz->attrib,node->nodes[0].string);
                    return 0;
                case TYPE_Italic:
                    a_fg(thiz->attrib,mkfg(COLOR_Green));
                    break;
                case TYPE_Quote:
                    a_fg(thiz->attrib,mkfg(COLOR_Purple));
                    printf(" > ");
                    break;
                case TYPE_List:
                    a_fg(thiz->attrib,mkfg(COLOR_DartGreen));
                    printf("- ");
                    break;
                default:
                    break;
                }
            }
            return 1;
        });
        _render->render.destroy = $(void,(Render *render){
            _Render *thiz = container_of(render,_Render,render);
            delStack(&thiz->stack);
            free(thiz);
        });
        _render->render.push = $(void,(Render *render){
            _Render *thiz = container_of(render,_Render,render);
            pushStack(&thiz->stack,thiz->attrib);
        });
        _render->render.pop = $(void,(Render *render){
            _Render *thiz = container_of(render,_Render,render);
            thiz->attrib = popStack(thiz->stack);
            if(a_line(thiz->attrib)){
                //puts("| -> ");
                putchar('\n');
            }
        });
        return &_render->render;
    }
    return NULL;
}
