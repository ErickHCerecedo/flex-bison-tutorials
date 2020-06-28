/************************************************************/
/*                                                          */
/*  FUNCIONES PARA ARBOL DE SINTAXIS                        */
/*  @author ERICK DE JESUS HERNANDEZ CERECEDO - A01066428   */
/*  @author EVERARDO BECERRIL - A01552016                   */
/*                                                          */
/************************************************************/

%option yylineno
%{
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include "compilador.tab.h"
    #include "simboltab.h"

    int integer_value(int);
    int float_value(int);
    int valor_id(int);
%}

 /********* RULES *********/
%%

 /**** ESPACIOS EN BLANCO ****/
[[:space:]]+

 /**** UN SOLO CARACTER OPERACION ****/
"+"								{return SUMA;}
"-"								{return RESTA;}
"*"								{return MULTIPLICACION;}
"/"								{return DIVISION;}
"="								{return IGUAL;}
"("								{return APARENTESIS;}
")"								{return CPARENTESIS;}
"{"								{return ALLAVE;}
"}"								{return CLLAVE;}
";"                             {return PUNTOYCOMA;}	
":"                             {return DOSPUNTOS;}	

 /**** OPERADORES DE COMPARACION ****/
"<"								{return MENOR;}
">"								{return MAYOR;}
"<="							{return MENORIGUAL;}
">="							{return MAYORIGUAL;}

 /**** PALABRAS RESERVADAS - TERMINALES ****/
"program"						{return PROGRAM;}
"var"							{return VARCHAR;}
"int"							{return INT_P;}
"float"							{return FLOAT_P;}
"set"							{return SET;}
"read"							{return READ;}
"print"							{return PRINT;}
"if"							{return IF;}
"ifelse"						{return IFELSE;}
"while"							{return WHILE;}
"for"							{return FOR;}
"step"							{return PASOS;}
"to"							{return TO;}
"do"							{return DO;}


 /**** NOMBRES Y NUMEROS ****/
[a-zA-Z]+                       {return valor_id(ID);}
[0-9]+                          {return integer_value(INTEGER);}
[0-9]+.[0-9]+                   {return float_value(FLOAT);}

.                               { perror("Mystery character \n"); } /* IGNORA PALABRAS NO RECONOCIDAS */


%%

int integer_value(int token) {
    yylval.value = getInt(atoi(yytext));
    return token;
}
int float_value(int token) {
    yylval.value = getFloat(atof(yytext));
    return token;
}
int valor_id(int token) {
    yylval.identifier = strdup(yytext);
    return token;
}

int yywrap(void) {}