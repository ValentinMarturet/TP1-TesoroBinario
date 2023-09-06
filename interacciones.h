/*
 * interacciones.h
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#ifndef INTERACCIONES_H_
#define INTERACCIONES_H_

#include "Jugador.h"



/*
 * Imprime el tablero para el jugador dado
 */
void imprimirTablero(Tablero * tablero, Jugador * jugador);

/*
 * Pide por input que el usuario elija las posiciones de sus tesoros
 */
void pedirTesoros(Tesoros tesoros);

void pedirEspia(Tablero * tablero, int id);

#endif /* INTERACCIONES_H_ */
