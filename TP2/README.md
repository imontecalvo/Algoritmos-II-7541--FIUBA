# Trabajo práctico 2: Aventura Pokemon

## Introducción:
El trabajo consiste en un juego, el cual está basado en una Aventura Pokemon. El objetivo es recrear el trayecto que debe recorrer un personaje desde cero hasta convertirse en Maestro Pokemon. 
    
Para ello, dicho personaje contará con un conjunto de pokemones iniciales los cuales usará para enfrentarse a entrenadores rivales. Cuando se logre derrotar a todos los entrenadores de un gimnasio, el jugador se enfrentará al lider. En caso de vencerlo, se habrá derrotado a dicho gimnasio y hasta puede tomarle prestado un pokemon al lider vencido.

A medida que se derroten los gimnasios, cada vez el personaje estará más cerca de lograr su objetivo: convertirse en Maestro Pokemon, y lo alcanzará cuando finalmente haya derrotado a todos los gimnasios existentes.
En caso de perder contra un entrenador, no te preocupes! se podrá rearmar el equipo de pokemones combatientes y reintentar la batalla comenzando desde el punto donde el personaje fue derrotado.

Además, se ofrecen dos modalidades de juego distintas: 
- Jugar la partida de forma interactiva de manera que no te pierdas ningún detalle.
- Jugar la partida de forma simulada, visualizando directamente si se ganó o no ( y hasta  dónde se llegó). Funcionalidades como pedir pokemon prestado, rearmar equipo y reintentar batallas NO están disponibles en esta modalidad.

## Información de uso y Aclaraciones:
   
- Para poder iniciar la partida (jugarla o simularla), el personaje principal y los gimnasios
deben estar previamente cargados, de lo contrario las opciones aparecen bloqueadas.

- Para cargar correctamente el personaje, el archivo debe poseer el siguiente formato:
            
      E;nombre_personaje
	  P;pokemon_1;velocidad;ataque;defensa
	  P;pokemon_2;velocidad;ataque;defensa
      ...
	  P;pokemon_n;velocidad;ataque;defensa

- Para cargar correctamente los gimnasios, el archivo debe poseer el siguiente formato: (Para que un gimnasio sea válido debe tener al menos un entrenador válido incluyendo al lider)
            
	  G;nombre_gimnasio;dificultad;id_batalla
	  L;nombre_lider
	  P;pokemon_1;velocidad;ataque;defensa
	  P;pokemon_2;velocidad;ataque;defensa
	  ...
	  P;pokemon_n;velocidad;ataque;defensa
	  E;nombre_entrenador_1
	  P;pokemon_1;velocidad;ataque;defensa
	  P;pokemon_2;velocidad;ataque;defensa
	  ...
	  P;pokemon_n;velocidad;ataque;defensa
	  ...
	  E;nombre_entrenador_n
	  P;pokemon_1;velocidad;ataque;defensa
	  P;pokemon_2;velocidad;ataque;defensa
	  ...
	  P;pokemon_n;velocidad;ataque;defensa


- En caso de error al momento de leer el archivo, la lectura finalizará y se usará la información leída hasta entonces.

- En caso de que se haya cargado un personaje equivocado, se puede volver a la opción de cargar personaje. El nuevo personaje se sobreescribirá reemplazando al anterior.

- En caso de que querer cargar gimnasios desde más de un archivo no hay problema. Simplemente se debe volver a seleccionar la opción de cargar gimnasios en el menú inicio. Esto sólo se puede hacer antes de comenzar la partida.

- Por último, notar que en cada menú están presentes las instrucciones a seguir para realizar cada acción.

## Archivos entregados

La entrega contiene TDAs usados, cinco bibliotecas del juego (2 TDAs) y un main:
        
- Los TDAs usados:
	* Carpeta "TDA_lista" dentro de la cual se encuentran los archivos: TDA_lista.h y TDA_lista.c
	* Carpeta "TDA_heap" dentro de la cual se encuentran los archivos: TDA_heap.h y TDA_heap.c
        
- Carpeta "BATALLAS", donde se encuentran los archivos: batallas.h y batallas.c que contienen los cinco tipos de batallas que se usarán para hacer los combates entre pokemones.
        
- Carpeta "Interaccion_usuario", están los archivos: interaccion_usuario.h e interaccion_usuario.c que contienen las funciones necesarias para garantizar una correcta interacción entre el usuario y el juego. En síntesis, acá se encuentran las funciones que imprimen información por pantalla y/o solicitan el ingreso de información por teclado al usuario.

- Carpeta "Funciones_juego", que contiene a: funciones_juego.h y funciones_juego.c en los cuales se encuentran las principales funciones para realizar las acciones intrínsecas del funcionamiento del juego. Son propias de la lógica del juego y no tienen ningún tipo de interacción directa con el usuario.

- Archivo: aventura_pokemon.c en el cual se encuentra el main. En este archivo se combinan las funciones de interacción con el usuario, las de batallas y las de la lógica del juego, (junto con algunas nuevas funciones) para crear y controlar el flujo del programa.

- Por último, también se encuentra un Enunciado.pdf que es el enunciado del trabajo, el archivo makefile y dos archivos .csv con formato correcto para cargar el personaje y los gimnasios.
         

## Compilación y Ejecución:

Para el proceso de COMPILACIÓN se utiliza make con el objetivo de simplificar y agilizar el proceso de introducir el comando en la terminal.

[Aclaración] Se debe introducir "make" seguido del nombre de la regla.
		
	make nombre_de_regla
		
Reglas:
- compilar: Compila los archivos: TDA_heap.c, TDA_lista.c, batallas.c, interaccion_usuario.c, funciones_juego.c y aventura_pokemon.c creando el ejecutable "aventura_pokemon"

- valgrind: Corre Valgrind sobre el ejecutable "aventura_pokemon".

- all: Compila todos los .c mencionados y realiza el chequeo con Valgrind, es decir, equivale 
               a introducir las anteriores dos reglas.

	
Por otro lado, para EJECUTAR el programa, se utiliza la regla "ejecutar" 
Es decir, se introduce en terminal:

	make ejecutar


## Estructuras utilizadas:

De acuerdo a las necesidades que surgieron a la hora de trabajar con las distintas estructuras se recurrió a hacer uso de distintos TDAs.

#### Conjunto de gimnasios:
Para el conjunto de gimnasios se utiliza el TDA Heap ya que permite contener todos los  gimnasios ordenados bajo un cierto criterio. En este caso, se usó un heap minimal y el  criterio fue el nivel de dificultad de cada gimnasio, tal que quedan "ordenados" de los más sencillos a los más difíciles. Además, resulta esencial la posibilidad de acceder al gimnasio más sencillo ya que siempre es la raiz, y poder extraerlo del heap cuando sea necesario.

#### Conjunto de entrenadores:
Para el conjunto de entrenadores pertenecientes a un mismo gimnasio, se optó por utiliza el TDA Pila. La razón es que este conjunto respeta una estructura LIFO (Last In First Out), es decir, que el último elemento en ser insertado es el primero en ser retirado. Y exactamente así es el comportamiento de los conjuntos de entrenadores en este trabajo dado a que se requiere acceder sólo al último entrenador ya que es contra quien el personaje debe enfrentarse. A medida que los entrenadores van siendo derrotados, van siendo desapilados del conjunto de modo que ahora el último entrenador de la pila es el siguiente rival, y así sucesivamente hasta llegar al líder, que es el primer entrenador en ser insertado de acuerdo al formato que posee el archivo de donde se cargan los datos para inicializar el juego.

Es importante aclarar que dicho TDA realmente se encuentra en el TDA Lista, sólo que se lo trata como pila utilizando las funciones que corresponden al TDA Pila,

#### Conjunto de Pokemones:
Para el conjunto de pokemones de los entrenadores, como así también para los conjuntos de pokemones obtenidos y de combate del personaje principal se utilizó el TDA Lista implementado como una lista simplemente enlazada. La razón de esta decisión es que la lista nos permite almacenar estos pokemones ofreciendo muchas más ventajas sobre vectores, que tienen ciertas limitaciones: tamaño fijo (vector estático) o requieren de bloques de memoria contigua (vector dinámico). 

Por otro lado, se decidió usar lista en lugar de otras estructuras como pilas y colas  debido a que en diversas circunstancias es necesario acceder a posiciones intermedias de la lista (por ejemplo al pedir prestado un pokemon o al rearmar el equipo de pokemones) o incluso recorrer todos sus elementos, lo cual es un gran impedimento si usamos pila o cola ya que sólo podemos acceder al último y al primer elemento respectivamente.

Sin embargo, es importante mencionar que para el conjunto de pokemones de combate se usó el TDA Lista debido a que el propósito el trabajo era evaluar el uso de TDAs aplicados a estas estructuras, pero una buena opción hubiese sido un vector estático debido a que se conoce la cantidad máxima de elementos (6), es mucho más sencillo de manipular que una lista y además las algunas operaciones poseen menor complejidad algorítmica dado a que se puede acceder de forma directa, es decir con O(1), a cualquier posición del vector con su índice.

Por otro lado, también se usó el TDA Iterador Externo para poder recorrer las listas de  pokemones de una forma más manual y personalizada (a diferencia de un iterador interno). El uso de este TDA permitió recorrer las listas con una complejidad O(n) a diferencia de si se hubiera utilizado un bucle y la función 'lista_elemento_en_posicion(..)' donde sería O(n²). Se usó al momento de hacer que los pokemones propios y rivales batallen entre sí, y también se usó para imprimir la lista de pokemones en distintas opciones de menú.
