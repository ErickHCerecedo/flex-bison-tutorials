Tarea 4 | Reconocedor sintáctico con flex y bisont

Pasos 1
flex scanner.flex

Paso 2 
bison -d scanner.y

Paso 3 (En mi caso agrege la direccion de las librerias )

gcc -o scanner lex.yy.c scanner.tab.c -L"C:\MinGW\GnuWin32\lib" -lfl

o bien 

gcc -o scanner lex.yy.c scanner.tab.c -lfl

Paso 4 | Para correr el ejecutable
./scanner t1.txt

Nota omitir el caracter '<' al correr.

Observaciones:

1.- Verificacion de tipos de datos en variables no lograda
2.- Duda en si guardar o no el valor de la variable en la tabla de simbolos