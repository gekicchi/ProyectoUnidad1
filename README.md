# The Clash Of The Guardians
## Problema
La creación de un juego de cartas llamado "The Clash of the Guardians" con las funcionalidades mínimas de:
* Lectura de cartas desde archivo externo
* Capacidad de crear cartas nuevas
* Combatir contra la CPU
* Ver el historial de movimientos de la ultima partida jugada
## Solución
### 2 estructuras:
* Guardián; con nombre, tipo, vida, ataque, defensa
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
* copy_stats: copia las estadísticas de un guardián y las transfiere a uno nuevo
* list_to_list: mueve a guardián de una lista a otra
* shuffle_deck: crea los mazos de los jugadores usando números aleatorios
* look_by_stats: devuelve al guardián con mas ataque o menos vida
* get_list_size: devuelve el tamaño de la lista ingresada
* start_fight: donde ocurre la pelea en sí, y donde se ocupan las anteriores funciones
### Link para Video
https://youtu.be/AKlgMF-9ahI
