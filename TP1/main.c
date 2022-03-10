#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define RUTA_ARCHIVO_ARRECIFE "arrecife.txt"
#define RUTA_ARCHIVO_ACUARIO "acuario.txt"
#define MAX_FILTROS 5
#define MAX_FORMAS_DE_MOSTRAR 5

#define ROJO          "\e[91m"
#define VERDE         "\e[32m"
#define AMARILLO      "\e[33m"
#define AZUL          "\e[94m"
#define VIOLETA       "\e[35m"
#define CYAN          "\e[36m"
#define COLOR_DEFAULT "\e[0m"


const int PESO_MIN = 20;
const int VELOCIDAD_ALTA = 80;
const int LONGITUD_NOMBRE_LARGO = 9;
const int ERROR = -1;


//---------- SELECCION DE POKEMONES ----------//

/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Devuelve:
 *				   	> True si el nombre de la especie del pokemon en cuestión es muy largo (mayor o igual a 9 caracteres).
 *					> False si el nombre de la especie no es muy largo (menor a 9 caracteres).
 *
 */
bool especie_mucho_texto(pokemon_t* pokemon_actual){

	size_t longitud_nombre_especie = strlen( pokemon_actual->especie );

	return (longitud_nombre_especie >= LONGITUD_NOMBRE_LARGO);
}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Devuelve:
 *				   	> True si el pokemon apuntado es muy veloz (posee VELOCIDAD mayor a 80).
 *					> False si el el pokemon apuntado no es muy veloz.
 *
 */
bool pistea_como_un_campeon (pokemon_t* pokemon_actual){

	return (pokemon_actual->velocidad >= VELOCIDAD_ALTA);
}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Devuelve:
 *				   	> True si el peso del pokemon apuntado es muy bajo (PESO menor a 20).
 *					> False si el pokemon apuntado no tiene un peso tan bajo.
 *
 */
bool es_peso_pluma(pokemon_t* pokemon_actual){

	return (pokemon_actual->peso <= PESO_MIN);

}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Devuelve:
 *				   	> True si el pokemon apuntado es de color AZUL o AMARILLO.
 *					> False si el pokemon apuntado es de otro color.
 *
 */
bool es_de_bokita (pokemon_t* pokemon_actual){

	return ( ( strcmp(pokemon_actual->color,"azul") == 0 ) || ( strcmp(pokemon_actual->color,"amarillo") == 0 ) );
}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Devuelve:
 *				   	> True si el nombre de la especie del pokemon apuntado tiene una cantidad de caracteres PAR.
 *				   	> False si el nombre de la especie del pokemon apuntado tiene una cantidad de caracteres IMPAR.
 *
 */
bool es_especie_par(pokemon_t* pokemon_actual){
	
	size_t longitud_nombre_especie = strlen( pokemon_actual->especie );

	return (longitud_nombre_especie % 2 == 0);
}


/*
 *	PRE: --- (El vector de puntero a función no debe cumplir ninguna condición previa)
 *
 *	POST: Devuelve un vector de puntero a función cargado correctamente con las cinco funciones de selección de pokemon.
 *				   
 */
void inicializar_ptr_seleccion( bool (*seleccionar_pokemon[MAX_FILTROS]) (pokemon_t*) ){

	seleccionar_pokemon[0] = especie_mucho_texto;
	seleccionar_pokemon[1] = pistea_como_un_campeon;
	seleccionar_pokemon[2] = es_peso_pluma;
	seleccionar_pokemon[3] = es_de_bokita;
	seleccionar_pokemon[4] = es_especie_par;

}



//---------- VISUALIZACIÓN DE POKEMONES ----------//

/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Imprime por pantalla la información del pokemon apuntado (especie, velocidad, peso y color) separando cada uno de los valores con una coma (',').
 *
 */
void mostrar_pokemon_csv (pokemon_t* pokemon_actual){

	printf("\t%s;%i;%i;%s\n", pokemon_actual->especie, pokemon_actual->velocidad, pokemon_actual->peso, pokemon_actual->color);
}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Imprime por pantalla la información del pokemon apuntado (especie, velocidad, peso y color) en forma de tabla.
 *
 */
void mostrar_pokemon_tabla (pokemon_t* pokemon_actual){
	printf(VIOLETA"\t╔═══════════════╦═════╦═════╦══════════╗\n"COLOR_DEFAULT);
	
	printf(VIOLETA"\t║"COLOR_DEFAULT"%-15s"VIOLETA"║"COLOR_DEFAULT"%-5i"VIOLETA"║"COLOR_DEFAULT"%-5i"VIOLETA"║"COLOR_DEFAULT"%-10s"VIOLETA"║\n", 
		              pokemon_actual->especie, pokemon_actual->velocidad, pokemon_actual->peso, pokemon_actual->color);
	
	printf(VIOLETA"\t╚═══════════════╩═════╩═════╩══════════╝\n"COLOR_DEFAULT);
}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Imprime por pantalla la información del pokemon apuntado (especie, velocidad, peso y color) en forma de lista.
 *
 */
void mostrar_pokemon_lista (pokemon_t* pokemon_actual){
	
	printf("\t* "ROJO"Especie: "COLOR_DEFAULT"%-15s - "CYAN"Velocidad: "COLOR_DEFAULT"%-5i - "VERDE"Peso: "COLOR_DEFAULT"%-5i - "AMARILLO"Color: "COLOR_DEFAULT"%-10s\n", 
		  pokemon_actual->especie, pokemon_actual->velocidad, pokemon_actual->peso, pokemon_actual->color);
}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Imprime por pantalla la información del pokemon apuntado (especie, velocidad, peso y color) con un diseño en forma de tarjeta.
 *
 */
void mostrar_pokemon_tarjeta (pokemon_t* pokemon_actual){
	printf("\t╔═════════════════════════════╗\n");
	printf("\t║"ROJO"· · ·| %12s    |· · ·"COLOR_DEFAULT"║\n"    , pokemon_actual->especie);
	printf("\t║                             ║\n");
	printf("\t║-----------------------------║\n");
	printf("\t║     "CYAN"VELOCIDAD:"COLOR_DEFAULT" %10i   ║\n"  , pokemon_actual->velocidad);
	printf("\t║     "VERDE"PESO:"COLOR_DEFAULT" %15i   ║\n"      , pokemon_actual->peso);
	printf("\t║     "AMARILLO"COLOR: "COLOR_DEFAULT"%14s   ║\n"   , pokemon_actual->color);
	printf("\t╚═════════════════════════════╝\n\n");
}


/*
 *	PRE: Recibe un puntero a un pokemon previamente inicializado con datos válidos en todos sus campos.
 *
 *	POST: Imprime por pantalla la información del pokemon apuntado (especie, velocidad, peso y color), en el que cada uno de sus campos
 *		  se encuentran en forma escalonada.
 *
 */
void mostrar_pokemon_escalonado (pokemon_t* pokemon_actual){

	printf(ROJO"\tE S P E C I E"COLOR_DEFAULT" ---> %s\n", pokemon_actual->especie);
	printf(CYAN"\t\t╚> V E L O C I D A D"COLOR_DEFAULT" ---> %i\n", pokemon_actual->velocidad);
	printf(VERDE"\t\t\t╚> P E S O"COLOR_DEFAULT" ---> %i\n", pokemon_actual->peso);
	printf(AMARILLO"\t\t\t\t╚> C O L O R"COLOR_DEFAULT" ---> %s\n", pokemon_actual->color);
	printf("================================================================\n\n");
}


/*
 *	PRE: --- (El vector de puntero a función no debe cumplir ninguna condición previa)
 *
 *	POST: Devuelve un vector de puntero a función cargado correctamente con las cinco funciones que muestran la información de cada pokemon por pantalla.
 *				   
 */
void inicializar_ptr_mostrar ( void (*mostrar_pokemon[MAX_FORMAS_DE_MOSTRAR]) (pokemon_t*)){

	mostrar_pokemon[0] = mostrar_pokemon_csv;
	mostrar_pokemon[1] = mostrar_pokemon_tabla;
	mostrar_pokemon[2] = mostrar_pokemon_lista;
	mostrar_pokemon[3] = mostrar_pokemon_tarjeta;
	mostrar_pokemon[4] = mostrar_pokemon_escalonado;

}


//---------- MENSAJES POR PANTALLA ----------//

/*
 *	PRE: ---
 *
 *	POST: Imprime por pantalla un mensaje de error para advertir al usuario que algo falló.
 *				   
 */
void mostrar_mensaje_error(){

	printf("\nERROR: Algo falló en el transcurso de la simulación :(\n\n");
}


/*
 *	PRE: ---
 *
 *	POST: Imprime por pantalla un mensaje de bienvenida a modo de introducción.
 *				   
 */
void mostrar_bienvenida(){

	system("clear");
	printf("\n\n");
	printf(AZUL "\t	                                                                         o                                                                    \n");
	printf("\t                                                                               .hNMh.                                                                 \n");
	printf("\t                                                                              oNm/sNm:                                                                \n");
	printf("\t                                                                            /mNo    mNo                                                               \n");
	printf("\t                                                                          :dNh-    odNd                                                               \n");
	printf("\t                  ..----..                         -:+ydmN.`hNy:        .yNN/::ohmdy/.              :yyyyyyyys                                        \n");
	printf("\t           -/oydmNNNNNNNNNNmho:              -/oydmNNmhmMM.hMmdNd/      :mMNdmNMdo:.      .mmmmmmmmmNMNssssyMN           ::-.                         \n");
	printf("\t      .:ohmNNmhyo/:--..-:/+shNNms.          /NNdys/-.``oMMdNy.`/dNm+   -+dMMNNmmmmNmds:   +MM/:::::/MMh    `NM/          dNNmmdhyo+:-.                \n");
	printf("\t   -+hNMmho:.`               ./dMNo         :MM/-.     /MMm+    `/hNmshNNho:..   .-/sdNm+ dMm       mM/     hMh          dMs-/+oyhddmmd :so/:-.       \n");
	printf("\t  sNMNo-`                      `/NMy        .MMmNy     :Mh-       `sMMmo.  `-:::.     +NNdNMo       oN`     +MN          hMdo.      +MM:hMdddmmdhyo/  \n");
	printf("\t  `yMN+                .--.      /MM+       `s+dMd     .o        -hNMd.   +dhsyNm:   /dMmmMM-       .y      .NM/  ---:::-+omM-       NMdNN.    /oNMh  \n");
	printf("\t  `sMMo              dNdhdd/     MMy   .-----.sMN             -yNMMN.   /M+`/dh-  /dNMh.hMm                 dMy+hmmddhddddNN`       sMMMs      oMN-   \n");
	printf("\t     +NMy             +My`.dM-   .MMy/yddhhhhhdmMM.          .sNmomMh    /Mohd/` :hNmdMmsNMo                 sMNms/:/-```./hNh-      .NMN.     -NM+   \n");
	printf("\t      :NMmmMN:        `dM-.mM-   hMMNdo:--.```./yNh-        +mMNo-dMd     omo` .sdh+. /dNMM+                oNm+.`ym+`   `  /Nm-      hMs      dMd    \n");
	printf("\t       -ddsdMN-        :Mmmm/   yMMd/` /ds.   `  :Nm-       .:oydmNMN/                  /NMNo    :         oNd.  sMMs.``.y`  sMy      :N.     oMN-    \n");
	printf("\t        `  `mMm.        yd+.  :dMMy`  :NMy.``.o-  +Md           `.:sNNo               -odMm+`   `N+    /  -NN-   :NMMmddmy   /Md       o     -NMo     \n");
	printf("\t            .mMd`           :yMMMh`   .mMMmhhmm.  .MM`   s/.        /dNms:.      .-/sdNNMM-     :MN/  :N. +Md     -ohdhs/`   yMs  /          hMd`     \n");
	printf("\t             -NMh`        odMNyNM/     .ohddho.   /Mm   .MMNhs:.     `:sdmmmddddmmNmds/dMm      yMMN:.mM+ :MN`              oNd` .y         +MN-      \n");
	printf("\t              :NMy        mMN- NM/               .mN+   .MMosdNmhs:.     .:/sMMo/:-`  `NMh:     mNmMNdMMh  yMh.           -hNh.  oy        .NMo       \n");
	printf("\t               +MMo       +MM/ oMm.             /mMy    .MM-  ./sdNmhs:.    :MM-      -hdmmmmmddMy-mMNmMN` `sNmo-      -+hNm/    dh        hMd`       \n");
	printf("\t                oMM+       mMm `yNm/`         /hNNMo    .MM-      ./sdNNho: /MM-                    do:MM/   -odNmdhhdmmdNM:    -Md       +MN-        \n");
	printf("\t                 sMM/      /MM/  /dNmyo///+shmNd+hMh-:/+oMM-          ./sdNNdMM-                       NMmyso+/:mMm//:-`.MM:    oMd      .NMo         \n");
	printf("\t                 hMN:      mMm    -+ydmmmdhs/.  oNNNNmmdhy.              ./sdN-                         osyhmmNNNN`    :NNNmmdhNMm      hMd`          \n");
	printf("\t                  `dMN.     /MM/                                                                                         ``.-://sMN     /MN-          \n");
	printf("\t                   `mMm.``-+sMMm                                                                                                -NNyo/-.NMs           \n");
	printf("\t                    .NMmmMMNmyo/`                                                                                               `:+shmNNNm`           \n");
	printf("\t                     -dyo/-`                                                                                                                          \n\n\n" COLOR_DEFAULT);

	printf(AMARILLO"\t\t\t\t\t\t\t\t ARRECIFE SUPER SIMULATOR 1.0.0.\n"COLOR_DEFAULT);

	sleep(3);

	system("clear");                                                                                                                                          
}

/*
 *	PRE: ---
 *
 *	POST: Imprime por pantalla información útil para el usuario a la hora de visualizar el resultado del traslado.
 *		  Permite que se visualice la cantidad pedida de pokemon y el número de filtros de selección aplicados.
 *				   
 */
void mostrar_informacion(int filtro, int cant_seleccion){

	printf("\n\n--------------------------------------------------\n");
	printf("--------------------------------------------------\n");
	printf("\n FILTRO #%i | Cantidad solicitada a trasladar: %i pokemon\n\n", filtro, cant_seleccion);
}



int main(){

	srand ((unsigned)time(NULL));

	int cant_seleccion;
	bool hay_error = false;
	bool (*seleccionar_pokemon[MAX_FILTROS]) (pokemon_t*);
	void (*mostrar_pokemon[MAX_FILTROS]) (pokemon_t*);

	mostrar_bienvenida();

	inicializar_ptr_seleccion (seleccionar_pokemon);	
	inicializar_ptr_mostrar (mostrar_pokemon);

	arrecife_t* arrecife = crear_arrecife (RUTA_ARCHIVO_ARRECIFE);
	acuario_t* acuario = crear_acuario();

	for (int i = 0; i < MAX_FILTROS; i++){

		cant_seleccion = rand() %15;	
		mostrar_informacion(i + 1, cant_seleccion);

		if ( trasladar_pokemon (arrecife, acuario, seleccionar_pokemon[i], cant_seleccion) != ERROR ){
			censar_arrecife (arrecife, mostrar_pokemon[i]);
		
		}else{
			hay_error = true;
			mostrar_mensaje_error();
		}
	}

	if (!hay_error){
		guardar_datos_acuario(acuario, RUTA_ARCHIVO_ACUARIO);
	}
	
	liberar_arrecife(arrecife);
	liberar_acuario(acuario);

	return 0;
}
