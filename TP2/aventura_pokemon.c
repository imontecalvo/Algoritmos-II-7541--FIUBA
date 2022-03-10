#include "Bibliotecas/Funciones_juego/funciones_juego.h"
#include "Bibliotecas/Interaccion_usuario/interaccion_usuario.h"
#include <string.h>

#include <stdio.h>


#define RUTA_MAX 50


const int ERROR = -1, EXITO = 0;
const int VICTORIA = 0;



//------------------------- CARGAR DATOS -------------------------

/* 
 * Reinicia los datos del personaje inicializándolos con los
 * valores por defecto. De esta forma, si el usuario se equivoca
 * de archivo de personaje, puede sobreescribir los datos y usar 
 * el último personaje que cargue.
 */ 
void inicializar_personaje(personaje_t* personaje){

    strcpy(personaje->nombre, "\0");
    lista_vaciar(personaje->pokemon_para_combatir);
    lista_vaciar(personaje->pokemon_obtenidos);
}

int manejar_carga_personaje(personaje_t* personaje){

    inicializar_personaje(personaje);
    char ruta_archivo[RUTA_MAX];
    pedir_archivo_entrenador_ppal(ruta_archivo);

    return cargar_personaje(personaje, ruta_archivo);
}

int manejar_carga_gimnasios(heap_t* heap_gimnasios){

    char ruta_archivo[RUTA_MAX];
    pedir_archivo_gimnasios(ruta_archivo);

    return cargar_gimnasios(heap_gimnasios, ruta_archivo);
}


//------------------------- OPCIONALES -------------------------

/*
 * Recibe un pokemon y una lista válidos.
 * Devuelve true si el pokemon NO se encuentra en la lista recibida.
 * En caso contrario, devuelve false.
 */
bool es_intercambio_valido(lista_t* pokemones_combate, pokemon_t* pokemon_a_chequear){
	
    if(!pokemones_combate || !pokemon_a_chequear) return false;

	bool hay_repetido = false;

	lista_iterador_t* iterador_pokemones = lista_iterador_crear(pokemones_combate);

	while ( lista_iterador_tiene_siguiente(iterador_pokemones) && !hay_repetido ){

		pokemon_t* pokemon_actual = (pokemon_t*)lista_iterador_elemento_actual(iterador_pokemones);

		if( pokemon_a_chequear == pokemon_actual )
			hay_repetido = true;
		else
			lista_iterador_avanzar(iterador_pokemones);
	}
	
	lista_iterador_destruir(iterador_pokemones);

	return !hay_repetido;
}

/*
 * Permite al usuario realizar el rearmado del equipo reemplazando 
 * uno o varios pokemones del conjunto de combate por pokemones del 
 * conjunto obtenidos.
 * El intercambio se realiza sólo si el pokemon que se desea añadir 
 * NO se encuentra ya en el conjunto pokemones de combate.
 */
void manejar_rearmado_equipo(personaje_t* personaje){
	
	char letra = NO_MAYUS;
	while(letra != SI_MAYUS && letra != SI_MINUS){
    	
        int apuntador_1 = PRIMERA_POSICION , apuntador_2 = FUERA_DE_RANGO;
	    mostrar_rearmar_equipo(personaje, apuntador_1, apuntador_2);

		pokemon_t* pokemon_entrante = NULL;
		
		do{
			solicitar_posiciones_cambio(&apuntador_1, &apuntador_2, personaje);
			pokemon_entrante = (pokemon_t*)lista_elemento_en_posicion(personaje->pokemon_obtenidos, (size_t)apuntador_2);
		
		}while( !es_intercambio_valido(personaje->pokemon_para_combatir, pokemon_entrante) );

		mover_pokemon_a_combate(pokemon_entrante, (size_t)apuntador_1, personaje->pokemon_para_combatir);
		
		mostrar_rearmar_equipo(personaje, FUERA_DE_RANGO, FUERA_DE_RANGO);
		
		letra = solicitar_continuar_cambios();
	}
}

/*
 * Permite al usuario seleccionar un pokemon del lider rival y 
 * añadirlo al conjunto de sus pokemones obtenidos.
 */
void pedir_pokemon_prestado(lista_t* pokemones_propios, lista_t* pokemones_lider_rival, bool* se_presto_pokemon){

    int posicion = PRIMERA_POSICION;
    solicitar_posicion_poke_prestado(pokemones_lider_rival, &posicion);

    int salida = tomar_pokemon(pokemones_propios, pokemones_lider_rival, posicion);

    if (salida == EXITO)
        *se_presto_pokemon = true;
}


//------------------------- RESULTADOS BATALLA -------------------------

/*
 * Devuelve true si el heap contiene un sólo gimnasio.
 * En caso contrario, devuelve false. 
 */
bool es_ultimo_gimnasio_del_heap(heap_t* heap_gimnasios){

    size_t gimnasios_restantes = heap_elementos(heap_gimnasios);

    return (gimnasios_restantes == 1);
}

/*
 * Muestra el menu de victoria contra un gimnasio y de acuerdo a 
 * la opción seleccionada por el usuario, realiza alguna acción:
 *      -Llama a pedir pokemon prestado.
 *      -Llama a rearmar equipo.
 *      -Continua con el siguiente gimnasio.
 * 
 * Si no queda más gimnasios, el juego cambia su estado a 'terminado'.
 */
void manejar_menu_victoria(juego_t* juego, lista_t* pokemones_lider_rival){
    
    char letra = 0;
    bool es_ultimo_gimnasio = es_ultimo_gimnasio_del_heap(juego->heap_gimnasios);
    bool se_presto_pokemon = false;
    
    while ( (letra != CONTINUAR_MAYUS) && (letra != CONTINUAR_MINUS) && !(juego->esta_terminado) ){

        letra = menu_victoria(se_presto_pokemon, es_ultimo_gimnasio);

        if ( (letra == PEDIR_PRESTADO_POKEMON_MAYUS) || (letra == PEDIR_PRESTADO_POKEMON_MINUS) )
            pedir_pokemon_prestado(juego->personaje_principal->pokemon_obtenidos, pokemones_lider_rival, &se_presto_pokemon);
        
        if ( (letra == REARMAR_EQUIPO_MAYUS) || (letra == REARMAR_EQUIPO_MINUS) )
            manejar_rearmado_equipo(juego->personaje_principal);
        
        if(es_ultimo_gimnasio) juego->esta_terminado = true;
    }
}

/*
 * Muestra el menu de derrota contra un entrenador y de acuerdo a 
 * la opción seleccionada por el usuario, realiza alguna acción:
 *      -Llama a rearmar equipo.
 *      -Reintenta combate.
 *      -Finaliza la partida, el juego cambia su estado a 'terminado'. 
 */
void manejar_menu_derrota(juego_t* juego){

    char letra = 0;

    while ( (letra != REINTENTAR_GIMNASIO_MAYUS) && (letra != REINTENTAR_GIMNASIO_MINUS) &&
            (letra != FINALIZAR_PARTIDA_MAYUS)   && (letra != FINALIZAR_PARTIDA_MINUS) ){
        
        letra = menu_derrota();

        if ( (letra == REARMAR_EQUIPO_MAYUS)      || (letra == REARMAR_EQUIPO_MINUS) )
            manejar_rearmado_equipo(juego->personaje_principal);
        
        if ( (letra == FINALIZAR_PARTIDA_MAYUS)   || (letra == FINALIZAR_PARTIDA_MINUS) ){
            mostrar_mensaje_derrota();
            juego->esta_terminado = true;
        }
    }

}


//------------------------- PARTIDA -------------------------

/*
 * Realiza todo el combate completo entre el personaje principal y 
 * todos los entrenadores de un gimnasio.
 * Si se logra derrotarlos a todos llama al menu victoria en caso 
 * de no estar simulado.
 * Si se sufre una derrota contra algún entrenador, se muestra el 
 * menu derrota si el juego no está simulado o un mensaje de derrota 
 * si sí lo está.
 */
void avanzar_proximo_rival(juego_t* juego, bool esta_simulado){

    gimnasio_t* gimnasio_actual = heap_obtener_raiz(juego->heap_gimnasios);
    entrenador_t* entrenador_actual = (entrenador_t*)lista_tope(gimnasio_actual->entrenadores);
    int id_batalla = gimnasio_actual->id_batalla;

    int resultado;
    if(!esta_simulado)
        resultado = batallar_pokemones( *juego->personaje_principal, *entrenador_actual, 
                                        id_batalla, menu_batalla, juego->batallas[id_batalla-1] );
    else
        resultado = batallar_pokemones( *juego->personaje_principal, *entrenador_actual, 
                                        id_batalla, NULL, juego->batallas[id_batalla-1] );
    if (resultado == VICTORIA){
        
        if( lista_elementos(gimnasio_actual->entrenadores) == 1){
            
            if(!esta_simulado){
                entrenador_t* lider = (entrenador_t*)lista_tope(gimnasio_actual->entrenadores);
                manejar_menu_victoria(juego, lider->pokemones);
            }
            lista_desapilar(gimnasio_actual->entrenadores);
            heap_extraer_raiz(juego->heap_gimnasios);
        
        }else
            lista_desapilar(gimnasio_actual->entrenadores);

    }else{
        if(!esta_simulado)
            manejar_menu_derrota(juego);
        else{
            juego->esta_terminado = true;
            mensaje_derrota_simulacion(gimnasio_actual, heap_elementos(juego->heap_gimnasios) );
        }
    }
}

/*
 * Muestra el menu gimnasio y de acuerdo a la opción seleccionada 
 * por el usuario, realiza alguna acción:
 *      -Muestra información del personaje principal.
 *      -Muestra información del gimnasio actual.
 *      -Llama a rearmar equipo.
 *      -Continua hacia el siguiente combate contra el próximo
 *       entrenador rival. 
 */
void jugar_partida(juego_t* juego){

    while( !juego->esta_terminado ){

        char letra = menu_gimnasio();

        if ( (letra == INFO_ENTRENADOR_PPAL_MAYUS) || (letra == INFO_ENTRENADOR_PPAL_MINUS) )
            mostrar_info_entrenador_ppal(juego->personaje_principal);

        else if ( (letra == INFO_GIMNASIO_MAYUS)   || (letra == INFO_GIMNASIO_MINUS) )
            mostrar_info_gimnasio( heap_obtener_raiz(juego->heap_gimnasios) );

        else if ( (letra == REARMAR_EQUIPO_MAYUS)  || (letra == REARMAR_EQUIPO_MINUS) )
            manejar_rearmado_equipo(juego->personaje_principal);

        else if ( (letra == PROXIMA_BATALLA_MAYUS) || (letra == PROXIMA_BATALLA_MINUS) ){
            avanzar_proximo_rival(juego, false);
        }
    }
}


/*
 * Se juega la partida de forma automática sin interacción con el 
 * usuario.
 * Si logra vencer a todos los entrenadores de todos los gimnasios, 
 * muestra el mensaje de victoria.
 * Si pierde en el camino, muestra el mensaje de derrota informando 
 * hasta dónde llegó y contra quién perdió.
 */
void simular_partida(juego_t* juego){

    while ( !juego->esta_terminado && heap_elementos(juego->heap_gimnasios) ){
        avanzar_proximo_rival(juego, true);
    }

    if( !heap_elementos(juego->heap_gimnasios)){
        juego->esta_terminado = true;
        mostrar_mensaje_victoria();
    }
}


//-------------------------

/*
 * Recibe el resultado de la carga del personaje principal y el de 
 * la carga de los gimnasios.
 * Devuelve true sólo si ambos resultados son EXITO (0)
 * En caso contrario, devuelve false.
 */
bool chequear_inicializacion(int carga_personaje, int carga_gimnasios){

    return ( (carga_personaje == EXITO) && (carga_gimnasios == EXITO) );
}


int main(){

    mostrar_intro();
    juego_t* juego_nuevo = crear_juego();
    if(!juego_nuevo) return ERROR;

    bool juego_inicializado = false;
    int salida_1 = ERROR, salida_2 = ERROR;
    while( !juego_nuevo->esta_terminado ){
        
        char letra = menu_inicio(juego_inicializado);

        if ( (letra == ARCH_ENTRENADOR_PPAL_MAYUS) || (letra == ARCH_ENTRENADOR_PPAL_MINUS) )
            salida_1 = manejar_carga_personaje(juego_nuevo->personaje_principal);
        
        if ( (letra == ARCH_GIMNASIOS_MAYUS)       || (letra == ARCH_GIMNASIOS_MINUS) )
            salida_2 = manejar_carga_gimnasios(juego_nuevo->heap_gimnasios);
        
        if ( (letra == COMENZAR_PARTIDA_MAYUS)     || (letra == COMENZAR_PARTIDA_MINUS) )
            jugar_partida(juego_nuevo);

        if ( (letra == SIMULAR_PARTIDA_MAYUS)      || (letra == SIMULAR_PARTIDA_MINUS) )
            simular_partida(juego_nuevo);

        juego_inicializado  = chequear_inicializacion(salida_1, salida_2);
    }
    
    destruir_juego(juego_nuevo);

    return EXITO;
}