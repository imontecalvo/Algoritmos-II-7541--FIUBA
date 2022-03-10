#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>

typedef int (*heap_comparador)(void*, void*);
typedef void (*heap_destructor)(void*);


typedef struct heap{
    void** vector;
    int tope;
    heap_comparador comparador;
    heap_destructor destructor;
}heap_t;

/*
 * Crea el heap reservando la memoria correspondiente.
 * Devuelve un puntero al heap o NULL si hay un error.
 */ 
heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor);

/*
 * Inserta el elemento en la última posición y lo coloca
 * en su posición correcta.
 * Devuelve 0 si se insertó correctamente o -1 si 
 * hay un error.  
 */ 
int heap_insertar(heap_t* heap, void* elemento);

/*
 * Elimina el primer elemento del heap (la raiz) y 
 * lo sustituye por la nueva raíz correspondiente.
 */ 
void heap_extraer_raiz (heap_t* heap);

/*
 * Devuelve la raíz pero sin eliminarla.
 */ 
void* heap_obtener_raiz(heap_t* heap);

/*
 * Devuelve la cantidad de elementos que hay almacenados 
 * en el heap.
 */
size_t heap_elementos(heap_t* heap);

/*
 * Destruye el heap eliminando la memoria reservada.
 * En caso de que haya destructor, también se libera 
 * los elementos.
 */ 
void heap_destruir(heap_t* heap);



#endif /* __HEAP_H__ */