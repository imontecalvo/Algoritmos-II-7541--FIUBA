#include "lista.h"
#include <stdio.h>

bool mostrar_elemento(void* elemento, void* contador){
    if(elemento && contador)
        printf("Elemento %i: %c \n", (*(int*)contador)++, *(char*)elemento);
    return true;
}

void probar_operaciones_lista(){
    lista_t* lista = lista_crear();
    char a='a', b='b', c='c', d='d', w='w';
  
    lista_insertar(lista, &a);
    lista_insertar(lista, &c);
    lista_insertar_en_posicion(lista, &d, 100);
    lista_insertar_en_posicion(lista, &b, 1);
    lista_insertar_en_posicion(lista, &w, 3);
  
    lista_borrar_de_posicion(lista, 3);
    
    printf("Elementos en la lista: ");
    for(size_t i=0; i<lista_elementos(lista); i++)
        printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));
    
    printf("\n\n");

    printf("Imprimo la lista usando el iterador externo: \n");
    lista_iterador_t* it = NULL;

    for(it = lista_iterador_crear(lista);
        lista_iterador_tiene_siguiente(it);
        lista_iterador_avanzar(it))
        printf("%c ", *(char*)lista_iterador_elemento_actual(it));
    printf("\n\n");

    lista_iterador_destruir(it);

    int contador=0;
    size_t elementos_recorridos = 0;
    printf("Imprimo la lista usando el iterador interno: \n");
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);

    printf("Recorri %zu elementos con el iterador interno y sume %i elementos\n", elementos_recorridos, contador);
    
    printf("\n");
    lista_destruir(lista);
}

void probar_operaciones_cola(){
    lista_t* cola = lista_crear();

    int numeros[]={1,2,3,4,5,6};

    for(size_t i=0; i<sizeof(numeros)/sizeof(int); i++){
        printf("Encolo %i\n", numeros[i]);
        lista_encolar(cola, &numeros[i]);
    }
  
    printf("\nDesencolo los numeros y los muestro: ");
    while(!lista_vacia(cola)){
        printf("%i ", *(int*)lista_primero(cola));
        lista_desencolar(cola);
    }
    printf("\n");
    lista_destruir(cola);
}

void probar_operaciones_pila(){
    lista_t* pila = lista_crear();
    char* algo="somtirogla";

    for(int i=0; algo[i]!= 0; i++){
        printf("Apilo %c\n", algo[i]);
        lista_apilar(pila, &algo[i]);
    }

    printf("\nDesapilo y muestro los elementos apilados: ");
    while(!lista_vacia(pila)){
        printf("%c", *(char*)lista_tope(pila));
        lista_desapilar(pila);
    }
    printf("\n");
    lista_destruir(pila);
}

int main(){

    printf("Pruebo que la lista se comporte como lista\n");
    probar_operaciones_lista();
  
    printf("\nPruebo el comportamiento de cola\n");
    probar_operaciones_cola();
    
    printf("\nPruebo el comportamiento de pila\n");
    probar_operaciones_pila();
    
    return 0;
}
