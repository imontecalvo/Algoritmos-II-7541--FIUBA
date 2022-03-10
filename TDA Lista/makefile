all: compilar valgrind

all_mini: compilar_minipruebas valgrind_minipruebas

compilar: 
	gcc lista.c mis_pruebas.c -o lista -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista

compilar_minipruebas: 
	gcc lista.c lista_minipruebas.c -o lista_minipruebas -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

valgrind_minipruebas:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_minipruebas