/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y"

	#include <iostream>
	#include <fstream>

#line 54 "y.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ADD = 258,                     /* ADD  */
    ADDI = 259,                    /* ADDI  */
    SUB = 260,                     /* SUB  */
    SUBI = 261,                    /* SUBI  */
    AND = 262,                     /* AND  */
    ANDI = 263,                    /* ANDI  */
    OR = 264,                      /* OR  */
    ORI = 265,                     /* ORI  */
    SLL = 266,                     /* SLL  */
    SRL = 267,                     /* SRL  */
    NOR = 268,                     /* NOR  */
    SW = 269,                      /* SW  */
    LW = 270,                      /* LW  */
    BEQ = 271,                     /* BEQ  */
    BNEQ = 272,                    /* BNEQ  */
    J = 273,                       /* J  */
    REGISTER = 274,                /* REGISTER  */
    COMMA = 275,                   /* COMMA  */
    COLON = 276,                   /* COLON  */
    LPAREN = 277,                  /* LPAREN  */
    RPAREN = 278,                  /* RPAREN  */
    LABEL = 279,                   /* LABEL  */
    INT = 280,                     /* INT  */
    PUSH = 281,                    /* PUSH  */
    POP = 282                      /* POP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ADD 258
#define ADDI 259
#define SUB 260
#define SUBI 261
#define AND 262
#define ANDI 263
#define OR 264
#define ORI 265
#define SLL 266
#define SRL 267
#define NOR 268
#define SW 269
#define LW 270
#define BEQ 271
#define BNEQ 272
#define J 273
#define REGISTER 274
#define COMMA 275
#define COLON 276
#define LPAREN 277
#define RPAREN 278
#define LABEL 279
#define INT 280
#define PUSH 281
#define POP 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef std::string YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
