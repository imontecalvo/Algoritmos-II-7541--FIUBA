# TDA Lista

## Introducción:
	
El presente trabajo consta de la implementación de un TDA Lista, incluyendo tanto su estructura como a si también las funciones primitivas, es decir, las operaciones asociadas al manejo de dicho tipo de dato abstracto. A su vez, se presentan también  las primitivas correspondientes para poder manejar dicha lista como si fuese una pila o una cola.

La implementación del TDA se realizó utilizando nodos entrelazados debido a la gran ventaja que proporcionan al solucionar el problema de la memoria contigua presente en las otras posibles implementaciones. Cada nodo está compuesto por un contenedor que contiene el elemento, y un puntero que apunta al siguiente (lista simplemente enlazada), mientras que la estructura de la lista está conformada por un puntero al primer elemento, al último elemento y una variable que nos indica la cantidad de elementos que posee la lista. Por otro lado, también se encuentran presentes todas las operaciones para el manejo de la lista: como insertar y borrar un elemento, crear y destruir, chequear si está vacía, obtener algun elemento en particular, averiguar la cantidad de elementos que posee la lista, y a su vez las operaciones que permiten manejar la lista como pila y cola: apilar y desapilar / encolar y desencolar, y averiguar el primer y último elemento.

Además de las operaciones comentadas, también se presentan un iterador externo (TDA) con su estructura y correspondientes funciones primitivas, y un iterador interno, el cual consta de una función. Ambos permiten al usuario recorrer la lista elemento a elemento sin necesidad de que el mismo conozca/acceda a la estructura interna de la lista y bajo una complejidad de O(n). Más adelante se tratarán con mayor profundidad estos conceptos.

Finalmente, para garantizar el correcto funcionamiento de la implementación llevada a cabo de todo lo anterior, se crearon una serie de pruebas con el objetivo de probar el comportamiento de las distintas funciones en diversos escenarios. Por un lado se encuentra el archivo "mis_pruebas.c" que contiene una gran variedad de pruebas, y por el otro está el archivo "lista_minipruebas.c" proporcionado por la cátedra, el cual contempla menor cantidad de casos bordes ya que sirve para hacer un análisis general de nuestra implementación y no un análisis estricto. Para compilar con un archivo de pruebas o el otro, se deberá seguir lo explicado en la seccion de "Compilación y ejecución". Además, para la visualización de las pruebas corridas y sus resultados, se utiliza el archivo "pa2mm.h" también proporcionado por la cátedra.

Para la elaboración de las pruebas se decidió optar por probar las funciones de una forma más aislada tal que su funcionamiento se vea condicionado lo menos posible por el funcionamiento de las demás funciones. Al momento de llevar a cabo las pruebas, las mismas se realizan desde las más generales hasta las más específicas, es decir, antes de probar inserciones hay que asegurarse de que la función encargada de crear la lista funcione correctamente, y por ejemplo, siempre que se pudo, se hizo uso de la estructura (lista->nodo_inicio y lista->nodo_fin) en lugar de condicionar las pruebas al funcionamiento de operaciones tales como lista_tope, lista_primero, lista_ultimo, etc.

A su vez, como en reiteradas ocasiones era necesario hacer pruebas con pilas, listas y colas no vacías, se creó una función que se encarga de obtener una lista, cola y pila con valores ya cargados. Como para esto se necesitaba una función que inserte múltiples  elementos, se aprovechó para hacer uso de la misma en las pruebas donde era necesario insertar, apilar o encolar múltiples elementos, pasando la correspondiente función por parámetro mediante un puntero (&lista_insertar, &lista_apilar, &lista_encolar), a diferencia de las pruebas de borrar múltiples elementos, en las cuales se realizó cada borrado "manualmente" (uno por uno).

## Compilación y Ejecución:

=> Para el proceso de compilación se utiliza make con el objetivo de simplificar y agilizar el proceso de introducir el comando en la terminal.

A su vez, debido a la existencia de dos conjuntos de pruebas: las  proporcionadas y las pruebas creadas, se puede compilar el archivo lista.c con cualquiera de los dos archivos de pruebas utilizando las distintas reglas, las cuales serán detalladas a continuación.

[Aclaración: Para poder utilizar estos comandos en la terminar, se debe "make" seguido del nombre de la regla.]
		
Reglas:

- compilar: Compila lista.c utilizando el archivo mis_pruebas.c que contiene el conjunto de pruebas creadas por mi, creando el ejecutable "lista".

- valgrind: Corre Valgrind sobre el ejecutable "lista".

- all: Compila lista.c junto con mis_pruebas.c y realiza el chequeo con Valgrind, es decir, equivale a introducir las anteriores dos reglas.

- compilar_minipruebas: Compila lista.c pero ahora lo hace junto con lista_minipruebas.c, creando el archivo "lista_minipruebas", que contiene las minipruebas proporcionadas por la cátedra.

- valgrind_minipruebas: Corre Valgrind pero ahora sobre "lista_minipruebas"

- all_mini: Similar a "all", compila y corre valgrind utilizando "lista.c" y "minipruebas.c", es decir, es equivalente a intrducir las dos reglas anteriores.

	
=> Por otro lado, para EJECUTAR el programa, introduciremos:

	./lista
	./lista_minipruebas

Dependiendo de las pruebas con las que deseemos ejecutarlo.


## Conceptos:

#### LISTAS
El concepto de lista no dista demasiado del que utilizamos cotidianamente, es decir, interpretamos una lista como un conjunto de diversos elementos, los cuales mantienen un orden dentro de dicha lista. 
				  
Una vez dejado esto en claro, se puede decir que una lista es un TDA (tipo de dato asbtracto) que contiene una serie de elementos ordenados de manera tal que cada elemento cuenta con un antecesor y un sucesor (excepto el primero y el último respectivamente). 
Como todo TDA, tiene una serie de operaciones y funciones asociadas con 
las que podemos utilizar dicho tipo de dato, en el caso de la lista son: 
				  		
- Crear lista.
- Insertar un elemento.
- Eliminar un elemento.
- Chequear si está vacía.
- Ver un elemento de la lista.
- Averiguar cantidad de elementos dentro de la lista.
- Destruir lista.

 Otro aspecto muy importante es la forma en que se implementa la lista. La misma puede ser implementada ya sea como un vector estático, un vector dinámico o como una lista de nodos entrelazados. Las primeras dos implementaciones no son muy útiles ya que cuentan con ciertas limitaciones como tamaño reducido y requerir de un cierto bloque de memoria contigua que no siempre se puede conseguir, siendo la lista como conjunto de nodos entrelazados la implementación más favorable. Consiste en un conjunto de nodos los cuales están conformados por un contenedor y por uno o más punteros hacia el nodo siguiente y/o el nodo anterior, de manera que cada elemento está conectado con su siguiente o con su siguiente y anterior a la vez.

Esto último depende de que tipo de lista se trate: simplemente enlazada o doblemente enlazada. La simplemente enlazada cada elemento tiene un "lazo simple", es decir, tiene un puntero sólo al elemento siguiente, de manera tal que es unidireccional y nos permite recorrer la lista de inicio a fin. Seria algo asi...

				  ╔══════════╦═══╗		   ╔══════════╦═══╗		   ╔══════════╦═══╗  null
				  ║ elemento ║ ⬤---------> ║ elemento ║ ⬤--------->║ elemento ║ ⬤--------->
				  ║		1	 ║   ║		   ║	 2	  ║   ║		   ║	3	  ║   ║
 				  ╚══════════╩═══╝		   ╚══════════╩═══╝		   ╚══════════╩═══╝
 				  	Posición #0				  Posición #1			  Posición #2
 				  

Por otro lado, la doblemente enlazada, como su nombre lo indica, utiliza un "doble lazo", lo cual significa que cada elemento posee un puntero al elemento siguiente pero también al elemento anterior, de manera tal que ahora se vuelve bidireccional, permitiéndonos recorrer la lista de inicio a fin y regresar de fin a inicio, es decir, podemos volver hacia atrás. El esquema es muy similar: 

 				  ╔═══╦══════════╦═══╗		   ╔═══╦══════════╦═══╗			╔═══╦══════════╦═══╗  null
		     null ║   ║ elemento ║ ⬤---------> ║   ║ elemento ║ ⬤--------->	║   ║ elemento ║ ⬤--------->
	      <---------⬤ ║		1	 ║   ║ <---------⬤ ║	2	  ║   ║ <---------⬤ ║	 3	   ║   ║
 				  ╚═══╩══════════╩═══╝		   ╚═══╩══════════╩═══╝			╚═══╩══════════╩═══╝
 				      Posición #0				   Posición #1			         Posición #2
 				  
 				  
Por último, es necesario destacar que existen las listas circulares, las cuales se caracterizan principalmente por el hecho de que el puntero del último elemento apunte al primer elemento de la lista, estas también pueden ser simplemente enlazadas o doblemente enlazadas.

---
#### PILAS 
Las pilas también agrupan a un conjunto de elementos bajo cierto orden. Sin embargo, poseen una serie de particularidades en cuanto a su estructura y forma en que se las maneja. La estructura de las pilas se conoce como L.I.F.O (Last in, first out), es decir, que las pilas se comportan de tal manera que el último elemento que se añade es el primero en eliminarse. El comportamiento es similar a una pila en el mundo real, en donde sólo podemos acceder al último elemento, es decir, al de arriba de la pila. Lo mismo sucede cuando utilizamos una pila en este contexto, no podemos acceder a elementos que se encuentren en otra posición. Las operaciones más características de un TDA Pila son:

- Crear pila.
- Apilar un elemento (insertarlo al final).
- Desapilar un elemento (eliminar el último).
- Averiguar tope -> último elemento de la pila.
- Ver si está vacía.
- Destruir pila.
---
#### COLAS
Las colas también comparten cierta similitud con las pilas y las listas dado a que contienen elementos ordenados, aunque se diferencian de estas dos en cuanto a  estructura. A diferencia de las pilas, la estructura de una cola es F.I.F.O (First in, first out), es decir, el primer elemento añadido en la cola es el primero en eliminarse, al igual que sucede en el mundo real con por ejemplo las colas en un supermercado. En síntesis, las colas se manejan de tal forma que los nuevos elementos se añaden al final de la misma (al igual que con las pilas), pero se eliminan los elementos "más viejos" primero, es decir, los que se añadieron primero en la cola. Esto hace que tampoco podamos acceder a cualquier elemento de la cola.

Las operaciones principales que podemos realizar con un TDA Cola son:
- Crear cola.
- Encolar un elemento (insertarlo al final).
- Desencolar un elemento (eliminar el primero).
- Averiguar el primer elemento.
- Ver si está vacía.
- Destruir cola.

---
#### ITERADOR
El concepto de iterador es bastante simple, no es más que una herramienta que nos permite recorrer la serie de elementos que conforma la lista secuencialmente. Sin embargo, un iterador puede implementarse de dos formas distintas: como uno externo o uno interno.

Un iterador externo consiste en un TDA, es decir, que tiene una estructura y un conjunto de funciones primitivas que  permiten al usuario recorrer una lista. La gran ventaja es que el proceso de recorrer la lista sin acceder a la estructura interna representa una complejidad de O(n²), mientras que con el iterador este proceso se vuelve O(n) debido a que la acción de buscar el siguiente elemento pasa de O(n) a O(1). 

De todas formas, es importante aclarar que quien implemente el iterador debe conocer cómo está implementada la lista, de lo contrario la complejidad se mantendrá en O(n²).
 					
El funcionamiento de este iterador consiste basicamente en hacer uso de sus primitvas para crear un bucle en el cual mientras haya un elemento siguiente, el puntero del iterador avance hacia el próximo elemento hasta que llegue al final, quedando en NULL.

Por otra parte, un iterador interno consiste simplemente en una función, la cual recibe una lista, una función y puede que también algún parámetro adicional. Su funcionamiento se basa en recorrer secuencialmente todos los elementos de la lista recibida por parámetro y aplicarle una función a cada elemento. Cuando llegue al final de la lista o cuando la función que le estamos aplicando a cada elemento lo determine (por ejemplo al devolver false), la iteración finalizará.

Existen grandes diferencias entre un iterador externo y uno interno de acuerdo a lo explicado anteriormente. La principal diferencia radica en QUÉ es cada uno: el externo es un TDA con una estructura y operaciones asociadas, con lo cual, para usarlo debemos crearlo reservando un espacio en memoria y luego destruirlo (liberar la memoria), mientras que el interno es sólo una simple función. Y si nos enfocamos en su funcionamiento, también hay claras diferencias debido a que el iterador externo ofrece mucho mayor control acerca de cómo se realizará la iteración ya que es el usuario quien creará el bucle. Por el contrario, el iterador externo no nos proporciona este control ya que la iteración se realiza de forma interna, es decir, una vez llamada la función, se recorren todos los elementos aplicándole la correspondiente función.
