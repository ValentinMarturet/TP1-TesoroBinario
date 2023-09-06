/*
 * Casillero.h
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#ifndef CASILLERO_H_
#define CASILLERO_H_


typedef struct{
	int columna;
	int fila;
} Coordenada;

typedef struct {
	Coordenada coordenada;
	int espia;
} Casillero;

#endif /* CASILLERO_H_ */
