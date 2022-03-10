#include "abb.h"
#include <stdio.h>

const int EXITO = 0, ERROR = -1;
const int MENOR = 0, MAYOR = 1;


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

	if(!comparador) return NULL;

	abb_t* ptr_abb = malloc(sizeof(abb_t));
	
	if (!ptr_abb) return NULL;

	ptr_abb->nodo_raiz = NULL;
	ptr_abb->comparador = comparador;
	ptr_abb->destructor = destructor;
	

	return ptr_abb;
}

//-------------------------------------------------------------------------------------------------

nodo_abb_t* nuevo_nodo_hoja(void* elemento){

	nodo_abb_t* ptr_nodo_hoja = malloc(sizeof(nodo_abb_t));
	if(!ptr_nodo_hoja) return NULL;

	ptr_nodo_hoja->elemento = elemento;
	ptr_nodo_hoja->derecha = NULL;
	ptr_nodo_hoja->izquierda = NULL;

	return ptr_nodo_hoja;
}


nodo_abb_t* insertar_rec(nodo_abb_t* nodo_actual, abb_comparador comparador, void* elemento, bool* hay_error){

	if(!nodo_actual){
		nodo_abb_t* ptr_nodo_hoja = nuevo_nodo_hoja(elemento);
		
		if(!ptr_nodo_hoja) *hay_error = true;
		return ptr_nodo_hoja;
	}

	if(comparador(elemento, nodo_actual->elemento) > 0)
		nodo_actual->derecha = insertar_rec(nodo_actual->derecha,comparador, elemento, hay_error);
	
	else
		nodo_actual->izquierda = insertar_rec(nodo_actual->izquierda,comparador, elemento, hay_error);

	return nodo_actual;
}


int arbol_insertar(abb_t* arbol, void* elemento){

	if(!arbol) return ERROR;

	bool hay_error = false;

	arbol->nodo_raiz = insertar_rec(arbol->nodo_raiz, arbol->comparador, elemento, &hay_error);

	if(hay_error) return ERROR;
	return EXITO;
}

//-------------------------------------------------------------------------------------------------

void destruir_nodo(nodo_abb_t* nodo_a_destruir, abb_liberar_elemento destructor){

	if(destructor) destructor(nodo_a_destruir->elemento);
	free(nodo_a_destruir);
}


/*
 * Siempre llega un nodo actual y nodo padre NO nulos porque el nodo padre que llega es el nodo a eliminar y el nodo actual 
 * es el nodo hijo de su izquierda, el cual existe ya que se llama a esta funcion sólo cuando el nodo a eliminar tiene 2 hijos.
 */
nodo_abb_t* predecesor_inorden(nodo_abb_t* nodo_actual, nodo_abb_t* aux, nodo_abb_t** nodo_padre){

	if(nodo_actual->derecha)
		return predecesor_inorden(nodo_actual->derecha, nodo_actual, nodo_padre);	
	
	*nodo_padre = aux;
	return nodo_actual;
}


nodo_abb_t* eliminar_nodo_sin_hijos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	
	destruir_nodo(nodo, destructor);
	return NULL;
}

nodo_abb_t* eliminar_nodo_con_un_hijo(nodo_abb_t* nodo, abb_liberar_elemento destructor){

	nodo_abb_t* nodo_hijo = NULL;

	if(nodo->derecha)
		nodo_hijo = nodo->derecha;
	
	else
		nodo_hijo = nodo->izquierda;

	destruir_nodo(nodo, destructor);
	return nodo_hijo;
}

nodo_abb_t* eliminar_nodo_con_dos_hijos(nodo_abb_t* nodo, abb_liberar_elemento destructor){

	nodo_abb_t* nodo_sustituto = nodo->izquierda;

	if(!nodo_sustituto->derecha){
		nodo_sustituto->derecha = nodo->derecha;
	
	}else{
		nodo_abb_t* nodo_padre = nodo;
		nodo_sustituto = predecesor_inorden(nodo_sustituto, nodo ,&nodo_padre);

		nodo_padre->derecha = nodo_sustituto->izquierda;
		nodo_sustituto->derecha = nodo->derecha;
		nodo_sustituto->izquierda = nodo->izquierda;
	}
	
	destruir_nodo(nodo, destructor);
	return nodo_sustituto;
}


nodo_abb_t* borrar_rec( nodo_abb_t* nodo_actual, abb_comparador comparador, abb_liberar_elemento destructor, 
						void* elemento, bool* hay_error){

	
	if (comparador(elemento, nodo_actual->elemento) == 0){

		if ( (!nodo_actual->derecha) && (!nodo_actual->izquierda))
			return eliminar_nodo_sin_hijos(nodo_actual, destructor);

		if (nodo_actual->derecha && nodo_actual->izquierda)
			return eliminar_nodo_con_dos_hijos(nodo_actual, destructor);

		return eliminar_nodo_con_un_hijo(nodo_actual, destructor);
	}


	if ( (comparador(elemento, nodo_actual->elemento) > 0) && (nodo_actual->derecha) )
		nodo_actual->derecha = borrar_rec(nodo_actual->derecha, comparador, destructor, elemento, hay_error);

	else if ( (comparador(elemento, nodo_actual->elemento) < 0) && (nodo_actual->izquierda) )
		nodo_actual->izquierda = borrar_rec(nodo_actual->izquierda, comparador, destructor, elemento, hay_error);

	else
		*hay_error = true;

	return nodo_actual;
}


int arbol_borrar(abb_t* arbol, void* elemento){

	if(!arbol || arbol_vacio(arbol)) return ERROR;

	bool hay_error = false;

	arbol->nodo_raiz = borrar_rec(arbol->nodo_raiz, arbol->comparador, arbol->destructor, elemento, &hay_error);

	if(hay_error) return ERROR;
	return EXITO;
}

//-------------------------------------------------------------------------------------------------

void* buscar_rec (nodo_abb_t* nodo_actual, abb_comparador comparador, void* elemento){

	if(!nodo_actual) return NULL;

	if ( nodo_actual->izquierda && comparador(elemento, nodo_actual->elemento) < 0)
		return buscar_rec(nodo_actual->izquierda, comparador, elemento);

	else if ( nodo_actual->derecha && comparador(elemento, nodo_actual->elemento) > 0)
		return buscar_rec(nodo_actual->derecha, comparador, elemento);

	else if( comparador(elemento, nodo_actual->elemento) == 0 )
		return nodo_actual->elemento;

	return NULL;
}


void* arbol_buscar(abb_t* arbol, void* elemento){

	if(!arbol) return NULL;

	return buscar_rec(arbol->nodo_raiz, arbol->comparador, elemento);
}


//-------------------------------------------------------------------------------------------------

void* arbol_raiz(abb_t* arbol){

	if( !arbol || arbol_vacio(arbol) ) return NULL;

	return arbol->nodo_raiz->elemento;
}

//-------------------------------------------------------------------------------------------------

bool arbol_vacio(abb_t* arbol){

	if(!arbol) return true;

	return(!arbol->nodo_raiz);
}

//-------------------------------------------------------------------------------------------------

void recorrer_inorden_rec(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* cantidad_cargados){

	if(!nodo_actual) return;

	if(nodo_actual->izquierda)
		recorrer_inorden_rec(nodo_actual->izquierda, array, tamanio_array, cantidad_cargados);

	if(*cantidad_cargados < tamanio_array){
		array[*cantidad_cargados] = nodo_actual->elemento;
		(*cantidad_cargados)++;
	}

	if(nodo_actual->derecha)
		recorrer_inorden_rec(nodo_actual->derecha, array, tamanio_array, cantidad_cargados);
}

void recorrer_preorden_rec(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* cantidad_cargados){

	if(!nodo_actual) return;

	if(*cantidad_cargados < tamanio_array){
		array[*cantidad_cargados] = nodo_actual->elemento;
		(*cantidad_cargados)++;
	}

	if(nodo_actual->izquierda)
		recorrer_preorden_rec(nodo_actual->izquierda, array, tamanio_array, cantidad_cargados);

	if(nodo_actual->derecha)
		recorrer_preorden_rec(nodo_actual->derecha, array, tamanio_array, cantidad_cargados);
}

void recorrer_postorden_rec(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* cantidad_cargados){

	if(!nodo_actual) return;

	if(nodo_actual->izquierda)
		recorrer_postorden_rec(nodo_actual->izquierda, array, tamanio_array, cantidad_cargados);

	if(nodo_actual->derecha)
		recorrer_postorden_rec(nodo_actual->derecha, array, tamanio_array, cantidad_cargados);

	if(*cantidad_cargados < tamanio_array){
		array[*cantidad_cargados] = nodo_actual->elemento;
		(*cantidad_cargados)++;
	}
}


size_t arbol_recorrido_generico(abb_t* arbol, void** array, size_t tamanio_array, 
								void (*funcion_recorrido)(nodo_abb_t*, void**, size_t, size_t*) ){

	if(!arbol || arbol_vacio(arbol) || !array || !tamanio_array) return 0;

	size_t cantidad_cargados = 0;
	
	funcion_recorrido(arbol->nodo_raiz, array, tamanio_array, &cantidad_cargados);

	return cantidad_cargados;
}

//-------------------------------------------------------------------------------------------------

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){

	return arbol_recorrido_generico(arbol, array, tamanio_array, &recorrer_inorden_rec);
}

//-------------------------------------------------------------------------------------------------

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){

	return arbol_recorrido_generico(arbol, array, tamanio_array, &recorrer_preorden_rec);
}

//-------------------------------------------------------------------------------------------------

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){

	return arbol_recorrido_generico(arbol, array, tamanio_array, &recorrer_postorden_rec);
}


//-------------------------------------------------------------------------------------------------

void eliminar_todos_los_nodos (nodo_abb_t* nodo_actual, abb_liberar_elemento destructor_elemento){

	if (!nodo_actual){
		return;
	}

	if(nodo_actual->izquierda) 
		eliminar_todos_los_nodos(nodo_actual->izquierda, destructor_elemento);

	if(nodo_actual->derecha)
		eliminar_todos_los_nodos(nodo_actual->derecha, destructor_elemento);

	destruir_nodo(nodo_actual, destructor_elemento);
}

void arbol_destruir(abb_t* arbol){

	if(arbol)
		eliminar_todos_los_nodos(arbol->nodo_raiz, arbol->destructor);

	free(arbol);
}

//-------------------------------------------------------------------------------------------------

bool iterar_inorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* contador_elementos){

	if(!nodo_actual) return true;

	bool cortar_iteracion = false;

	if(nodo_actual->izquierda && !cortar_iteracion)
		cortar_iteracion = iterar_inorden(nodo_actual->izquierda, funcion, extra, contador_elementos);

	if(!cortar_iteracion){
		cortar_iteracion = funcion(nodo_actual->elemento, extra);
		(*contador_elementos)++;
	}

	if(nodo_actual->derecha && !cortar_iteracion)
		cortar_iteracion = iterar_inorden(nodo_actual->derecha, funcion, extra, contador_elementos);

	return cortar_iteracion;
}

bool iterar_preorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* contador_elementos){

	if(!nodo_actual) return true;

	bool cortar_iteracion = false;

	if(!cortar_iteracion){
		cortar_iteracion = funcion(nodo_actual->elemento, extra);
		(*contador_elementos)++;
	}

	if(nodo_actual->izquierda && !cortar_iteracion)
		cortar_iteracion = iterar_preorden(nodo_actual->izquierda, funcion, extra, contador_elementos);

	if(nodo_actual->derecha && !cortar_iteracion)
		cortar_iteracion = iterar_preorden(nodo_actual->derecha, funcion, extra, contador_elementos);

	return cortar_iteracion;
}


bool iterar_postorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* contador_elementos){

	if(!nodo_actual) return true;
	
	bool cortar_iteracion = false;

	if(nodo_actual->izquierda && !cortar_iteracion)
		cortar_iteracion = iterar_postorden(nodo_actual->izquierda, funcion, extra, contador_elementos);

	if(nodo_actual->derecha && !cortar_iteracion)
		cortar_iteracion = iterar_postorden(nodo_actual->derecha, funcion, extra, contador_elementos);
	
	if(!cortar_iteracion){
		cortar_iteracion = funcion(nodo_actual->elemento, extra);
		(*contador_elementos)++;
	}

	return cortar_iteracion;
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){

	if(!arbol || !funcion ){
		return 0;
	}
	
	size_t contador_elementos = 0;

	if (recorrido == ABB_RECORRER_INORDEN)
		iterar_inorden(arbol->nodo_raiz, funcion, extra, &contador_elementos);

	if (recorrido == ABB_RECORRER_PREORDEN)
		iterar_preorden(arbol->nodo_raiz, funcion, extra, &contador_elementos);

	if (recorrido == ABB_RECORRER_POSTORDEN)
		iterar_postorden(arbol->nodo_raiz, funcion, extra, &contador_elementos);

	return contador_elementos;
}