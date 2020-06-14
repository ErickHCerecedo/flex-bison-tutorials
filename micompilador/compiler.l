/* RECONOCEDOR LEXICO DEL COMPILADOR */
/* @AUTHOR ERICK DE JESUS HERNANDEZ CERECEDO - A01066428
/* @AUTHOR EVERARDO BECERRIL 
%option noyywrap nodefault yylineno
%{
# include "compiler.h"
# include "compiler.c"
%}

/* float exponent */
EXP ([Ee][-+]?[0-9]+)

%%

 /**** UN SOLO CARACTER OPERACION - OPS ****/
"+"								|
"-"								|
"*"								|
"/"								|
"="								|
"{"								|
"}"								|
"("								|
")"								|
";"                             |	
":"                             { return yytext[0]; }

 /**** OPERADORES DE COMPARACION - CMP ****/
"<"								{ yylval.fn = 1; return CMP; }
">"								{ yylval.fn = 2; return CMP; }
"=="                            { yylval.fn = 3; return CMP; }
"<="							{ yylval.fn = 4; return CMP; }
">="							{ yylval.fn = 5; return CMP; }

 /**** PALABRAS RESERVADAS - TERMINALES ****/
"program"						{ return PROGRAM_T; }
"var"							{ return VAR_T;     }
"int"							{ return INT_T;     }
"float"							{ return FLOAT_T;   }
"fun"                           { return FUN_T;     }
"set"							{ return SET_T;     }
"read"							{ return READ_T;    }
"print"							{ return PRINT_T;   } /*BUILT-IN FUNCION*/
"return"                        { return RETURN_t;  }
"if"							{ return IF_T;      }
"ifelse"						{ return IFELSE_T;  }
"while"							{ return WHILE_T;   }
"for"							{ return FOR_T;     }
"step"							{ return STEP_T;    }
"to"							{ return TO_T;      }
"do"							{ return DO_T;      }

 /**** NOMBRES ****/
[a-zA-Z][a-zA-Z0-9]*            { yylval.s = lookup(yytext); return NAME; }
[0-9]+                          { yylval.d = atof(yytext);   return NUMBERI; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?                { yylval.d = atof(yytext);   return NUMBERF; }

 /**** EXTRAS ****/
"//".*
[ \t]                                               /* IGNORA ESPACION EN BLANCO */
\\\n                            { printf("c> "); }  /* IGNORA LINEA CONTINUA */

.                               { yyerror("Mystery character %c\n", *yytext); } /* IGNORA PALABRAS NO RECONOCIDAS */

%%