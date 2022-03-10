#ifndef __MENU_H__
#define __MENU_H__

#include <stdlib.h>
#include <stdbool.h>

static const char ARCH_ENTRENADOR_PPAL_MAYUS   = 'E', ARCH_ENTRENADOR_PPAL_MINUS   = 'e';
static const char ARCH_GIMNASIOS_MAYUS         = 'A', ARCH_GIMNASIOS_MINUS         = 'a';
static const char COMENZAR_PARTIDA_MAYUS       = 'I', COMENZAR_PARTIDA_MINUS       = 'i';
static const char SIMULAR_PARTIDA_MAYUS        = 'S', SIMULAR_PARTIDA_MINUS        = 's';

static const char INFO_ENTRENADOR_PPAL_MAYUS   = 'E', INFO_ENTRENADOR_PPAL_MINUS   = 'e';
static const char INFO_GIMNASIO_MAYUS          = 'G', INFO_GIMNASIO_MINUS          = 'g';
static const char REARMAR_EQUIPO_MAYUS         = 'C', REARMAR_EQUIPO_MINUS         = 'c';
static const char PROXIMA_BATALLA_MAYUS        = 'B', PROXIMA_BATALLA_MINUS        = 'b';

static const int FUERA_DE_RANGO = -1, PRIMERA_POSICION = 0;

static const char SI_MAYUS = 'Y',    SI_MINUS  = 'y',    NO_MAYUS = 'N',  NO_MINUS = 'n';

static const char SELECCIONAR_POKEMON_MAYUS    = 'G', SELECCIONAR_POKEMON_MINUS    = 'g';

static const char CONTINUAR_MAYUS              = 'N', CONTINUAR_MINUS              = 'n';

static const char PEDIR_PRESTADO_POKEMON_MAYUS = 'T', PEDIR_PRESTADO_POKEMON_MINUS = 't';

static const char REINTENTAR_GIMNASIO_MAYUS    = 'R', REINTENTAR_GIMNASIO_MINUS    = 'r';
static const char FINALIZAR_PARTIDA_MAYUS      = 'F', FINALIZAR_PARTIDA_MINUS      = 'f';


/*
 * Imprime por pantalla mensaje de introducción.
 */ 
void mostrar_intro();

//------------------------------------ MENU INICIO -------------------------------------

/*
 * Muestra por pantalla el MENU INICIO junto con sus opciones.
 * Devuelve la opción seleccionada por el usuario.
 */
char menu_inicio(bool juego_inicializado);

/*
 * Solicita al usuario la ruta del archivo donde se encuentra 
 * la información del entrenador principal a cargar.
 */
void pedir_archivo_entrenador_ppal(char* ruta_archivo);

/*
 * Solicita al usuario la ruta del archivo donde se encuentra 
 * la información de los gimnasios a cargar.
 */
void pedir_archivo_gimnasios(char* ruta_archivo);


//------------------------------------ MENU GIMNASIO -------------------------------------

/*
 * Muestra por pantalla el MENU GIMNASIOS junto con sus opciones.
 * Devuelve la opción (válida) seleccionada por el usuario.
 */
char menu_gimnasio();

/*
 * Muestra por pantalla la información del entrenador principal
 * junto a sus pokemones.
 */
void mostrar_info_entrenador_ppal(void* personaje);

/*
 * Muestra por pantalla la información del gimnasio:
 *      Nombre, lider, dificultad, id de batalla y total de entrenadores.
 */
void mostrar_info_gimnasio(void* gimnasio);

/*
 * Muestra por pantalla los dos conjuntos de pokemones que posee el
 * entrenador principal para poder realizar el rearmado del equipo.
 */ 
void mostrar_rearmar_equipo(void* personaje, int pos_apuntador_1, int pos_apuntador_2);

/*
 * Solicita al usuario las posiciones de los pokemones que desea 
 * retirar y añadir a la lista de pokemones de combate a través de 
 * una interfaz interactiva.
 */ 
void solicitar_posiciones_cambio(int* apuntador_1, int* apuntador_2, void* personaje);

/*
 * Solicita al usuario si desea continuar rearmando su equipo o si
 * quiere finalizar los cambios.
 */ 
char solicitar_continuar_cambios();

//------------------------------------ MENU BATALLA -------------------------------------

/*
 * Muestra por pantalla el MENU BATALLA junto con las caracteristicas de 
 * los dos pokemones que están batallando y el ganador en cuestión.
 */
void menu_batalla(void* pokemon_1, void* pokemon_2, int id_batalla, int ganador);


//------------------------------------ MENU VICTORIA -------------------------------------

/*
 * Muestra por pantalla el MENU VICTORIA junto con sus opciones.
 * Devuelve la opción (válida) seleccionada por el usuario.
 * En caso de que haya derrotado al ultimo gimnasio, se muestra 
 * por pantalla el mensaje de victoria de la partida.
 */
char menu_victoria(bool se_presto_pokemon, bool es_ultimo_gimnasio);

/*
 * Imprime por pantalla el mensaje final tras haber ganado 
 * la partida y convertirse en Maestro Pokemon.
 */ 
void mostrar_mensaje_victoria();

/*
 * Solicita al usuario que seleccione el pokemon que desea tomar 
 * prestado, de forma que se obtiene la posicion del mismo en la 
 * lista a la que pertenece.
 */ 
void solicitar_posicion_poke_prestado(void* pokemones_lider_rival, int* posicion );

//------------------------------------ MENU DERROTA -------------------------------------

/*
 * Muestra por pantalla el MENU DERROTA y solicita al usuario que 
 * seleccione una opción de todas las exhibidas.
 * Devuelve la letra de la opción válida elegida por el usuario.
 */
char menu_derrota();

/*
 * Imprime por pantalla el mensaje de derrota tras haber perdido 
 * contra un entrenador rival.
 */ 
void mostrar_mensaje_derrota();

/*
 * Imprime por pantalla el mensaje de derrita tras haber perdido 
 * contra un entrenador rival, anunciado el final de la partida.
 * Muestra información acerca del rival, gimnacion contra el que 
 * se perdió y cuantos gimnasios quedaban por vencer.
 */ 
void mensaje_derrota_simulacion(void* gimnasio, size_t gimnasios_restantes);


#endif /* __MENU_H__ */