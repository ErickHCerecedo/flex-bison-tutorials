/************************************************************/
/*                                                          */
/*  FUNCIONES PARA ARBOL DE SINTAXIS                        */
/*  @author ERICK DE JESUS HERNANDEZ CERECEDO - A01066428   */
/*  @author EVERARDO BECERRIL - A01552016                   */
/*                                                          */
/************************************************************/

%{
    #include <stdio.h>
    #include <stdbool.h>
    #include "simboltab.h"
    #include "sintaxis.h"

    extern FILE * yyin;
    extern int yylineno;
    extern char * yytext;

    int yylex(void);
    void yyerror(char *);

    struct tableNode *table_head = NULL;
    struct treeNode *tree_head = NULL;

    void error_declaracion(char *id);
    void error_de_entrada(char *id);
%}

%union{
    int var_type;
    bool boolean;
    char *identifier;
    struct variableValue* value;
    struct treeNode* node;
}

%token PROGRAM READ PRINT IF IFELSE WHILE FOR TO DO PASOS
%token SET VARCHAR INT_P FLOAT_P SUMA RESTA MULTIPLICACION DIVISION
%token IGUAL MENOR MAYOR MENORIGUAL MAYORIGUAL ALLAVE CLLAVE APARENTESIS CPARENTESIS PUNTOYCOMA DOSPUNTOS
%token<value> INTEGER FLOAT
%token<identifier> ID
%type<value> tipo
%type<node> prog stmt assign_stmt stmt_lst cmp_stmt 
%type<node> if_stmt iter_stmt
%type<node> factor expr term expression


%start prog

/*GRAMATICA*/
%%

prog: PROGRAM ID ALLAVE opt_decls CLLAVE stmt {
    tree_head= $6;
};

opt_decls: 
    decls
    | /*nothing*/
;

decls: 
    dec PUNTOYCOMA decls 
    | dec
;

dec: VARCHAR ID DOSPUNTOS tipo {
    if(!variableHasBeenDeclared(table_head, $2)){
        declareVariable(&table_head, $2, $4); 
    }else {
        error_declaracion($2);
        YYERROR;
    }
};

tipo: 
    INT_P       {$$ = getInt(0);}
    | FLOAT_P   {$$ = getFloat(0.0);}
;

stmt: 
    assign_stmt {$$ = $1;}
    | if_stmt   {$$ = $1;}
    | iter_stmt {$$ = $1;}
    | cmp_stmt  {$$ = $1;}
;

assign_stmt:
    SET ID expr PUNTOYCOMA {
        if(!variableHasBeenDeclared(table_head, $2)){
            error_declaracion($2);
            YYERROR;
        }
        struct treeNode * id_node = getIdNode(getVariable(table_head, $2));
        $$ = getSetNode(id_node, $3);
    }
    | READ ID PUNTOYCOMA {
        if(!variableHasBeenDeclared(table_head, $2)){
            error_de_entrada($2);
            YYERROR;
        }
        struct treeNode * id_node = getIdNode(getVariable(table_head, $2));
        $$ = getReadNode(id_node);
        
    }
    | PRINT expr PUNTOYCOMA {
        $$ = getPrintNode($2);
    }
;

if_stmt: 
    IF APARENTESIS expression CPARENTESIS stmt    {
            $$ = getIfNode($3, reverse($5));
        }
    | IFELSE APARENTESIS expression CPARENTESIS stmt stmt {
            $$ = getIfElseNode($3, reverse($5), reverse($6));
        }
;

iter_stmt: 
    WHILE APARENTESIS expression CPARENTESIS stmt { $$ = getWhileNode($3, $5); }
    | FOR SET ID expr TO expression PASOS expr DO stmt { 
            struct treeNode * id_node = getIdNode(getVariable(table_head, $3));
            $$ = getForNode(id_node, $4, $6, $8, $10); 
        }
;

cmp_stmt: 
    ALLAVE CLLAVE { $$ = NULL;}
    | ALLAVE stmt_lst CLLAVE { $$ = $2;}
;

stmt_lst: 
    stmt            {$$ = $1;}
    | stmt_lst stmt {$2->next = $1;$$ = $2;}
;

expr: 
    expr SUMA term {$$=getExprNode(SUMA_OP, $1, $3);}
    | expr RESTA term {$$=getExprNode(RESTA_OP, $1, $3);}
    | term {$$=$1;}
;

term:
    term MULTIPLICACION factor {$$=getTermNode(MULTIPLICACION_OP, $1, $3);}
    | term DIVISION factor {$$ = $$ = getTermNode(DIVISION_OP, $1, $3);}
    | factor {$$=$1;}
;

factor: 
    APARENTESIS expr CPARENTESIS {$$ = reverse($2);}
    | ID {$$ = getIdNode(getVariable(table_head, $1));}
    | INTEGER {$$ = getValueNode($1);}
    | FLOAT {$$ = getValueNode($1);}
;

expression: 
    expr MENOR expr {$$=getExpressionNode(MENORQUE, $1, $3);}
    | expr MAYOR expr {$$=getExpressionNode(MAYORQUE, $1, $3);}
    | expr IGUAL expr {$$=getExpressionNode(IGUALA, $1, $3);}
    | expr MENORIGUAL expr {$$=getExpressionNode(MENORIGUALQUE, $1, $3);}
    | expr MAYORIGUAL expr {$$=getExpressionNode(MAYORIGUALQUE, $1, $3);}
;

%%


/********* EPILOGUE *********/

void error_declaracion(char *id){
    printf("Error: %s ya fue declarada o no fue encontrada\n", id);
    
}
void error_de_entrada(char *id){
    printf("Error: %s dato de entrada incompatible\n", id);
    
}

void yyerror(char *s) {
    fprintf(stdout, "%s en la linea %d\n", s, yylineno);
}

int main(int argc, char **argv) {
    if ((yyin = fopen(argv[1], "r")) == NULL) {
        printf("NO SE PUDO ABRIR EL ARCHIVO.\n");
        return 1;
    }
    int parse = yyparse();
    symbol_table = table_head;
    syntax_tree= reverse(tree_head);
    execute(syntax_tree);
    printf("\n");
    printf("Tabla de simbolos \n");
    printSymbolTable(symbol_table);
    return 0;
}