#ifndef __FUNCIONES_JUEGO_H__
#define __FUNCIONES_JUEGO_H__

#include <stdbool.h>
#include "../TDA_lista/TDA_lista.h"
#include "../TDA_heap/TDA_heap.h"

#define NOMBRE_MAX     25
#define POKENOMBRE_MAX 15
#define BATALLAS_MAX    5

typedef struct pokemon{
	char nombre[POKENOMBRE_MAX];
	int velocidad;
	int defensa;
	int ataque;
    int pokemejoras;
}pokemon_t;

typedef struct entrenador{
	char nombre[NOMBRE_MAX];
	lista_t* pokemones;
}entrenador_t;

typedef struct gimnasio{
	char nombre[NOMBRE_MAX];
	int dificultad;
	int id_batalla;
	char lider[NOMBRE_MAX];
	lista_t* entrenadores;
}gimnasio_t;

typedef struct personaje{
	char nombre[NOMBRE_MAX];
	lista_t* pokemon_para_combatir;
	lista_t* pokemon_obtenidos;
}personaje_t;

typedef struct juego{
    personaje_t* personaje_principal;
    heap_t* heap_gimnasios;
	int (*batallas[BATALLAS_MAX])(void*, void*);
    bool esta_terminado;

}juego_t;



/*
 * Crea la estructura del juego y todas las estructuras que lo forman
 * reservando la correspondiente memoria.
 * Si algo falla durante la reserva de memoria, devuelve NULL y se 
 * libera lo que corresponda.
 * Si no hay error, devuelve un puntero al juego creado.
 */ 
juego_t* crear_juego();

/*
 * Carga toda la información del personaje mediante la lectura
 * del archivo cuya ruta fue recibida por parametro.
 * Devuelve 0 si se pudo cargar correctamente la información (o 
 * parte de ella).
 * Devuelve -1 si no se pudo leer como mínimo el nombre del 
 * personaje y al menos un pokemon ya sea porque no se pudo acceder 
 * al archivo o el archivo no posee el formato correcto.
 * 
 * Lee hasta el final o hasta donde haya un error, si la información 
 * leida hasta el momento es suficiente, la conserva.
 */ 
int cargar_personaje(personaje_t* personaje, char* ruta_archivo);

/*
 * Carga toda la información de todos los gimnasios mediante la
 * lectura del archivo cuya ruta fue recibida por parametro y 
 * los guarda en un heap minimal de acuerdo a su dificultad.
 * Devuelve 0 si se pudo cargar correctamente la información (o 
 * parte de ella).
 * Devuelve -1 si no se pudo leer como mínimo un gimnasio completo
 * con toda su información válida y suficiente.
 * 
 * Lee hasta el final o hasta donde haya un error, si la información 
 * leida hasta el momento es suficiente, la conserva.
 */ 
int cargar_gimnasios(heap_t* heap_gimnasios, char* ruta_archivo);

/*
 * Lleva a cabo las batallas entre los pokemones de combate 
 * propios contra los pokemones de un entrenador rival.
 * Devuelve 0 si gana la batalla el personaje principal o
 * devuelve -1 si la gana el entrenador rival.
 */ 
int batallar_pokemones( personaje_t personaje, entrenador_t entrenador_rival, int id_batalla,
                        void (*funcion_visualizar_batalla)(void*, void*, int, int),
                        int  (*funcion_batalla)(void*, void*) );

/*
 * Recibido un pokemon, una posición y una lista, reemplaza 
 * el pokemon que se encontraba en dicha posición de la lista
 * por el pokemon recibido. 
 */ 
void mover_pokemon_a_combate(pokemon_t* pokemon_entrante, size_t posicion, lista_t* lista_pokemones_combate);

/*
 * Dada una lista de pokemones de un rival y una posición, 
 * toma prestado el pokemon que está en esa posicion de dicha
 * lista y lo añade al conjunto de pokemones obtenidos del 
 * personaje principal.
 */
int tomar_pokemon(lista_t* pokemones_propios, lista_t* pokemones_lider_rival, int posicion);

/*
 * Destruye el juego liberando correctamente la memoria que fue
 * reservada previamente.
 */ 
void destruir_juego(juego_t* juego);


#endif /* __FUNCIONES_JUEGO_H__ */