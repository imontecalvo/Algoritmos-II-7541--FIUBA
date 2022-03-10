# Trabajo Práctico 1: Evento de pesca

## Introducción:

El trabajo consta de un simulador el cual permite visualizar el estado de un arrecife luego de trasladar del mismo una cierta cantidad de pokemones que cumplan una determinada condición hacia un acuario, y a su vez, obtener la información del acuario en un archivo.

En primer lugar, se crean las variables a utilizarse, se le da un mensaje de bienvenida al usuario, y se inicializan los vectores de las funciones de selección y listar pokemones utilizando punteros a funciones, las cuales serán utilizadas posteriormente.

A su vez, se reserva espacio en el heap y se crean allí un acuario correctamente inicializado y un arrecife, el cual se inicializa extrayendo la información del archivo cuya ruta fue especificada previamente. La ruta del archivo del arrecife se encuentra como constante en el main, y en caso de querer utilizar un archivo distinto deberá modificarse dicha constante.

Durante el proceso de creación e inicialización del arrecife, se procede a leer la información desde el archivo correspondiente y en cuanto falle alguna lectura o realloc, el proceso se detendrá y se devolverá el arrecife con los pokemones que pudo leer hasta ese momento. En caso de que no se haya podido leer ninguno, ya sea porque no se pudo acceder al archivo, falló el malloc inicial o el primer realloc durante la lectura, se devolverá un puntero nulo, es decir, que no apunta a ningún arrecife, pues no se pudo obtener ninguna información del archivo.

En caso de que lo anteriormente mencionado se haya hecho exitosamente, se procederá a trasladar desde el arrecife hacia el acuario a los pokemones que cumplan una determinada condición. Para ello, se hará uso de un puntero a funciones que permite enviar la función de selección que el usuario desee como parámetro de la función trasladar. Durante el traslado, también se irán actualizando continuamente la cantidad de pokemones del arrecife y del acuario. Es importante destacar que en cuanto se produzca algún fallo durante el traslado se devolverá ERROR y se notificará al usuario mediante un mensaje impreso por pantalla.

Aclaración: En caso de algún fallo durante el traslado, el arrecife y el acuario NO volverán a su estado inicial, sino que quedarán como estaban en el momento en que se produjo el fallo, existiendo la posibilidad de que haya pokemones repetidos. De todas formas, esto no supone un problema dado que se le advierte al usuario de que hubo un error y NO se procederá a censar el arrecife ni a cargar los datos del acuario al archivo correspondiente.
También, es importante tener en cuenta un caso muy particular: si al arrecife le queda un solo pokemon y es necesario trasladarlo al acuario, su cantidad se reducirá a cero y el realloc devolverá NULL, con lo cual no habría forma de distinguir un fallo del realloc, por lo que se descartó esto, se detecta error sólo si el realloc devuelve NULL y se cumple que la cantidad de pokemones en el arrecife es mayor a uno (1).

Si el traslado fue exitoso, se imprimirá por pantalla la información de los pokemones que aún perduran en el arrecife y se cargarán los datos del acuario a su respectivo archivo de texto.

Finalmente, se liberará la memoria reservada tanto del acuario y arrecife, como así también de sus respectivos vectores de pokemones, teniendo en cuenta las particularidades que pueden llegar a darse.

(Es importante mencionar que la cantidad de pokemones a trasladar se asigna de forma aleatoria, pero le usuario debe asignarle la cantidad que desee).


## Compilación y Ejecución:

Para compilarlo, se deberá introducir la siguiente linea por terminal, haciendo uso de los flags indicados:
	
	gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca

	
A su vez, antes de correrlo, se deberá realizar un chequeo con Valgrind para asegurarse de que no hay fuga de memoria. Se introducirá la siguiente linea:

	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca

Finalmente, para llevar a cabo la ejecución del programa, se debe introducir;

	./evento_pesca


## Conceptos:

#### Punteros: 
Los punteros son un tipo de dato los cuales se caracterizan por almacenar direcciones de memoria. De allí proviene su nombre, es decir, "apuntan" a un espacio en la memoria, permitiendo manipular el valor de la variable a la que apuntan sin importar el ambito en que esté.
Es por esto que poseen gran potencial ya que nos permiten acceder a una posición en la memoria y modificar su contenido, por ejemplo al pasar una variable por referencia a una función. 
En el uso de punteros resultan fundamentales los operadores '*' y '&' los cuales nos permiten respectivamente desreferenciar y referenciar una variable.
La aplicación de punteros a lo largo de este trabajo fue fundamental, y se utilizó principalmente para poder administrar la memoria dinámica a la hora de realizar los realloc y malloc necesarios (conceptos que serán explicados luego). 
El uso de punteros posibilitó el manejo del arrecife y del acuario, que a su vez poseían entre sus campos otro puntero que apuntaba a pokemones, permitiendo así trabajar con un vector dinámico de pokemones (haciendo uso de la aritmética de punteros) de tamaño variable.
Por último, también es importante destacar la importancia de manejar dichos punteros de forma correcta ya que son esenciales para llevar a cabo la liberación del espacio en memoria reservado en el heap, evitando posibles fugas.


#### Aritmética de punteros: 
Consiste en el conjunto de las operaciones aritméticas que se pueden llevar a cabo con este tipo de datos (punteros). Entre estas operaciones destacan principalmente la suma y la resta, las cuales nos permiten acceder a distintas posiciones en la memoria a partir de un puntero en cuestión. Para poder hacer uso de esta útil "herramienta" se requiere de un puntero que no sea de tipo void, debido que cuando le sumamos o restamos un número X, el puntero se desplazará X unidades/elementos de acuerdo al tipo de dato al que apunte, por lo cual, en caso de tratarse de un puntero void, el mismo no sabría cuantos bytes moverse.
Es decir, si tengo un puntero a un entero: int* ptr el cual apunta a un cierto lugar en memoria, al hacer *(ptr+1) ahora apuntará a la posición que se encuentra 4 bytes más adelante.

Evidentemente, el uso de aritmética de punteros tuvo un rol importante en el trabajo, ya que permitió trabajar con los dos vectores de pokemones (del arrecife y del acuario), especialmente al momento de realizar el traslado, donde es necesario recorrerlos.


#### Punteros a funciones: 
La lógica es similar a lo planteado anteriormente, se trata de un puntero que en lugar de apuntar a una variable apunta a una función, es decir, apunta a una parte de código. Esto implica grandes ventajas, porque al tener un puntero que apunte a una función significa que mediante el mismo podemos pasar una función como parámetro de otra función, de manera tal que esta última se vuelve mucho más flexible, genérica y personalizable, conduciendo a un posible ahorro de varias lineas de código ya que ahora no será necesario reescribir funciones que sean muy similares. A su vez, también nos permiten tener un vector de funciones e incluso también que una función retorne un puntero a otra función.

En el trabajo podemos observar el uso de punteros a funciones a la hora de seleccionar los pokemones que cumplan con X condición, en donde la función de trasladar es la misma. También, se hizo uso de estos tipos de punteros a la hora de censar el arrecife, usando múltiples funciones que listen los pokemones de distintas formas. Además, se puede ver ejemplificado en el trabajo esta cuestión de crear un vector de funciones utilizando el puntero.

#### Malloc y Relloc: 
La memoria dinámica, tal como su nombre lo indica, es una memoria que varía en el tiempo, la cual sólo se utiliza en tiempo de ejecución y se reserva en el heap. Una gran particularidad es que nosotros somos quienes debemos manejar dicha memoria. Para ello se utilizan dos funciones claves que son malloc y realloc. Malloc es una función que simplemente reserva en el heap la cantidad de bytes que se le pasa por parámetro y devuelve el puntero a la primera posición de dicho bloque reservado. En cambio, Realloc es una función a la cual se le pasa por parámetro un puntero a un bloque de memoria ya reservado y una cantidad de bytes (positiva o negativa) y ampliará/reducirá el tamaño del bloque reservado en cuestión, y devolverá el puntero que apunta a la primera posición del bloque nuevo reservado que no necesariamente coincide con el puntero pasado por parámetro, puede ocurrir que no pueda modificar el bloque viejo y tenga que crear uno nuevo, liberando automaticamente el viejo. 
Por último, es importante mencionar que toda memoria que reservemos en el heap debe ser liberada mediante la funcion 'free', de lo contrario tendremos una fuga de memoria.

En el trabajo, estas funciones adquirieron también un papel central ya que posibilitó el almacenamiento del arrecife y del acuario en el heap, de manera tal que la manipulación de cualquiera de estas dos estructuras no dependa del ámbito en el que nos encontremos.
