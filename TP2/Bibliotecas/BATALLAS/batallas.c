#include "batallas.h"
#include <string.h>
#include <stdio.h>

#define POKENOMBRE_MAX 15

typedef struct pokemon{
	char nombre[POKENOMBRE_MAX];
	int velocidad;
	int defensa;
	int ataque;
}pokemon_t;

/*
 * Gana el pokemon con mayor puntaje de ataque.
 * En caso de empate, gana el pokemon con mayor velocidad.
 * En caso de empate, gana el segundo arbitrariamente.
 */ 
int funcion_batalla_1(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
    pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

    if (pokemon_1->ataque > pokemon_2->ataque)
        return GANO_PRIMERO;
    
    if (pokemon_1->ataque < pokemon_2->ataque)
        return GANO_SEGUNDO;

    if (pokemon_1->velocidad > pokemon_2->velocidad)
        return GANO_PRIMERO;

    return GANO_SEGUNDO;

}

/*
 * Gana el pokemon que esté primero alfabeticamente
 * segun su nombre. En caso de que tengan el mismo
 * nombre, gana el primer pokemon arbitrariamente.
 */ 
int funcion_batalla_2(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
    pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

    int resultado = strcmp(pokemon_1->nombre, pokemon_2->nombre);
    if (resultado <= 0)
        return GANO_PRIMERO;

    return GANO_SEGUNDO;
}

/*
 * Gana el pokemon cuya suma de sus caracteristicas 
 * tenga el valor más alto.
 * En caso de empate, gana el primero arbitrariamente.
 */ 
int funcion_batalla_3(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
    pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

    int suma_1 = pokemon_1->velocidad + pokemon_1->ataque + pokemon_1->defensa;
    int suma_2 = pokemon_2->velocidad + pokemon_2->ataque + pokemon_2->defensa;

    if (suma_1 >= suma_2)
        return GANO_PRIMERO;
    
    return GANO_SEGUNDO;
}

/*
 * Gana el pokemon con puntaje de defensa más alto.
 * En caso de empate, se llama a la batalla 3, de forma
 * que se determinará el ganador de acuerdo a las reglas
 * de la misma.
 */
int funcion_batalla_4(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
    pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

    if (pokemon_1->defensa > pokemon_2->defensa)
        return GANO_PRIMERO;
    
    if (pokemon_1->defensa < pokemon_2->defensa)
        return GANO_SEGUNDO;
    
    return funcion_batalla_3(pkm_1, pkm_2);
}

/*
 * Cuenta la cantidad de vocales de un string.
 */ 
int contador_vocales(char* pokenombre){

    int tope = (int)strlen(pokenombre);
    int contador = 0;

    for (int i = 0; i < tope; i++){
        if( (pokenombre[i] == 'A') || (pokenombre[i] == 'a') ||  
            (pokenombre[i] == 'E') || (pokenombre[i] == 'e') ||
            (pokenombre[i] == 'I') || (pokenombre[i] == 'i') ||
            (pokenombre[i] == 'O') || (pokenombre[i] == 'o') ||
            (pokenombre[i] == 'U') || (pokenombre[i] == 'u')   )
                contador ++;

    }
    return contador;
}

/*
 * Gana el pokemon con menos vocales en su nombre.
 * En caso de empate, se llama a la batalla 1, de forma
 * que se determinará el ganador de acuerdo a las reglas
 * de la misma.
 */
int funcion_batalla_5(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
    pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

    int vocales_1 = contador_vocales(pokemon_1->nombre);
    int vocales_2 = contador_vocales(pokemon_2->nombre);

    if( vocales_1 > vocales_2)
        return GANO_SEGUNDO;

    if( vocales_2 > vocales_1)
        return GANO_PRIMERO;

    return funcion_batalla_1(pkm_1, pkm_2);
}