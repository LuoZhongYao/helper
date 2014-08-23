#ifndef __RENDER_H__
#define __RENDER_H__
#include "ast.h"
typedef struct Render Render;
struct Render{
    int  (*rndr)(Render *thiz,Node *node);
    void (*destroy)(Render *thiz);
    void (*pop)(Render *thiz);
    void (*push)(Render *thiz);
};
Render *newRender(void);
#endif
