# The Clash Of The Guardians
## Problema
La creacion de un juego de cartas llamado "The Clash of the Guardians" con las funcionalidades minimas de:
* Lectura de cartas desde archivo externo
* Capacidad de crear cartas nuevas
* Combatir contra la CPU
* Ver el historial de movimientos de la ultima partida jugada
## Solucion
### 2 estructuras:
* Guardian; con nombre, tipo, vida, ataque, defensa
* Historial; con turno actual, vida de jugador y CPU y acciones realizadas
### Listas:
* Mazo general de +60 cartas
* Cartas de los jugadores en la mano
* Cartas de los jugadores en la arena
### Cola:
* Historial de movimientos
### Pilas:
* Mazo de los Jugadores
* Copia de mazo de los jugadores
### Funciones Importantes
* copy_stats: copia estadisticas de un guardian y las transfiere a uno nuevo
* list_to_list: mueve a guardian de una lista a otra
* shuffle_deck: crea los mazos de los jugadores usando numeros aleatorios
* look_by_stats: devuelve al guardian con mas ataque o menos vida
* get_list_size: devuelve el tamaño de la lista ingresada
* start_fight: donde ocurre la pelea en si, y donde se ocupan las anteriores funciones
### Link para Video
https://youtu.be/AKlgMF-9ahI
