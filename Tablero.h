/*
 * Tablero.h
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "Casillero.h"

typedef struct Tablero {
	Casillero ** matriz;
	int ancho;
	int alto;

} Tablero;

Tablero inicializarTablero(int ancho, int alto);

void borrarTablero(Tablero * tablero);

#endif /* TABLERO_H_ */
