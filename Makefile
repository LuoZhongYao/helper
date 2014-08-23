all: help test

CFLAGS := --std=gnu99 -g -Wall

help : help.yy.o help.tab.o ast.o stack.o render.o
	@gcc $^ -o $@ $(CFLAGS)

%.yy.c : %.l
	@flex -o $@ $^

%.tab.c %.tab.h : %.y
	@bison $^ -d -v

%.o : %.c
	@gcc -c $< -o $@ $(CFLAGS)

test:
	@./help < test.md

clean:
	@-rm -f help.yy.c help help.tab.[ch] *.o

render.o : render.c render.h stack.h ast.h attribule.h
ast.o : ast.c ast.h help.y render.h
stack.o : stack.c stack.h ast.h help.y
help.yy.o :  help.tab.h help.yy.c
help.tab.o : help.y ast.h
