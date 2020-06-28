/* DECLARACIONES PARA EL COMPILADOR                             */
/* @AUTHOR ERICK DE JESUS HERNANDEZ CERECEDO - A01066428        */
/* @AUTHOR EVERARDO BECERRIL - A01552015                        */

/**** 
 * 
 * 
 *      VARIABLES DESDE RECONOCEDOR LEXICO    
 * 
 * 
 * ****/
extern int yylineno;                    
void yyerror(char *s, ...);




/**** 
 * 
 * 
 * TABLA DE SIMBOLOS                     
 *      name    = nombre del simbolo
 *      valor   = valor del simbolo
 *      func    = Puntero a arbol
 *      symlist = Lista de argumentos (opcional)
 * 
 * 
 * ****/
struct symbol {                
    char *name;                                
    double value;
    struct ast *func;           
    struct symlist *syms;       
};




/**** 
 * 
 * 
 * TABLA DE SIMBOLOS DE TAMAÑO NHASH     
 * 
 * 
 * ****/
#define NHASH 9997
struct symbol symtab[NHASH];
struct symbol *lookup(char*);





/**** 
 * 
 * 
 * LISTA DE ARGUMENTOS                   
 *      symbo   = Simbolo
 *      symlist = Puntero a siguiente simbolo
 * 
 * ****/
struct symlist {
    struct symbol *sym;
    struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);




/**** 
 *      
 * 
 * TIPOS DE NODOS                        
 * 
 * 
 * + - * /
 * 0-7 comparison ops, bit coded 04 equal, 02 less, 01 greater
 * M Menos unitario
 * L Expreciones o Lista de declaraciones
 * I Declaracion IF
 * W Declaracion While
 * N Simbolo (Referencia a tabla)
 * = Asignacion
 * S Lista de simbolos (opcional)
 * F Funciones preestablecidas (Print)
 * C Funciones dinamicas
 * K Constantes
 * 
 * 
 * ****/



/**** 
 * 
 * 
 * Built-in functions                    
 * 
 * 
 * ****/
enum bifs {                 
    B_print = 1,
};




/**** 
 * 
 * 
 * ARBOL DE SINTAXIS Y NODOS
 *      nodetype    = Tipo de nodo
 *      l           = puntero hacia la izquierda
 *      r           = puntero hacia la derecha                  
 *      
 * 
 * ****/
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
};

/* Funciones preestablecidas (Print) - F */
struct fncall {             
    int nodetype;
    struct ast *l;
    enum bifs functype;
};

/* Funciones dinamicas - C */
struct ufncall {            
    int nodetype;           
    struct ast *l;          
    struct symbol *s;
};

/* Funciones Condicion - I (If), W (while) */
struct flow {
    int nodetype;           
    struct ast *cond;       
    struct ast *tl;         
    struct ast *el;         
};

/* Constantes - K */
struct numval {
    int nodetype;               
    double number;
};

/* Simbolo - N */
struct symref {
    int nodetype;              
    struct symbol *s;
};

/* Asignacion - = */
struct symasgn {
    int nodetype;               
    struct symbol *s;
    struct ast *v;              
};

/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

/* evaluate an AST */
double eval(struct ast *);

/* delete and free an AST */
void treefree(struct ast *);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);