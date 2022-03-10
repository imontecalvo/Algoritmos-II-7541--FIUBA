#include <stdlib.h>
#include "TDA_heap.h"

static const int ERROR = -1, EXITO = 0;
static const int ES_MENOR = -1, ES_MAYOR = 1;



heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor){
    
    if(!comparador) return NULL;

    heap_t* heap = calloc(1, sizeof(heap_t));
    
    heap->comparador = comparador;
    heap->destructor = destructor;
    
    return heap;
}

/*
 * Dada una posición existente, devuelve la posición del padre 
 * del elemento que está en dicha posición.
 * Si se recibe la posición 0 (la raíz) o una posición no válida,
 * devuelve -1.
 */ 
int posicion_padre(int posicion_hijo){
    if (posicion_hijo < 1) return ERROR;

    return ( (posicion_hijo - 1) /2 );
}

/*
 * Intercambia dos elementos del heap.
 */ 
void intercambiar(void** vector, int pos_elemento_1, int pos_elemento_2){

    void* aux = vector[pos_elemento_1];
    vector[pos_elemento_1] = vector[pos_elemento_2];
    vector[pos_elemento_2] = aux;
}

/*
 * Compara el elemento de la posición recibida con su padre 
 * y si es menor (heap minimal) los intercambia y así sucesivamente 
 * hasta que su nuevo padre sea menor a él o hasta que llegue a la raíz,
 * según corresponda.
 */ 
void sift_up( heap_t* heap, int pos){
    
    if( !heap || !pos ) return;
    int pos_padre = posicion_padre(pos);
    
    if( heap->comparador(heap->vector[pos], heap->vector[pos_padre]) == ES_MENOR ){
        intercambiar(heap->vector, pos, pos_padre);
        sift_up(heap, pos_padre);
    }
}

int heap_insertar(heap_t* heap, void* elemento){

    if(!heap) return ERROR;

    void** aux = realloc(heap->vector, sizeof(void*) * (size_t)(heap->tope +1));
    if(!aux) return ERROR;

    heap->vector = aux;
    heap->tope ++;
    heap->vector[ heap->tope -1 ] = elemento;

    sift_up(heap, heap->tope - 1);
    return EXITO;
}

/*
 * Dada la posición de un padre válida, devuelve la posición 
 * de su hijo derecho. De lo contrario, devuelve -1
 */ 
int posicion_hijo_derecho(int posicion_padre){
    if (posicion_padre < 0) return ERROR;

    return ( (2*posicion_padre) + 2 );
}

/*
 * Dada la posición de un padre válida, devuelve la posición 
 * de su hijo izquierdo. De lo contrario, devuelve -1
 */ 
int posicion_hijo_izquierdo(int posicion_padre){
    if (posicion_padre < 0) return ERROR;

    return ( (2*posicion_padre) + 1 );
}

/*
 * Compara dos elementos del heap y devuelve la posición del 
 * elemento menor.
 */ 
int determinar_menor(heap_t* heap, int posicion_1, int posicion_2){
    void* elemento_1 = heap->vector[posicion_1];
    void* elemento_2 = heap->vector[posicion_2];
    
    if(heap->comparador(elemento_1, elemento_2) == ES_MENOR)
        return posicion_1;
    
    return posicion_2;
}

/*
 * Compara un elemento con sus hijos y en caso de ser mayor a 
 * uno de ellos, se intercambian. En caso de ser mayor a ambos 
 * hijos, se intercambia con el hijo más menor. Asi sucesivamente 
 * hasta que ambos hijos sean mayor a él o hasta que no tenga 
 * más hijos, según corresponda.
 */ 
void sift_down(heap_t* heap, int pos_padre){

    int pos_hijo_derecho = posicion_hijo_derecho(pos_padre);
    int pos_hijo_izquierdo = posicion_hijo_izquierdo(pos_padre);
    int pos_hijo_menor = pos_hijo_izquierdo;

    if(pos_hijo_izquierdo >= heap->tope) return;

    if(pos_hijo_derecho < heap->tope)
        pos_hijo_menor = determinar_menor(heap, pos_hijo_izquierdo, pos_hijo_derecho);
    
    if( heap->comparador( heap->vector[pos_padre],heap->vector[pos_hijo_menor] ) == ES_MAYOR){
        intercambiar(heap->vector, pos_padre, pos_hijo_menor);
        sift_down(heap, pos_hijo_menor);
    }
}

void heap_extraer_raiz (heap_t* heap){
    
    if( !heap || !(heap->tope) ) return;

    void* raiz = heap->vector[0];
    heap->vector[0] = heap->vector[heap->tope-1];
    heap->tope --;

    if ((heap->tope))
        sift_down(heap, 0);

    if(heap->destructor)
        heap->destructor(raiz);
}

void* heap_obtener_raiz(heap_t* heap){

    if(!heap) return NULL;

    return heap->vector[0];
}

size_t heap_elementos(heap_t* heap){

    if(!heap) return 0;

    return( (size_t)(heap->tope) );
}

/*
 * Destruye el vector del heap liberando la memoria reservada.
 * En caso de haber destructor, también destruye los elementos.
 */ 
void destruir_vector_heap(heap_t* heap){

    if(heap->destructor){

        for(int i = 0; i < heap->tope; i++)
            heap->destructor(heap->vector[i]);
    }
 
    free(heap->vector);
}

void heap_destruir(heap_t* heap){

    if(heap)
        destruir_vector_heap(heap);
    
    free(heap);
}