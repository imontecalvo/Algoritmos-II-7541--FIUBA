#include "pa2mm.h"
#include "lista.h"

#define MAX_ELEM_INSERTADOS 10000
const static int ERROR = -1, EXITO = 0;

void imprimir_separador(){

	printf("-------------------------------------------------------------------------------------------------------------------\n");
}

//=============================================|| FUNCIONES AUXILIARES ||=============================================

/*
 * PRE: Recibe una lista/pila/cola NO nula, un vector de elemento de elementos a cargar correctamente inicializado, 
 *		la cantidad de elementos se desea añadir, el puntero a la función mediante la cual se añadirán dichos elementos
 *		y dos variables booleanas inicializadas en false para controlar el proceso de incersión.
 *
 * POST: Devuelve:
 *				-En caso exitoso: una lisa/pila/cola con todos los elementos insertados y los dos booleanos en false.
 *				-En caso de error: una lista/pila/cola con los elementos que se llegaron a insertar y con el booleano
 *								   hay_error_insercion true, mientras que hay_coincidencia puede ser true si alguno de
 *								   los elementos que llegaron a insertarse no es correcto.
 */
void insertar_multiples_elementos_al_final (lista_t* lista, int elementos[], size_t cantidad, bool* hay_error_insercion, 
											bool* hay_error_coincidencia, int (*funcion_incersion) (lista_t*, void*) ){
	
	int i = 0;

	while ( (i < cantidad) && (!(*hay_error_insercion)) && !(*hay_error_coincidencia) ){

		if( funcion_incersion(lista, elementos+i) != EXITO ){ 
			*hay_error_insercion = true;
		}

		if ( *(int*)(lista->nodo_fin->elemento) != elementos[i] ){
			*hay_error_coincidencia = true;
		}
		i++;
	}
}

//---------------------------------------------------------------------------------------------------------------------------

/*
 * PRE: Recibe un vector de elementos vacío no nulo y una cantidad de elementos a insertar válida.
 *
 * POST: Devuelve un vector de n elementos, inicializado con valores del 0 al n-1, siendo n la
 *		 cantidad de elementos recibida.
 */
void cargar_elementos_a_insertar(int elementos[MAX_ELEM_INSERTADOS], size_t cantidad){

	for (int i = 0; i < cantidad; i++){
		elementos[i] = i;
	}
}

//---------------------------------------------------------------------------------------------------------------------------

/*
 * PRE: Recibe un vector de elementos válidos a insertarse y la cantidad de los mismos-
 *
 * POST: Devuelve una lista con dichos elementos insertados.
 */

lista_t* obtener_lista_no_vacia(int elementos[MAX_ELEM_INSERTADOS], size_t cantidad){

	lista_t* nueva_lista = NULL;
	nueva_lista = lista_crear(nueva_lista);
	if(!nueva_lista) return NULL;

	bool hay_error_insercion = false, hay_error_coincidencia = false;
	insertar_multiples_elementos_al_final(nueva_lista, elementos, cantidad, &hay_error_insercion, 
										  &hay_error_coincidencia, &lista_insertar);

	if ( hay_error_insercion || hay_error_coincidencia || ( nueva_lista->cantidad    		   != cantidad  )    || 
														  ( nueva_lista->nodo_inicio->elemento != elementos )    ||
														  ( nueva_lista->nodo_fin->elemento    !=  elementos+cantidad - 1 ) ){
		lista_destruir(nueva_lista);
		return NULL;
	}

	return nueva_lista;
}

//---------------------------------------------------------------------------------------------------------------------------

static nodo_t* obtener_nodo_anterior(nodo_t* nodo, size_t posicion){

	if ( (posicion-1) == 0 ){
		return nodo;
	}

	if(nodo->siguiente != NULL){
		return obtener_nodo_anterior(nodo->siguiente, posicion - 1);
	}

	return NULL;
}

//=============================================|| PRUEBA CREACIÓN DE LA LISTA ||=============================================

void probar_creacion_lista(){

	lista_t* lista = NULL;

	pa2m_afirmar( ( lista = lista_crear() ) != NULL, "Se pudo crear la lista");
	if(!lista) return;

	pa2m_afirmar( (lista->cantidad == 0) && (lista->nodo_inicio == NULL) && (lista->nodo_inicio == NULL), 
				  "Se creó una lista correctamente inicializada");

	lista_destruir(lista);
}


//=============================================|| PRUEBAS VARIAS DE LA LISTA ||=============================================


void probar_si_lista_nula_esta_vacia(){

	lista_t* lista = NULL;

	pa2m_afirmar( lista_vacia(lista) , "Lista nula está vacía");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_si_lista_vacia_esta_vacia(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	pa2m_afirmar( lista_vacia(lista) , "Lista vacía efectivamennte está vacía");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_si_lista_llena_esta_vacia(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	pa2m_afirmar( !lista_vacia(lista) , "Lista con elementos NO está vacía" );

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_ultimo_elem_lista_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	pa2m_afirmar( lista_ultimo(lista) == elementos_iniciales + (cant_inicial-1) , 
				  "Se pide el último elemento de una lista con varios elementos, se devuelve correctamente");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_ultimo_elem_lista_de_un_elem(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10};
	size_t cant_inicial = 1;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	pa2m_afirmar( (lista_ultimo(lista) == elementos_iniciales) && (lista->nodo_inicio->elemento == elementos_iniciales), 
				  "Se pide el último elemento de una lista con 1 sólo elemento, se lo devuelve correctamente");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_ultimo_elem_lista_vacia(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	pa2m_afirmar( !lista_ultimo(lista) , "Se pide el último elemento de una lista vacía y devuelve NULL");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_ultimo_elem_lista_nula(){

	lista_t* lista = NULL;

	pa2m_afirmar( !lista_ultimo(lista) , "Se pide el último elemento de una lista nula y devuelve NULL" );
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_cualquier_elem_lista_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	size_t posicion = 5;
	pa2m_afirmar( lista_elemento_en_posicion(lista, posicion) == elementos_iniciales + posicion , 
				  "Se pide el elemento de una posición cualquiera de una lista con varios elementos y se lo devuelve correctamente");

	lista_destruir(lista);	
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_primer_elem_lista_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	size_t posicion = 0;
	void* elemento_buscado = lista_elemento_en_posicion(lista, posicion);
	pa2m_afirmar( (elemento_buscado == elementos_iniciales) && (elemento_buscado == lista->nodo_inicio->elemento) , 
				  "Se pide el primer elemento de una lista con varios elementos y se lo devuelve correctamente");

	lista_destruir(lista);	
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_elem_inexistente_lista_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	size_t posicion = 20;
	pa2m_afirmar( !lista_elemento_en_posicion(lista, posicion) , 
				  "Se pide el elemento de una posición inexistente de una lista con varios elementos y se devuelve NULL");

	lista_destruir(lista);	
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_cualquier_elem_lista_vacia(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	size_t posicion = 20;
	pa2m_afirmar( !lista_elemento_en_posicion(lista, posicion) ,
				  "Se pide el elemento de una posición cualquiera de una lista vacía y se devuelve NULL");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_cualquier_elem_lista_nula(){

	lista_t* lista = NULL;

	size_t posicion = 20;
	pa2m_afirmar( !lista_elemento_en_posicion(lista, posicion) ,
				  "Se pide el elemento de una posición cualquiera de una lista nula y se devuelve NULL");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_cant_elementos_lista_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	pa2m_afirmar( lista_elementos(lista) == cant_inicial ,
				  "Se pide la cantidad de elementos de una lista no vacía y se la devuelve correctamente");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_cant_elementos_lista_vacia(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	pa2m_afirmar( !lista_elementos(lista) , "La cantidad de elementos de una lista vacía es cero");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_cant_elementos_lista_nula(){

	lista_t* lista = NULL;

	pa2m_afirmar( !lista_elementos(lista) , "La cantidad de elementos de una lista nula es cero");
}



//=============================================|| PRUEBAS INSERCIÓN AL FINAL DE LA LISTA ||=============================================


void probar_una_insercion_lista_nula_al_final(){

	int elemento = 10; 
	lista_t* lista = NULL;

	pa2m_afirmar( lista_insertar(lista, &elemento) == ERROR, "LISTA NULA: No se puede insertar AL FINAL de lista nula");
}

//------------------------------------------------------------------------------------------------------------------------------------------

void probar_una_insercion_lista_vacia_al_final(){

	int elemento = 10;

	lista_t* lista = lista_crear();
	if(!lista) return;

	pa2m_afirmar( lista_insertar(lista, &elemento) == EXITO, "LISTA VACÍA: Se pudo insertar 1 elemento en lista");
	
	pa2m_afirmar( (lista->nodo_fin->elemento) == &elemento, "El elemento insertado es correcto" );
	
	pa2m_afirmar( (lista->cantidad == 1) && (lista->nodo_inicio == lista->nodo_fin) ,
				   "La información de la lista se actualizó correctamente para una incersión" );

	lista_destruir(lista);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void probar_insercion_multiple_lista_vacia_al_final(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	size_t cantidad_elementos_a_cargar = 100;
	int elementos[cantidad_elementos_a_cargar];
	cargar_elementos_a_insertar(elementos, cantidad_elementos_a_cargar);

	bool hay_error_insercion = false, hay_error_coincidencia = false;
	
	insertar_multiples_elementos_al_final(lista, elementos, cantidad_elementos_a_cargar, &hay_error_insercion, 
										  &hay_error_coincidencia, &lista_insertar);

	pa2m_afirmar( !hay_error_insercion, "LISTA VACÍA: Se pudo insertar múltiples elementos (100/100)");
	
	pa2m_afirmar( !hay_error_coincidencia, "Los múltiples elementos insertados son correctos (100/100)" );
	
	pa2m_afirmar( (lista->cantidad              == cantidad_elementos_a_cargar) && 
		          (lista->nodo_inicio->elemento == elementos)                   && 
			      (lista->nodo_fin->elemento    == elementos+(cantidad_elementos_a_cargar-1)) , 
			      "La información de la lista se actualizó correctamente para múltiples inserciones" );

	lista_destruir(lista);

}

//------------------------------------------------------------------------------------------------------------------------------------------

void probar_insercion_multiple_lista_no_vacia_al_final(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;
	
	size_t cantidad_elementos_a_cargar = 100;
	int elementos_a_insertar[cantidad_elementos_a_cargar];
	cargar_elementos_a_insertar(elementos_a_insertar, cantidad_elementos_a_cargar);
	bool hay_error_insercion = false, hay_error_coincidencia = false;
	
	insertar_multiples_elementos_al_final(lista, elementos_a_insertar, cantidad_elementos_a_cargar, &hay_error_insercion, 
								          &hay_error_coincidencia, &lista_insertar);

	pa2m_afirmar( !hay_error_insercion, "LISTA NO VACÍA: Se pudo insertar múltiples elementos (100/100)");
	
	pa2m_afirmar( !hay_error_coincidencia, "Los múltiples elementos insertados son correctos (100/100)" );
	
	pa2m_afirmar( (lista->cantidad              == (int)(cantidad_elementos_a_cargar + cant_inicial))  && 
				  (lista->nodo_inicio->elemento == elementos_iniciales)                                && 
			      (lista->nodo_fin->elemento    == elementos_a_insertar+(cantidad_elementos_a_cargar-1))        , 
			      
			      "La información de la lista se actualizó correctamente para múltiples inserciones" );

	lista_destruir(lista);

}

//------------------------------------------------------------------------------------------------------------------------------------------

void probar_insercion_10k_elementos_lista_vacia_al_final(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	size_t cantidad_elementos_a_cargar = 10000;
	int elementos[cantidad_elementos_a_cargar];
	cargar_elementos_a_insertar(elementos, cantidad_elementos_a_cargar);

	bool hay_error_insercion = false, hay_error_coincidencia = false;
	
	insertar_multiples_elementos_al_final(lista, elementos, cantidad_elementos_a_cargar, &hay_error_insercion, 
										  &hay_error_coincidencia, &lista_insertar);

	pa2m_afirmar( !hay_error_insercion, "LISTA VACÍA: Se pudo insertar gran cantidad de elementos (10000/10000)");
	
	pa2m_afirmar( !hay_error_coincidencia, "Los elementos insertados son correctos (10000/10000)" );
	
	pa2m_afirmar( (lista->cantidad              == cantidad_elementos_a_cargar) && 
		          (lista->nodo_inicio->elemento == elementos)                   && 
			      (lista->nodo_fin->elemento    == elementos+(cantidad_elementos_a_cargar-1)) , 
			      "La información de la lista se actualizó correctamente para 10k inserciones" );

	lista_destruir(lista);

}


//=============================================|| PRUEBAS INSERCIÓN CUALQUIER LUGAR DE LA LISTA ||=============================================


void probar_una_insercion_lista_nula_en_medio(){

	int elemento = 1111; 
	size_t posicion = 5;
	lista_t* lista = NULL;

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento, posicion) == ERROR, "LISTA NULA: No se puede insertar EN MEDIO de lista nula" );
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_una_insercion_lista_nula_al_inicio(){

	int elemento = 1111; 
	size_t posicion = 0;
	lista_t* lista = NULL;

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento, posicion) == ERROR, "LISTA NULA: No se puede insertar AL INICIO de lista nula" );
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_una_insercion_lista_vacia_en_medio(){

	lista_t* lista = lista_crear();
	if (!lista) return;

	int elemento = 1111;

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento, 5) == EXITO, 
				  "LISTA VACÍA: Se quiere insertar 1 elemento en posición 5 pero se inserta al inicio porque la lista está vacía" );
	
	pa2m_afirmar( lista->nodo_inicio->elemento == &elemento , "El elemento insertado es correcto" );
	
	pa2m_afirmar( (lista->cantidad == 1) && (lista->nodo_inicio == lista->nodo_fin),
				   "La información de la lista se actualizó correctamente para una incersión" );

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_una_insercion_lista_en_medio_cant_suficiente(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	int elemento = 1111;
	size_t posicion = 5;

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento, posicion) == EXITO , 
				  "LISTA NO VACÍA: Se pudo insertar 1 elemento EN MEDIO de la lista ya existente" );
	
	pa2m_afirmar( lista_elemento_en_posicion(lista, posicion) == &elemento , 
					"El elemento es correcto y se insertó en la posición correcta" );
	
	pa2m_afirmar( (lista->cantidad              == cant_inicial + 1)      && 
				  (lista->nodo_inicio->elemento == elementos_iniciales)   && 
				  (lista->nodo_fin->elemento    == elementos_iniciales + (cant_inicial-1)) ,
				   "La información de la lista se actualizó correctamente para una incersión" );

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_multiples_inserciones_lista_en_medio(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	int elemento_1 = 1111, elemento_2 = 2222, elemento_3 = 3333;  

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento_1, 2) == EXITO , 
				  "LISTA NO VACÍA: Se pudo insertar el 1/3 elementos en cualquier posicion");
	pa2m_afirmar( lista_elemento_en_posicion(lista, 2) == &elemento_1, 
				  "El elemento es correcto y se insertó en la posición correcta");
	
	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento_2, 7) == EXITO ,
				  "LISTA NO VACÍA: Se pudo insertar el 2/3 elementos en cualquier posicion");
	pa2m_afirmar( lista_elemento_en_posicion(lista, 7) == &elemento_2, 
				  "El elemento es correcto y se insertó en la posición correcta");

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento_3, 1000) == EXITO ,
				  "LISTA NO VACÍA: Se pudo insertar el 3/3 elementos en cualquier posicion");
	pa2m_afirmar( lista_elemento_en_posicion(lista, cant_inicial+2) == &elemento_3, 
				  "El elemento es correcto y se insertó en la posición correcta");

	pa2m_afirmar( (lista->cantidad              == cant_inicial + 3)      && 
				  (lista->nodo_inicio->elemento == elementos_iniciales)   && 
				  (lista->nodo_fin->elemento    == &elemento_3)            ,
				   "LISTA NO VACÍA: La información de la lista se actualizó correctamente para multiples incersiones" );

	lista_destruir(lista);
}


//---------------------------------------------------------------------------------------------------------------------------

void probar_una_insercion_lista_al_inicio_cant_suficiente(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	int elemento = 1111;
	size_t posicion = 0;

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento, posicion) == EXITO , 
				  "LISTA NO VACÍA: Se pudo insertar 1 elemento AL INICIO de la lista ya existente");
	
	pa2m_afirmar( lista->nodo_inicio->elemento == &elemento , 
					"El elemento es correcto y se insertó en la posición correcta" );
	
	pa2m_afirmar( (lista->cantidad              == cant_inicial + 1)   && 
				  (lista->nodo_fin->elemento    == elementos_iniciales + (cant_inicial-1)) ,
				   "La información de la lista se actualizó correctamente para una incersión" );

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_una_insercion_lista_cant_insuficiente(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;
	
	int elemento = 1111;
	size_t posicion = 25;

	pa2m_afirmar( lista_insertar_en_posicion(lista, &elemento, posicion) == EXITO , 
				  "LISTA NO VACÍA: Se quiere insertar 1 elemento en posición inexistente, se inserta AL FINAL de la lista");

	pa2m_afirmar( lista->nodo_fin->elemento == &elemento, 
				  "El elemento insertado es correcto");

	pa2m_afirmar( (lista->cantidad              == cant_inicial + 1)     && 
				  (lista->nodo_inicio->elemento == elementos_iniciales)   ,
				  "La información de la lista se actualizó correctamente para una incersión" );

	lista_destruir(lista);
}


//=============================================|| PRUEBAS BORRAR ELEMENTO DE LA LISTA ||=============================================


void probar_borrar_ultimo_elemento_lista_nula(){

	lista_t* lista = NULL;

	pa2m_afirmar( lista_borrar(lista) == ERROR, "LISTA NULA: No se puede eliminar el último elemento porque la lista no existe");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_borrar_ultimo_elemento_lista_vacia(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	pa2m_afirmar( lista_borrar(lista) == ERROR, "LISTA VACÍA: No se puede eliminar el último elemento porque la lista está vacía");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_borrar_ultimo_elemento_lista(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	nodo_t* anteultimo_elemento = obtener_nodo_anterior(lista->nodo_inicio, cant_inicial - 1);
	
	pa2m_afirmar( (lista_borrar(lista) == EXITO) && (lista->nodo_fin == anteultimo_elemento) && (!lista->nodo_fin->siguiente), 
				   "LISTA NO VACÍA: Se eliminó el último elemento de la lista");
	
	pa2m_afirmar( (lista->cantidad == cant_inicial-1) && (lista->nodo_inicio->elemento == elementos_iniciales) ,
				   "La información de la lista se actualizó luego del borrar el elemento");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_borrar_primer_elemento_lista(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	nodo_t* segundo_elemento = lista->nodo_inicio->siguiente;

	pa2m_afirmar( (lista_borrar_de_posicion(lista, 0) == EXITO) && (lista->nodo_inicio == segundo_elemento) , 
				  "LISTA NO VACÍA:Se eliminó el primer elemento de la lista");

	pa2m_afirmar( (lista->cantidad == cant_inicial-1) && (lista->nodo_fin->elemento == elementos_iniciales + (cant_inicial-1)) ,
				   "La información de la lista se actualizó luego del borrar el elemento");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_borrar_cualquier_elemento_lista(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	size_t posicion = 5;
	nodo_t* nodo_anterior = obtener_nodo_anterior(lista->nodo_inicio, posicion);
	nodo_t* nodo_siguiente = nodo_anterior->siguiente->siguiente;

	pa2m_afirmar( (lista_borrar_de_posicion(lista, posicion) == EXITO) && (nodo_anterior->siguiente == nodo_siguiente) , 
				  "LISTA NO VACÍA: Se eliminó el elemento de una posición intermedia de la lista");

	pa2m_afirmar( (lista->cantidad == cant_inicial-1)                    && 
				  (lista->nodo_inicio->elemento == elementos_iniciales)  &&
				  (lista->nodo_fin->elemento == elementos_iniciales + (cant_inicial-1)) ,
				   "La información de la lista se actualizó luego de borrar el elemento");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_borrar_elemento_lista_con_un_elemento(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10};
	size_t cant_inicial = 1;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	pa2m_afirmar( (lista_borrar_de_posicion(lista, 0) == EXITO) && (!lista->nodo_fin), 
				   "LISTA NO VACÍA CON 1 ELEMENTO: Se eliminó el único elemento de la lista, ahora está VACÍA");

	pa2m_afirmar( (lista->cantidad == 0) && (lista->nodo_inicio == lista->nodo_fin) , 
		 		   "La información de la lista se actualizó luego de borrar el elemento");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_borrar_multiples_elementos_de_lista(){
	
	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	nodo_t* nodo_anterior;
	nodo_t* nodo_siguiente;
	
	nodo_siguiente = lista->nodo_inicio->siguiente;
	pa2m_afirmar( (lista_borrar_de_posicion(lista, 0) == EXITO) && (lista->nodo_inicio == nodo_siguiente), //Elimino el 10
				   "Se eliminó el primer elemento de la lista. Eliminados 1/5");

	nodo_anterior = obtener_nodo_anterior(lista->nodo_inicio, 8);
	pa2m_afirmar( (lista_borrar_de_posicion(lista, 20) == EXITO) && (lista->nodo_fin == nodo_anterior), 	//Elimino el 100
				   "Se pide eliminar elemento inexistente y se eliminó el último de la lista. Eliminados 2/5");

	nodo_anterior = obtener_nodo_anterior(lista->nodo_inicio, 4);
	nodo_siguiente = nodo_anterior->siguiente->siguiente;
	pa2m_afirmar( (lista_borrar_de_posicion(lista, 4) == EXITO) && (nodo_anterior->siguiente == nodo_siguiente), //Elimino el 60
				   "Se eliminó otro elemento de la lista. Eliminados 3/5");

	nodo_siguiente = nodo_siguiente->siguiente;
	pa2m_afirmar( (lista_borrar_de_posicion(lista, 4) == EXITO) && (nodo_anterior->siguiente == nodo_siguiente), //Elimino el 70
				   "Se eliminó otro elemento de la lista. Eliminados 4/5");

	nodo_anterior = obtener_nodo_anterior(lista->nodo_inicio, 1);
	nodo_siguiente = nodo_anterior->siguiente->siguiente;
	pa2m_afirmar( (lista_borrar_de_posicion(lista, 1) == EXITO) && (nodo_anterior->siguiente == nodo_siguiente), //Elimino el 30
				   "Se eliminó otro elemento de la lista. Eliminados 5/5");

	

	pa2m_afirmar( (lista->cantidad              == cant_inicial-5)        && 
				  (lista->nodo_inicio->elemento == elementos_iniciales+1) &&
				  (lista->nodo_fin->elemento    == elementos_iniciales+8), 
		 		  "La información de la lista se actualizó luego de borrar el elemento");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_borrar_todos_los_elementos_de_lista_desde_final(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;
	
	bool hay_error_eliminacion = false;
	while (lista->nodo_inicio){
		
		if( lista_borrar(lista) == ERROR ){
			hay_error_eliminacion = true;
		}
	}

	pa2m_afirmar( (!hay_error_eliminacion) && (!lista->nodo_fin) && (lista->nodo_inicio == lista->nodo_fin), 
				   "Se eliminaron todos los elementos de la lista, ahora está VACÍA");

	pa2m_afirmar( (lista->cantidad == 0) , "La información de la lista se actualizó luego de borrar todos sus elementos");

	lista_destruir(lista);
}


//=============================================|| PRUEBAS APILAR EN UNA PILA ||=============================================

void probar_apilar_pila_nula(){

	int elemento = 10; 
	lista_t* pila = NULL;

	pa2m_afirmar( lista_apilar(pila, &elemento) == ERROR, "PILA NULA: No se puede apilar elemento en pila nula");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_apilar_pila_vacia(){

	int elemento = 10;

	lista_t* pila = lista_crear();
	if(!pila) return;

	pa2m_afirmar( lista_apilar(pila, &elemento) == EXITO, "PILA VACÍA: Se pudo apilar 1 elemento en la pila");
	
	pa2m_afirmar( pila->nodo_fin->elemento == &elemento, "El elemento apilado es correcto");
	
	pa2m_afirmar( pila->cantidad == 1 && pila->nodo_inicio ==  pila->nodo_fin, 
				  "La información de la pila se actualizó correctamente");

	lista_destruir(pila);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_apilar_pila_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* pila = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!pila) return;

	int elemento = 1111;

	pa2m_afirmar( lista_apilar(pila, &elemento) == EXITO , 
				  "PILA NO VACÍA: Se pudo apilar 1 elemento en pila ya existente" );
	
	pa2m_afirmar( pila->nodo_fin->elemento == &elemento, "El elemento apilado es correcto");
	
	pa2m_afirmar( (pila->cantidad              == cant_inicial + 1) && 
				  (pila->nodo_fin->elemento    == &elemento) ,
				   "La información de la pila se actualizó correctamente para una incersión" );

	lista_destruir(pila);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_apilar_multiples_elementos(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* pila = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!pila) return;

	size_t cantidad_elementos_a_cargar = 100;
	int elementos_a_insertar[cantidad_elementos_a_cargar];
	cargar_elementos_a_insertar(elementos_a_insertar, cantidad_elementos_a_cargar);
	bool hay_error_insercion = false, hay_error_coincidencia = false;
	
	insertar_multiples_elementos_al_final(pila, elementos_a_insertar, cantidad_elementos_a_cargar, &hay_error_insercion, 
								          &hay_error_coincidencia, &lista_apilar);

	pa2m_afirmar( !hay_error_insercion, "PILA NO VACÍA: Se pudo apilar múltiples elementos (100/100)");
	
	pa2m_afirmar( !hay_error_coincidencia, "Los múltiples elementos apilados son correctos (100/100)" );
	
	pa2m_afirmar( (pila->cantidad              == (int)(cantidad_elementos_a_cargar + cant_inicial))  && 
			      (pila->nodo_fin->elemento    == elementos_a_insertar+(cantidad_elementos_a_cargar-1))        , 
			      "La información de la pila se actualizó correctamente para múltiples elementos apilados" );

	lista_destruir(pila);
}

//=============================================|| PRUEBAS DESAPILAR EN UNA PILA ||=============================================

void probar_desapilar_pila_nula(){

	lista_t* pila = NULL;

	pa2m_afirmar( lista_desapilar(pila) == ERROR, "PILA NULA: No se puede desapilar ningún elemento de una pila nula");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desapilar_pila_vacia(){
	
	lista_t* pila = lista_crear();
	if(!pila) return;

	pa2m_afirmar( lista_desapilar(pila) == ERROR, "PILA VACÍA: No se puede desapilar ningún elemento de una pila vacía");

	lista_destruir(pila);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desapilar_pila_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* pila = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!pila) return;
	
	pa2m_afirmar( (lista_desapilar(pila) == EXITO) && (pila->nodo_fin->elemento == elementos_iniciales+8) , 
				   "PILA NO VACÍA: Se pudo desapilar el último elemento de la pila");
	
	pa2m_afirmar( (pila->cantidad == cant_inicial-1) && (!pila->nodo_fin->siguiente),
				   "La información de la pila se actualizó luego de desapilar el elemento");

	lista_destruir(pila);	
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desapilar_multiples_elementos(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* pila = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!pila) return;
	
	pa2m_afirmar( (lista_desapilar(pila) == EXITO) && (pila->nodo_fin->elemento == elementos_iniciales+8) , 
				   "PILA NO VACÍA: Se pudo desapilar el último elemento de la pila. Desapilados 1/5");

	pa2m_afirmar( (lista_desapilar(pila) == EXITO) && (pila->nodo_fin->elemento == elementos_iniciales+7) , 
				   "PILA NO VACÍA: Se pudo desapilar el último elemento de la pila. Desapilados 2/5");

	pa2m_afirmar( (lista_desapilar(pila) == EXITO) && (pila->nodo_fin->elemento == elementos_iniciales+6) , 
				   "PILA NO VACÍA: Se pudo desapilar el último elemento de la pila. Desapilados 3/5");

	pa2m_afirmar( (lista_desapilar(pila) == EXITO) && (pila->nodo_fin->elemento == elementos_iniciales+5) , 
				   "PILA NO VACÍA: Se pudo desapilar el último elemento de la pila. Desapilados 4/5");

	pa2m_afirmar( (lista_desapilar(pila) == EXITO) && (pila->nodo_fin->elemento == elementos_iniciales+4) , 
				   "PILA NO VACÍA: Se pudo desapilar el último elemento de la pila. Desapilados 5/5");


	pa2m_afirmar( (pila->cantidad == cant_inicial - 5) && (!pila->nodo_fin->siguiente) ,
				  "La información de la pila se actualizó luego de desapilar varios de sus elementos");
	
	lista_destruir(pila);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desapilar_todos(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* pila = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!pila) return;
	
	bool hay_error_eliminacion = false;
	while(pila->nodo_fin && !hay_error_eliminacion){
		
		if (lista_desapilar(pila) == ERROR){
			hay_error_eliminacion = true;
		}
	}

	pa2m_afirmar( (!hay_error_eliminacion) && (!pila->nodo_fin) , 
				   "PILA NO VACÍA: Se desapilaron todos los elementos de la pila, ahora está vacía");

	pa2m_afirmar( (pila->cantidad == 0), "La información de la pila se actualizó luego de desapilar todos sus elementos");
	
	lista_destruir(pila);
}



//=============================================|| PRUEBAS TOPE EN PILA ||=============================================

void probar_obtener_tope_pila_nula(){

	lista_t* pila = NULL;

	pa2m_afirmar( !lista_tope(pila), "El último elemento (tope) de una pila nula es nulo");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_tope_pila_vacia(){

	lista_t* pila = lista_crear();
	if(!pila) return;

	pa2m_afirmar( !lista_tope(pila), "El último elemento (tope) de una pila vacía es nulo")

	lista_destruir(pila);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_tope_pila_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* pila = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!pila) return;

	pa2m_afirmar( *(int*)lista_tope(pila) == 100, "El último elemento (tope) de una piĺa no vacía es correcto" )

	lista_destruir(pila);
}

//=============================================|| PRUEBAS ENCOLAR EN UNA COLA ||=============================================

void probar_encolar_cola_nula(){

	int elemento = 10; 
	lista_t* cola = NULL;

	pa2m_afirmar( lista_encolar(cola, &elemento) == ERROR, "COLA NULA: No se puede encolar elemento en cola nula");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_encolar_cola_vacia(){

	int elemento = 10;

	lista_t* cola = lista_crear();
	if(!cola) return;

	pa2m_afirmar( lista_encolar(cola, &elemento) == EXITO, "COLA VACÍA: Se pudo encolar 1 elemento en la cola");
	
	pa2m_afirmar( cola->nodo_fin->elemento == &elemento, "El elemento encolado es correcto");
	
	pa2m_afirmar( cola->cantidad == 1 && cola->nodo_inicio ==  cola->nodo_fin, 
				  "La información de la cola se actualizó correctamente");

	lista_destruir(cola);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_encolar_cola_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* cola = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!cola) return;

	int elemento = 1111;

	pa2m_afirmar( lista_encolar(cola, &elemento) == EXITO , 
				  "COLA NO VACÍA: Se pudo encolar 1 elemento en cola ya existente" );
	
	pa2m_afirmar( cola->nodo_fin->elemento == &elemento, "El elemento encolado es correcto");
	
	pa2m_afirmar( (cola->cantidad              == cant_inicial + 1)      && 
				  (cola->nodo_inicio->elemento == elementos_iniciales)   && 
				  (cola->nodo_fin->elemento    == &elemento) ,
				   "La información de la cola se actualizó correctamente para 1 elemento encolado" );

	lista_destruir(cola);	
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_encolar_multiples_elementos(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* cola = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!cola) return;

	size_t cantidad_elementos_a_cargar = 100;
	int elementos_a_encolar[cantidad_elementos_a_cargar];
	cargar_elementos_a_insertar(elementos_a_encolar, cantidad_elementos_a_cargar);
	bool hay_error_encolar= false, hay_error_coincidencia = false;
	
	insertar_multiples_elementos_al_final(cola, elementos_a_encolar, cantidad_elementos_a_cargar, &hay_error_encolar, 
								 &hay_error_coincidencia, &lista_encolar);

	pa2m_afirmar( !hay_error_encolar, "COLA NO VACÍA: Se pudo encolar múltiples elementos (100/100)");
	
	pa2m_afirmar( !hay_error_coincidencia, "Los múltiples elementos encolados son correctos (100/100)" );
	
	pa2m_afirmar( (cola->cantidad              == cantidad_elementos_a_cargar + cant_inicial)  && 
				  (cola->nodo_inicio->elemento == elementos_iniciales)                                && 
			      (cola->nodo_fin->elemento    == elementos_a_encolar+(cantidad_elementos_a_cargar-1))        , 
			      
			      "La información de la cola se actualizó correctamente para múltiples elementos encolados" );

	lista_destruir(cola);
}



//=============================================|| PRUEBAS DESENCOLAR EN UNA COLA ||=============================================

void probar_desencolar_cola_nula(){

	lista_t* cola = NULL;

	pa2m_afirmar( lista_desencolar(cola) == ERROR, "COLA NULA: No se puede desencolar ningún elemento de una cola nula");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desencolar_cola_vacia(){

	lista_t* cola = lista_crear();
	if(!cola) return;

	pa2m_afirmar( lista_desencolar(cola) == ERROR, "COLA VACÍA: No se puede desencolar ningún elemento de una cola vacía");

	lista_destruir(cola);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desencolar_cola_llena(){
	
	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* cola = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!cola) return;

	nodo_t* segundo_elemento = cola->nodo_inicio->siguiente;
	
	pa2m_afirmar( (lista_desencolar(cola) == EXITO) && (cola->nodo_inicio == segundo_elemento) , 
				   "COLA NO VACÍA: Se pudo desencolar el primer elemento de la cola");
	
	pa2m_afirmar( (cola->cantidad == cant_inicial-1) ,
				   "La información de la cola se actualizó luego de desencolar el elemento");

	lista_destruir(cola);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desencolar_multiples_elementos(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* cola = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!cola) return;
	

	pa2m_afirmar( (lista_desencolar(cola) == EXITO) && (cola->nodo_inicio->elemento == elementos_iniciales + 1) , 
				   "COLA NO VACÍA: Se desencoló correctamente el primer elemento. Desencolados 1/5");

	pa2m_afirmar( (lista_desencolar(cola) == EXITO) && (cola->nodo_inicio->elemento == elementos_iniciales + 2) , 
				   "COLA NO VACÍA: Se desencoló correctamente el primer elemento. Desencolados 2/5");

	pa2m_afirmar( (lista_desencolar(cola) == EXITO) && (cola->nodo_inicio->elemento == elementos_iniciales + 3) , 
				   "COLA NO VACÍA: Se desencoló correctamente el primer elemento. Desencolados 3/5");

	pa2m_afirmar( (lista_desencolar(cola) == EXITO) && (cola->nodo_inicio->elemento == elementos_iniciales + 4) , 
				   "COLA NO VACÍA: Se desencoló correctamente el primer elemento. Desencolados 4/5");

	pa2m_afirmar( (lista_desencolar(cola) == EXITO) && (cola->nodo_inicio->elemento == elementos_iniciales + 5) , 
				   "COLA NO VACÍA: Se desencoló correctamente el primer elemento. Desencolados 5/5");

	

	pa2m_afirmar( (cola->cantidad == cant_inicial - 5)  ,
				  "La información de la cola se actualizó luego de desencolar varios de sus elementos");
	
	lista_destruir(cola);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_desencolar_todos(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* cola = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!cola) return;
	
	bool hay_error_desencolar = false;
	
	while(cola->nodo_inicio && !hay_error_desencolar){
		
		if (lista_desencolar(cola) == ERROR){
			hay_error_desencolar = true;
		}
	}

	pa2m_afirmar( (!hay_error_desencolar) && (!cola->nodo_inicio) , 
				   "COLA NO VACÍA: Se desencolaron todos los elementos de la cola, ahora está vacía");

	pa2m_afirmar( (cola->cantidad == 0), "La información de la cola se actualizó luego de desencolar todos sus elementos");
	
	lista_destruir(cola);	
}

//=============================================|| PRUEBAS PRIMER ELEMENTO EN UNA COLA ||=============================================

void probar_obtener_primer_elemento_cola_nula(){

	lista_t* cola = NULL;

	pa2m_afirmar( !lista_primero(cola), "El primer elemento de una cola nula es nulo");
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_primer_elemento_cola_vacia(){

	lista_t* cola = lista_crear();
	if(!cola) return;

	pa2m_afirmar( !lista_primero(cola), "El primer elmento de una cola vacía es nulo");

	lista_destruir(cola);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_obtener_primer_elemento_cola_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* cola = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!cola) return;

	pa2m_afirmar( lista_primero(cola) == elementos_iniciales, "El primer elemento de una cola no vacía es correcto.");

	lista_destruir(cola);
}



//=============================================|| PRUEBAS ITERADOR EXTERNO ||=============================================

void probar_it_externo_lista_nula(){

	lista_t* lista = NULL;
	lista_iterador_t* iterador = lista_iterador_crear(lista);

	pa2m_afirmar( !iterador, "No se puede crear iterador de una lista nula" );
	pa2m_afirmar( !lista_iterador_tiene_siguiente(iterador), "El iterador de una lista nula no tiene siguiente, pues es nulo" );
	pa2m_afirmar( !lista_iterador_avanzar(iterador), "El iterador de una lista nula no puede avanzar" );
	pa2m_afirmar( !lista_iterador_tiene_siguiente(iterador), "El siguiente sigue siendo nulo luego de intentar avanzar" );
	pa2m_afirmar( !lista_iterador_elemento_actual(iterador), "El elemento actual de iterador de una lista nula es NULL" );

}

//---------------------------------------------------------------------------------------------------------------------------

void probar_it_externo_lista_vacia(){

	lista_t* lista = lista_crear();
	if(!lista) return;

	lista_iterador_t* iterador = lista_iterador_crear(lista);

	pa2m_afirmar( iterador, "Se puede crear iterador de una lista vacía" );
	pa2m_afirmar( !lista_iterador_tiene_siguiente(iterador), "El iterador de una lista vacía no tiene siguiente" );
	pa2m_afirmar( !lista_iterador_avanzar(iterador), "El iterador de una lista vacía no puede avanzar" );
	pa2m_afirmar( !lista_iterador_tiene_siguiente(iterador), "El siguiente sigue siendo nulo luego de intentar avanzar" );
	pa2m_afirmar( !lista_iterador_elemento_actual(iterador), "El elemento actual de iterador de una lista vacía es NULL" );

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_it_externo_lista_llena(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	lista_iterador_t* iterador = lista_iterador_crear(lista);

	pa2m_afirmar( iterador, "Se puede crear iterador de una lista no vacía" );
	pa2m_afirmar( lista_iterador_tiene_siguiente(iterador), "El iterador tiene siguiente porque la lista no está vacía");
	
	int i = 0;

	while ( lista_iterador_tiene_siguiente(iterador) ){

		pa2m_afirmar( lista_iterador_elemento_actual(iterador) == elementos_iniciales+i, 
					  "El elemento actual del iterador es correcto." );

		if (i == 9){
			pa2m_afirmar( !lista_iterador_avanzar(iterador), "El iterador no puede avanzar porque ya está en el último elemento" );
		
		}else{
			pa2m_afirmar( lista_iterador_avanzar(iterador), "El iterador puede avanzar, aún no llegó al último elemento" );
		}
		i++;
	}

	pa2m_afirmar( !lista_iterador_tiene_siguiente(iterador), "El iterador no tiene siguiente porque ya recorrió toda la lista");
	pa2m_afirmar( !lista_iterador_elemento_actual(iterador), "El elemento actual de iterador es NULL, pues llegó al final" );

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}


//=============================================|| PRUEBAS ITERADOR INTERNO ||=============================================

bool contar_pares(void* elemento, void* contador){

	if(!elemento || !contador){
		return false;
	}

	if ( (*(int*)elemento) % 2 == 0){
		(*(int*)contador) ++;
	}

	return true;
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_it_interno_lista_nula( bool (*funcion)(void*, void*) ){

	lista_t* lista = NULL;
	int contador = 0;

	pa2m_afirmar( lista_con_cada_elemento(lista, funcion, &contador) == 0, 
				  "Se iteraron cero elementos porque la lista no existe");

}

//---------------------------------------------------------------------------------------------------------------------------

void probar_it_interno_lista_vacia( bool (*funcion)(void*, void*) ){

	lista_t* lista = lista_crear();
	int contador = 0;

	pa2m_afirmar( lista_con_cada_elemento(lista, funcion, &contador) == 0, 
				  "Se iteraron cero elementos porque la lista existe pero está vacía");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_it_interno_funcion_nula(){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	int contador = 0;

	pa2m_afirmar( lista_con_cada_elemento(lista, NULL, &contador) == 0, 
				  "Se iteraron cero elementos la función es recibida es nula");

	lista_destruir(lista);
}

//---------------------------------------------------------------------------------------------------------------------------

void probar_it_interno_lista_llena_y_funcion_no_nula( bool(*funcion)(void*, void*)){

	int elementos_iniciales[MAX_ELEM_INSERTADOS] = {10, 25, 30, 45, 50, 65, 70, 85, 90, 105};
	size_t cant_inicial = 10;
	lista_t* lista = obtener_lista_no_vacia(elementos_iniciales, cant_inicial);
	if(!lista) return;

	int contador = 0;

	pa2m_afirmar( lista_con_cada_elemento(lista, funcion, &contador) == 10, "Se iteraron todos los elementos de la lista");

	pa2m_afirmar( contador == 5 , "La cantidad de elementos que cumplen la condición es correcta")

	lista_destruir(lista);

}



//=================================================================================================================
//=============================================|| LLAMADO A PRUEBAS ||=============================================
//=================================================================================================================


void pruebas_con_lista(){

	pa2m_nuevo_grupo("PRUEBAS CREACION - LISTA");
	probar_creacion_lista();


	pa2m_nuevo_grupo("PRUEBAS INSERCIÓN AL FINAL - LISTA");
	probar_una_insercion_lista_nula_al_final();
	imprimir_separador();

	probar_una_insercion_lista_vacia_al_final();
	imprimir_separador();

	probar_insercion_multiple_lista_vacia_al_final();
	imprimir_separador();

	probar_insercion_multiple_lista_no_vacia_al_final();
	imprimir_separador();

	probar_insercion_10k_elementos_lista_vacia_al_final();
	imprimir_separador();


	pa2m_nuevo_grupo("PRUEBAS INSERCIÓN EN CUALQUIER POSICIÓN - LISTA");
	probar_una_insercion_lista_nula_en_medio();
	imprimir_separador();

	probar_una_insercion_lista_nula_al_inicio();
	imprimir_separador();

	probar_una_insercion_lista_vacia_en_medio();
	imprimir_separador();

	probar_una_insercion_lista_en_medio_cant_suficiente();
	imprimir_separador();

	probar_multiples_inserciones_lista_en_medio();
	imprimir_separador();

	probar_una_insercion_lista_al_inicio_cant_suficiente();
	imprimir_separador();

	probar_una_insercion_lista_cant_insuficiente();


	pa2m_nuevo_grupo("PRUEBAS BORRAR - LISTA");
	probar_borrar_ultimo_elemento_lista_nula();
	imprimir_separador();

	probar_borrar_ultimo_elemento_lista_vacia();
	imprimir_separador();

	probar_borrar_ultimo_elemento_lista();
	imprimir_separador();

	probar_borrar_primer_elemento_lista();
	imprimir_separador();

	probar_borrar_cualquier_elemento_lista();
	imprimir_separador();

	probar_borrar_elemento_lista_con_un_elemento();
	imprimir_separador();

	probar_borrar_multiples_elementos_de_lista();
	imprimir_separador();

	probar_borrar_todos_los_elementos_de_lista_desde_final();
	imprimir_separador();


	pa2m_nuevo_grupo("PRUEBAS VARIAS - LISTA");
	probar_si_lista_nula_esta_vacia();
	probar_si_lista_vacia_esta_vacia();
	probar_si_lista_llena_esta_vacia();
	imprimir_separador();
		
	probar_obtener_ultimo_elem_lista_llena();
	probar_obtener_ultimo_elem_lista_de_un_elem();
	probar_obtener_ultimo_elem_lista_vacia();
	probar_obtener_ultimo_elem_lista_nula();
	imprimir_separador();

	probar_obtener_cualquier_elem_lista_llena();
	probar_obtener_primer_elem_lista_llena();
	probar_obtener_elem_inexistente_lista_llena();
	probar_obtener_cualquier_elem_lista_vacia();
	probar_obtener_cualquier_elem_lista_nula();
	imprimir_separador();

	probar_obtener_cant_elementos_lista_llena();
	probar_obtener_cant_elementos_lista_vacia();
	probar_obtener_cant_elementos_lista_nula();
}

void pruebas_con_pila(){

	pa2m_nuevo_grupo("PRUEBAS APILAR - PILA");
	probar_apilar_pila_nula();
	imprimir_separador();

	probar_apilar_pila_vacia();
	imprimir_separador();

	probar_apilar_pila_llena();
	imprimir_separador();

	probar_apilar_multiples_elementos();
	imprimir_separador();
		

	pa2m_nuevo_grupo("PRUEBAS DESAPILAR - PILA");
	probar_desapilar_pila_nula();
	imprimir_separador();

	probar_desapilar_pila_vacia();
	imprimir_separador();

	probar_desapilar_pila_llena();
	imprimir_separador();

	probar_desapilar_multiples_elementos();
	imprimir_separador();

	probar_desapilar_todos();
	imprimir_separador();
		

	pa2m_nuevo_grupo("PRUEBAS TOPE - PILA");
	probar_obtener_tope_pila_nula();
	imprimir_separador();

	probar_obtener_tope_pila_vacia();
	imprimir_separador();

	probar_obtener_tope_pila_llena();
	imprimir_separador();
}

void pruebas_con_cola(){
	
	pa2m_nuevo_grupo("PRUEBAS ENCOLAR - COLA");
	probar_encolar_cola_nula();
	imprimir_separador();

	probar_encolar_cola_vacia();
	imprimir_separador();
		
	probar_encolar_cola_llena();
	imprimir_separador();
		
	probar_encolar_multiples_elementos();
	imprimir_separador();
		

	pa2m_nuevo_grupo("PRUEBAS DESENCOLAR - COLA");
	probar_desencolar_cola_nula();
	imprimir_separador();

	probar_desencolar_cola_vacia();
	imprimir_separador();

	probar_desencolar_cola_llena();
	imprimir_separador();

	probar_desencolar_multiples_elementos();
	imprimir_separador();
		
	probar_desencolar_todos();
	imprimir_separador();
		
	pa2m_nuevo_grupo("PRUEBAS PRIMER ELEMENTO - COLA");
	probar_obtener_primer_elemento_cola_nula();
	imprimir_separador();

	probar_obtener_primer_elemento_cola_vacia();
	imprimir_separador();

	probar_obtener_primer_elemento_cola_llena();
	imprimir_separador();
}

void pruebas_iterador_externo(){

	pa2m_nuevo_grupo("PRUEBAS ITERADOR EXTERNO");
	probar_it_externo_lista_nula();
	imprimir_separador();

	probar_it_externo_lista_vacia();
	imprimir_separador();

	probar_it_externo_lista_llena();
	imprimir_separador();
}

void pruebas_iterador_interno(){

	pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO");
	probar_it_interno_lista_nula(&contar_pares);
	imprimir_separador();

	probar_it_interno_lista_vacia(&contar_pares);
	imprimir_separador();

	probar_it_interno_funcion_nula();
	imprimir_separador();

	probar_it_interno_lista_llena_y_funcion_no_nula(&contar_pares);
	imprimir_separador();

}


//------------------------------------------------------------------------------------------------------------------------------------------

int main(){

	pruebas_con_lista();
	pruebas_con_pila();
	pruebas_con_cola();
	pruebas_iterador_externo();
	pruebas_iterador_interno();

	pa2m_mostrar_reporte();

	return 0;
}

