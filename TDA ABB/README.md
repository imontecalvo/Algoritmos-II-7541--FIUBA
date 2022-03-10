# TDA ABB

## Introducción:

El presente trabajo consta de la implementación de un TDA ABB (Árbol Binario de Búsqueda), incluyendo tanto su estructura como a si también las funciones primitivas u operaciones que están asociadas al manejo de dicho TDA.

La implementación del ABB se realizó a partir de nodos entrelazados, los cuales contienen tres punteros: uno apunta al elemento que contienen, y los otros dos apuntan a sus hijos derecho e izquierdo respectivamente. Por otro lado, la estructura del ABB está conformada por un puntero al nodo raíz (nodo a partir del cual se desarrolla todo el árbol), un comparador y un destructor. Estos dos últimos serán detallados a continuación para un correcto uso de dicho TDA.

El comparador debe ser construido por el usuario de acuerdo a la necesidad que el mismo. Recibe dos punteros a elementos y en base a la clave o característica que el usuario deba comparar, el comparador determinará cuál de los dos es mayor. Esta herramienta es indispensable para poder llevar a cabo la creación del ABB, de lo contrario habrá un error durante su creación, pues sin un comparador no  se puede recorrer el árbol ni llevar a cabo cualquiera de las demás operaciones/funciones primitivas, dado a que imposibilita hacer uso de la propiedad fundamental de un ABB, la cual es aprovechar la noción de izquierda y derecha ordenando los elementos de manera tal que los menores a la raíz de cada sub-árbol vayan hacia la izquierda mientras que los mayores a la derecha.

Por otro lado, el destructor, a diferencia del comparador, es de carácter optativo en cuanto a la creación del ABB. El usuario es quien debe determinar si lo necesitará o no. En caso de que el mismo desee trabajar con elementos que están en el heap, puede construir un destructor que dado un puntero a un elemento, lo libere, y de esta forma, al momento de invocar ya sea la destrucción del árbol o el borrado de algún elemento, se llamará al destructor y la liberación de dicho elemento se hará automáticamente. En caso de que el usuario trabaje con elementos pertenecientes al stack, trabaje con elementos del heap que no quiera liberar o que posea sus punteros para liberarlos  posteriormente de otra forma, no será necesario hacer uso del destructor.

A su vez, en cuanto a las operaciones que proporciona este TDA se encuentran: 
- Crear y destruir un ABB.
- Insertar un elementos en el ABB respetando el orden propio de este TDA.
- Borrar un elemento del ABB.
- Buscar un elementos
- Chequear si el ABB está vacío.
- Averiguar la raíz del ABB.
- Recorrer el ABB de tres formas distintas: in orden, pre orden y post orden.
- Iterar los elementos de ABB mediante un iterador interno que posibilita aplicar una función a cada elemento iterado.

Por otro lado, es importante destacar ciertas convenciones utilizadas. En primer lugar, la más importante (y ya mencionada anteriormente), es que los elementos del ABB están distribuidos de forma tal que los menores a la raíz de cada sub-arbol se distribuyen a la izquierda del mismo mientras que los mayores lo hacen a la derecha. Una aclaración importante es que en caso de desear insertar un elemento que posee la misma clave que uno ya perteneciente al árbol, se considerará que el mismo es menor, por lo tanto, se dirigirá hacia la izquierda.
Otra convención utilizada se visibiliza al momento de borrar un elemento que posea dos hijos. A diferencia del borrado de un elemento que es nodo hoja o sólo posee un hijo donde el borrado es casi automático y supone simplemente una pequeña reasignación de punteros, cuando se desea eliminar un nodo que posee dos hijos hay que buscar un sustituto: el predecesor inorden (el máximo de todos los mínimos) o el sucesor in orden (el mínimo de todos los máximos). En esta implementación se decidió hacer uso de la primera, el predecesor inorden.

Finalmente, para garantizar un correcto funcionamiento de las operaciones  conforman dicho TDA, se sometió dicha implementación a una serie de pruebas que tienen como objetivo evaluar el comportamiento de las distintas funciones abarcando la mayor cantidad de casos y escenarios posibles.
Por un lado se encuentra el archivo "mis_pruebas.c" que contiene una gran variedad de pruebas, y por el otro está el archivo "abb_minipruebas.c" proporcionado por la cátedra, el cual contempla menor cantidad de casos bordes ya que sirve para hacer un análisis general de la implementación y no un análisis estricto. Para compilar con un archivo de pruebas o el otro, se deberá seguir lo explicado en la sección de "Compilación y ejecución". Además, para la visualización de las pruebas corridas y sus resultados,  utiliza el archivo "pa2mm.h" también proporcionado por la cátedra.

En cuanto a las pruebas que conforman parte de este trabajo, se encuentran organizadas en tres grandes grupos, las que pertenecen a un ABB nulo, a un ABB vacío o a un ABB NO vacío. Evidentemente, los dos primeros grupos poseen pruebas mas limitadas debido a que no existen tantos escenarios posibles a la hora de tener un ABB nulo o vacío. Mientras que en el tercer grupo, las pruebas cuentan con mucha mayor diversidad y están subdivididas en otros grupos de acuerdo a la función que se desea poner a prueba, hay pruebas de: insertar, borrar, buscar, recorrer de distintas formas el ABB, pruebas del iterador y pruebas varias que son pruebas mixtas que tienen objetivo evaluar principalmente el buen funcionamiento de las operaciones encargadas chequear si el árbol está vacío y de averiguar su raíz, aunque también se utilizan para ello las funciones de borrar e insertar previamente probadas. Por último, es oportuno mencionar que para poner a prueba el correcto funcionamiento del destructor, se creó una prueba donde se hace uso de un ABB que contiene punteros a elementos del heap y posteriormente se realiza el chequeo con Valgrind, es decir, no se determina de forma automática su funcionamiento.


## Compilación y Ejecución

=> Para el proceso de compilación se utiliza make con el objetivo de simplificar y agilizar el proceso de introducir el comando en la terminal.

A su vez, debido a la existencia de dos conjuntos de pruebas: las proporcionadas y las pruebas creadas, se puede compilar el archivo abb.c con cualquiera de los dos archivos de pruebas utilizando las distintas reglas, las cuales serán detalladas a continuación.

[Aclaración: Para poder utilizar estos comandos en la terminar, se debe introducir "make" seguido del nombre de la regla.]
		
Reglas:

- compilar: Compila abb.c utilizando el archivo mis_pruebas.c que contiene el conjunto de pruebas creadas que forman parte, de este trabajo, creando el ejecutable "abb".

- valgrind: Corre Valgrind sobre el ejecutable "abb".

- all: Compila abb.c junto con mis_pruebas.c y realiza el chequeo con Valgrind, es decir, equivale a introducir las anteriores dos reglas.

---
- compilar_minipruebas: Compila abb.c pero ahora lo hace junto con abb_minipruebas.c, creando el archivo "abb_minipruebas", que contiene las minipruebas proporcionadas por la cátedra.

- valgrind_minipruebas: Corre Valgrind pero ahora sobre "abb_minipruebas"

- all_mini: Similar a "all", compila y corre valgrind utilizando "abb.c" y "abb_minipruebas.c", es decir, es equivalente a intrducir las dos reglas anteriores.

	
=> Por otro lado, para EJECUTAR el programa, introduciremos:

	./abb
	./abb_minipruebas

Dependiendo de las pruebas con las que deseemos ejecutarlo.


## Conceptos

#### ABB
Un ABB, tal como sus siglas lo indican, es un Árbol Binario de Búsqueda, el cual es un tipo de dato abstracto (TDA) que consiste en un árbol binario, en el cual los elementos que lo forman respetan un determinado orden otorgando ciertas ventajas. Sin embargo, antes de continuar es necesario comprender qué es un árbol y qué es un árbol binario.

Un árbol consiste en un conjunto de nodos entrelazados, en el que cada nodo es un elemento, y están todos conectados (directa o indirectamente) a un nodo principal y único, el nodo raíz. A partir del nodo raíz comienzan a ramificarse descendientemente más nodos, de manera tal que se van creando sub-árboles. Esto da lugar a las nociones de nodos padres/hijos, y/o ancestros/descendientes. Es decir, un árbol es una estructura que permite organizar elementos de cierta forma estableciendo relaciones de descendencia entre dichos elementos.
			   
Por otro lado, un árbol binario es un árbol con una particularidad adicional. Además de cumplir con lo mencionado anteriormente, debe cumplir con que cada nodo/elemento tenga dos hijos, un hijo o ningún hijo, es decir, como máximo dos hijos, de allí el nombre binario. Esto es muy importante ya que da lugar a una noción de izquierda y derecha que puede ser muy útil a la hora de identificar un elemento. De todas maneras, un árbol binario como tal no tiene gran utilidad a la hora de utilizarlo ya que se desconoce en un principio su estructura y cómo es la distribución de los nodos.

Un posible esquema de un árbol binario podría ser algo como lo siguiente:

			   												╔════╗ 
			   												║ A  ║ <--- RAIZ
			   												╚════╝
			   								   _______________/\_______________
			   								  /								   \
			   								╔════╗ 							 ╔════╗ 
			   								║ B  ║							 ║ C  ║
			   								╚════╝							 ╚════╝
			   							 _____/\_____ 				      _____/\_____
			   							/			 \					 /			  \
			   						 ╔════╗ 	    ╔════╗			 ╔════╗ 	    ╔════╗	
			   						 ║ D  ║	 		║ E  ║			 ║ F  ║	 		║ G  ║
			   						 ╚════╝	 		╚════╝			 ╚════╝	 		╚════╝
			   						 					\__
			   						 					   \
			   						 					 ╔════╗
			   						 					 ║ H  ║
			   						 					 ╚════╝

Una vez en claro estos dos conceptos, ya podemos abordar el de árbol binario de búsqueda. Un ABB, evidentemente cumple con las condiciones de árbol y de árbol binario mencionadas anteriormente, pero además tiene una característica fundamental que nos permite explotar su utilidad. Dicha propiedad es la existencia de una relación de orden entre los elementos según su posición (derecha o izquierda) respecto de su padre. Es decir, se hace uso de la noción derecha/izquierda proporcionada por el árbol binario distribuyendo los elementos de manera tal que los que sean menores a su padre van a la izquierda y los que sean mayores a su padre van a la derecha.
			   
El potencial de dicha imposición radica en que ahora sí se conoce la estructura del árbol, con lo cual se obtienen en total dos grandes ventajas:
			   			
- La primera es tener una estructura que almacena elementos a partir de nodos entrelazados, los cuales no requieren de la disponibilidad de cierta cantidad de memoria contigua. Esta ventaja también la tiene una lista implementada con nodos.
			   			
- La segunda y más importante, permite obtener la complejidad reducida propia de una búsqueda binaria -> O(log n) ya que al saber cómo se distribuyen los elementos, no es necesario recorrerlos todos. Cuando se requiera buscar un elemento sólo hay comparar su clave con la del nodo raíz del árbol y de cada sub-árbol y decidir si recorrer a la derecha o izquierda. 
Igual, más adelante cuando se explique la complejidad se hará una aclaración al respecto ya que un ABB puede degenerar en una lista, perdiendo esta ventaja.

Por último, no está de más mencionar que entre las operaciones básicas que podemos hacer con un ABB podemos encontrar: crear y destruir el ABB, insertar y eliminar un elemento, chequear si está vacío, buscar un elemento en particular y recorrer todo el árbol (se puede hacer de distintas formas, por ejemplo inorden, preorden y postorden).

Entonces, en concreto la diferencia entre un ABB y un árbol binario se basa es que un ABB es un tipo de árbol binario en el que los elementos deben cumplir con el órden anteriormente mencionado según su valor o clave, lo cual permite conocer su  estructura y valerse de ella para reducir la complejidad algorítmica evitando tener que pasar por todos los nodos que conforman al árbol. Con lo cual, se obtiene una ventaja real respecto de otras estructuras para almacenar elementos, como por ejemplo una  lista o incluso un árbol binario no ABB, el cual no tiene gran utilidad por si solo.


## FUNCIÓN DESTRUCCIÓN
El árbol implementado debe contar con cierta versatilidad permitiendo almacenar cualquier tipo de elemento, proporcionándole así al usuario la posibilidad de almacenar el tipo de elemento que desee. Sin embargo, para poder lograr esto, cada nodo en lugar de almacenar el elemento en sí, debe almacenar un puntero que apunte al elemento asociado a ese nodo (de esta forma a su vez ya no se requiere de tener que conocer el tipo de dato que va a utilizar el usuario al momento de reservar memoria para el ABB y para cada nodo). Dependiendo de las necesidades del usuario, estos punteros apuntarán a elementos del stack o del heap en caso de que así lo requiera el usuario, y acá es donde entra en juego el destructor. Es necesario contar con una función que permita destruir los elementos almacenados en cada nodo, es decir, liberar el espacio en memoria reservado donde están los elementos apuntados por el puntero que contiene su respectivo nodo. Dicho de forma más general, el destructor permite que la  implementación del ABB se adapte a las necesidades de cada usuario, permitiendo la eliminación de elementos y/o de todo el abb de forma sencilla sin importar el tipo de datos con el que se desee trabajar.

En caso de NO existir dicha función, implicaría que el usuario en principio no puede eliminar nodos ni el árbol entero si es que trabaja con elementos almacenados en el heap, de lo contrario tendría fuga de memoria, viéndose limitado a trabajar únicamente con elementos pertenecientes al stack, ya que no tendría cómo liberarlos.
Esto podría solucionarse si el usuario conserva por su cuenta punteros que apunten a los elementos del heap y luego debería eliminarlos de forma manual uno a uno, lo cual resultaría tedioso y poco eficiente si se trabaja con un gran volumen de elementos, es por eso que la existencia del destructor facilita significativamente el proceso de destrucción y borrado para el usuario.


## COMPLEJIDAD DE OPERACIONES:

#### CREAR ABB
Tiene complejidad O(1), es decir constante ya que se realiza una única acción aislada la cual es reservar espacio en memoria para el abb e inicializarlo.

#### DESTRUIR ABB
Tiene complejidad O(n), es decir lineal debido a que para llevarse a cabo la destrucción del árbol, debe llevarse a cabo la destrucción de TODOS sus nodos que lo conforman (incluyendo la destrucción de cada elemento si es necesario), con lo cual se debe recorrer todo el árbol, de manera tal que para un árbol de n elementos, la operación de destruir nodos debe realizarse n veces.

#### INSERTAR
Como al momento de evaluar la complejidad siempre tomamos el peor de los casos para cubrir todos los casos que se pueden presentar, la complejidad de insertar un elemento en el ABB es de O(n). Esto sucede porque no siempre el árbol se encuentra balanceado, con lo cual puede degenerar en una lista de tal forma que para insertar el elemento debamos hacer las comparaciones con los n elementos presentes en el árbol.
										
En caso de que este balanceado, la complejidad seria de O(log n) tal como sucede con los AVLs, pero este no es más que un caso ideal.

#### BORRAR
La complejidad en el peor de los casos es O(n) y sucede lo mismo que para la operación insertar. Al momento de borrar, primero hay que encontrar el elemento y luego el elemento que lo reemplazará, con lo cual en el  mejor de los casos la complejidad sería O(log n) si está balanceado, pero considerando que puede degenerar en lista, la complejidad sería O(n) para el peor de los casos ya que habría que pasar por todos los nodos.

#### BUSCAR
Pasa exactamente lo mismo que en BORRAR, para el peor de los casos teniendo en cuenta la distribución de los nodos y la posición del elemento a buscar, la complejidad sería O(n) ya que habría que comparar el elemento buscado con los n elementos que forman el ABB.

#### CHEQUEAR VACÍO
La complejidad que supone chequear que el ABB está vacío es de O(1), es constante ya que sólo requiere de hacer una única tarea una sola vez, ésta es la de chequear que el nodo raiz sea nulo o no.

#### RAIZ
La complejidad que tiene obtener la raíz del ABB también es de O(1), aplica la misma justificación que en la operación de chequear si está vacío, una unica instrucción que consiste en obtener la raíz del ABB a la cual se puede acceder de forma directa sin necesidad de pasar por otros nodos ni recorrer el árbol.

#### RECORRER
La complejidad de recorrer el árbol es obviamente O(n) SIEMPRE indistintamente de qué tipo de recorrido se quiera hacer o de cómo se haya formado el árbol, a diferencia de insertar/buscar/borrar donde sólo O(n) era en el peor de los casos, acá es siempre O(n). La razón de dicha complejidad es que justamente debemos pasar por los n elementos que posee el árbol porque queremos recorrerlo completamente.

#### ITERAR
Cuando se emplea el iterador interno, la cantidad de elementos recorridos puede variar según la función utilizada (puede cortar antes). Sin embargo, una vez más consideramos el peor de los casos, siendo este el caso en que se deben recorrer todos los n elementos que conforman el árbol, por lo tanto, dicha operación contaría también con una complejidad O(n).
