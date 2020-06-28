
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     READ = 259,
     PRINT = 260,
     IF = 261,
     IFELSE = 262,
     WHILE = 263,
     FOR = 264,
     TO = 265,
     DO = 266,
     PASOS = 267,
     SET = 268,
     VARCHAR = 269,
     INT_P = 270,
     FLOAT_P = 271,
     SUMA = 272,
     RESTA = 273,
     MULTIPLICACION = 274,
     DIVISION = 275,
     IGUAL = 276,
     MENOR = 277,
     MAYOR = 278,
     MENORIGUAL = 279,
     MAYORIGUAL = 280,
     ALLAVE = 281,
     CLLAVE = 282,
     APARENTESIS = 283,
     CPARENTESIS = 284,
     PUNTOYCOMA = 285,
     DOSPUNTOS = 286,
     INTEGER = 287,
     FLOAT = 288,
     ID = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 27 "compilador.y"

    int var_type;
    bool boolean;
    char *identifier;
    struct variableValue* value;
    struct treeNode* node;



/* Line 1676 of yacc.c  */
#line 96 "compilador.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


