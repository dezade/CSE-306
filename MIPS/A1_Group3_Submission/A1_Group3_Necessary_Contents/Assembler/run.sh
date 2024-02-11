#!/bin/bash
bison -d -y parser.y
g++ -w -c -o y.o y.tab.c
flex lexer.lex
g++ -w -c -o l.o lex.yy.c
g++ y.o l.o -lfl -o code.out
./code.out instructionsAssembly.txt CLIJMHOEBKFGDNAP