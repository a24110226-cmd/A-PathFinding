# Mochi Moods / A*

Juego de mascota virtual inspirado en Tamagotchi. La implementación nativa está organizada con una arquitectura modular: `Game` coordina las clases del juego, `Mochi` administra la mascota, `State` describe sus estados y `Pathfinder` resuelve la búsqueda informada A*.

## Estructura

```text
include/
	Game.hpp          Coordinador del ciclo principal
	Mochi.hpp         Estado y necesidades de la mascota
	Pathfinder.hpp    Interfaz del algoritmo A*
	State.hpp         Point y StateInfo
src/
	main.cpp          Punto de entrada
	Game.cpp          Entrada, actualización y render de consola
	Mochi.cpp         Acciones y evolución de necesidades
	Pathfinder.cpp    Vecinos, heurística Manhattan y rutas
Makefile             Compilación modular
```

## Ejecutar C++

Requiere `g++` y C++17. Desde la carpeta del proyecto:

```bash
make
./bin/mochi_moods
```

Para borrar objetos y ejecutables generados:

```bash
make clean
```

## Controles

```text
[1] Comer       [2] Jugar       [3] Dormir
[4] Limpiar     [5] Acariciar   [6] Cambiar estado
[7] Esperar     [8] Ayuda       [9] Salir
```

Mochi cuenta con siete estados: Explorando, Hambriento, Feliz, Cansado, Curioso, Aburrido y Dormido. Cada estado tiene un destino diferente y cada cuatro turnos puede cambiar automáticamente.

## Búsqueda informada

`Pathfinder` usa A* con la función `f(n) = g(n) + h(n)` y la heurística Manhattan. La pantalla muestra el costo recorrido, la estimación restante y los nodos explorados, para que el funcionamiento de la búsqueda informada sea visible durante la demostración.

La interfaz web original se conserva en `index.html`, `styles.css` y `app.js`; la versión estructurada que debe compilarse y presentarse en C++ es `bin/mochi_moods`.