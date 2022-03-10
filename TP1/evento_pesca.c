#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>

#define MAX_RUTA 25

const static int ERROR = -1, EXITO = 0;
const int CANT_CAMPOS = 4;


/*
 *	PRE: --- (El puntero al arrecife no debe cumplir con ninguna condición previa).
 *
 *	POST: Libera la memoria, apuntada por el puntero recibido, que había sido reservada previamente para guardar un arrecife.
 *		  
 *		  Aclaración: En caso de que el puntero recibido sea nulo, no ocurrirá nada. De lo contrario, también se liberará el espacio
 *		  en memoria dinámica (apuntado por el puntero pokemon_t* en caso de que NO sea nulo) el cual contiene un vector de pokemon.
 *				   
 */
void liberar_arrecife(arrecife_t* arrecife){

	if (arrecife){
		free(arrecife->pokemon);
	}

	free(arrecife);
}

/*
 *	PRE: --- (El puntero al acuario no debe cumplir con ninguna condición previa).
 *
 *	POST: Libera la memoria, apuntada por el puntero recibido, que había sido reservada previamente para guardar un acuario.
 *		  
 *		  Aclaración: En caso de que el puntero recibido sea nulo, no ocurrirá nada. De lo contrario, también se liberará el espacio
 *		  en memoria dinámica (apuntado por el puntero pokemon_t* en caso de que NO sea nulo) el cual contiene un vector de pokemon.
 *				   
 */
void liberar_acuario(acuario_t* acuario){

	if (acuario){
		free(acuario->pokemon);
	}

	free(acuario);
}


/*
 *	PRE: La dirección de memoria recibida (correspondiente al primer elemento del vector de pokemon) debe ser válida y el pokemon a 
 *		 agregar recibido debe estar correctamente inicializado.
 *
 *	POST: 
 *			> Si no falla el realloc:
 *				Reserva un espacio en memoria (en el heap) ampliando en una unidad el bloque actual de pokemones, guardando en la última
 *		  		posición el pokemon recibido. Finalmente, devuelve la dirección de memoria correspondiente al primer elemento del nuevo
 *		  		bloque reservado.
 *			
 *			> Si falla el realloc:
 *				Devuelve la misma dirección de memoria recibida, necesaria en un futuro para liberar dicho espacio en el heap, y además, 
 *				devuelve que hubo un error durante el realloc.
 *				   
 */
pokemon_t* agregar_pokemon (pokemon_t* ptr_pokemon, int cantidad_pokemones, pokemon_t pokemon_actual, bool* hay_error){

	pokemon_t* ptr_pokemon_aux = NULL;
	ptr_pokemon_aux = realloc( ptr_pokemon, (size_t)(cantidad_pokemones + 1) * sizeof(pokemon_t) );

	if (ptr_pokemon_aux == NULL){
		*hay_error = true;
		return ptr_pokemon;
	}

	ptr_pokemon_aux[cantidad_pokemones] = pokemon_actual;

	return ptr_pokemon_aux;
}


/*
 *	PRE: La dirección de memoria recibida (correspondiente al primer elemento del vector de pokemon) debe ser válida y la posición del
 *		 pokemon que se desea eliminar del vector de pokemones también debe ser correcta.
 *
 *	POST: 
 *			> Si no falla el realloc:
 *				Reemplaza el pokemon a eliminar por el último pokemon del vector y reserva un espacio en memoria (en el heap) reduciendo 
 *				en una unidad el bloque actual de pokemones. Finalmente, devuelve la dirección de memoria correspondiente al primer elemento 
 *				del nuevo bloque reservado.
 *			
 *			> Si falla el realloc:
 *				Devuelve la misma dirección de memoria recibida, necesaria en un futuro para liberar dicho espacio en el heap, y además, 
 *				devuelve que hubo un error durante el realloc.
 *				   
 */
pokemon_t* retirar_pokemon( pokemon_t* ptr_pokemon, int cantidad_pokemones, int posicion_pokemon, bool* hay_error){

	pokemon_t* ptr_pokemon_aux = NULL;

	ptr_pokemon[posicion_pokemon] = ptr_pokemon[cantidad_pokemones - 1];
	ptr_pokemon_aux = realloc( ptr_pokemon, (size_t)(cantidad_pokemones - 1) * sizeof(pokemon_t) );

	if ( (ptr_pokemon_aux == NULL) && (cantidad_pokemones > 1) ){
		*hay_error = true;
		return ptr_pokemon;
	}
	
	return ptr_pokemon_aux;
}


/*
 *	PRE: --- (La ruta recibida no debe cumplir con ninguna condición previa).
 *
 *	POST: 
 *			> Si el archivo no se encuentra (ruta no existente), o si falla el malloc al momento de reservar espacio en el heap para el 
 *			  arrecife, devuelve NULL.
 *			
 *			> Si el archivo se puede abrir correctamente y se logró reservar espacio en el heap sin inconvenientes, los pokemones
 *			  leidos del archivo se guardan en el vector de pokemones del arrecife hasta que se termine de leer el archivo o 
 *			  haya un fallo de lectura o de realloc en el transcurso. 
 *			  Finalmente, devuelve la dirección de memoria del arrecife del heap, cuyo campo 'pokemon_t* pokemon' apunta al vector cargado
 *			  con los pokemones que se pudieron leer, y su otro campo, 'cantidad_pokemon' se actualiza asignándole la cantidad de pokemones
 *			  leidos. 
 *			
 *			Aclaración: En el caso particular en que se pueda abrir el archivo y no falle el malloc inicial, pero SI falle el realloc 
 *			correspondiente a la lectura del PRIMER pokemon, se liberará el espacio reservado al arrecife y se devovlerá NULL, pues
 *			la lectura falló en el primer elemento y el arrecife quedará vacío.
 *				   
 */
arrecife_t* crear_arrecife (const char* ruta_archivo){


	FILE* archivo_arrecife = fopen(ruta_archivo, "r");

	if (!archivo_arrecife){
		printf("\nERROR: No se pudo acceder al archivo del arrecife :(\n");
		return NULL;
	}


	pokemon_t pokemon_leido;
	strcpy(pokemon_leido.especie, "\0");
	strcpy(pokemon_leido.color, "\0");
	pokemon_leido.peso = 0;
	pokemon_leido.velocidad = 0;

	bool hay_error = false;

	arrecife_t* ptr_arrecife = malloc( sizeof(arrecife_t) );
	
	if (ptr_arrecife == NULL){
		fclose(archivo_arrecife);
		return NULL;
	}
	
	ptr_arrecife->cantidad_pokemon = 0;
	ptr_arrecife->pokemon = NULL;
	
	int leidos = fscanf( archivo_arrecife, "%50[^;];%i;%i;%50[^\n]\n", pokemon_leido.especie, &(pokemon_leido.velocidad), 
																   &(pokemon_leido.peso)  , pokemon_leido.color );
	

	while ( (leidos == CANT_CAMPOS) && (!hay_error) ){

		ptr_arrecife->pokemon = agregar_pokemon( ptr_arrecife->pokemon, ptr_arrecife->cantidad_pokemon, pokemon_leido, &hay_error );
		(ptr_arrecife->cantidad_pokemon) ++;

		leidos = fscanf( archivo_arrecife, "%50[^;];%i;%i;%50[^\n]\n", pokemon_leido.especie, &(pokemon_leido.velocidad), 
																   &(pokemon_leido.peso)  , pokemon_leido.color );
	}
	
	if ( (ptr_arrecife->pokemon == NULL) ){
		
		fclose(archivo_arrecife);
		liberar_arrecife(ptr_arrecife);
		return NULL;
	} 

	fclose(archivo_arrecife);

	return ptr_arrecife;
}


/*
 *	PRE: ---
 *
 *	POST: 
 *			> Si falla malloc a la hora de reservar espacio en el heap para guardar el acuario, devuelve NULL.
 *			
 *			> Si malloc NO falla, se inicializa el arcuario y devuelve la dirección de memoria del mismo.
 *				   
 */
acuario_t* crear_acuario (){

	acuario_t* ptr_acuario = malloc( sizeof(acuario_t) );

	if (ptr_acuario == NULL){
		return NULL;
	}

	ptr_acuario->cantidad_pokemon = 0;
	ptr_acuario->pokemon = NULL;

	return ptr_acuario;
}


/*
 *	PRE: Debe recibir un puntero a un arrecife correctamente cargado, un puntero a una función de selección de pokemones válida y la cantidad
 *		 mínima (entero positivo) de pokemones que cumplan con cierta condición que se desea comprobar si hay en el vector de pokemones.
 *
 *	POST: 
 *			> True si hay suficientes pokemones en el vector (al que apunta pokemon_t* pokemon) que cumplan con la/s condición/es solicitadas. 
 *			
 *			> False si NO hay suficiente cantidad de pokemones con dichas caracteristicas en el vector de pokemones.
 *				   
 */
bool hay_suficientes_pokemones (arrecife_t* arrecife, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){

	int contador_pokemones = 0;

	for (int i = 0; i < (arrecife->cantidad_pokemon); i++){

		if ( seleccionar_pokemon( &(arrecife->pokemon[i]) ) ) {
			
			contador_pokemones ++;
		}
	}

	return (contador_pokemones >= cant_seleccion);

}


/*
 *	PRE: El puntero a función de selección de pokemon recibido por parametro debe apuntar a una función válida (de selección).
 *
 *	POST: Devuelve:
 *
 *			> ERROR (-1) si:
 *				- El puntero al arrecife es nulo, es decir, no apunta a ningún arrecife.
 *				- El puntero al acuario es nulo, es decir, no apunta a ningún acuario.
 *				- No hay suficiente cantidad de pokemones en el arrecife que cumplan con las condiciones de selección.
 *				- Falló algún realloc, ya sea para agrandar el acuario o achicar el arrecife, impidiendo un traslado exitoso.
 *			
 *			> EXITO (0) si se logran trasladar exitosamente la cantidad de pokemones solicitada del arrecife hacia el acuario
 *						sin que falle ningún realloc. Además, se actualizan el arrecife y acuario apuntados por los punteros
 *						recibidos ajustando su cantidad de pokemones que poseen actualmente y el vector de los mismos.
 *
 */
int trasladar_pokemon (arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
	
	bool hay_error = false;
	
	if ( (arrecife != NULL) && (acuario != NULL) && hay_suficientes_pokemones(arrecife, seleccionar_pokemon, cant_seleccion) ){

		int pokemones_trasladados = 0;
		int i = 0;

		while ( (pokemones_trasladados < cant_seleccion) && (!hay_error) ){

			if ( seleccionar_pokemon( &(arrecife->pokemon[i]) ) ) {

				acuario->pokemon = agregar_pokemon( acuario->pokemon, acuario->cantidad_pokemon, arrecife->pokemon[i], &hay_error);

				if (!hay_error){
					
					arrecife->pokemon = retirar_pokemon( arrecife->pokemon, arrecife->cantidad_pokemon, i, &hay_error );
				
					if (!hay_error){

						acuario->cantidad_pokemon ++;
						arrecife->cantidad_pokemon --;
						pokemones_trasladados ++;
					}
				}
				

			}else{
				i++;
			}
		}
	
	}else{
		hay_error = true;
	}


	if (hay_error){
		return ERROR;
	}

	return EXITO;
}


/*
 *	PRE: Debe recibir un puntero (no nulo) a un arrecife correctamente cargado y un puntero a una función de mostrar pokemones válida.
 *
 *	POST: Muestra por pantalla la información (especie, velocidad, peso y color) de todos los pokemones que se encuentran actualmente
 *		  en el arrecife.
 *
 */
void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){

	for (int i = 0; i < arrecife->cantidad_pokemon; i++){

		mostrar_pokemon( &(arrecife->pokemon[i]) );
	}
}



/*
 *	PRE: --- (Los parámetros recibidos no deben cumplir previamente con ninguna condición).
 *
 *	POST: Devuelve:
 *
 *			> ERROR (-1) si no se puede crear el archivo o si el puntero al acuario recibido es nulo.
 *
 *			> EXITO (0) si se logró copiar todos los pokemones del acuario con su respectiva información al archivo en cuestión.
 *
 */
int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){

	if (!acuario){
		return ERROR;
	}

	FILE* archivo_acuario = fopen(nombre_archivo, "w");

	if (!archivo_acuario){
		printf("\nERROR: No se pudo crear el archivo acuario! :(\n");
		return ERROR;
	}

	for (int i = 0; i < acuario->cantidad_pokemon; i++){
		
		fprintf(archivo_acuario, "%s;%i;%i;%s\n", acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, 
											  acuario->pokemon[i].peso   , acuario->pokemon[i].color);	
	}


	fclose(archivo_acuario);

	return EXITO;
}