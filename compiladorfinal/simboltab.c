/** 
 * 
 *  FUNCIONES PARA ARBOL DE SINTAXIS
 *  @author ERICK DE JESUS HERNANDEZ CERECEDO - A01066428
 *  @author EVERARDO BECERRIL - A01552016
 * 
 * 
 */




#include "simboltab.h"
#include "sintaxis.h"



/* 
 * 
 *  FUNCIONES PARA REDUCCION DE SINTAXIS EN EL ARBOL
 * 
 */




/**
 *  
 *  Funcion getNewNode
 *  @param type
 *  @param instr
 *  @param nextTreeNode
 * 
 **/
tree_node * getNewNode(int type, instruction * instr, tree_node *nextTreeNode){
    struct treeNode * newTreeNode = (struct treeNode *)malloc(sizeof(tree_node));

    newTreeNode->nodetype = type;
    newTreeNode->node = instr;
    newTreeNode->next = nextTreeNode;

    return newTreeNode;
}




/**
 *  
 *  Funcion getWhileNode
 *  @param cond
 *  @param stmt
 * 
 **/
tree_node * getWhileNode(struct treeNode * cond, struct treeNode * stmt){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->while_ = (struct whileNode *)malloc(sizeof(struct whileNode));
    newInstr->while_->condition = NULL;
    newInstr->while_->condition = cond;
    newInstr->while_->statement = NULL;
    newInstr->while_->statement = stmt;

    return getNewNode(WHILE_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getIfElseNode
 *  @param cond
 *  @param i_stmt
 *  @param e_stmt
 * 
 **/
tree_node * getIfElseNode(struct treeNode * cond, struct treeNode * i_stmt, struct treeNode * e_stmt){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->if_else = (struct ifElseNode *)malloc(sizeof(struct ifElseNode));
    newInstr->if_else->condition = NULL;
    newInstr->if_else->condition = cond;
    newInstr->if_else->if_statement = NULL;
    newInstr->if_else->if_statement = i_stmt;
    newInstr->if_else->else_statement = NULL;
    newInstr->if_else->else_statement = e_stmt;

    return getNewNode(IFELSE_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getForNode
 *  @param var
 *  @param var_val
 *  @param t
 *  @param s
 *  @param d
 * 
 **/
tree_node * getForNode(struct treeNode * var, struct treeNode * var_val, struct treeNode * t, struct treeNode * s, struct treeNode * d){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->for_ = (struct forNode *)malloc(sizeof(struct forNode));
    newInstr->for_->id = NULL;
    newInstr->for_->id = var;
    newInstr->for_->id_value = NULL;
    newInstr->for_->id_value = var_val;
    newInstr->for_->to = NULL;
    newInstr->for_->to = t;
    newInstr->for_->step = NULL;
    newInstr->for_->step = s;
    newInstr->for_->do_ = NULL;
    newInstr->for_->do_ = d;

    return getNewNode(FOR_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getIfNode
 *  @param cond
 *  @param stmt
 * 
 **/
tree_node * getIfNode(struct treeNode * cond, struct treeNode * stmt){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->if_ = (struct ifNode *)malloc(sizeof(struct ifNode));
    newInstr->if_->condition = NULL;
    newInstr->if_->condition = cond;
    newInstr->if_->statement = NULL;
    newInstr->if_->statement = stmt;

    return getNewNode(IF_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getSetNode
 *  @param var
 *  @param e
 * 
 **/
tree_node * getSetNode(struct treeNode * var, struct treeNode * e){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->set = (struct setNode *)malloc(sizeof(struct setNode));
    newInstr->set->id = NULL;
    newInstr->set->id = var;
    newInstr->set->expr = NULL;
    newInstr->set->expr = e;

    return getNewNode(SET_N, newInstr, NULL);

}




/**
 *  
 *  Funcion getExprNode
 *  @param op
 *  @param e
 *  @param t
 * 
 **/
tree_node * getExprNode(enum tipos_operaciones op, struct treeNode * e, struct treeNode * t){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->expr = (struct exprNode *)malloc(sizeof(struct exprNode));
    newInstr->expr->operation = op;
    newInstr->expr->expr = NULL;
    newInstr->expr->expr = e;
    newInstr->expr->term = NULL;
    newInstr->expr->term = t;

    return getNewNode(EXPR_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getExpressionNode
 *  @param cond
 *  @param l
 *  @param r
 * 
 **/
tree_node * getExpressionNode(enum tipos_operaciones_2 cond, struct treeNode * l, struct treeNode * r){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->expression = (struct expressionNode *)malloc(sizeof(struct expressionNode));
    newInstr->expression->condition = cond;
    newInstr->expression->left = NULL;
    newInstr->expression->left = l;
    newInstr->expression->right = NULL;
    newInstr->expression->right = r;

    return getNewNode(EXPRESSION_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getTermNode
 *  @param op
 *  @param t
 *  @param f
 * 
 **/
tree_node * getTermNode(int op, struct treeNode * t, struct treeNode * f){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->term = (struct termNode *)malloc(sizeof(struct termNode));
    newInstr->term->operation = op;
    newInstr->term->term = NULL;
    newInstr->term->term = t;
    newInstr->term->factor = NULL;
    newInstr->term->factor = f;

    return getNewNode(TERM_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getPrintNode
 *  @param node
 * 
 **/
tree_node * getPrintNode(struct treeNode * node){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->print = (struct printNode *)malloc(sizeof(struct printNode));
    newInstr->print->expr = NULL;
    newInstr->print->expr = node;

    return getNewNode(PRINT_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getReadNode
 *  @param node
 * 
 **/
tree_node * getReadNode(struct treeNode * node){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->read = (struct readNode *)malloc(sizeof(struct readNode));
    newInstr->read->id = node;

    return getNewNode(READ_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getValueNode
 *  @param val
 * 
 **/
tree_node * getValueNode(variable_value * val){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->value = (struct valueNode *)malloc(sizeof(struct valueNode));
    newInstr->value->val = val;

    return getNewNode(VALUE_N, newInstr, NULL);
}




/**
 *  
 *  Funcion getIdNode
 *  @param var
 * 
 **/
tree_node * getIdNode(variable * var){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));
    
    newInstr->id = (struct idNode *)malloc(sizeof(struct idNode));
    newInstr->id->symbol = var;
    return getNewNode(IDENTIFIER_N, newInstr, NULL);
}




/**
 *  
 *  Funcion printSyntaxTree
 *  @param root
 * 
 **/
void printSyntaxTree(struct treeNode *root){
    if(root==NULL) {printf("\n"); return;}
    switch(root->nodetype) {
        case VALUE_N:
                printVal(root->node->value->val);
            break;
        case IDENTIFIER_N:
                printVariable(root->node->id->symbol);
            break;
        case READ_N:
                printf("Read:\n");
                printSyntaxTree(root->node->read->id);
            break;
        case SET_N:
                printf("Set:\n");
                printSyntaxTree(root->node->set->id);
                printSyntaxTree(root->node->set->expr);
            break;
        case PRINT_N:
                printf("Print:\n");
                printSyntaxTree(root->node->print->expr);
            break;
        case EXPR_N:
                printf("Expr:\n");
                printSyntaxTree(root->node->expr->expr);
                printf("-operation-\n");
                printSyntaxTree(root->node->expr->term);
            break;
        case TERM_N:
                printf("Term:\n");
                printSyntaxTree(root->node->term->term);
                printf("-operation-\n");
                printSyntaxTree(root->node->term->factor);
            break;
        case EXPRESSION_N:
                printf("Expression:\n");
                printSyntaxTree(root->node->expression->left);
                printf("- evaluation -\n");
                printSyntaxTree(root->node->expression->right);
            break;
        case IF_N:
                printf("If:\n");
                printSyntaxTree(root->node->if_->condition);
                printf("- stmt -");
                printSyntaxTree(root->node->if_->statement);
            break;
        case IFELSE_N:
                printf("If Else:\n");
                printSyntaxTree(root->node->if_else->condition);
                printf("- if stmt -");
                printSyntaxTree(root->node->if_else->if_statement);
                printf("- else stmt -");
                printSyntaxTree(root->node->if_else->else_statement);
            break;
        case WHILE_N:
                printf("While:\n");
                printSyntaxTree(root->node->while_->condition);
                printf("- stmt -");
                printSyntaxTree(root->node->while_->statement);
            break;
        case FOR_N:
                printf("For:\n");
                printSyntaxTree(root->node->for_->id);
                printSyntaxTree(root->node->for_->id_value);
                printf("- to -");
                printSyntaxTree(root->node->for_->to);
                printf("- step -");
                printSyntaxTree(root->node->for_->step);
                printf("- do -");
                printSyntaxTree(root->node->for_->do_);
            break;
        default: perror("ERROR: Palabra reservada desconocida\n"); exit(0); break;
    }
    printSyntaxTree(root->next);
}




/**
 *  
 *  Funcion reverse
 *  @param root
 * 
 **/
struct treeNode * reverse(struct treeNode * root){
    if (root == NULL || root->next == NULL)  return root; 
    struct treeNode * rest = reverse(root->next); 
    root->next->next = root;
    root->next = NULL; 
    return rest; 
}




/* 
 * 
 *  FUNCIONES PARA EJECUTAR REDUCCION DE SINTAXIS EN EL ARBOL
 * 
 */




/**
 *  
 *  Funcion executeFactor
 *  @param root
 * 
 **/
variable_value * executeFactor(struct treeNode * root) {
    if(root->nodetype == IDENTIFIER_N)
        return root->node->id->symbol->value;
    if(root->nodetype == VALUE_N)
        return root->node->value->val;
    return executeExpr(root);
}




/**
 *  
 *  Funcion executeTerm
 *  @param root
 * 
 **/
variable_value * executeTerm(struct treeNode * root){
    term_node * current = root->node->term;
    switch (current->operation){
        case MULTIPLICACION_OP:
                return operationValue(executeTerm(current->term), executeFactor(current->factor),  MULTIPLICACION_OP);
            break;
        case DIVISION_OP:
                return operationValue(executeTerm(current->term), executeFactor(current->factor),  DIVISION_OP);
            break;
        default:
            break;
    }
    return executeFactor(root);
}




/**
 *  
 *  Funcion executeExpr
 *  @param root
 * 
 **/
variable_value * executeExpr(struct treeNode * root){
    expr_node * expr = root->node->expr;
    switch (expr->operation){
        case SUMA_OP:
                return operationValue(executeExpr(expr->expr), executeTerm(expr->term),  SUMA_OP);
            break;
        case RESTA_OP:
                return operationValue(executeExpr(expr->expr), executeTerm(expr->term),  RESTA_OP);
            break;
        default:
            break;
    }
    return executeTerm(root);
}   




/**
 *  
 *  Funcion executeExpression
 *  @param root
 * 
 **/
bool executeExpression(struct treeNode * root){
    return valueEvaluation(
        executeExpr(root->node->expression->left), 
        executeExpr(root->node->expression->right), 
        root->node->expression->condition
    );
}




/**
 *  
 *  Funcion executeIf
 *  @param root
 * 
 **/
void executeIf(struct treeNode * root){
    if(executeExpression(root->node->if_->condition)){
        execute(root->node->if_->statement);
    }
}




/**
 *  
 *  Funcion executeIfElse
 *  @param root
 * 
 **/
void executeIfElse(struct treeNode * root){
    if(executeExpression(root->node->if_else->condition)){
        execute(root->node->if_else->if_statement);
    } else {
        execute(root->node->if_else->else_statement);
    }
}




/**
 *  
 *  Funcion executeWhile
 *  @param root
 * 
 **/
void executeWhile(struct treeNode * root){
    while(executeExpression(root->node->while_->condition)){
        execute(root->node->while_->statement);
    }
}




/**
 *  
 *  Funcion executeFor
 *  @param root
 * 
 **/
void executeFor(struct treeNode * root){
    tree_node * set = getSetNode(root->node->for_->id, root->node->for_->id_value);
    for(
        executeSet(set); 
        executeExpression(root->node->for_->to);
        setVariableValue(root->node->for_->id->node->id->symbol, executeExpr(root->node->for_->step))
    ){
        execute(root->node->for_->do_);
    }
}




/**
 *  
 *  Funcion executePrint
 *  @param root
 * 
 **/
void executePrint(struct treeNode * root){
    printf("= ");
    printVal(executeExpr(root));
    printf("\n");
}




/**
 *  
 *  Funcion executeRead
 *  @param root
 * 
 **/
void executeRead(struct treeNode * root){
    variable * var = root->node->id->symbol;
    variable_value * val = var->value;
    printf("read %s: ", var->identifier);
    if(val->type == TIPO_INT){
        int newValue;
        scanf(" %d", &newValue);
        val->value.int_t = newValue;
        if(!setVariableValue(var, val)){
            perror("Error: Tipo de variable incompatible, se esperaba int.\n");
            exit(0);
        }
    }
    if(val->type == TIPO_FLOAT){
        float newValue;
        scanf(" %f", &newValue);
        val->value.float_t = newValue;
        if(!setVariableValue(var, val)){
            perror("Error: Tipo de variable incompatible, se esperaba float.\n");
            exit(0);
        }
    }
}




/**
 *  
 *  Funcion executeSet
 *  @param root
 * 
 **/
void executeSet(struct treeNode * root){
    id_node * id = root->node->set->id->node->id;
    tree_node * expr = root->node->set->expr;
    variable * var = id->symbol;
    if(!setVariableValue(var, executeExpr(expr))){
        perror("Error: Tipo de variable incompatible.\n");
        exit(0);
    }
}




/**
 *  
 *  Funcion execute
 *  @param root
 * 
 **/
void execute(struct treeNode *root){
    if(root==NULL) {return;}
    switch(root->nodetype) {
        case READ_N:
                executeRead(root->node->read->id);
            break;
        case SET_N:
                executeSet(root);
            break;
        case PRINT_N:
                executePrint(root->node->print->expr);
            break;
        case IF_N:
                executeIf(root);
            break;
        case IFELSE_N:
                executeIfElse(root);
            break;
        case WHILE_N:
                executeWhile(root);
            break;
        case FOR_N:
                executeFor(root);
            break;
        default: perror("ERROR: Palabra reservada desconocida\n"); exit(0); break;
    }
    execute(root->next);
}
