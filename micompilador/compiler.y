/* RECONOCEDOR SINTACTICO DEL COMPILADOR                        */
/* @AUTHOR ERICK DE JESUS HERNANDEZ CERECEDO - A01066428        */
/* @AUTHOR EVERARDO BECERRIL - A01552015                        */
%{
# include <stdio.h>
# include <stdlib.h>
//# include "compiler.h"
%}

%union {
    struct ast *a;
    float d;
    int i;
    struct symbol *s;       /* Apuntador a simbolo */
    struct symlist *sl;
    int fn;                 /* Apuntador a function */
}

/**** DECLARACION DE TOKENS ****/
%token <d>  NUMBERF
%token <i>  NUMBERI
%token <s>  NAME             
%token <fn> FUNC 
%token PROGRAM_T VAR_T INT_T    FLOAT_T FUN_T SET_T  READ_T PRINT_T 
%token RETURN_T  IF_T  IFELSE_T WHILE_T FOR_T STEP_T TO_T   DO_T

%nonassoc <fn> CMP
%right  '='
%left   '+' '-'
%left   '*' '/'
%nonassoc UMINUS

//%type <a>   prog stmt assig_stmt stmt_lst cmp_stmt if_stmt iter_stmt factor expr term expresion 
//%type <sl>  oparams

%start prog

%%

prog:           PROGRAM_T NAME '{' opt_decls opt_fun_decls '}' stmt {   
                                                                        printf("= %4.4g\n> ", eval($7));
                                                                        treefree($2);
                                                                    }
;

opt_decls:      decls
|               /* empty */
;

decls:          dec ';' decls
|               dec
;

dec:            VAR_T NAME ':' tipo     { $$ = newasgn($2, $4); }
;

tipo:           INT_T
|               FLOAT_T
;

opt_fun_decls:  fun_decls
|               /* empty */
;

fun_decls:      fun_decls fun_dec
|               fun_dec
;

fun_dec:        FUN_T NAME '(' oparams ')' ':' tipo '{' opt_decls '}' stmt
|               FUN_T NAME '(' oparams ')' ':' tipo ';'
;

oparams:        params
|               /* empty */
;

params:         param ',' params
|               param
;

param:          VAR_T NAME ':' tipo
;

stmt:           assig_stmt
|               if_stmt
|               iter_stmt
|               cmp_stmt
;

assig_stmt:     SET_T NAME expr ';'   
|               READ_T NAME ';'   
|               FUNC expr ';'
|               RETURN_T expr ';'
;

if_stmt:        IF_T '(' expresion ')' stmt
|               IFELSE_T '(' expresion ')' stmt stmt
;

iter_stmt:      WHILE_T '(' expresion ')' stmt
|               FOR_T SET_T NAME expr TO_T expr STEP_T expr DO_T stmt
;

cmp_stmt:       '{' '}'
|               '{' stmt_lst '}'
;

stmt_lst:       stmt 
|               stmt_lst stmt
;

expr:           expr '+' term
|               expr '-' term
|               term
;

term:           term '*' factor
|               term '/' factor
|               factor
;

factor:         '(' expr ')'
|               NAME     
|               NUMBERI      
|               NUMBERF
|               NAME '(' opt_exprs ')' 
;

opt_exprs:      expr_lst
|               /* empty */
;

expr_lst:       expr_lst ',' expr
|               expr
;

expresion:      expr CMP expr
|               expr '=' expr
;

%%