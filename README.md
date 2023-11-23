# Parcial 03

- [Parcial 03](#parcial-03)
  - [Instrucciones](#instrucciones)
  - [Introducción](#introducción)
  - [Ejercicio 1 (35 puntos)](#ejercicio-1-35-puntos)
    - [Ejemplo 1.1](#ejemplo-11)
    - [Ejemplo 1.2](#ejemplo-12)
    - [Ejemplo 1.3](#ejemplo-13)
    - [Restricciones](#restricciones)
  - [Ejercicio 2 (30 puntos)](#ejercicio-2-30-puntos)
    - [Ejemplo 2.1](#ejemplo-21)
    - [Ejemplo 2.2](#ejemplo-22)
    - [Restricciones](#restricciones-1)
  - [Ejercicio 3 (35 puntos)](#ejercicio-3-35-puntos)
    - [Ejemplo 3.1](#ejemplo-31)
    - [Restricciones](#restricciones-2)

## Instrucciones

1. Para iniciar, debe crear un *Fork* del repositorio:

![fork button](images/fork.png)

2. Vaya la pestaña de **actions** de su repositorio. Si ve un botón verde, haga clic en él para poder ejecutar las pruebas en el futuro.

![actions tab](images/actions.png)

3. Clone el nuevo repositorio en su computadora y ábralo en Visual Studio.

4. En el menú de Visual Studio, en la sección de *Build* o *Compilar*, construya la solución.

5. En el menú de Visual Studio, en la sección de Tests, seleccione *Run All Tests*

6. La mayoría de las pruebas deberían fallar.

## Introducción

- Todos los ejercicios deben compilar para poder ser probados. Si por lo menos uno de los ejercicios no compila, la nota será **cero**.
- Si el código original de un ejercicio no se modifica o la intención de su resolución no es clara, la nota del ejercicicio será de **cero puntos**, aún si hay pruebas que sí pasen para dicho ejercicio.
- NO agregue nuevos métodos `main()`, de lo contrario ninguna prueba podrá ejecutarse.
- NO cambie la firma de los métodos existentes (no agrege más parámetros ni cambie el nombre), estos son utilizados para probar su código.
- NO haga cambios en las pruebas, esto resulta en un **cero inmediato**.
- Puede agregar nuevas clases y/o archivos, como sea necesario.
- Las definiciones de funciones y atributos de las clases se encuentran en archivos `.h`, pero debe implementar las funciones dentro de los `.cpp` equivalentes.
- A continuación encontrará los enunciados de cada uno de los ejercicios. Su nota en cada uno de los ejercicios será la relación entre la cantidad de pruebas que sí pasen sobre la cantidad total de pruebas para ese ejercicio.
- En la pestaña de **Actions** podrá ver como las pruebas se ejecutan con su código implementado (si hace `git push` previamente). En los últimos pasos, puede ver los resultados y su nota:

![results step](images/results.png)
___

## Ejercicio 1 (35 puntos)

Dada una lista enlazada de listas enlazadas de números enteros `lists`, en donde cada una de la listas de números se encuentran ordenadas descendentemente.

Mezcle todas las listas enlazadas en una sola lista enlazada ordenada descendentemente y retornela.

### Ejemplo 1.1

    lists = [[5 -> 4 -> 1] -> [4 -> 3 -> 1] -> [6 -> 2]
    resultado = [6 -> 5 -> 4 -> 4 -> 3 -> 2 -> 1 -> 1]
___

### Ejemplo 1.2

    lists = []
    resultado = []
___

### Ejemplo 1.3

    lists = [[100]]
    resultado = [100]
___

### Restricciones

- La cantidad de listas se encuentra entre **0** y **10<sup>4</sup>**.
- Cada lista de números enteros puede tener entre **0** y **500** nodos.
- Los números enteros se encuentran en el rango **[ -10<sup>4</sup>, 10<sup>4</sup> ]**.
- Las listas se encuentran ordenadas **descendentemente**, es decir, de mayor a menor.

___

## Ejercicio 2 (30 puntos)

La **secuencia de ADN** se compone de una serie de nucleótidos que se abrevian con: `'A'`, `'C'`, `'G'` y `'T'`.

- Por ejemplo, `"ACGAATTCCG"` es una **secuencia de ADN**.

Cuando se estudia el ADN, es importante encontrar secuencias repetidas en el ADN.

Dado el nodo `head` de una lista simplemente enlazada, en donde cada nodo tiene un caracter de una **secuencia de ADN**, retorne todas las secuencias, en forma de **`string`** de **10 carácteres de longitud**, que aparecen más de una vez en una molécula de ADN. Puede retornar el resultado en **cualquier orden**.

### Ejemplo 2.1

    head = A -> A -> A -> A -> A -> C -> C -> C -> C -> C -> A -> A -> A -> A -> A -> C -> C -> C -> C -> C -> C -> A -> A -> A -> A -> A -> G -> G -> G -> T -> T -> T
    resultado ["AAAAACCCCC","CCCCCAAAAA"]

___

### Ejemplo 2.2

    head = A -> A -> A -> A -> A -> A -> A -> A -> A -> A -> A -> A -> A
    resultado = ["AAAAAAAAAA"]

___

### Restricciones

- La cantidad de nodos se encuentra entre **1** y **10<sup>5</sup>**.
- `Node<char>.value` solo puede ser `'A'`, `'C'`, `'G'` o `'T'`.

___

## Ejercicio 3 (35 puntos)

Diseñe una estructura de datos de clave-valor (key-value pair) consciente del tiempo de almacenamiento, en donde se puedan almacenar distintos valores para la misma llave en diferentes instantes de tiempo (**timestamps**) y en donde también se puedan buscar los valores utilizando la llave y el instante de tiempo.

Implemente la clase `TimeMap` que se encuentra en `Ejercicio03.h` y `Ejercicio03.cpp`;

- `TimeMap()` instancia un objeto para la estructura de datos.
- `void set(String key, String value, int timestamp)` almacena la llave `key` con el valor `value` en el instante de tiempo `timestamp` proporcionado.
- `String get(String key, int timestamp)` retorna un valor dado que `set()` fue llamado previamente, con un instante de tiempo previo menor al instante de tiempo actual (`timestamp_prev <= timestamp`). Si existen varios valores para la misma clave (`key`), retorna el valor asociado al instante de tiempo previo (`timestamp_prev`) más cercano que sea menor que el instante de tiempo dado. Si no existen valores retorna `""`.

### Ejemplo 3.1

```c++
    TimeMap* timeMap = new TimeMap();
    timeMap->set("foo", "bar", 1);  // almacene la clave (key) "foo" y el valor (value) "bar" con el instante de tiempo (timestamp = 1).
    timeMap->get("foo", 1);         // return "bar"
    timeMap->get("foo", 3);         // return "bar", ya que no hay un valor exacto para "foo" con instante de tiempo 3 ni con instante de tiempo 2, el valor menor y el más cercano es el valor "bar" que fue almacenada en el instante de tiempo 1 (timestamp = 1).
    timeMap->set("foo", "bar2", 4); // almacene la clave (key) "foo" y el valor (value) "bar2" con el instante de tiempo (timestamp = 4).
    timeMap->get("foo", 4);         // return "bar2"
    timeMap->get("foo", 5);         // return "bar2"
```

### Restricciones

- **1** <= `key.length()`, `value.length()` <= **100**
- Tanto `key` como `value` consisten únicamente de letras minúsculas del alfabeto.
- **1** <= `timestamp` <= **10<sup>7</sup>**
- Cada nueva llamada a **set()** será con un **timestamp** mayor al anterior.
- No más de **2 * 10<sup>5</sup>** llamadas a `get()` y `set()` se realizarán.
