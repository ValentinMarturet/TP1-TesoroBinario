/*
 * Tablero.cpp
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#include "Tablero.h"

Tablero inicializarTablero(int alto, int ancho){
	Tablero tablero;

	tablero.alto = alto;
	tablero.ancho = ancho;
	tablero.matriz = new Casillero * [tablero.alto];

	for(int i = 0; i < alto; i++){
		tablero.matriz[i] = new Casillero[tablero.ancho];
		for(int j=0; j<ancho ; j++){
			tablero.matriz[i][j].coordenada.fila = i;
			tablero.matriz[i][j].coordenada.columna = j;
			tablero.matriz[i][j].espia = 0;

		}
	}
	return tablero;
}


void borrarTablero(Tablero * tablero){
	for (int i = 0; i< 20; i++){
		delete [] tablero->matriz[i];
	}
	delete [] tablero->matriz;
}
