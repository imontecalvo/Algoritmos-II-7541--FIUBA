#include "interaccion_usuario.h"
#include "../TDA_lista/TDA_lista.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define POKENOMBRE_MAX 15
#define NOMBRE_MAX 25

#define ROJO          "\033[31m"
#define VERDE         "\033[32m"
#define VERDE_CLARO   "\033[92m"
#define AMARILLO      "\033[93m"
#define AZUL_CLARO    "\033[94m"
#define AZUL          "\033[34m"
#define MAGENTA       "\033[35m"
#define CYAN          "\033[36m"
#define GRIS          "\033[1;3;90m"

#define AZUL_FONDO      "\033[44m"
#define ROJO_FONDO      "\033[41m"
#define VERDE_FONDO     "\033[42m"
#define AMARILLO_FONDO  "\033[43m"

#define NORMAL "\033[0m"


typedef struct pokemon{
	char nombre[POKENOMBRE_MAX];
	int velocidad;
	int defensa;
	int ataque;
    int pokemejoras;
}pokemon_t;

typedef struct entrenador{
	char nombre[NOMBRE_MAX];
	lista_t* pokemones;
}entrenador_t;

typedef struct gimnasio{
	char nombre[NOMBRE_MAX];
	int dificultad;
	int id_batalla;
	char lider[NOMBRE_MAX];
	lista_t* entrenadores;
}gimnasio_t;

typedef struct personaje{
	char nombre[NOMBRE_MAX];
	lista_t* pokemon_para_combatir;
	lista_t* pokemon_obtenidos;
}personaje_t;


const char ARRIBA = 'w', ABAJO = 's';
static const char VICTORIA = 'V';
const int  GANO_PRIMERO = 1;


//------------------------- FUNCIONES GENERALES -------------------------


void mostrar_intro(){

	system("clear");
	printf(AZUL"\n\n");

    printf("\t                                                                  :md                                                      \n");  
    printf("\t                                                                 hNodN/                                                    \n");  
    printf("\t                                                               sNy.  sNy                                                   \n");  
    printf("\t                                                             +md    odds                                                   \n");  
    printf("\t           -:/+osssso+:-                +shmN   yNNy-       hNm/oddy+       /////    mmmmm                                 \n");  
    printf("\t      -+ydNmdhyyssssyhdNms:          hmmdhs+:  NyNs:hNh     sMMNMMNdho/    mMysssshMM:   yM            yo+:                \n");  
    printf("\t  ./ymmds/-           .+hNd:         m--    .MNm:  `-yNd+ymdyo/    +sdmy  MN      Nm     /Mh         oMy+oyyhddmy          \n");  
    printf("\t /NMh/                  `/NN/        Nmm    `Ny.     `+NMh:   ://-    +NNdMs      ho     `NN`       +Mh+     .NM:mmhhdddyo/\n");  
    printf("\t  oMm-            :/+/-    /MN        :NM     /`     -yNMs   oh++md-  +mNyNM:      /      hM/`-:+ooo+omd      sMmM+    -mMo\n");  
    printf("\t   +NN            mN+sms   .MM.-/ossso/NM:         .smmMm    M//ho  /dNMy/Mm`      `      +Mdddyso++shNd.     .NMm`    /Nd`\n");  
    printf("\t    :mNoyd        /M/ dm   sMMdhs+/:-/ohNs       .omN++Md    hdy.`:hms:yNNMy              yNh  ss.     dm-     hMo     mN: \n");  
    printf("\t     -ddyNN        hmym/  +MMh: :y:     :mh      .+yhhdMN-              -yMNo            hN/  mMs.  +   Nd     /N`    yMs  \n");  
    printf("\t         +Mm       -d+   yMN+   NM/. -s  /Mo          -+mm/            -omNo    yo   :  oMo   yNNmddh   dN      +    :Nd`  \n");  
    printf("\t          oMd          sNMMs    hNNmdms  .Mh   ho-.      ymds/     /oydmNMy     NN+ .m/ yM-    :+so:   :Ny           mN:   \n");  
    printf("\t           sMh       yNNohM:     :++/-   oM+   MNmdho-.    /shdmNmdhyo:.mM/     MNN/hMy +Ns           :md  +/       sMs    \n");  
    printf("\t            hMy      oMd +Ms            +Nh`   Mm`-+hmdh+-     sMs`    .mNhhysohN NNNMm  sNy-      ./hms   h+      :Nm`    \n");  
    printf("\t             dMs      NM/`yNs.        /hNM+    Mm    `-+hmdy+  sMo                   mM-  -yddyssyhdNM/    No      mN:     \n");  
    printf("\t              mM+     +Md  /dmyo+/+oydmsoMy:/+oMm        `-+hmdmMo                    Ndyso++      .dM    oMo     sMs      \n");  
    printf("\t               NM/     mM/    /oyyso/-   mmdhyso/            `-+h+                                  yhdmddmMs    :Nm`      \n");  
    printf("\t                NN:    oMm                                                                                /Mh.   dN:       \n");  
    printf("\t                 MNoyhmNmh.                                                                                ydmdhhMy        \n");  
    printf("\t                  mhs/:                                                                                        :+s`        \n");

	printf(AMARILLO"%50c SUPER AVENTURA POKEMON SIMULATOR 1.0.0\n"NORMAL, ' ');

	sleep(1);

	system("clear");                                                                                                                                          
}

/*
 * Imprime una interfaz de un menu y solicita al usuario que 
 * seleccione una opción válida para dicho menu.
 * Devuelve la letra de la opción válida elegida por el usuario.
 */ 
char menu_generico( void (*mostrar_interfaz)(char, bool), bool (*es_letra_valida)(char, bool), bool adicional  ){

    mostrar_interfaz(0, adicional);

    char letra;
    printf("\n\tOPCIÓN SELECCIONADA: ");
    scanf(" %c", &letra);

    while(!es_letra_valida(letra, adicional)){
        mostrar_interfaz(letra, adicional);
        printf("\tPor favor, ingresá una letra válida :)\n");
        printf("\n\tOPCIÓN SELECCIONADA: ");
        scanf(" %c", &letra);
    }
    
    mostrar_interfaz(letra,adicional);
    sleep(1);
    return letra;
}

/*
 * Imprime por pantalla el dibujo de un archivo.
 */ 
void imprimir_archivo_ascii_art(){

    printf(VERDE_CLARO"\t\t\t%32c╔══════════════╗\n", ' ');
	printf(           "\t\t\t%32c║              ║\n", ' ');
	printf(           "\t\t\t%32c║     FILE     ║\n", ' ');
	printf(           "\t\t\t%32c║              ║\n", ' ');
	printf(           "\t\t\t%32c║              ║\n", ' ');
	printf(           "\t\t\t%32c║     ▛▘▛▘▌▌   ║\n", ' ');
	printf(           "\t\t\t%32c║  ▗  ▙▖▄▌▚▘   ║\n", ' ');
	printf(           "\t\t\t%32c║              ║\n", ' ');
	printf(           "\t\t\t%32c║              ║\n", ' ');
	printf(           "\t\t\t%32c╚══════════════╝\n\n\n"NORMAL, ' ');
}

/*
 * Imprime por pantalla dibujo del apartado 'Información'
 */ 
void imprimir_info_ascii_art(){

    printf("\t\t\t%30c"VERDE_CLARO"           █████████       \n", ' ');
    printf("\t\t\t%30c"           "          ██       ██      \n", ' ');   
    printf("\t\t\t%30c"           " ▘  ▐▘    ██       ██      \n", ' ');
    printf("\t\t\t%30c"           " ▌▛▌▜▘▛▌  ██       ██      \n", ' ');
    printf("\t\t\t%30c"           " ▌▌▌▐ ▙▌   █████████       \n", ' ');
    printf("\t\t\t%30c"           "                    ██     \n", ' ');
    printf("\t\t\t%30c"           "                      ██   \n", ' ');
    printf("\t\t\t%30c"           "                        ██ \n\n\n"NORMAL, ' ');
}

/*
 * Imprime por pantalla un pokemon junto con sus caracteristicas.
 */ 
void imprimir_pokemon_normal(pokemon_t pokemon, int nro){

    printf("     ║ %-3i║ %-15s║      %-5i║   %-5i║    %-5i║", 
            nro, pokemon.nombre, pokemon.velocidad, pokemon.ataque, pokemon.defensa);
    
}

/*
 * Imprime por pantalla un pokemon junto con sus caracteristicas
 * usando un fondo rojo (está seleccionado).
 */ 
void imprimir_pokemon_seleccionado(pokemon_t pokemon, int nro){

    printf(" --> ║ %-3i║"ROJO_FONDO" %-15s"NORMAL"║      %-5i║   %-5i║    %-5i║",
           nro, pokemon.nombre, pokemon.velocidad, pokemon.ataque, pokemon.defensa);
}

/*
 * Imprime por pantalla toda una lista de pokemones.
 * Si el apuntado coincide con una posición válida, dicho
 * pokemon será mostrado 'seleccionado'.
 */ 
void imprimir_lista_pokemon(lista_t* lista_pokemones, int apuntador){
	
	printf("%40c╔════╦════════════════╦═══════════╦════════╦═════════╗\n", ' ');
	printf("%40c║ n° ║     NOMBRE     ║ VELOCIDAD ║ ATAQUE ║ DEFENSA ║\n", ' ');

    lista_iterador_t* iterador =  lista_iterador_crear(lista_pokemones);

    int i = 0;
    while(lista_iterador_tiene_siguiente(iterador)){

		pokemon_t pokemon = *(pokemon_t*)lista_iterador_elemento_actual(iterador);

        printf("%35c", ' ');
        if( apuntador == i)
			imprimir_pokemon_seleccionado(pokemon, i);
		else
            imprimir_pokemon_normal(pokemon, i);
        printf("\n");

        lista_iterador_avanzar(iterador);
        i++;
    }
	printf("%40c╚════╩════════════════╩═══════════╩════════╩═════════╝\n", ' ');

    lista_iterador_destruir(iterador);
}


//------------------------- MENU INICIO -------------------------

/*
 * Devuelve TRUE si la letra recibida corresponde a una opción válida
 * del MENU INICIO.
 * De lo contrario, devuelve FALSE.
 */ 
bool es_letra_valida_inicio(char letra, bool juego_inicializado){

    return ( letra == ARCH_ENTRENADOR_PPAL_MAYUS   ||  letra == ARCH_ENTRENADOR_PPAL_MINUS   ||
             letra == ARCH_GIMNASIOS_MAYUS         ||  letra == ARCH_GIMNASIOS_MINUS         ||
            ( juego_inicializado                   &&
            (letra == COMENZAR_PARTIDA_MAYUS       ||  letra == COMENZAR_PARTIDA_MINUS       ||
             letra == SIMULAR_PARTIDA_MAYUS        ||  letra == SIMULAR_PARTIDA_MINUS       )    ));
}

/*
 * Imprime por pantalla la interfaz del MENU INICIO, mostrando
 * todas las opciones disponibles.
 */
void mostrar_interfaz_inicio(char letra, bool juego_inicializado){

    system("clear");
    printf("\n\t\t\t╔══════════════════════════════════════════════════╗\n");
    printf("\t\t\t║%50c║\n", ' ');
    printf("\t\t\t║%7c██╗███╗   ██╗██╗ ██████╗██╗ ██████╗ %7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║████╗  ██║██║██╔════╝██║██╔═══██╗%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║██╔██╗ ██║██║██║     ██║██║   ██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║██║╚██╗██║██║██║     ██║██║   ██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║██║ ╚████║██║╚██████╗██║╚██████╔╝%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c╚═╝╚═╝  ╚═══╝╚═╝ ╚═════╝╚═╝ ╚═════╝ %7c║\n", ' ', ' ');
    printf("\t\t\t║%50c║\n", ' ');
    printf("\t\t\t╚══════════════════════════════════════════════════╝\n");
    printf("\n\n");


    printf("\n\tSeleccioná una opción introduciendo la letra indicada:\n\n");

    if( (letra == ARCH_ENTRENADOR_PPAL_MAYUS) || (letra == ARCH_ENTRENADOR_PPAL_MINUS) )
        printf("\n\t\t" AZUL_FONDO "> %c para ingresar el archivo del entrenador principal.\n"NORMAL, 
                ARCH_ENTRENADOR_PPAL_MAYUS);
    else
        printf("\n\t\t> " AZUL "%c"NORMAL" para ingresar el "AZUL"archivo del entrenador principal.\n"NORMAL, 
                ARCH_ENTRENADOR_PPAL_MAYUS);


    if( letra == ARCH_GIMNASIOS_MAYUS || (letra == ARCH_GIMNASIOS_MINUS) )
        printf("\n\t\t" ROJO_FONDO "> %c para añadir un o varios gimnasios.\n"NORMAL, ARCH_GIMNASIOS_MAYUS);
    else
        printf("\n\t\t> " ROJO "%c"NORMAL" para añadir un o varios "ROJO"gimnasios.\n"NORMAL, ARCH_GIMNASIOS_MAYUS);
    

    if( ((letra == COMENZAR_PARTIDA_MAYUS) || (letra == COMENZAR_PARTIDA_MINUS)) && juego_inicializado)
        printf("\n\t\t" VERDE_FONDO "> %c para comenzar la partida.\n"NORMAL, COMENZAR_PARTIDA_MAYUS);
    else if (juego_inicializado)
       printf("\n\t\t> " VERDE "%c"NORMAL" para "VERDE"comenzar la partida.\n"NORMAL, COMENZAR_PARTIDA_MAYUS);
    else
       printf("\n\t\t> " GRIS "%c para comenzar la partida. [OPCIÓN BLOQUEADA -> INICIALIZAR JUEGO]\n"NORMAL, 
                COMENZAR_PARTIDA_MAYUS);
    
    
    if( ((letra == SIMULAR_PARTIDA_MAYUS) || (letra == SIMULAR_PARTIDA_MINUS)) && juego_inicializado)
        printf("\n\t\t" AMARILLO_FONDO "> %c para simular la partida."NORMAL"\n\n\n", SIMULAR_PARTIDA_MAYUS);
    else if (juego_inicializado)
        printf("\n\t\t> " AMARILLO "%c"NORMAL" para "AMARILLO"simular la partida."NORMAL"\n\n\n", SIMULAR_PARTIDA_MAYUS);
    else
       printf("\n\t\t> " GRIS "%c para simular la partida. [OPCIÓN BLOQUEADA -> INICIALIZAR JUEGO]"NORMAL"\n\n\n", 
                SIMULAR_PARTIDA_MAYUS);

}

char menu_inicio(bool juego_inicializado){
    return menu_generico(mostrar_interfaz_inicio, es_letra_valida_inicio, juego_inicializado);
}

void pedir_archivo_entrenador_ppal(char* ruta_archivo){
    
    system("clear");

	printf("\n\t\t\t    ╔═══════════════════════════════════════════════════════════════════════╗\n");
	printf("\t\t\t    ║*· · · · · · · · · ·  ARCHIVO ENTRENADOR PRINCIPAL · · · · · · · · · ·*║\n");
	printf("\t\t\t    ╚═══════════════════════════════════════════════════════════════════════╝\n\n");

    imprimir_archivo_ascii_art();

    printf("\n\t\t\tIngresá a continuación el archivo que contiene la informacion del entrenador principal :)\n");
    printf("\t\t\t"ROJO"ATENCIÓN: Para un correcto funcionamiento, asegurate que tenga formato CSV"NORMAL"\n\n");
    printf("\t\t\t"AMARILLO"> ARCHIVO: "NORMAL);
    scanf("%99s", ruta_archivo);
}

void pedir_archivo_gimnasios(char* ruta_archivo){
    
    system("clear");

	printf("\n\t\t\t    ╔═══════════════════════════════════════════════════════════════════════╗\n");
	printf("\t\t\t    ║*· · · · · · · · · · · · · ARCHIVO GIMNASIOS · · · · · · · · · · · · ·*║\n");
	printf("\t\t\t    ╚═══════════════════════════════════════════════════════════════════════╝\n\n");

    imprimir_archivo_ascii_art();

    printf("\n\t\t\tIngresá a continuación el archivo que contiene la informacion de los gimnasios :)\n");
    printf("\t\t\t"ROJO"ATENCIÓN: Para un correcto funcionamiento, asegurate que tenga formato CSV"NORMAL"\n\n");
    printf("\t\t\t"AMARILLO"> ARCHIVO: "NORMAL);
    scanf("%99s", ruta_archivo);
}


//------------------------- MENU GIMNASIO -------------------------

/*
 * Imprime por pantalla la interfaz del MENU GIMNASIO, mostrando
 * todas las opciones disponibles.
 */
void mostrar_interfaz_gimnasio(char letra, bool adicional){
    
    system("clear");

    printf("\n\t\t\t╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║%75c║\n", ' ');
    printf("\t\t\t║%7c ██████╗ ██╗███╗   ███╗███╗   ██╗ █████╗ ███████╗██╗ ██████╗ %7c║\n", ' ', ' ' );
    printf("\t\t\t║%7c██╔════╝ ██║████╗ ████║████╗  ██║██╔══██╗██╔════╝██║██╔═══██╗%7c║\n", ' ', ' ' );
    printf("\t\t\t║%7c██║  ███╗██║██╔████╔██║██╔██╗ ██║███████║███████╗██║██║   ██║%7c║\n", ' ', ' ' );
    printf("\t\t\t║%7c██║   ██║██║██║╚██╔╝██║██║╚██╗██║██╔══██║╚════██║██║██║   ██║%7c║\n", ' ', ' ' );
    printf("\t\t\t║%7c╚██████╔╝██║██║ ╚═╝ ██║██║ ╚████║██║  ██║███████║██║╚██████╔╝%7c║\n", ' ', ' ' );
    printf("\t\t\t║%7c ╚═════╝ ╚═╝╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝ ╚═════╝ %7c║\n", ' ', ' ' );
    printf("\t\t\t║%75c║\n", ' ');
    printf("\t\t\t╚═══════════════════════════════════════════════════════════════════════════╝\n");


    printf("\n\tSeleccioná una opción introduciendo la letra indicada:\n\n");

    if( (letra == INFO_ENTRENADOR_PPAL_MAYUS) || (letra == INFO_ENTRENADOR_PPAL_MINUS) )
        printf("\n\t\t" AZUL_FONDO "> %c para visualizar la información del entrenador principal.\n"NORMAL,
                INFO_ENTRENADOR_PPAL_MAYUS);
    else
        printf("\n\t\t> " AZUL "%c"NORMAL" para visualizar la "AZUL"información del entrenador principal.\n"NORMAL,
                INFO_ENTRENADOR_PPAL_MAYUS);


    if( (letra == INFO_GIMNASIO_MAYUS) || (letra == INFO_GIMNASIO_MINUS) )
        printf("\n\t\t" ROJO_FONDO "> %c para visualizar_la información del gimnasio actual.\n"NORMAL, 
                INFO_GIMNASIO_MAYUS);
    else
        printf("\n\t\t> " ROJO "%c"NORMAL" para visualizar la "ROJO"información del gimnasio actual.\n"NORMAL, 
                INFO_GIMNASIO_MAYUS);
    

    if( (letra == REARMAR_EQUIPO_MAYUS) || (letra == REARMAR_EQUIPO_MINUS) )
        printf("\n\t\t" VERDE_FONDO "> %c para rearmar tu equipo.\n"NORMAL, REARMAR_EQUIPO_MAYUS);
    else
       printf("\n\t\t> " VERDE "%c"NORMAL" para "VERDE"rearmar tu equipo.\n"NORMAL, REARMAR_EQUIPO_MAYUS);
    

    if( (letra == PROXIMA_BATALLA_MAYUS) || (letra == PROXIMA_BATALLA_MINUS) )
        printf("\n\t\t" AMARILLO_FONDO "> %c para ir hacia la siguiente batalla."NORMAL"\n\n\n", 
                PROXIMA_BATALLA_MAYUS);
    else
        printf("\n\t\t> " AMARILLO "%c"NORMAL" para ir hacia la "AMARILLO"siguiente batalla."NORMAL"\n\n\n", 
                PROXIMA_BATALLA_MAYUS);

}

/*
 * Devuelve TRUE si la letra recibida corresponde a una opción válida
 * del MENU GIMNASIO.
 * De lo contrario, devuelve FALSE.
 */ 
bool es_letra_valida_gimnasio(char letra, bool adicional){

    return ( letra == INFO_ENTRENADOR_PPAL_MAYUS   ||  letra == INFO_ENTRENADOR_PPAL_MINUS   ||
             letra == INFO_GIMNASIO_MAYUS          ||  letra == INFO_GIMNASIO_MINUS          ||
             letra == REARMAR_EQUIPO_MAYUS         ||  letra == REARMAR_EQUIPO_MINUS         ||
             letra == PROXIMA_BATALLA_MAYUS        ||  letra == PROXIMA_BATALLA_MINUS           );
}

char menu_gimnasio(){
    return menu_generico(mostrar_interfaz_gimnasio, es_letra_valida_gimnasio, NULL);
}


void mostrar_info_entrenador_ppal(void* personaje){

    personaje_t personaje_aux = *(personaje_t*)personaje;

    system("clear");

	printf("\n\t\t\t    ╔═══════════════════════════════════════════════════════════════════════╗\n");
	printf("\t\t\t    ║*· · · · · · · · · · · · · ENTRENADOR PRINCIPAL· · · · · · · · · · · ·*║\n");
	printf("\t\t\t    ╚═══════════════════════════════════════════════════════════════════════╝\n\n");

    imprimir_info_ascii_art();

    printf(AMARILLO"\t\t\t%25c╔════════════════════════════════════╗\n", ' ');
    printf(        "\t\t\t%25c║ NOMBRE:  %-25s ║\n",' ', personaje_aux.nombre);
    printf(        "\t\t\t%25c╚════════════════════════════════════╝\n"NORMAL, ' ');

    imprimir_lista_pokemon( personaje_aux.pokemon_obtenidos, -1);

    char letra;
    printf("\n\tPara volver al MENU GIMNASIO, apretá cualquier letra: ");
    scanf(" %c", &letra);
}

void mostrar_info_gimnasio(void* gimnasio){

    gimnasio_t gimnasio_aux = *(gimnasio_t*)gimnasio;

    system("clear");

	printf("\n\t\t\t    ╔═══════════════════════════════════════════════════════════════════════╗\n");
	printf("\t\t\t    ║*· · · · · · · · · · · · · · GIMNASIO ACTUAL · · · · · · · · · · · · ·*║\n");
	printf("\t\t\t    ╚═══════════════════════════════════════════════════════════════════════╝\n\n");

    imprimir_info_ascii_art();

    size_t cantidad_entrenadores = lista_elementos(gimnasio_aux.entrenadores);

    printf(AMARILLO"\t\t\t%25c╔════════════════════════════════════╗\n", ' ');
    printf(        "\t\t\t%25c║ NOMBRE:  %-25s ║\n",' ', gimnasio_aux.nombre);
    printf(        "\t\t\t%25c╠════════════════════════════════════╣\n", ' ');
    printf(        "\t\t\t%25c║ LIDER:   %-25s ║\n",' ', gimnasio_aux.lider);
    printf(        "\t\t\t%25c║ DIFICULTAD:   %-20i ║\n",' ', gimnasio_aux.dificultad);
    printf(        "\t\t\t%25c║ ID BATALLA:   %-20i ║\n",' ', gimnasio_aux.id_batalla);
    printf(        "\t\t\t%25c║%35c ║\n",' ', ' ');
    printf(        "\t\t\t%25c║"ROJO" RIVALES RESTANTES: %-15lu"AMARILLO" ║\n",' ', cantidad_entrenadores);
    printf(        "\t\t\t%25c╚════════════════════════════════════╝\n"NORMAL, ' ');

    char letra;
    printf("\n\tPara volver al MENU GIMNASIO, apretá cualquier letra: ");
    scanf(" %c", &letra);
}

/*
 * Imprime por pantalla las instrucciones que debe seguir el 
 * usuario durante el re-armado del equipo de pokemones de combate.
 */ 
void mostrar_instrucciones_rearmar_equipo(){
	printf("\nSeleccioná el pokemon que desea retirar de la primera lista:\n");
	printf("\t> Usá %c para moverte hacia arriba y %c para moverte hacia abajo.\n", ARRIBA, ABAJO);
	printf("\t> Si ya estas apuntando al pokemon que deseas retirar, apretá %c\n\n", SELECCIONAR_POKEMON_MAYUS);
	printf("(Para realizar cada acción, apretá ENTER luego de la respectiva tecla indicada!)\n");
}

/*
 * Recibe dos listas válidas y existentes e imprime los pokemones 
 * que contiene cada una de ellas. Además si el apuntador recibido
 * coincide con la posición de algun pokemon de la lista, lo 
 * imprime con fondo rojo (seleccionado).
 */ 
void imprimir_ambas_listas(lista_t* lista_1, lista_t* lista_2, int pos_apuntador_1, int pos_apuntador_2){

    lista_iterador_t* iterador_1 =  lista_iterador_crear(lista_1);
    lista_iterador_t* iterador_2 =  lista_iterador_crear(lista_2);

    int i = 0;
	while(lista_iterador_tiene_siguiente(iterador_1) && lista_iterador_tiene_siguiente(iterador_2)){
		pokemon_t* pokemon_combate = lista_iterador_elemento_actual(iterador_1);
		pokemon_t* pokemon_obtenido = lista_iterador_elemento_actual(iterador_2);

        if( i == pos_apuntador_1 )
            imprimir_pokemon_seleccionado(*pokemon_combate, i);
        else 
            imprimir_pokemon_normal(*pokemon_combate, i);
        
        printf("%8c", ' ');

        if(i == pos_apuntador_2 )
            imprimir_pokemon_seleccionado(*pokemon_obtenido, i);
        else
            imprimir_pokemon_normal(*pokemon_obtenido, i);
        
        printf("\n");

        lista_iterador_avanzar(iterador_1);
        lista_iterador_avanzar(iterador_2);
        i++;
    }

    printf("     ╚════╩════════════════╩═══════════╩════════╩═════════╝");

    if( !lista_iterador_tiene_siguiente(iterador_2) )
		printf("%13c╚════╩════════════════╩═══════════╩════════╩═════════╝", ' ');
    
    else{

        bool primera_iteracion = true;
        while( lista_iterador_tiene_siguiente(iterador_2) ){
            pokemon_t* pokemon_obtenido = lista_iterador_elemento_actual(iterador_2);
            
            if(primera_iteracion)
                printf("%8c", ' ');
            else
                printf("%67c", ' ');

            if(i == pos_apuntador_2 )
                imprimir_pokemon_seleccionado(*pokemon_obtenido, i);
            else
                imprimir_pokemon_normal(*pokemon_obtenido, i);

            printf("\n");

            lista_iterador_avanzar(iterador_2);
            primera_iteracion = false;
            i++;
        }

        printf("%72c╚════╩════════════════╩═══════════╩════════╩═════════╝\n", ' ' );
    }   

    lista_iterador_destruir(iterador_1);
    lista_iterador_destruir(iterador_2);

}

void mostrar_rearmar_equipo(void* personaje, int pos_apuntador_1, int pos_apuntador_2){

    personaje_t personaje_aux = *(personaje_t*)personaje;

	system("clear");

	printf("\n\t\t\t    ╔═══════════════════════════════════════════════════════════════════════╗\n");
	printf("\t\t\t    ║*· · · · · · · · · · · · · REARMAR TU EQUIPO · · · · · · · · · · · · ·*║\n");
	printf("\t\t\t    ╚═══════════════════════════════════════════════════════════════════════╝\n");

	printf("\n\n\t\t    ╔══════════════════════╗%38c╔════════════════════════╗\n", ' ');
	printf("\t\t    ║ POKEMONES DE COMBATE ║%38c║  POKEMONES OBTENIDOS   ║\n", ' ');
	printf("\t\t    ╚══════════════════════╝%38c╚════════════════════════╝\n", ' ');
	printf("     ╔════╦════════════════╦═══════════╦════════╦═════════╗%13c", ' ');
    printf("╔════╦════════════════╦═══════════╦════════╦═════════╗\n");
	printf("     ║ n° ║     NOMBRE     ║ VELOCIDAD ║ ATAQUE ║ DEFENSA ║%13c", ' ');
    printf("║ n° ║     NOMBRE     ║ VELOCIDAD ║ ATAQUE ║ DEFENSA ║\n");

    imprimir_ambas_listas(personaje_aux.pokemon_para_combatir, personaje_aux.pokemon_obtenidos, 
                          pos_apuntador_1, pos_apuntador_2);
    
	mostrar_instrucciones_rearmar_equipo();
}

/*
 * Si recibe la letra 'w', el apuntador disminuye en 1, y si recibe
 * la letra 's', aumenta en 1. Siempre se mantiene dentro de los 
 * limites 0 - tope.
 */ 
void hacer_movimiento(char letra, int* pos_apuntador, size_t tope){
	
	if(letra == ARRIBA && *pos_apuntador > 0)
		(*pos_apuntador) --;
		
	if(letra == ABAJO && (*pos_apuntador < tope) )
		(*pos_apuntador) ++;

}

/*
 * Solicita al usuario que seleccione un pokemon de la lista mostrada
 * a través de una interfaz interactiva.
 */ 
void seleccionar_pokemon_rearmar_equipo(int* apuntador, int apuntador_secundario, size_t tope, personaje_t personaje){
	
	char letra = 0;

	while( (letra != SELECCIONAR_POKEMON_MAYUS) && (letra != SELECCIONAR_POKEMON_MINUS)  ){

		scanf(" %c", &letra);
		hacer_movimiento(letra, apuntador, tope);

		if(apuntador_secundario == FUERA_DE_RANGO)
			mostrar_rearmar_equipo(&personaje, *apuntador, apuntador_secundario);
		else
			mostrar_rearmar_equipo(&personaje, apuntador_secundario, *apuntador);

		printf("\nPOSICION SELECCIONADA: %i\n", *apuntador);
	}
}

void solicitar_posiciones_cambio(int* apuntador_1, int* apuntador_2, void* personaje){

    personaje_t* personaje_aux = (personaje_t*)personaje;

	*apuntador_1 = PRIMERA_POSICION;
	*apuntador_2 = FUERA_DE_RANGO;

	seleccionar_pokemon_rearmar_equipo(apuntador_1, FUERA_DE_RANGO, lista_elementos(personaje_aux->pokemon_para_combatir) - 1, 
									  *personaje_aux);
	
	*apuntador_2 = PRIMERA_POSICION;
	
	mostrar_rearmar_equipo(personaje_aux, *apuntador_1, *apuntador_2);
	
	seleccionar_pokemon_rearmar_equipo(apuntador_2, *apuntador_1, lista_elementos(personaje_aux->pokemon_obtenidos) - 1, 
									  *personaje_aux);

}

char solicitar_continuar_cambios(){

    char letra;

	printf("\n Querés terminar los cambios? Apretá 'y' para sí, 'n' para no: ");
	scanf(" %c", &letra);

	if( (letra != SI_MAYUS) && (letra != SI_MINUS) && (letra != NO_MAYUS) && (letra != NO_MINUS) ){
		printf("\n Asegurate de apretar 'y' (Sí) o 'n' (No) :)  Elegí una opción: ");
		scanf(" %c", &letra);
	}

    return letra;
}

//------------------------- MENU BATALLA -------------------------

/*
 * Devuelve TRUE si la letra recibida corresponde a una opción válida
 * del MENU BATALLA.
 * De lo contrario, devuelve FALSE.
 */ 
bool es_letra_valida_batalla(char letra){

    return ( letra == CONTINUAR_MAYUS || letra == CONTINUAR_MINUS );
}

/*
 * Imprime por pantalla la interfaz del MENU BATALLA, mostrando
 * todas las opciones disponibles.
 */
void mostrar_interfaz_batalla(pokemon_t pkm_1, pokemon_t pkm_2, int id_batalla, int ganador){


    system("clear");

    printf("\n\t\t\t╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║%71c║\n", ' ');
    printf("\t\t\t║%7c██████╗  █████╗ ████████╗ █████╗ ██╗     ██╗      █████╗ %7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗██║     ██║     ██╔══██╗%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██████╔╝███████║   ██║   ███████║██║     ██║     ███████║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██╔══██╗██╔══██║   ██║   ██╔══██║██║     ██║     ██╔══██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██████╔╝██║  ██║   ██║   ██║  ██║███████╗███████╗██║  ██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝%7c║\n", ' ', ' ');
    printf("\t\t\t║%71c║\n", ' ');
    printf("\t\t\t╚═══════════════════════════════════════════════════════════════════════╝\n\n\n");

    printf("\t\t                             "AMARILLO    "██╗   ██╗███████╗  \n"                                 NORMAL);
    printf(AZUL"\t\t╔════════════════════╗"AMARILLO"       ██║   ██║██╔════╝       "ROJO"╔════════════════════╗\n"NORMAL);   
    printf(AZUL"\t\t║     %-15s║"          AMARILLO"       ██║   ██║███████╗       "ROJO"║     %-15s║\n"          NORMAL, 
           pkm_1.nombre, pkm_2.nombre);
    printf(AZUL"\t\t╚════════════════════╝"AMARILLO"       ╚██╗ ██╔╝╚════██║       "ROJO"╚════════════════════╝\n"NORMAL);
    printf(AMARILLO      "\t\t                              ╚████╔╝ ███████║  \n"                                       );
    printf(              "\t\t                               ╚═══╝  ╚══════╝  \n"                                 NORMAL);

    printf("\t\t"AZUL"╔═══════════╦═════════╗%30c" ROJO"╔═══════════╦═════════╗\n" NORMAL, ' ');
    printf("\t\t"AZUL"║ VELOCIDAD ║  %-5i  ║%30c"ROJO  "║ VELOCIDAD ║  %-5i  ║\n"NORMAL, pkm_1.velocidad, ' ' , pkm_2.velocidad);
    printf("\t\t"AZUL"╠═══════════╬═════════╣%30c" ROJO"╠═══════════╬═════════╣\n" NORMAL, ' ');
    printf("\t\t"AZUL"║   ATAQUE  ║  %-5i  ║%30c"ROJO  "║   ATAQUE  ║  %-5i  ║\n"NORMAL, pkm_1.velocidad, ' ' , pkm_2.velocidad);
    printf("\t\t"AZUL"╠═══════════╬═════════╣%30c" ROJO"╠═══════════╬═════════╣\n" NORMAL, ' ');
    printf("\t\t"AZUL"║  DEFENSA  ║  %-5i  ║%30c"ROJO  "║  DEFENSA  ║  %-5i  ║\n"NORMAL, pkm_1.velocidad, ' ' , pkm_2.velocidad);
    printf("\t\t"AZUL"╚═══════════╩═════════╝%30c" ROJO"╚═══════════╩═════════╝\n" NORMAL, ' ');

    printf("\t\t%28c╔════════════════════╗\n", ' ');
    printf("\t\t%28c║   ID BATALLA: %-5i║\n", ' ', id_batalla);
    printf("\t\t%28c╚════════════════════╝\n\n", ' ');

    pokemon_t pkm_ganador;
    
    if ( ganador == GANO_PRIMERO)
        pkm_ganador = pkm_1;
    else
        pkm_ganador = pkm_2;
        
    printf("\n\t\t"AMARILLO"    ╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t    ║*· · · · · · · · · · · · GANADOR: %-15s· · · · · · · · · · ·*║\n", pkm_ganador.nombre);
    printf("\t\t    ╚═══════════════════════════════════════════════════════════════════════╝\n"NORMAL);


}


void menu_batalla(void* pokemon_1, void* pokemon_2, int id_batalla, int ganador){
    
    pokemon_t pokemon_1_aux = *(pokemon_t*)pokemon_1;
    pokemon_t pokemon_2_aux = *(pokemon_t*)pokemon_2;

    mostrar_interfaz_batalla(pokemon_1_aux, pokemon_2_aux, id_batalla, ganador);

    char letra;
    printf("\n\tIngresá %c para avanzar a la próxima batalla de pokemones: ", CONTINUAR_MAYUS);
    scanf(" %c", &letra);

    while(!es_letra_valida_batalla(letra)){
        mostrar_interfaz_batalla(pokemon_1_aux, pokemon_2_aux, id_batalla, ganador);
        printf("\n\tAcordate que debes ingresar la letra %c :)\n", CONTINUAR_MAYUS);
        printf("\tIngresá %c para avanzar a la próxima batalla de pokemones: ", CONTINUAR_MAYUS);
        scanf(" %c", &letra);
    }
}


//------------------------- MENU VICTORIA -------------------------

/*
 * Imprime por pantalla una animación que indica haber 
 * ganado la partida.
 */ 
void animacion_victoria(){

    system("clear");
    sleep(1);

    printf(VERDE_CLARO"\n");
    printf("\t\t\t"VERDE_CLARO" ██████╗ \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██╔════╝ \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║  ███╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║   ██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"╚██████╔╝\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO" ╚═════╝ \n"NORMAL);

    sleep(1);
    system("clear");

    printf("\n");
    printf("\t\t\t"VERDE_CLARO" ██████╗  █████╗ \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██╔════╝ ██╔══██╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║  ███╗███████║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║   ██║██╔══██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"╚██████╔╝██║  ██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO" ╚═════╝ ╚═╝  ╚═╝\n"NORMAL);

    sleep(1);
    system("clear");

    printf("\n");
    printf("\t\t\t"VERDE_CLARO" ██████╗  █████╗ ███╗   ██╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██╔════╝ ██╔══██╗████╗  ██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║  ███╗███████║██╔██╗ ██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║   ██║██╔══██║██║╚██╗██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"╚██████╔╝██║  ██║██║ ╚████║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO" ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝\n"NORMAL);

    sleep(1);
    system("clear");

    printf("\n");
    printf("\t\t\t"VERDE_CLARO" ██████╗  █████╗ ███╗   ██╗ █████╗ \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██╔════╝ ██╔══██╗████╗  ██║██╔══██╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║  ███╗███████║██╔██╗ ██║███████║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║   ██║██╔══██║██║╚██╗██║██╔══██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"╚██████╔╝██║  ██║██║ ╚████║██║  ██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO" ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝\n"NORMAL);

    sleep(1);
    system("clear");

    printf("\n");
    printf("\t\t\t"VERDE_CLARO" ██████╗  █████╗ ███╗   ██╗ █████╗ ███████╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██╔════╝ ██╔══██╗████╗  ██║██╔══██╗██╔════╝\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║  ███╗███████║██╔██╗ ██║███████║███████╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║   ██║██╔══██║██║╚██╗██║██╔══██║╚════██║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"╚██████╔╝██║  ██║██║ ╚████║██║  ██║███████║\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO" ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝\n"NORMAL);

    sleep(1);
    system("clear");

    printf("\n");
    printf("\t\t\t"VERDE_CLARO" ██████╗  █████╗ ███╗   ██╗ █████╗ ███████╗████████╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██╔════╝ ██╔══██╗████╗  ██║██╔══██╗██╔════╝╚══██╔══╝\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║  ███╗███████║██╔██╗ ██║███████║███████╗   ██║   \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║   ██║██╔══██║██║╚██╗██║██╔══██║╚════██║   ██║   \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"╚██████╔╝██║  ██║██║ ╚████║██║  ██║███████║   ██║   \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO" ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝   ╚═╝   \n"NORMAL);

    sleep(1);
    system("clear");

    printf("\n");
    printf("\t\t\t"VERDE_CLARO" ██████╗  █████╗ ███╗   ██╗ █████╗ ███████╗████████╗███████╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██╔════╝ ██╔══██╗████╗  ██║██╔══██╗██╔════╝╚══██╔══╝██╔════╝\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║  ███╗███████║██╔██╗ ██║███████║███████╗   ██║   █████╗  \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"██║   ██║██╔══██║██║╚██╗██║██╔══██║╚════██║   ██║   ██╔══╝  \n"NORMAL);
    printf("\t\t\t"VERDE_CLARO"╚██████╔╝██║  ██║██║ ╚████║██║  ██║███████║   ██║   ███████╗\n"NORMAL);
    printf("\t\t\t"VERDE_CLARO" ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝\n"NORMAL);

    sleep(1);

}

void mostrar_mensaje_victoria(){

    animacion_victoria();

    printf("\n\n\n\t\t\tFELICIDADES! DERROTASTE A TODOS LOS GIMNASIOS... AHORA SOS UN "AMARILLO"MAESTRO POKEMON"NORMAL"!!\n\n\n");
    
    printf("\t\t\t"AMARILLO"%30c██     ██\n"NORMAL, ' ');
    printf("\t\t\t"AMARILLO"%30c         \n"NORMAL, ' ');
    printf("\t\t\t"AMARILLO"%30c██     ██\n"NORMAL, ' ');
    printf("\t\t\t"AMARILLO"%30c ███████ \n"NORMAL, ' ');
} 

/*
 * Devuelve TRUE si la letra recibida corresponde a una opción válida
 * del MENU VICTORIA.
 * De lo contrario, devuelve FALSE.
 */ 
bool es_letra_valida_victoria(char letra, bool se_presto_pokemon){

    return ( ( !se_presto_pokemon && 
            (letra == PEDIR_PRESTADO_POKEMON_MAYUS ||  letra == PEDIR_PRESTADO_POKEMON_MINUS) ) ||
             letra == REARMAR_EQUIPO_MAYUS         ||  letra == REARMAR_EQUIPO_MINUS            ||
             letra == CONTINUAR_MAYUS              ||  letra == CONTINUAR_MINUS                 );
}

/*
 * Imprime por pantalla la interfaz del MENU VICTORIA, mostrando
 * todas las opciones disponibles.
 */
void mostrar_interfaz_victoria(char letra, bool se_presto_pokemon){
    
    system("clear");

    printf("\n\t\t\t╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║%71c║\n", ' ');
    printf("\t\t\t║%7c██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗ █████╗ %7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║   ██║██║██║        ██║   ██║   ██║██████╔╝██║███████║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗██║██╔══██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║██║██║  ██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c  ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝%7c║\n", ' ', ' ');
    printf("\t\t\t║%71c║\n", ' ');
    printf("\t\t\t╚═══════════════════════════════════════════════════════════════════════╝\n");

    printf(VERDE_CLARO"\n\t\tACABAS DE VENCER AL GIMNASIO ACTUAL!\n"NORMAL);
    printf("\n\t\tSeleccioná una opción introduciendo la letra indicada:\n\n");

    if(!se_presto_pokemon){

        if( letra == PEDIR_PRESTADO_POKEMON_MAYUS || letra == PEDIR_PRESTADO_POKEMON_MINUS ){
            printf("\n\t\t" AZUL_FONDO "> %c para pedir prestado un pokemon al lider rival.\n"NORMAL, 
                   PEDIR_PRESTADO_POKEMON_MAYUS);
        
        }else{
            printf("\n\t\t> " AZUL "%c"NORMAL" para "AZUL"pedir prestado un pokemon al lider rival.\n"NORMAL,
                   PEDIR_PRESTADO_POKEMON_MAYUS);
        }
    }

    if( letra == REARMAR_EQUIPO_MAYUS || letra == REARMAR_EQUIPO_MINUS){
        printf("\n\t\t" ROJO_FONDO "> %c para rearmar tu equipo de pokemones de combate.\n"NORMAL, 
                REARMAR_EQUIPO_MAYUS);
    }else{
        printf("\n\t\t> " ROJO "%c"NORMAL" para "ROJO"rearmar tu equipo de pokemones de combate.\n"NORMAL,
                REARMAR_EQUIPO_MAYUS);
    }

    if( letra == CONTINUAR_MAYUS || letra == CONTINUAR_MINUS){
        printf("\n\t\t" VERDE_FONDO "> %c para continuar con el siguiente gimnasio."NORMAL"\n\n\n", CONTINUAR_MAYUS);
    }else{
       printf("\n\t\t> " VERDE "%c"NORMAL" para "VERDE"continuar con el siguiente gimnasio."NORMAL"\n\n\n", CONTINUAR_MAYUS);
    }
}

char menu_victoria(bool se_presto_pokemon, bool es_ultimo_gimnasio){
    
    if (!es_ultimo_gimnasio)
        return menu_generico(mostrar_interfaz_victoria, es_letra_valida_victoria, se_presto_pokemon);
    
    mostrar_mensaje_victoria();
    return VICTORIA;
}

/*
 * Imprime por pantalla la interfaz de pedir prestado un pokemon 
 * junto a las instrucciones que debe seguir el usuario.h
 */
void mostrar_interfaz_pedir_pokemon(){
	
	system("clear");

	printf("\n\t\t\t    ╔═══════════════════════════════════════════════════════════════════════╗\n");
	printf("\t\t\t    ║*· · · · · · · · · · · PEDIR POKEMON PRESTADO! · · · · · · · · · · · ·*║\n");
	printf("\t\t\t    ╚═══════════════════════════════════════════════════════════════════════╝\n\n\n");

	printf("\n\tSeleccioná el pokemon que desea pedir prestado:\n");
	printf("\t\t> Usá %c para moverte hacia arriba y %c para moverte hacia abajo.\n", ARRIBA, ABAJO);
	printf("\t\t> Si ya estas apuntando al pokemon que deseas elegir, apretá %c \n\n", SELECCIONAR_POKEMON_MAYUS);
	printf("\t(Para realizar cada acción, apretá ENTER luego de la respectiva tecla indicada!)\n\n\n");

}

void solicitar_posicion_poke_prestado(void* pokemones_lider_rival, int* posicion ){
    
	char letra = 0;

    mostrar_interfaz_pedir_pokemon();
	imprimir_lista_pokemon(pokemones_lider_rival, *posicion);
	
	while( (letra != SELECCIONAR_POKEMON_MAYUS) && (letra != SELECCIONAR_POKEMON_MINUS) ){
		
        scanf(" %c", &letra);
		hacer_movimiento(letra, posicion, lista_elementos(pokemones_lider_rival) - 1);
		
        mostrar_interfaz_pedir_pokemon();
        imprimir_lista_pokemon(pokemones_lider_rival, *posicion);
		printf("\nPOSICION SELECCIONADA: %i\n", *posicion);
	}
}

//------------------------- MENU DERROTA -------------------------

/*
 * Devuelve TRUE si la letra recibida corresponde a una opción válida
 * del MENU DERROTA.
 * De lo contrario, devuelve FALSE.
 */ 
bool es_letra_valida_derrota(char letra, bool se_presto_pokemon){

    return ( letra == REARMAR_EQUIPO_MAYUS         ||  letra == REARMAR_EQUIPO_MINUS         ||
             letra == REINTENTAR_GIMNASIO_MAYUS    ||  letra == REINTENTAR_GIMNASIO_MINUS    ||
             letra == FINALIZAR_PARTIDA_MAYUS      ||  letra == FINALIZAR_PARTIDA_MINUS          );
}

/*
 * Imprime por pantalla la interfaz del MENU DERROTA, mostrando
 * todas las opciones disponibles.
 */
void mostrar_interfaz_derrota(char letra, bool se_presto_pokemon){
    
    system("clear");

    printf("\n\t\t\t╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║%72c║\n", ' ');
    printf("\t\t\t║%7c██████╗ ███████╗██████╗ ██████╗  ██████╗ ████████╗ █████╗ %7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║  ██║█████╗  ██████╔╝██████╔╝██║   ██║   ██║   ███████║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██║  ██║██╔══╝  ██╔══██╗██╔══██╗██║   ██║   ██║   ██╔══██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c██████╔╝███████╗██║  ██║██║  ██║╚██████╔╝   ██║   ██║  ██║%7c║\n", ' ', ' ');
    printf("\t\t\t║%7c╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝%7c║\n", ' ', ' ');
    printf("\t\t\t║%72c║\n", ' ');
    printf("\t\t\t╚════════════════════════════════════════════════════════════════════════╝\n");



    printf(ROJO"\n\t\tACABAS DE SER DERROTADO POR EL GIMNASIO ACTUAL! :(\n"NORMAL);
    printf("\n\t\tSeleccioná una opción introduciendo la letra indicada:\n\n");

    if( letra == REARMAR_EQUIPO_MAYUS || (letra == REARMAR_EQUIPO_MINUS) ){
        printf("\n\t\t" AZUL_FONDO "> %c para rearmar tu equipo de pokemones de combate.\n"NORMAL, 
                REARMAR_EQUIPO_MAYUS);
    }else{
        printf("\n\t\t> " AZUL "%c"NORMAL" para "AZUL"rearmar tu equipo de pokemones de combate.\n"NORMAL,
                REARMAR_EQUIPO_MAYUS);
    }

    if( (letra == REINTENTAR_GIMNASIO_MAYUS) || (letra == REINTENTAR_GIMNASIO_MINUS ) ){
        printf("\n\t\t" ROJO_FONDO "> %c para reintentar gimnasio actual.\n"NORMAL, 
                REINTENTAR_GIMNASIO_MAYUS);
    }else{
        printf("\n\t\t> " ROJO "%c"NORMAL" para "ROJO"reintentar gimnasio actual.\n"NORMAL,
                REINTENTAR_GIMNASIO_MAYUS);
    }

    if( (letra == FINALIZAR_PARTIDA_MAYUS) || (letra == FINALIZAR_PARTIDA_MINUS) ){
        printf("\n\t\t" VERDE_FONDO "> %c para finalizar la partida."NORMAL"\n\n\n", FINALIZAR_PARTIDA_MAYUS);
    }else{
       printf("\n\t\t> " VERDE "%c"NORMAL" para "VERDE"finalizar la partida."NORMAL"\n\n\n", FINALIZAR_PARTIDA_MAYUS);
    }
}


char menu_derrota(){
    
    return menu_generico(mostrar_interfaz_derrota, es_letra_valida_derrota, NULL);

}

void mostrar_mensaje_derrota(){

    system("clear");
    printf("\n"CYAN);
    printf("\t\t\t███████╗   ██╗   ███╗   ██╗\n");
    printf("\t\t\t██╔════╝   ██║   ████╗  ██║\n");
    printf("\t\t\t█████╗     ██║   ██╔██╗ ██║\n");
    printf("\t\t\t██╔══╝     ██║   ██║╚██╗██║\n");
    printf("\t\t\t██║        ██║   ██║ ╚████║\n");
    printf("\t\t\t╚═╝        ╚═╝   ╚═╝  ╚═══╝\n\n\n"NORMAL);


    printf("\t\t\tACABAS DE PERDER LA PARTIDA :(\n");
    printf("\t\t\t   SUERTE PARA LA PRÓXIMA ...\n\n\n");

    printf("\t\t\t"AMARILLO"%10c██     ██\n"NORMAL, ' ');
    printf("\t\t\t"AMARILLO"%10c         \n"NORMAL, ' ');
    printf("\t\t\t"AMARILLO"%10c ███████ \n"NORMAL, ' ');
    printf("\t\t\t"AMARILLO"%10c██     ██\n"NORMAL, ' ');
}

void mensaje_derrota_simulacion(void* gimnasio, size_t gimnasios_restantes){

    gimnasio_t gimnasio_aux = *(gimnasio_t*)gimnasio;
    entrenador_t entrenador_vendedor = *(entrenador_t*)lista_ultimo(gimnasio_aux.entrenadores);

    mostrar_mensaje_derrota();

    printf("\n\n\t\t FUISTE DERROTADO POR EL ENTRENADOR: "ROJO"%s"NORMAL", perteneciente al gimnasio:\n\n", 
            entrenador_vendedor.nombre);

    size_t cantidad_entrenadores = lista_elementos(gimnasio_aux.entrenadores);

    printf(AMARILLO"\t\t\t╔════════════════════════════════════╗\n");
    printf(        "\t\t\t║ NOMBRE:  %-25s ║\n", gimnasio_aux.nombre);
    printf(        "\t\t\t╠════════════════════════════════════╣\n");
    printf(        "\t\t\t║ LIDER:   %-25s ║\n", gimnasio_aux.lider);
    printf(        "\t\t\t║ DIFICULTAD:   %-20i ║\n", gimnasio_aux.dificultad);
    printf(        "\t\t\t║ ID BATALLA:   %-20i ║\n", gimnasio_aux.id_batalla);
    printf(        "\t\t\t║%35c ║\n", ' ');
    printf(        "\t\t\t║"ROJO" RIVALES RESTANTES: %-15lu"AMARILLO" ║\n", cantidad_entrenadores);
    printf(        "\t\t\t╚════════════════════════════════════╝\n"NORMAL);

    printf("\n\n\t\t\t"ROJO"GIMNASIOS RESTANTES SIN VENCER: %lu\n"NORMAL, gimnasios_restantes);
}
//---------------------------------------------------------------------------------------------------------------

