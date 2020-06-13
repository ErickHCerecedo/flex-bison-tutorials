/* fb2-5 C cross-ref */
%option noyywrap nodefault yylineno
%x COMMENT
%x IFILE
/* some complex named patterns */
/* Universal Character Name */
UCN (\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})
/* float exponent */
EXP ([Ee][-+]?[0-9]+)
/* integer length */
ILEN ([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)