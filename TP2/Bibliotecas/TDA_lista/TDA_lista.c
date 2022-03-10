#include "TDA_lista.h"
#include <stdlib.h>
#include <stdio.h>

static const int ERROR = -1, EXITO = 0;

//=======================================|| FUNCIONES AUXILIARES ||=======================================

/*
 * PRE: Recibe una lista existente, no nula.
 *
 * POST: Devuelve una lista correctamente inicializada para comenzar a trabajar con ella.
 *		 Si recibe una lista nula, no hará nada.
 */
void inicializar_lista(lista_t* lista, lista_destructor destructor){

	if(!lista) return;

	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;
	lista->destructor = destructor;
}

//--------------------------------------------------------------------------------

/*
 * PRE: Recibe un nodo existente de una lista.
 *
 * POST: Devuelve el nodo que se encuentra en la posición anterior al nodo recibido.
 *		 Si se pide el nodo anterior al primer nodo, devuelve NULL ya que no existe.
 */
nodo_t* obtener_nodo_anterior(nodo_t* nodo, size_t posicion){

	if(posicion == 0){
		return NULL;
	}

	if ( (posicion-1) == 0 ){
		return nodo;
	}

	if(nodo->siguiente != NULL){
		return obtener_nodo_anterior(nodo->siguiente, posicion - 1);
	}

	return NULL;
}


//=======================================|| FUNCIONES PRIMITIVAS TDA ||=======================================

lista_t* lista_crear(lista_destructor destructor){

	lista_t* ptr_lista = NULL;
	ptr_lista = malloc(sizeof(lista_t));

	if(!ptr_lista){
		return NULL;
	}

	inicializar_lista(ptr_lista, destructor);

	return ptr_lista;
}

//--------------------------------------------------------------------------------

int lista_insertar(lista_t* lista, void* elemento){

	if(!lista){
		return ERROR;
	}
	
	nodo_t* ptr_nodo_nuevo = malloc(sizeof(nodo_t));
	if(!ptr_nodo_nuevo){
		return ERROR; 
	}

	ptr_nodo_nuevo->elemento = elemento;
	ptr_nodo_nuevo->siguiente = NULL;

	if(lista->cantidad == 0){
		lista->nodo_inicio = ptr_nodo_nuevo;
	}else{
		lista->nodo_fin->siguiente = ptr_nodo_nuevo;
	}
	lista->nodo_fin = ptr_nodo_nuevo;
	lista->cantidad ++;

	return EXITO;
}

//--------------------------------------------------------------------------------

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

	if(!lista){
		return ERROR;
	}

	if(lista->cantidad <= posicion){
		return lista_insertar(lista, elemento);
	}

	nodo_t* ptr_nodo_nuevo = malloc(sizeof(nodo_t));
	if(!ptr_nodo_nuevo){
		return ERROR;
	}

	ptr_nodo_nuevo->elemento = elemento;

	if(posicion == 0){
		ptr_nodo_nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = ptr_nodo_nuevo;
	
	}else{
		nodo_t* ptr_nodo_anterior = obtener_nodo_anterior(lista->nodo_inicio, posicion);
		if(!ptr_nodo_anterior){
			return ERROR;
		}

		ptr_nodo_nuevo->siguiente = ptr_nodo_anterior->siguiente;
		ptr_nodo_anterior->siguiente = ptr_nodo_nuevo;
	}
	
	lista->cantidad ++;

	return EXITO;
}

//--------------------------------------------------------------------------------

int lista_reemplazar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

	if( !lista || (posicion >= lista_elementos(lista)) ) return ERROR;

	if(posicion == 0)
		lista->nodo_inicio->elemento = elemento;
		
	else{
		nodo_t* nodo_actual = obtener_nodo_anterior(lista->nodo_inicio, posicion);
		nodo_actual = nodo_actual->siguiente;
		nodo_actual->elemento = elemento;
	}
	
	return EXITO;
}

//--------------------------------------------------------------------------------

int lista_borrar(lista_t* lista){

	if( (!lista) || (lista->cantidad == 0) || !lista->nodo_inicio ){  //Para ver si está vacía hago doble chequeo por las dudas
		return ERROR;												  //  -> chequeo cantidad igual a cero y nodo inicial nulo
	}

	lista->destructor(lista->nodo_fin->elemento);
	free(lista->nodo_fin);
	
	if(lista->cantidad == 1){
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	
	}else{
		nodo_t* ptr_nodo_anterior = obtener_nodo_anterior(lista->nodo_inicio, (lista->cantidad) - (size_t)1);
		ptr_nodo_anterior->siguiente = NULL;
		lista->nodo_fin = ptr_nodo_anterior;
	}
	
	lista->cantidad --;

	return EXITO;
}

//--------------------------------------------------------------------------------

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

	if( (!lista) || (lista->cantidad == 0) || !lista->nodo_inicio){
		return ERROR;
	}

	if(lista->cantidad <= (posicion + 1)){
		return lista_borrar(lista);
	}

	if (posicion == 0){
		if (lista->nodo_inicio->siguiente){
			nodo_t* segundo_nodo = lista->nodo_inicio->siguiente;
			lista->destructor(lista->nodo_inicio->elemento);
			free(lista->nodo_inicio);
			lista->nodo_inicio = segundo_nodo;

		}else{
			lista->destructor(lista->nodo_inicio->elemento);
			free(lista->nodo_inicio);
			lista->nodo_inicio = NULL;
			lista->nodo_fin = NULL;
		}
		
	
	}else{
		nodo_t* ptr_nodo_anterior = obtener_nodo_anterior(lista->nodo_inicio, posicion);
		nodo_t* ptr_aux = ptr_nodo_anterior->siguiente;
		ptr_nodo_anterior->siguiente = ptr_aux->siguiente;
		lista->destructor(ptr_aux->elemento);
		free(ptr_aux);
	}

	lista->cantidad --;

	return EXITO;
}

//--------------------------------------------------------------------------------

/*
 * PRE: Recibe un nodo existente (debe ser le nodo inicial de la lista).
 *
 * POST: Devuelve el elemento de la lista que se encuentra en la posición solicitada.
 */
void* obtener_elemento_aux(nodo_t* nodo, size_t posicion){

	if(posicion == 0){
		return (nodo->elemento);
	}

	if(nodo->siguiente != NULL){
		return obtener_elemento_aux(nodo->siguiente, posicion-1);
	}

	return NULL;
}


void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	
	if ( (!lista) || (lista->cantidad <= posicion) ){
		return NULL;
	}

	return obtener_elemento_aux(lista->nodo_inicio, posicion);
}

//--------------------------------------------------------------------------------

void* lista_ultimo(lista_t* lista){
	
	if ( (!lista) || (lista->nodo_inicio == NULL) ){
		return NULL;
	}

	return (lista->nodo_fin->elemento);
}

//--------------------------------------------------------------------------------

bool lista_vacia(lista_t* lista){
	
	return ( (!lista) || (lista->nodo_inicio == NULL) );
}

//--------------------------------------------------------------------------------

size_t lista_elementos(lista_t* lista){
	
	if (!lista){
		return 0;
	}
	
	return (lista->cantidad);
}

//--------------------------------------------------------------------------------

int lista_apilar(lista_t* lista, void* elemento){

	return lista_insertar(lista, elemento);
}

//------------------------------------------------------

int lista_desapilar(lista_t* lista){

	return lista_borrar(lista);
}
//------------------------------------------------------
void* lista_tope(lista_t* lista){

	return lista_ultimo(lista);
}

//------------------------------------------------------

int lista_encolar(lista_t* lista, void* elemento){

	return lista_insertar(lista, elemento);
}

//------------------------------------------------------

int lista_desencolar(lista_t* lista){

	return lista_borrar_de_posicion(lista, 0);
}

//------------------------------------------------------

void* lista_primero(lista_t* lista){

	return lista_elemento_en_posicion(lista, 0);
}

//--------------------------------------------------------------------------------

void destruir_elementos(nodo_t* nodo_a_destruir, nodo_t* nodo_fin, lista_destructor destructor){

	if(nodo_fin == nodo_a_destruir){
		if(destructor)
			destructor(nodo_a_destruir->elemento);
		free(nodo_a_destruir);
		return;
	}

	destruir_elementos(nodo_a_destruir->siguiente, nodo_fin, destructor);
	
	if(destructor)
		destructor(nodo_a_destruir->elemento);
	free(nodo_a_destruir);
}



void lista_destruir(lista_t* lista){

	if(lista && !lista_vacia(lista)){
		destruir_elementos(lista->nodo_inicio, lista->nodo_fin, lista->destructor);
	}

	free(lista);

}

//--------------------------------------------------------------------------------

void lista_vaciar(lista_t* lista){

	if(lista && !lista_vacia(lista))
		destruir_elementos(lista->nodo_inicio, lista->nodo_fin, lista->destructor);
	lista->cantidad = 0;
}

//--------------------------------------------------------------------------------

lista_iterador_t* lista_iterador_crear(lista_t* lista){

	if (!lista){
		return NULL;
	}

	lista_iterador_t* iterador = NULL;
	iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador){
		return NULL;
	}

	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;

	return iterador;
}

//--------------------------------------------------------------------------------

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	
	if(!iterador){
		return false;
	}

	return (iterador->corriente);
}

//--------------------------------------------------------------------------------

bool lista_iterador_avanzar(lista_iterador_t* iterador){

	if( !iterador || !iterador->corriente ){
		return false;
	}
	
	iterador->corriente = iterador->corriente->siguiente;

	return (iterador->corriente);
}

//--------------------------------------------------------------------------------

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){

	if(!iterador || !iterador->corriente){
		return NULL;
	}

	return iterador->corriente->elemento;
}

//--------------------------------------------------------------------------------

void lista_iterador_destruir(lista_iterador_t* iterador){

	free(iterador);
}

//--------------------------------------------------------------------------------

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){

	if(!lista || !funcion){
		return 0;
	}

	size_t contador_elementos = 0;
	nodo_t* nodo_actual = lista->nodo_inicio;
	
	while( nodo_actual && funcion(nodo_actual->elemento, contexto) ){
		
		nodo_actual = nodo_actual->siguiente;
		contador_elementos ++;
	}

	return contador_elementos;
}
