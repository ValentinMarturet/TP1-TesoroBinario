/*
 * interacciones.h
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#ifndef INTERACCIONES_H_
#define INTERACCIONES_H_

#include "Jugador.h"

typedef struct {
	int fila;
	int columna;
} Posicion;


/*
 * Imprime el tablero para el jugador dado
 */
void imprimirTablero(Tablero * tablero, Jugador * jugador);

/*
 * Pide por input que el usuario elija las posiciones de sus tesoros
 */
void pedirTesoros(Tesoros tesoros);

void pedirEspia(Tablero * tablero, int id);

void pedirMoverTesoro(Jugador * jugador, Posicion * ultimoMovimiento);

/*
 * Se le otorga el tipo de movimiento y la lista de tesoros y esta pide cuantas casillas se quiere desplazar ese tesoro.
 * Chequee que el tesoro no se salga del tablero y que no ocupe el mismo lugar de un tesoro propio. Si cumple todas las
 * condiciones mueve el tesoro a la casilla indicada.
 */
void moverTesoro(int movimiento, Tesoros tesoro, int numeroTesoro, Posicion * ultimoMovimiento);


#endif /* INTERACCIONES_H_ */
