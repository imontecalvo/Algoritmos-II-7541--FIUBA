all: compilar valgrind

all_mini: compilar_minipruebas valgrind_minipruebas


compilar:
	gcc abb.c mis_pruebas.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

compilar_minipruebas:
	gcc abb.c abb_minipruebas.c -o abb_minipruebas -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

valgrind_minipruebas:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb_minipruebas