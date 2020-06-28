/** 
 * 
 *  FUNCIONES PARA TABLA DE SIMBOLOS
 *  @author ERICK DE JESUS HERNANDEZ CERECEDO - A01066428
 *  @author EVERARDO BECERRIL - A01552016
 * 
 * 
 **/




#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma once




/*
 * 
 *  NODOS EN OPERACIONES DE COMPARACION 
 *  
 */
enum tipos_operaciones_2 {                 
    MENORQUE = 150,
    MAYORQUE,
    MENORIGUALQUE,
    MAYORIGUALQUE,
    IGUALA
};




/*
 * 
 *  NODOS EN OPERACIONES ARITMETICAS
 *  
 */
enum tipos_operaciones {                 
    SUMA_OP = 110,
    RESTA_OP,
    MULTIPLICACION_OP,
    DIVISION_OP
};




/*
 * 
 *  NODO DE TIPO DE DATOS 
 *  
 */
enum tipos_number {                 
    TIPO_INT = 100,
    TIPO_FLOAT,
};




/*
 * 
 *  UNION QUE GUARDA UN FLOAT | ENTERO
 *  
 */
union valueOption{
    int int_t;
    float float_t;
};




/*
 * 
 *  ESTRUCTURA DE LA TABLA
 *  type  = Tipo de dato numerico
 *  value = Valor del simbolo
 */
struct variableValue {
    enum tipos_number type;
    union valueOption value;
}typedef variable_value;




/*
 * 
 *  NODOS DE LA TABLA
 *  identifier  = Simbolo de la tabla
 *  value       = Tipo y valos del dato
 *  *next       = Puntero a siguiente simbolo 
 */
struct tableNode {
    char *identifier;
    variable_value *value;
    struct tableNode *next;
} typedef variable;




/*
 * 
 *  FUNCIONES PARA TRABAJAR CON LA TABLA DE SIMBOLOS
 * 
 */




variable_value * getInt(int);
variable_value * getFloat(float);
variable_value * operationValue(variable_value *, variable_value *, int);
bool typesMatch(variable_value *, variable_value *);
bool valueEvaluation(variable_value *, variable_value *, int);
char * getString(variable_value *);
void printVal(variable_value *);
char *getId(struct tableNode *head);
void printSymbolTable(struct tableNode *head);
void freeSymbolTable(struct tableNode **head);
void printVariable(struct tableNode *head);
void declareVariable(struct tableNode **head, char *id, variable_value*);
bool setVariableValue(variable *, variable_value*);
bool variableHasBeenDeclared(struct tableNode *head, char *id);
bool variableHasValueAssigned(struct tableNode *head, char *id);
variable_value *getVariableValue(struct tableNode *head, char *id);
variable *getVariable(struct tableNode *head, char *id);
