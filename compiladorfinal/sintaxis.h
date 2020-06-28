/** 
 * 
 *  FUNCIONES PARA ARBOL DE SINTAXIS
 *  @author ERICK DE JESUS HERNANDEZ CERECEDO - A01066428
 *  @author EVERARDO BECERRIL - A01552016
 * 
 * 
 **/




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simboltab.h"
#pragma once

variable * symbol_table;

/*
 * 
 *  TIPOS DE NODOS  
 *  
 */
enum node_tipos {                 
    IDENTIFIER_N = 1,
    VALUE_N,
    EXPR_N,
    READ_N,
    PRINT_N,
    SET_N,
    IF_N,
    IFELSE_N,
    WHILE_N,
    FOR_N,
    TERM_N,
    EXPRESSION_N
};




/*
 * 
 *  ESTRUCTURA DE NODO  
 *  
 */
struct treeNode {
    enum node_tipos nodetype;
    union node * node;
    struct treeNode * next;
}typedef tree_node;




/*
 * 
 *  NODO ID  
 *  
 */
struct idNode {
    variable * symbol;
}typedef id_node;

/*
 * 
 *  NODO VALOR  
 *  
 */
struct valueNode{
    variable_value * val;
}typedef value_node;

/*
 * 
 *  NODO READ  
 *  
 */
struct readNode {
    tree_node * id;
}typedef read_node;

/*
 * 
 *  NODO PRINT  
 *  
 */
struct printNode {
    tree_node * expr;
}typedef print_node;

/*
 * 
 *  NODO SET  
 *  
 */
struct setNode {
    tree_node * id;
    tree_node * expr;
}typedef set_node;

/*
 * 
 *  NODO EXPR  
 *  
 */
struct exprNode {
    int operation;
    tree_node * expr;
    tree_node * term;
}typedef expr_node;

/*
 * 
 *  NODO TERM  
 *  
 */
struct termNode {
    int operation;
    tree_node * term;
    tree_node * factor;
}typedef term_node;

/*
 * 
 *  NODO EXPRESSION  
 *  
 */
struct expressionNode {
    int condition;
    tree_node * left;
    tree_node * right;
}typedef expression_node;

/*
 * 
 *  NODO IF  
 *  
 */
struct ifNode {
    tree_node * condition;
    tree_node * statement;
}typedef if_node;

/*
 * 
 *  NODO IFELSE  
 *  
 */
struct ifElseNode{
    tree_node * condition;
    tree_node * if_statement;
    tree_node * else_statement;
}typedef if_else_node;

/*
 * 
 *  NODO WHILE  
 *  
 */
struct whileNode{
    tree_node * condition;
    tree_node * statement;
}typedef while_node;

/*
 * 
 *  NODO FOR 
 *  
 */
struct forNode{
    tree_node * id;
    tree_node * id_value;
    tree_node * to;
    tree_node * step;
    tree_node * do_;
}typedef for_node;

/*
 * 
 *  NODO UNION  
 *  
 */
union node {
    id_node * id;
    value_node * value;
    read_node * read;
    print_node * print;
    set_node * set;
    expr_node* expr;
    term_node* term;
    expression_node* expression;
    if_node * if_;
    if_else_node * if_else;
    for_node * for_;
    while_node * while_;
} typedef instruction;

/* 
 * 
 *  PUNTERO A ARBOL DE SINTAXIS
 * 
 */
tree_node * syntax_tree;




/* 
 * 
 *  FUNCIONES PARA REDUCCION DE SINTAXIS EN EL ARBOL
 * 
 */
tree_node * reverse(tree_node *);
tree_node *getNewNode(int, union node *, tree_node *);
tree_node *getExprNode(enum tipos_operaciones, tree_node *, tree_node *);
tree_node *getTermNode(int, tree_node *, tree_node *);
tree_node *getExpressionNode(enum tipos_operaciones_2, tree_node *, tree_node *);
tree_node *getIfElseNode(tree_node *, tree_node *, tree_node *);
tree_node *getSetNode(tree_node *, tree_node *);
tree_node *getIfNode(tree_node *, tree_node *);
tree_node *getWhileNode(tree_node *, tree_node *);
tree_node *getReadNode(tree_node *);
tree_node *getPrintNode(tree_node *);
tree_node *getValueNode(variable_value *);
tree_node *getIdNode(variable *);
tree_node *getForNode( tree_node *, tree_node *, tree_node *, tree_node *, tree_node *);
void printSyntaxTree(tree_node *);




/* 
 * 
 *  FUNCIONES PARA EJECUTAR REDUCCION DE SINTAXIS EN EL ARBOL
 * 
 */
void execute(tree_node *t_head);
void executeRead(tree_node *t_head);
void executePrint(tree_node *t_head);
void executeSet(tree_node *t_head);
void executeIf(tree_node *t_head);
void executeIfElse(tree_node *t_head);
void executeWhile(tree_node *t_head);
void executeFor(tree_node *t_head);
variable_value *executeExpr(tree_node *t_head);
variable_value *executeTerm(tree_node *t_head);
variable_value *executeFactor(tree_node *t_head);
bool executeExpression(tree_node *t_head);
