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




/**
 *  
 *  Funcion getString
 *  @param value
 * 
 **/
char * getString(variable_value *value){
    return (value->type == TIPO_INT)?"int":"float";
}



/**
 *  
 *  Funcion getInt
 *  @param newInt
 * 
 **/
variable_value* getInt(int newInt) {
    variable_value *newValue = (variable_value *)malloc(sizeof(variable_value));
    newValue->type = TIPO_INT;
    newValue->value.int_t = newInt;
    return newValue;
}




/**
 *  
 *  Funcion getFloat
 *  @param newFloat
 * 
 **/
variable_value* getFloat(float newFloat) {
    variable_value *newValue = (variable_value *)malloc(sizeof(variable_value));
    newValue->type = TIPO_FLOAT;
    newValue->value.float_t = newFloat;
    return newValue;
}




/**
 *  
 *  Funcion typesMatch
 *  @param v1
 *  @param v2
 * 
 **/
bool typesMatch(variable_value *v1, variable_value *v2){
    return (v1->type == v2->type);
}




/**
 *  
 *  Funcion valueEvaluation
 *  @param v1
 *  @param v2
 *  @param condition
 * 
 **/
bool valueEvaluation(variable_value *v1, variable_value *v2, int condition){
    if(!typesMatch(v1, v2)) {
        perror("Error: Tipos no compatibles.\n");
        exit(0);
        return false;
    }
    else{
        if(v1->type == TIPO_INT){
        int valor1 = v1->value.int_t;
        int valor2 = v2->value.int_t;
        switch(condition){
            case MENORIGUALQUE: return valor1 <= valor2;
                break;
            case MAYORIGUALQUE: return valor1 >= valor2;
                break;
            case IGUALA: return valor1 == valor2;
                break;
            case MENORQUE: return valor1 < valor2;
                break;
            case MAYORQUE: return valor1 > valor2;
                break;
            default: return false; break;
        }
        }
        if(v1->type == TIPO_FLOAT){
            float valor1 = v1->value.float_t;
            float valor2 = v2->value.float_t;
            switch(condition){
                case MAYORIGUALQUE: return valor1 >= valor2;
                    break;
                case IGUALA: return valor1 == valor2;
                    break;
                case MENORQUE: return valor1 < valor2;
                    break;
                case MAYORQUE: return valor1 > valor2;
                    break;
                case MENORIGUALQUE: return valor1 <= valor2;
                    break;
                default: return false; break;
            }
        }
    }
    
}




/**
 *  
 *  Funcion operationValue
 *  @param v1
 *  @param v2
 *  @param operation
 * 
 **/
variable_value * operationValue(variable_value *v1, variable_value *v2, int operation){
    if(!typesMatch(v1, v2)){

    }         
    return getInt(0);

    if(v1->type == TIPO_INT){
        int valor1 = v1->value.int_t;
        int valor2 = v2->value.int_t;
        int result;
        switch(operation){
            case SUMA_OP: result = valor1 + valor2;
                break;
            case RESTA_OP: result = valor1 - valor2;
                break;
            case MULTIPLICACION_OP: result = valor1 * valor2;
                break;
            case DIVISION_OP: result = valor1 / valor2;
                break;
            default: result = 0; break;
        }
        return getInt(result);
    }
    
    if(v1->type == TIPO_FLOAT){
        float valor1 = v1->value.float_t;
        float valor2 = v2->value.float_t;
        float result;
        switch(operation){
            case SUMA_OP: result = valor1 + valor2;
                break;
            case RESTA_OP: result = valor1 - valor2;
                break;
            case MULTIPLICACION_OP: result = valor1 * valor2;
                break;
            case DIVISION_OP: result = valor1 / valor2;
                break;
            default: result = 0; break;
        }
        return getFloat(result);
    }
}




/**
 *  
 *  Funcion printVal
 *  @param v
 * 
 **/
void printVal(variable_value * v){
    if(v->type ==TIPO_INT){
        int value = v->value.int_t;
        printf("%d", value);
    }
    if(v->type ==TIPO_FLOAT){
        float value = v->value.float_t;
        printf("%.2f", value);
    }
}




/**
 *  
 *  Funcion declareVariable
 *  @param head_ref
 *  @param id
 *  @param variableValue
 * 
 **/
void declareVariable(struct tableNode **head_ref, char* id, variable_value* variableValue){
    struct tableNode * new_symbol = (struct tableNode *)malloc(sizeof(struct tableNode));

    new_symbol->identifier = id;
    new_symbol->value = variableValue;
    new_symbol->next = (*head_ref);

    (*head_ref) = new_symbol;
}




/**
 *  
 *  Funcion getVariable
 *  @param head
 *  @param id
 * 
 **/
struct tableNode* getVariable(struct tableNode *head, char* id){
    if(head == NULL) return NULL;
    if(strcmp(head->identifier, id) == 0) return head;
    return getVariable(head->next, id);
}




/**
 *  
 *  Funcion setVariableValue
 *  @param id
 *  @param newValue
 * 
 **/
bool setVariableValue(variable* id, variable_value *newValue) {
    if(typesMatch(id->value, newValue)){
        if(!id){
            return false;
        }else {
            id->value = newValue;
            return true;
        }
    }
    return false;
} 




/**
 *  
 *  Funcion getVariableValue
 *  @param head
 *  @param id
 * 
 **/
variable_value *getVariableValue(struct tableNode *head, char *id){
    struct tableNode *p = getVariable(head, id);
    if(!p){
        printf("Error: %s no fue declarada.\n", id);
        return NULL; // default value
    }
    return p->value;
}




/**
 *  
 *  Funcion variableHasBeenDeclared
 *  @param head
 *  @param id
 * 
 **/
bool variableHasBeenDeclared(struct tableNode *head, char *id) {
    if(head == NULL) return false;
    if(strcmp(head->identifier, id) == 0) return true;
    return getVariable(head->next, id);
}




/**
 *  
 *  Funcion variableHasValueAssigned
 *  @param head
 *  @param id
 * 
 **/
bool variableHasValueAssigned(struct tableNode *head, char *id){
    if(head == NULL) return false;
    if(strcmp(head->identifier, id) == 0) return head->value != NULL;
    return getVariable(head->next, id);
}




/**
 *  
 *  Funcion getId
 *  @param var
 * 
 **/
char *getId(struct tableNode *var){
    return var->identifier;
}




/**
 *  
 *  Funcion printVariable
 *  @param var
 * 
 **/
void printVariable(struct tableNode * var) {
    variable_value * val = var->value;
    if(val->type == TIPO_INT){
        printf("var %s: %s = %d ", var->identifier, getString(val), val->value.int_t);
    }
    if(val->type == TIPO_FLOAT){
        printf("var %s: %s = %d ", var->identifier, getString(val), val->value.int_t);
    }
}




/**
 *  
 *  Funcion printSymbolTable
 *  @param head
 * 
 **/
void printSymbolTable(struct tableNode *head){
    printf("\tvariable  |\ttipo \t|\tvalor\n");
    variable_value *currentVariableValue = NULL;
    while(head != NULL) {
        currentVariableValue = head->value;

        if(currentVariableValue->type == TIPO_INT){
            printf("\t%s \t\tint \t", head->identifier);
            printf(" \t%d ", currentVariableValue->value.int_t);
        }

        if(currentVariableValue->type == TIPO_FLOAT) {
            printf("\t%s \t\tfloat \t", head->identifier);
            printf(" \t%.2f ", currentVariableValue->value.float_t);
        }

        printf("\n");
        head = head->next;
    }
}




/**
 *  
 *  Funcion freeSymbolTable
 *  @param head
 * 
 **/
void freeSymbolTable(struct tableNode **head){
    while((*head) != NULL){
        free((*head));
        (*head) = (*head)->next;
    }
}