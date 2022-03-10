#include "funciones_juego.h"
#include "../BATALLAS/batallas.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LECTURA_PERSONAJE   "%[^\n]\n"
#define LECTURA_GIMNASIO    "%[^;];%i;%i\n"
#define LECTURA_ENTRENADOR  "%[^\n]\n"
#define LECTURA_POKEMON     "%[^;];%i;%i;%i\n"



static const int ERROR = -1, EXITO = 0;
const int ES_MENOR = -1, ES_MAYOR = 1;
const int ENTRENADORES_MIN = 1, POKEMONES_MIN = 1, POKEMONES_COMBATIENTES_MAX = 6;

const char CLAVE_POKEMON = 'P', CLAVE_LIDER = 'L', CLAVE_ENTRENADOR = 'E', CLAVE_GIMNASIO = 'G';
const int LEIDOS_POKEMON = 4, LEIDOS_ENTRENADOR = 1, LEIDOS_GIMNASIO = 3;

const int ID_BATALLA_MIN = 1, ID_BATALLA_MAX = 5;

static const int VICTORIA = 0, DERROTA = -1;
const int POKEMEJORAS_MAX = 63;

/*
 * Destruye a un pokemon liberando la memoria que se reservó.
 */
void destructor_pokemones(void* elemento){
	if(!elemento) return;
	free((pokemon_t*)elemento);
}

/*
 * Destruye a un entrenador liberando la memoria que se reservó.
 */
void destructor_entrenador(void* elemento){
    if(!elemento) return;
    
    lista_destruir( ((entrenador_t*)elemento)->pokemones );
    free(elemento);
}

/*
 * Destruye a un gimnasio liberando la memoria que se reservó.
 */
void destructor_gimnasio(void* elemento){
    if(!elemento) return;

    lista_destruir( ((gimnasio_t*)elemento)->entrenadores );
    free(elemento);
}

/*
 * Compara dos gimnasios de acuerdo a su dificultad.
 * Si el primer gimnasio posee menor dificultad, devuelve -1.
 * Si el segundo gimnasio posee menor dificultad o ambos 
 * tienen la misma, devuelve 1.
 */
int comparador_gimnasios( void* elemento_1, void* elemento_2){
    
    gimnasio_t gimnasio_1 = *(gimnasio_t*)elemento_1;
    gimnasio_t gimnasio_2 = *(gimnasio_t*)elemento_2;
    
    if( gimnasio_1.dificultad < gimnasio_2.dificultad ) return ES_MENOR;
    
    return ES_MAYOR;
}

/*
 * Destruye al personaje principal liberando la memoria que se reservó.
 */
void destruir_personaje(personaje_t* personaje){

	if(!personaje) return;

	lista_destruir(personaje->pokemon_para_combatir);
	lista_destruir(personaje->pokemon_obtenidos);

	free(personaje);
}

void destruir_juego(juego_t* juego){

    if(!juego) return;

    destruir_personaje(juego->personaje_principal);
    heap_destruir(juego->heap_gimnasios);
    
    free(juego);
}

/*
 * Inicializa el vector que contiene las funciones de batallas existentes.
 */ 
void cargar_batallas(int (*batallas[BATALLAS_MAX]) (void*, void*) ){

	batallas[0] = funcion_batalla_1;
	batallas[1] = funcion_batalla_2;
	batallas[2] = funcion_batalla_3;
	batallas[3] = funcion_batalla_4;
	batallas[4] = funcion_batalla_5;
}


//------------------------- INICIALIZAR JUEGO -------------------------


/*
 * Crea al personaje junto con los dos conjuntos de pokemones
 * reservando la memoria necesaria.
 * Si algo falla, devuelve NULL y se libera lo que corresponda.
 * Si no falla, se devuelve un puntero al personaje creado.
 */
personaje_t* crear_personaje_principal(){

    personaje_t* personaje = calloc(1, sizeof(personaje_t));
    if (!personaje) return NULL;

    personaje->pokemon_para_combatir = lista_crear(NULL);
    personaje->pokemon_obtenidos     = lista_crear(destructor_pokemones);

    if( (!personaje->pokemon_para_combatir) || (!personaje->pokemon_obtenidos) ){
        destruir_personaje(personaje);
        return NULL;
    }

    return personaje;
}

juego_t* crear_juego(){

    juego_t* juego_nuevo = calloc(1, sizeof(juego_t));
    if (!juego_nuevo) return NULL;

    juego_nuevo->personaje_principal = crear_personaje_principal();
    juego_nuevo->heap_gimnasios = heap_crear(comparador_gimnasios, destructor_gimnasio);
    
    if( (!juego_nuevo->personaje_principal) || (!juego_nuevo->heap_gimnasios) ){
        destruir_juego(juego_nuevo);
        return NULL;
    }

    cargar_batallas(juego_nuevo->batallas);

    juego_nuevo->esta_terminado = false;

    return juego_nuevo;
}

//------------------------- CARGAR DATOS -------------------------


/*
 * Recibe un puntero a un pokemon e inicializa sus campos 
 * usando los datos de un pokemon recibido por parametro.
 */ 
void inicializar_pokemon(pokemon_t* ptr_pokemon, pokemon_t pokemon){

	strcpy(ptr_pokemon->nombre, pokemon.nombre);
	ptr_pokemon->velocidad = pokemon.velocidad;
	ptr_pokemon->ataque    = pokemon.ataque;
	ptr_pokemon->defensa   = pokemon.defensa;
    ptr_pokemon->pokemejoras = 0;

}

/*
 * Lee los datos de un pokemon de un archivo y devuelve un
 * puntero a un pokemon con dichos datos inicializados. 
 * Devuelve NULL si:
 *   - No se logran leer los 4 atributos del pokemon
 *   - Falla la reserva en memoria para el pokemon.
 */
pokemon_t* obtener_pokemon(FILE* archivo){

    pokemon_t pokemon_leido;
    int leidos = fscanf(archivo, LECTURA_POKEMON ,  pokemon_leido.nombre, &pokemon_leido. velocidad, 
                                                   &pokemon_leido.ataque, &pokemon_leido.defensa   );

    if( leidos != LEIDOS_POKEMON )
        return NULL;

    pokemon_t* pokemon_actual = calloc(1, sizeof(pokemon_t));
    if(!pokemon_actual)
        return NULL;
    
    inicializar_pokemon(pokemon_actual, pokemon_leido);
    return pokemon_actual;
}

/*
 * Lee un pokemon del archivo y lo inserta en la o las listas correspondientes. 
 * Si se recibe una lista adicional se usa la función particular recibida 
 * por parametro para la inserción.
 * Si se recibe una sola lista, se usa 'lista_insertar'.
 * En caso de error en la reserva de memoria durante la creación del pokemon o 
 * en la incersion del mismo, se dará aviso mediante 'hay_error'.
 */  
void cargar_pokemon(FILE* archivo, bool* hay_error, lista_t* lista_pokemones, lista_t* lista_adicional, 
				   int (*insertar_pokemon)(pokemon_t*, lista_t*, lista_t*)){
	
	pokemon_t* pokemon_actual = obtener_pokemon(archivo);
			
	if (!pokemon_actual){
		*hay_error = true;
        return;
	}

    int salida = ERROR;

    if (!lista_adicional)
        salida = lista_insertar(lista_pokemones, pokemon_actual); 
    else
        salida = insertar_pokemon(pokemon_actual, lista_pokemones, lista_adicional);

    if (salida == ERROR){ 
        *hay_error = true;
        destructor_pokemones(pokemon_actual);
    }
}

/*
 * Lee los datos de un entrenador de un archivo y devuelve un
 * puntero a un entrenador con dichos datos inicializados. 
 * Devuelve NULL si:
 *   - No se logra realizar correctamente la lectura
 *   - Falla la reserva en memoria para el entrenador.
 */
entrenador_t* obtener_entrenador(FILE* archivo){

    char nombre_entrenador[NOMBRE_MAX];
    int leido = fscanf(archivo, LECTURA_ENTRENADOR, nombre_entrenador);
    if(leido != LEIDOS_ENTRENADOR)
        return NULL;

    lista_t* lista_pokemon = lista_crear(destructor_pokemones);
    if(!lista_pokemon)
        return NULL;
    
    entrenador_t* entrenador_actual = calloc(1,sizeof(entrenador_t));
    if(!entrenador_actual){
        free(lista_pokemon);
        return NULL;
    }

    strcpy(entrenador_actual->nombre, nombre_entrenador);
    entrenador_actual->pokemones = lista_pokemon;

    return entrenador_actual;
}

/*
 * Recibe un puntero a un gimnasio e inicializa sus campos.
 * En caso de que id batalla sea mayor al máximo (5), se le 
 * asigna el valor 5. En caso de que sea menor al mínimo (1), 
 * se le asigna 1.
 */ 
void inicializar_gimnasio(gimnasio_t* gimnasio_actual, gimnasio_t gimnasio_leido, lista_t* entrenadores){

    strcpy(gimnasio_actual->nombre, gimnasio_leido.nombre);
    gimnasio_actual->dificultad = gimnasio_leido.dificultad;
    gimnasio_actual->entrenadores = entrenadores;

    if( gimnasio_leido.id_batalla > ID_BATALLA_MAX )
        gimnasio_actual->id_batalla = ID_BATALLA_MAX;

    else if ( gimnasio_leido.id_batalla < ID_BATALLA_MIN )
        gimnasio_actual->id_batalla = ID_BATALLA_MIN;

    else
        gimnasio_actual->id_batalla = gimnasio_leido.id_batalla;
}

/*
 * Lee los datos de un gimnasio de un archivo y devuelve un
 * puntero a un gimnasio con dichos datos inicializados. 
 * Devuelve NULL si:
 *   - No se logran leer los 3 campos del gimnasio.
 *   - Falla la reserva en memoria para el gimnasio.
 */
gimnasio_t* obtener_gimnasio(FILE* archivo){

    gimnasio_t gimnasio_leido;

    int leidos = fscanf(archivo, LECTURA_GIMNASIO, gimnasio_leido.nombre, &(gimnasio_leido.dificultad), 
                                                                         &(gimnasio_leido.id_batalla) );
    if(leidos != LEIDOS_GIMNASIO)
        return NULL;
    
    lista_t* lista_entrenadores = lista_crear(destructor_entrenador);
    if(!lista_entrenadores)
        return NULL;

    gimnasio_t* gimnasio_actual = calloc(1, sizeof(gimnasio_t));
    if(!gimnasio_actual){
        free(lista_entrenadores);
        return NULL;
    }
    
    inicializar_gimnasio(gimnasio_actual, gimnasio_leido, lista_entrenadores);

    return gimnasio_actual;
}


/*
 * Inserta un pokemon en el conjunto de pokemones obtenidos del
 * personaje principal. Ademas, si posee menos de 
 * POKEMONES_COMBATIENTES_MAX (6), añade el pokemon al conjunto
 * de pokemones de combate.
 */
int insertar_pokemon_personaje(pokemon_t* pokemon, lista_t* lista_1, lista_t* lista_2){
	
	int resultado = lista_insertar(lista_1, pokemon);
	if(resultado == ERROR)
		destructor_pokemones(pokemon);

	else if( lista_elementos(lista_2) < POKEMONES_COMBATIENTES_MAX ){
		resultado = lista_insertar(lista_2, pokemon);

		if(resultado == ERROR)
			lista_borrar(lista_1);
	}

	return resultado;
}

int cargar_personaje(personaje_t* personaje, char* ruta_archivo){

	if(!personaje || !ruta_archivo) return ERROR;

	FILE* archivo_pj = fopen(ruta_archivo,"r");
	if(!archivo_pj){
		return ERROR;
	}

	bool hay_error = false;
	char clave;
	int leidos = fscanf(archivo_pj, " %c;", &clave);
    
	if(clave != CLAVE_ENTRENADOR){
		fclose(archivo_pj);
		return ERROR;
	}
	
	fscanf(archivo_pj, LECTURA_PERSONAJE, personaje->nombre);
	leidos = fscanf(archivo_pj, "%c;", &clave);

	while((clave == CLAVE_POKEMON) && (leidos == 1) && !hay_error){
		cargar_pokemon(archivo_pj, &hay_error, personaje->pokemon_obtenidos, 
					   personaje->pokemon_para_combatir, insertar_pokemon_personaje);
		leidos = fscanf(archivo_pj, "%c;", &clave);
	}

	if( personaje->pokemon_obtenidos->cantidad < POKEMONES_MIN ){
		fclose(archivo_pj);
		return ERROR;
	}

	fclose(archivo_pj);
	return EXITO;
}


/*
 * Lee y carga a un gimnasio toda su información:
 *          > Todos sus entrenadores válidos.
 *          > Los pokemones que posee c/u de sus entrenadores.
 * En caso de algún error, se dará aviso mediante 'hay_error'.
 */ 
void cargar_entrenadores(FILE* archivo_gimnasios, gimnasio_t* gimnasio_actual, char* clave, int* leido, bool* hay_error){
	
    while( (*clave == CLAVE_ENTRENADOR || *clave == CLAVE_LIDER) && (*leido == 1) && !(*hay_error)){

		if( (*clave == CLAVE_LIDER) && lista_elementos(gimnasio_actual->entrenadores) ){
			*hay_error = true;

		}else{
			entrenador_t* entrenador_actual = obtener_entrenador(archivo_gimnasios);
            if (*clave == CLAVE_LIDER)
                strcpy(gimnasio_actual->lider, entrenador_actual->nombre);
			
            *leido = fscanf(archivo_gimnasios, "%c;", clave);

			while( (*clave == CLAVE_POKEMON) && (*leido == 1) && !(*hay_error) && entrenador_actual){
				
                cargar_pokemon(archivo_gimnasios, hay_error, entrenador_actual->pokemones, NULL, NULL);
				
                *leido = fscanf(archivo_gimnasios, "%c;", clave);
				
			}

			if( (!entrenador_actual || (lista_elementos(entrenador_actual->pokemones) < POKEMONES_MIN)) ||
				(lista_insertar(gimnasio_actual->entrenadores, entrenador_actual) == ERROR ) ){
                    
                    destructor_entrenador(entrenador_actual);
				    *hay_error = true;
            }
		}
	}
}

int cargar_gimnasios(heap_t* heap_gimnasios, char* ruta_archivo){

	if(!heap_gimnasios || !ruta_archivo) return ERROR;

    FILE* archivo_gimnasios = fopen(ruta_archivo, "r");
    if (!archivo_gimnasios){
        return ERROR;
	}
   
    bool hay_error = false;
    char clave;
    int leido = fscanf(archivo_gimnasios, "%c;", &clave);

    while( (clave == CLAVE_GIMNASIO) && (leido == 1) && !hay_error ){

        gimnasio_t* gimnasio_actual = obtener_gimnasio(archivo_gimnasios);
        leido = fscanf(archivo_gimnasios, "%c;", &clave);
        if(clave != CLAVE_LIDER) hay_error = true;

        cargar_entrenadores(archivo_gimnasios, gimnasio_actual, &clave, &leido, &hay_error);
   
        if( (lista_elementos(gimnasio_actual->entrenadores)) >= ENTRENADORES_MIN ){
            if (heap_insertar(heap_gimnasios, gimnasio_actual) == ERROR){
            	destructor_gimnasio(gimnasio_actual);
				hay_error = true;
			}

       }else{
            destructor_gimnasio(gimnasio_actual);
            hay_error = true;
        }
    }

	if(!heap_elementos(heap_gimnasios)){
 		fclose(archivo_gimnasios);
		return ERROR;
	}
    fclose(archivo_gimnasios);
	return EXITO;
}


//------------------------- BATALLA PRÓXIMO RIVAL -------------------------

/*
 * Aumenta un punto (+1) todos los atributos del pokemon recibido.
 * Sólo lo hace en caso de que haya recibido un número menor a 
 * POKEMEJORAS_MAX (63) bonificaciones.
 */ 
void hacer_pokemejora(pokemon_t* pokemon){

    if(pokemon->pokemejoras >= POKEMEJORAS_MAX) return;

	pokemon->velocidad ++;
	pokemon->ataque ++;
	pokemon->defensa ++;
}

int batallar_pokemones( personaje_t personaje, entrenador_t entrenador_rival, int id_batalla,
                        void (*funcion_visualizar_batalla)(void*, void*, int, int),
                        int  (*funcion_batalla)(void*, void*) ){


    size_t poke_rivales_vencidos = 0;

    lista_iterador_t* iterador_propios = lista_iterador_crear(personaje.pokemon_para_combatir);
    lista_iterador_t* iterador_rivales = lista_iterador_crear(entrenador_rival.pokemones);

    while(  lista_iterador_tiene_siguiente(iterador_propios)    && 
            lista_iterador_tiene_siguiente(iterador_rivales)    && 
           (poke_rivales_vencidos < POKEMONES_COMBATIENTES_MAX)    ){
        
        pokemon_t* poke_actual_propio = lista_iterador_elemento_actual(iterador_propios);
        pokemon_t* poke_actual_rival  = lista_iterador_elemento_actual(iterador_rivales);
		
        int resultado = funcion_batalla(poke_actual_propio, poke_actual_rival);

        if(funcion_visualizar_batalla)
            funcion_visualizar_batalla(poke_actual_propio, poke_actual_rival, id_batalla, resultado);

        if ( resultado == GANO_PRIMERO ){
			hacer_pokemejora(poke_actual_propio);
			lista_iterador_avanzar(iterador_rivales);
            poke_rivales_vencidos ++;
		}else
			lista_iterador_avanzar(iterador_propios);
    }

    lista_iterador_destruir(iterador_propios);
    lista_iterador_destruir(iterador_rivales);

    if( (poke_rivales_vencidos == lista_elementos(entrenador_rival.pokemones)) || 
        (poke_rivales_vencidos == POKEMONES_COMBATIENTES_MAX))
        return VICTORIA;
    return DERROTA;
}


void mover_pokemon_a_combate(pokemon_t* pokemon_entrante, size_t posicion, lista_t* lista_pokemones_combate){

	if(!pokemon_entrante || !lista_pokemones_combate) return;

	lista_reemplazar_en_posicion(lista_pokemones_combate, pokemon_entrante , posicion);
}

int tomar_pokemon(lista_t* pokemones_propios, lista_t* pokemones_lider_rival, int posicion){

	pokemon_t* pokemon_prestado = calloc(1, sizeof(pokemon_t));
	*pokemon_prestado = *(pokemon_t*)lista_elemento_en_posicion(pokemones_lider_rival, (size_t)posicion);
	
	if(lista_insertar(pokemones_propios, pokemon_prestado) == ERROR)
		return ERROR;
	return EXITO;
}

