all: compilar valgrind

CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

ARCHIVOS_COMPILAR = \
aventura_pokemon.c \
Bibliotecas/TDA_heap/TDA_heap.c \
Bibliotecas/TDA_lista/TDA_lista.c \
Bibliotecas/BATALLAS/batallas.c \
Bibliotecas/Funciones_juego/funciones_juego.c \
Bibliotecas/Interaccion_usuario/interaccion_usuario.c 

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

compilar:
	gcc $(ARCHIVOS_COMPILAR) -o aventura_pokemon $(CFLAGS)

valgrind:
	valgrind $(VFLAGS) ./aventura_pokemon

ejecutar:
	./aventura_pokemon
