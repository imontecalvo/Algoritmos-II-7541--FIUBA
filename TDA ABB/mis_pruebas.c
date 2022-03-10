#include "pa2mm.h"
#include "abb.h"


void imprimir_separador(){

	printf(AMARILLO"─────────────────────────────────────────────────────────────────────────────────────────────────────────────────── \n"NORMAL);	
}

void imprimir_separador2(){

	printf("-------------------------------------------------------------------------------------------------------------------\n");
}

//=============================================|| FUNCIONES AUXILIARES ||=============================================

bool contar_pares(void* elemento, void* contador){

	if(!elemento || !contador){
		return true;
	}

	if ( (*(int*)elemento) % 2 == 0){
		(*(int*)contador) ++;
	}

	return false;
}

//---------------------------------------------------------------------------------------------------------------------------

bool mostrar_primeros_3_impares(void* elemento, void* contador){

	if(!elemento || !contador ) return true;
	
	if ( (*(int*)contador < 3) && ((*(int*)elemento) % 2 != 0) ){
		printf("%i ", *(int*)elemento);
		(*(int*)contador) ++;
	}

	if(*(int*)contador == 3) return true;

	return false;
}

//---------------------------------------------------------------------------------------------------------------------------

bool tiene_hijos(nodo_abb_t* nodo){

	return (nodo->derecha || nodo->izquierda);
}

//---------------------------------------------------------------------------------------------------------------------------

void destructor_generico(void* elemento){

	if(!elemento) return;

	free((int*)elemento);
}

//---------------------------------------------------------------------------------------------------------------------------

int comparador(void* elemento_1, void* elemento_2){
    
    if(!elemento_1 || !elemento_2)
    	return 0;

    if( *(int*)elemento_1 > *(int*)elemento_2 )
        return 1;

    if( *(int*)elemento_1 < *(int*)elemento_2 )
        return -1;

    return 0;
}


//======================================================|| PRUEBAS CREACIÓN DE ABB ||======================================================


void probar_crear_abb_con_comparador_y_destructor(){

	abb_t* arbol = arbol_crear(comparador, destructor_generico);

	pa2m_afirmar( arbol , "Se pudo crear el arbol con comparador y destructor");
	if(!arbol) return;

	pa2m_afirmar( (!arbol->nodo_raiz) && (arbol->comparador == comparador) && (arbol->destructor == destructor_generico) , 
				  "Se creó un arbol correctamente inicializado");

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_crear_abb_con_comparador_sin_destructor(){

	abb_t* arbol = arbol_crear(comparador, NULL);

	pa2m_afirmar( arbol , "Se pudo crear el arbol con comparador y sin destructor");
	if(!arbol) return;

	pa2m_afirmar( (!arbol->nodo_raiz) && (arbol->comparador == comparador) && (!arbol->destructor) , 
				  "Se creó un arbol correctamente inicializado");

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_crear_abb_sin_comparador(){

	abb_t* arbol = arbol_crear(NULL, NULL);

	pa2m_afirmar( !arbol , "No se pudo crear el arbol sin comparador");
}


//=====================================================|| PRUEBAS VARIAS EN ABB NULO ||=====================================================

void pruebas_varias_abb_nulo(){

	abb_t* arbol = NULL;

	pa2m_afirmar( arbol_vacio(arbol) , "Un arbol nulo siempre está vacío");
	pa2m_afirmar( !arbol_raiz(arbol) , "La raiz de un arbol nulo no existe, pues el arbol no existe");

	int elemento = 10;
	pa2m_afirmar( arbol_insertar(arbol, &elemento) == -1 , "No se puede insertar un elemento en un arbol que no existe (nulo)");

	pa2m_afirmar( arbol_vacio(arbol) , "El arbol nulo sigue vacío despues de intentar inserción");
	pa2m_afirmar( !arbol_raiz(arbol) , "La raiz de un arbol nulo sigue sin existir despues de intentar inserción");

	pa2m_afirmar( arbol_borrar(arbol, &elemento) == -1, "No se puede eliminar un elemento en un arbol nulo");

	pa2m_afirmar( !arbol_buscar(arbol, &elemento), "No se puede encontrar el elemento buscado en un arbol nulo");

	
	int* array[50];
	size_t tamanio_array = 50;

	
	pa2m_afirmar( !arbol_recorrido_inorden(arbol, (void**)array, tamanio_array) , "Si recorro inorden un abb nulo devuelve array nulo");

	pa2m_afirmar( !arbol_recorrido_preorden(arbol, (void**)array, tamanio_array) , "Si recorro preorden un abb nulo devuelve array nulo");

	pa2m_afirmar( !arbol_recorrido_postorden(arbol, (void**)array, tamanio_array) , "Si recorro postorden un abb nulo devuelve array nulo");


	pa2m_afirmar( !abb_con_cada_elemento(arbol, 0, contar_pares, NULL), "La cantidad de elementos iterados es nula (cero) en un arbol nulo");
	
	pa2m_afirmar( !abb_con_cada_elemento(arbol, 0, 	NULL, NULL), 
				  "La cantidad de elementos iterados es nula (cero) en un arbol nulo con función nula");

}


//=====================================================|| PRUEBAS VARIAS ABB VACIO ||=======================================================

void pruebas_varias_abb_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if(!arbol) return;

	pa2m_afirmar( arbol_vacio(arbol) , "Un arbol vacio efectivamente está vacio");
	pa2m_afirmar( !arbol_raiz(arbol) , "La raiz de un arbol vacio no existe, es nula");

	int elemento = 10;
	pa2m_afirmar( arbol_insertar(arbol, &elemento) == 0 , "Se pudo insertar un elemento en un arbol inicialmente vacio");
	pa2m_afirmar( !arbol_vacio(arbol) , "El arbol ya no está vacio luego de la inserción");
	pa2m_afirmar( arbol_raiz(arbol) == &elemento , "La raiz del arbol se actualizó correctamente luego de la inserción");

	pa2m_afirmar( arbol_borrar(arbol, &elemento) == 0 , "Se elimina el elemento insertado");
	pa2m_afirmar( arbol_vacio(arbol) , "El arbol vuelve a estar vacio");
	pa2m_afirmar( !arbol_raiz(arbol) , "La raiz de un arbol vacio vuelve a ser nula");

	pa2m_afirmar( arbol_borrar(arbol, &elemento) == -1 , "No se puede eliminar un elemento en un arbol que está vacio");

	pa2m_afirmar( !arbol_buscar(arbol, &elemento) , "No se puede encontrar el elemento buscado en un arbol vacio");


	int* array[50];
	size_t tamanio_array = 50;


	pa2m_afirmar( !arbol_recorrido_inorden(arbol, (void**)array, tamanio_array) , "Si recorro inorden un abb vacio devuelve array nulo");

	pa2m_afirmar( !arbol_recorrido_preorden(arbol, (void**)array, tamanio_array) , "Si recorro preorden un abb vacio devuelve array nulo");

	pa2m_afirmar( !arbol_recorrido_postorden(arbol, (void**)array, tamanio_array) , "Si recorro postorden un abb vacio devuelve array nulo");


	pa2m_afirmar( !abb_con_cada_elemento(arbol, 0, contar_pares, NULL), "La cantidad de elementos iterados es nula (cero) en un arbol vacio");
	
	pa2m_afirmar( !abb_con_cada_elemento(arbol, 0, 	NULL, NULL), 
				  "La cantidad de elementos iterados es nula (cero) en un arbol vacio con función nula");
	

	arbol_destruir(arbol);
}


//=======================================================|| PRUEBAS ABB NO VACIO ||=========================================================

void pruebas_insertar_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 10, elemento_2 = 5, elemento_3 = 15, elemento_4 = 20, elemento_5 = 100, elemento_6 = 2, elemento_7 = 12;
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	nodo_abb_t* nodo = NULL;

	pa2m_afirmar( arbol_insertar(arbol, &elemento_1) == 0, "Se pudo insertar el elemento 1 en el arbol");
	nodo = arbol->nodo_raiz;
	pa2m_afirmar( (nodo->elemento == &elemento_1) && !tiene_hijos(nodo) , 
				  "El elemento 1 se insertó correctamente donde se esperaba que se inserte");

	pa2m_afirmar( !arbol_vacio(arbol) , "El arbol ya no está vacio luego de insertar el elemento" );
	pa2m_afirmar( arbol_raiz(arbol) == &elemento_1 , "Ahora el elemento 1 es la raiz del arbol" );
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar( arbol_insertar(arbol, &elemento_2) == 0, "Se pudo insertar el elemento 2 (menor a la raiz) en el arbol");
	pa2m_afirmar( (nodo->izquierda->elemento == &elemento_2) && !tiene_hijos(nodo->izquierda) ,
				  "El elemento 2 se insertó correctamente donde se esperaba que se inserte (a izquierda de raiz)");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar( arbol_insertar(arbol, &elemento_3) == 0, "Se pudo insertar el elemento 3 (mayor a la raiz) en el arbol");
	pa2m_afirmar( (nodo->derecha->elemento == &elemento_3) && !tiene_hijos(nodo->derecha), 
				  "El elemento 3 se insertó correctamente donde se esperaba que se inserte (a derecha de raiz)");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar( nodo->derecha && nodo->izquierda , "Ahora la raiz posee un hijo a la derecha y otro a la izquierda");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	nodo = arbol->nodo_raiz->derecha;
	pa2m_afirmar( arbol_insertar(arbol, &elemento_4) == 0, "Se pudo insertar el elemento 4 (mayor a todos) en el arbol");
	pa2m_afirmar( (nodo->derecha->elemento == &elemento_4) && !tiene_hijos(nodo->derecha) , 
				  "El elemento 4 se insertó correctamente donde se esperaba que se inserte (a derecha -> derecha de raiz)");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar( nodo->derecha && !(nodo->izquierda) , "Ahora el hijo derecho de la raiz posee un hijo a la derecha");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	nodo = arbol->nodo_raiz->derecha->derecha;
	pa2m_afirmar( arbol_insertar(arbol, &elemento_5) == 0, "Se pudo insertar el elemento 5 (mayor a todos) en el arbol");
	pa2m_afirmar( (nodo->derecha->elemento == &elemento_5) && !tiene_hijos(nodo->derecha) , 
				  "El elemento 5 se insertó correctamente donde se esperaba que se inserte (a derecha -> derecha -> derecha de raiz)");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar( nodo->derecha && !(nodo->izquierda) , "Ahora el hijo derecho del hijo derecho de la raiz posee un hijo a la derecha");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	nodo = arbol->nodo_raiz->izquierda;
	pa2m_afirmar( arbol_insertar(arbol, &elemento_6) == 0, "Se pudo insertar el elemento 6 (menor a todos) en el arbol");
	pa2m_afirmar( (nodo->izquierda->elemento == &elemento_6) && !tiene_hijos(nodo->izquierda) , 
				  "El elemento 6 se insertó correctamente donde se esperaba que se inserte (a izquierda -> izquierda de raiz)");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar( !(nodo->derecha) && nodo->izquierda , "Ahora el hijo izquierda de la raiz posee un hijo a la izquierda");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	nodo = arbol->nodo_raiz->derecha;
	pa2m_afirmar( arbol_insertar(arbol, &elemento_7) == 0, "Se pudo insertar el elemento 7 en el arbol");
	pa2m_afirmar( (nodo->izquierda->elemento == &elemento_7) && !tiene_hijos(nodo->izquierda) , 
				  "El elemento 7 se insertó correctamente donde se esperaba que se inserte (a derecha -> izquierda de raiz)");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar( nodo->derecha && nodo->izquierda , "Ahora el hijo derecho de la raiz posee un hijo a la izquierda y uno a la derecha");

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_buscar_abb_no_vacio(){
	
	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 10, elemento_2 = 5, elemento_3 = 15, elemento_4 = 12, elemento_5 = 2;
	int elemento_inexistente = 999;

	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);	

	pa2m_afirmar( !arbol_buscar(arbol, &elemento_inexistente)     , "No se encontró el elemento solicitado porque no existe, se devuelve NULL");
	pa2m_afirmar(  arbol_buscar(arbol, &elemento_1) == &elemento_1, "Se encontró el elemento 1 solicitado y fue devuelto exitosamente");
	pa2m_afirmar(  arbol_buscar(arbol, &elemento_2) == &elemento_2, "Se encontró el elemento 2 solicitado y fue devuelto exitosamente");
	pa2m_afirmar(  arbol_buscar(arbol, &elemento_3) == &elemento_3, "Se encontró el elemento 3 solicitado y fue devuelto exitosamente");
	pa2m_afirmar(  arbol_buscar(arbol, &elemento_4) == &elemento_4, "Se encontró el elemento 4 solicitado y fue devuelto exitosamente");
	pa2m_afirmar(  arbol_buscar(arbol, &elemento_5) == &elemento_5, "Se encontró el elemento 5 solicitado y fue devuelto exitosamente");

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_borrar_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 50, elemento_2 = 70, elemento_3 = 25, elemento_4 = 80, elemento_5 = 10, elemento_6 = 30, 
		elemento_7 = 45, elemento_8 = 14;

	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);
	arbol_insertar(arbol, &elemento_6);
	arbol_insertar(arbol, &elemento_7);
	arbol_insertar(arbol, &elemento_8);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	nodo_abb_t* nodo_padre;

	pa2m_afirmar(  arbol_borrar(arbol, &elemento_7) == 0 , "Se pudo eliminar un elemento sin hijos (nodo hoja)");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_7)      , "El elemento ya no está en el arbol");
	nodo_padre = arbol->nodo_raiz->izquierda->derecha;
	pa2m_afirmar( !nodo_padre->derecha , "Su padre ya no lo tiene como hijo");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar(  arbol_borrar(arbol, &elemento_2) == 0 , "Se pudo eliminar un elemento con un hijo (derecho)");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_2)      , "El elemento ya no está en el arbol");
	nodo_padre = arbol->nodo_raiz;
	pa2m_afirmar( nodo_padre->derecha->elemento == &elemento_4 , "El hijo del elemento eliminado fue reasignado correctamente a su padre");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	pa2m_afirmar(  arbol_borrar(arbol, &elemento_3) == 0 , "Se pudo eliminar un elemento con dos hijos");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_3)      , "El elemento ya no está en el arbol");
	pa2m_afirmar( (nodo_padre->izquierda->elemento == &elemento_8)            && (!tiene_hijos(nodo_padre->izquierda->izquierda))     &&
				  (nodo_padre->izquierda->izquierda->elemento == &elemento_5) && (nodo_padre->izquierda->derecha->elemento == &elemento_6) ,
				  "El elemento eliminado fue correctamente reemplazado por su sucesor inorden");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	pa2m_afirmar(  arbol_borrar(arbol, &elemento_8) == 0 , "Se pudo eliminar otro elemento con dos hijos");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_8)      , "El elemento ya no está en el arbol");
	pa2m_afirmar( (nodo_padre->izquierda->elemento == &elemento_5) && 
				  !(nodo_padre->izquierda->izquierda)              && (nodo_padre->izquierda->derecha->elemento == &elemento_6) ,
				  "El elemento eliminado fue correctamente reemplazado por su sucesor inorden que ademas era su hijo izquierdo");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	pa2m_afirmar(  arbol_borrar(arbol, &elemento_1) == 0 , "Se pudo eliminar la raiz del arbol");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_1)      , "El elemento ya no está en el arbol");
	pa2m_afirmar( (arbol->nodo_raiz->elemento == &elemento_6)            && 
				  (arbol->nodo_raiz->izquierda->elemento == &elemento_5) && (arbol->nodo_raiz->derecha->elemento == &elemento_4) &&
				  !tiene_hijos(arbol->nodo_raiz->derecha)                &&       !tiene_hijos(arbol->nodo_raiz->izquierda)   ,
				  "La raiz fue correctamente reemplazada por su sucesor inorden, quedando un arbol balanceado con 3 elementos");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	pa2m_afirmar(  arbol_borrar(arbol, &elemento_6) == 0 , "Se pudo volver a eliminar la nueva raiz del arbol");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_6)      , "El elemento ya no está en el arbol");
	pa2m_afirmar( (arbol->nodo_raiz->elemento == &elemento_5) && 
				  !(arbol->nodo_raiz->izquierda)              &&  (arbol->nodo_raiz->derecha->elemento == &elemento_4)  ,
				  "La raiz fue correctamente reemplazada por su sucesor inorden, quedando un arbol con 2 elementos");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar(  arbol_borrar(arbol, &elemento_5) == 0 , "Se pudo volver a eliminar la nueva raiz del arbol");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_5)      , "El elemento ya no está en el arbol");
	pa2m_afirmar( (arbol->nodo_raiz->elemento == &elemento_4)  &&  !tiene_hijos(arbol->nodo_raiz) ,
				  "La raiz fue correctamente reemplazada por su único hijo, quedando un arbol con 1 elemento");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	pa2m_afirmar(  arbol_borrar(arbol, &elemento_4) == 0 , "Se pudo volver a eliminar la nueva raiz, que es el único elemento del arbol");
	pa2m_afirmar( !arbol_buscar(arbol, &elemento_4)      , "El elemento ya no está en el arbol");
	pa2m_afirmar( !arbol->nodo_raiz , "El arbol ya no tiene ningun elemento, está vacio");

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_varias_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 10, elemento_2 = 5, elemento_3 = 15, elemento_4 = 9, elemento_5 = 8;

	pa2m_afirmar(  arbol_vacio(arbol) , "El arbol está inicialmente vacio");
	pa2m_afirmar( !arbol_raiz(arbol)  , "La raiz es nula");

	pa2m_afirmar(  arbol_insertar(arbol, &elemento_1) == 0, "Se inserta un elemento");
	pa2m_afirmar( !arbol_vacio(arbol) , "El arbol ya NO está vacio");
	pa2m_afirmar(  arbol_raiz(arbol) == &elemento_1, "La raiz ya NO es nula y se actualizó correctamente");

	pa2m_afirmar( arbol_insertar(arbol, &elemento_2) == 0, "Se inserta otro elemento");
	pa2m_afirmar( arbol_insertar(arbol, &elemento_3) == 0, "Se inserta otro elemento");
	pa2m_afirmar( arbol_insertar(arbol, &elemento_4) == 0, "Se inserta otro elemento");
	pa2m_afirmar( arbol_insertar(arbol, &elemento_5) == 0, "Se inserta otro elemento");

	pa2m_afirmar( arbol_borrar(arbol, &elemento_1) == 0, "Se elimina la raiz actual");
	pa2m_afirmar( arbol_raiz(arbol) == &elemento_4, "La raiz se actualizó correctamente");

	pa2m_afirmar( arbol_borrar(arbol, &elemento_4) == 0, "Se elimina la raiz actual");
	pa2m_afirmar( arbol_raiz(arbol) == &elemento_5, "La raiz se actualizó correctamente");

	pa2m_afirmar( arbol_borrar(arbol, &elemento_5) == 0, "Se elimina la raiz actual");
	pa2m_afirmar( arbol_raiz(arbol) == &elemento_2, "La raiz se actualizó correctamente");

	pa2m_afirmar( arbol_borrar(arbol, &elemento_2) == 0, "Se elimina la raiz actual");
	pa2m_afirmar( arbol_raiz(arbol) == &elemento_3, "La raiz se actualizó correctamente");

	pa2m_afirmar(  arbol_borrar(arbol, &elemento_3) == 0, "Se elimina la raiz actual, que a su vez es último elemento");
	pa2m_afirmar(  arbol_vacio(arbol) , "El arbol vuelve a quedar vacio");
	pa2m_afirmar( !arbol_raiz(arbol)  , "La raiz es nula");

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_recorrer_inorden_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 50, elemento_2 = 70, elemento_3 = 25, elemento_4 = 80, elemento_5 = 10, elemento_6 = 30, 
		elemento_7 = 45, elemento_8 = 14;

	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);
	arbol_insertar(arbol, &elemento_6);
	arbol_insertar(arbol, &elemento_7);
	arbol_insertar(arbol, &elemento_8);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	bool hay_error = false;

	int* array[8];
	size_t tamanio_array = 8;
	pa2m_afirmar( arbol_recorrido_inorden(arbol, (void**)array, tamanio_array) == 8 , 
				  "Con recorrido inorden se recorre todo el arbol y se devuelve la cantidad correcta de elementos");
	if ( (*array     != &elemento_5) || (*(array+1) != &elemento_8) || (*(array+2) != &elemento_3) || (*(array+3)!= &elemento_6) || 
		 (*(array+4) != &elemento_7) || (*(array+5) != &elemento_1) || (*(array+6) != &elemento_2) || (*(array+7) != &elemento_4)   ){

		hay_error = true;
	}
	pa2m_afirmar( !hay_error , "Los elementos están en el array en el orden correspondiente");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	int* array2[3];
	size_t tamanio_array2 = 3;
	pa2m_afirmar( arbol_recorrido_inorden(arbol, (void**)array2, tamanio_array2) == 3 , 
				  "Con recorrido inorden se recorren los tres primeros y se devuelve la cantidad correcta de elementos");
	if ( (*array2   != &elemento_5)   || (*(array2+1) != &elemento_8) || (*(array2+2) != &elemento_3)){

		hay_error = true;
	}
	pa2m_afirmar( !hay_error , "Los elementos están en el array en el orden correspondiente");

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_recorrer_preorden_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 50, elemento_2 = 70, elemento_3 = 25, elemento_4 = 80, elemento_5 = 10, elemento_6 = 30, 
		elemento_7 = 45, elemento_8 = 14;

	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);
	arbol_insertar(arbol, &elemento_6);
	arbol_insertar(arbol, &elemento_7);
	arbol_insertar(arbol, &elemento_8);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	bool hay_error = false;

	int* array[8];
	size_t tamanio_array = 8;
	pa2m_afirmar( arbol_recorrido_preorden(arbol, (void**)array, tamanio_array) == 8 , 
				  "Con recorrido preorden se recorre todo el arbol y se devuelve la cantidad correcta de elementos");
	if ( (*array     != &elemento_1) || (*(array+1) != &elemento_3) || (*(array+2) != &elemento_5) || (*(array+3)!= &elemento_8) || 
		 (*(array+4) != &elemento_6) || (*(array+5) != &elemento_7) || (*(array+6) != &elemento_2) || (*(array+7) != &elemento_4)   ){

		hay_error = true;
	}
	pa2m_afirmar( !hay_error , "Los elementos están en el array en el orden correspondiente");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	int* array2[3];
	size_t tamanio_array2 = 3;
	pa2m_afirmar( arbol_recorrido_preorden(arbol, (void**)array2, tamanio_array2) == 3 , 
				  "Con recorrido preorden se recorren los tres primeros y se devuelve la cantidad correcta de elementos");
	if ( (*array2   != &elemento_1)   || (*(array2+1) != &elemento_3) || (*(array2+2) != &elemento_5)){

		hay_error = true;
	}
	pa2m_afirmar( !hay_error , "Los elementos están en el array en el orden correspondiente");

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_recorrer_postorden_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 50, elemento_2 = 70, elemento_3 = 25, elemento_4 = 80, elemento_5 = 10, elemento_6 = 30, 
		elemento_7 = 45, elemento_8 = 14;

	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);
	arbol_insertar(arbol, &elemento_6);
	arbol_insertar(arbol, &elemento_7);
	arbol_insertar(arbol, &elemento_8);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	bool hay_error = false;

	int* array[8];
	size_t tamanio_array = 8;
	pa2m_afirmar( arbol_recorrido_postorden(arbol, (void**)array, tamanio_array) == 8 , 
				  "Con recorrido postorden se recorre todo el arbol y se devuelve la cantidad correcta de elementos");
	if ( (*array     != &elemento_8) || (*(array+1) != &elemento_5) || (*(array+2) != &elemento_7) || (*(array+3)!= &elemento_6) || 
		 (*(array+4) != &elemento_3) || (*(array+5) != &elemento_4) || (*(array+6) != &elemento_2) || (*(array+7) != &elemento_1)   ){

		hay_error = true;
	}
	pa2m_afirmar( !hay_error , "Los elementos están en el array en el orden correspondiente");
	imprimir_separador();

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	int* array2[3];
	size_t tamanio_array2 = 3;
	pa2m_afirmar( arbol_recorrido_postorden(arbol, (void**)array2, tamanio_array2) == 3 , 
				  "Con recorrido preorden se recorren los tres primeros y se devuelve la cantidad correcta de elementos");
	if ( (*array2   != &elemento_8)   || (*(array2+1) != &elemento_5) || (*(array2+2) != &elemento_7)){
		hay_error = true;
	}

	pa2m_afirmar( !hay_error , "Los elementos están en el array en el orden correspondiente");

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_iterador_abb_no_vacio_funcion_nula(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 10, elemento_2 = 15, elemento_3 = 20, elemento_4 = 25, elemento_5 = 31;
	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);


	pa2m_afirmar( !abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL), 
				  "Se iteraron cero elementos con recorrido inorden con función nula");

	pa2m_afirmar( !abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, NULL, NULL), 
				  "Se iteraron cero elementos con recorrido preorden con función nula");

	pa2m_afirmar( !abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, NULL, NULL), 
				  "Se iteraron cero elementos con recorrido postorden con función nula");

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_iterador_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 30, elemento_2 = 15, elemento_3 = 20, elemento_4 = 50, elemento_5 = 40;
	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);

	int contador = 0;

	pa2m_afirmar( abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, contar_pares, &contador) == 5, 
				 "Se iteraron todos los elementos");
	
	pa2m_afirmar( contador == 4, "La cantidad de elementos que cumplen la condición impuesta es correcta");

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

void pruebas_iterador_abb_no_vacio_2(){

	abb_t* arbol = arbol_crear(comparador, NULL);
	if (!arbol) return;

	int elemento_1 = 55, elemento_2 = 33, elemento_3 = 70, elemento_4 = 11, elemento_5 = 40, elemento_6 = 58, elemento_7 = 99;
	arbol_insertar(arbol, &elemento_1);	
	arbol_insertar(arbol, &elemento_2);	
	arbol_insertar(arbol, &elemento_3);	
	arbol_insertar(arbol, &elemento_4);	
	arbol_insertar(arbol, &elemento_5);
	arbol_insertar(arbol, &elemento_6);
	arbol_insertar(arbol, &elemento_7);
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	int contador = 0;
	printf("\nRecorrido in orden debe ser 11 33 55:\n");
	size_t iterados = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_primeros_3_impares, &contador);
	printf("\n");
	pa2m_afirmar( iterados == 4, "Se iteraron 4 elementos con recorrido inorden hasta encontrar los primeros 3 numeros impares.");
	
	pa2m_afirmar( contador == 3, "Se encontraron los primeros 3 numeros impares");
	imprimir_separador();
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	contador = 0;
	printf("\nRecorrido in orden debe ser 55 33 11:\n");
	iterados = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_primeros_3_impares, &contador);
	printf("\n");
	pa2m_afirmar( iterados == 3, "Se iteraron 3 elementos con recorrido preorden hasta encontrar los primeros 3 numeros impares.");
	
	pa2m_afirmar( contador == 3, "Se encontraron los primeros 3 numeros impares");
	imprimir_separador();
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	contador = 0;
	printf("\nRecorrido in orden debe ser 11 33 99:\n");
	iterados = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_primeros_3_impares, &contador);
	printf("\n");
	pa2m_afirmar( iterados == 5, "Se iteraron 4 elementos con recorrido postorden elementos hasta encontrar los primeros 3 numeros impares.");
	
	pa2m_afirmar( contador == 3, "Se encontraron los primeros 3 numeros impares");

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	arbol_destruir(arbol);
}

//---------------------------------------------------------------------------------------------------------------------------

int* crear_elemento(int clave){

	int* ptr_int = malloc(sizeof(int));

	if(!ptr_int) return NULL;

	*ptr_int = clave;

	return ptr_int;
}

void pruebas_destructor_abb_no_vacio(){

	abb_t* arbol = arbol_crear(comparador, destructor_generico);
	if (!arbol) return;
	
	arbol_insertar(arbol, crear_elemento(50));	
	arbol_insertar(arbol, crear_elemento(30));	
	arbol_insertar(arbol, crear_elemento(20));	
	arbol_insertar(arbol, crear_elemento(60));	
	arbol_insertar(arbol, crear_elemento(700));
	
	printf("Se insertaron 5 elementos que pertenecen al heap.\n");
	printf("Para un correcto funcionamiento del destructor chequear con Valgrind que no haya fuga de memoria al destruir arbol!\n");
	
	arbol_destruir(arbol);
}

//=================================================================================================================
//=============================================|| LLAMADO A PRUEBAS ||=============================================
//=================================================================================================================

void pruebas_crear_abb(){
	pa2m_nuevo_grupo("PRUEBAS CREACIÓN DE ABB");
	
	probar_crear_abb_con_comparador_y_destructor();
	imprimir_separador();
	probar_crear_abb_con_comparador_sin_destructor();
	imprimir_separador();
	probar_crear_abb_sin_comparador();
	imprimir_separador();
}

void pruebas_abb_nulo(){
	pa2m_nuevo_grupo("PRUEBAS VARIAS - ABB NULO");

	pruebas_varias_abb_nulo();
	imprimir_separador();
}

void pruebas_abb_vacio(){
	pa2m_nuevo_grupo("PRUEBAS VARIAS - ABB VACIO");
	pruebas_varias_abb_vacio();
	imprimir_separador();

}

void pruebas_abb_no_vacio(){

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR - ABB NO VACIO");
	pruebas_insertar_abb_no_vacio();
	imprimir_separador();
	
	pa2m_nuevo_grupo("PRUEBAS DE BUSCAR - ABB NO VACIO");
	pruebas_buscar_abb_no_vacio();
	imprimir_separador();

	pa2m_nuevo_grupo("PRUEBAS DE BORRAR - ABB NO VACIO");
	pruebas_borrar_abb_no_vacio();
	imprimir_separador();

	pa2m_nuevo_grupo("PRUEBAS VARIAS - ABB NO VACIO");
	pruebas_varias_abb_no_vacio();
	imprimir_separador();

	pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO INORDEN- ABB NO VACIO");
	pruebas_recorrer_inorden_abb_no_vacio();
	imprimir_separador();

	pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO PREORDEN- ABB NO VACIO");
	pruebas_recorrer_preorden_abb_no_vacio();
	imprimir_separador();

	pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO POSTORDEN- ABB NO VACIO");
	pruebas_recorrer_postorden_abb_no_vacio();
	imprimir_separador();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR - ABB NO VACIO");
	pruebas_iterador_abb_no_vacio_funcion_nula();
	imprimir_separador();
	pruebas_iterador_abb_no_vacio();
	imprimir_separador();
	pruebas_iterador_abb_no_vacio_2();
	imprimir_separador();

	/*
	 * Para probar el destructor, trabajo con elementos que viven en el heap y al destruir el arbol
	 * chequeo si hay posibles fugas de memoria con Valgrind.
	 * Entonces, si Valgrind no tira errores, el destructor cumple correctamente con su función.
	*/
	pa2m_nuevo_grupo("PRUEBAS DEL DESTRUCTOR - ABB NO VACIO");
	pruebas_destructor_abb_no_vacio();
	imprimir_separador();
	
}


//------------------------------------------------------------------------------------------------------------------------------------------

int main(){

	pruebas_crear_abb();
	pruebas_abb_nulo();
	pruebas_abb_vacio();
	pruebas_abb_no_vacio();

	pa2m_mostrar_reporte();

	return 0;
}
