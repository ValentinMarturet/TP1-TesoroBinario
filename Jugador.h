/*
 * Jugador.h
 *
 *  Created on: 3 sep. 2023
 *      Author: Valentin
 */

#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Casillero.h"
#include "Tablero.h"
#include <iostream>

//typedef Coordenada Tesoros[4];
//
typedef struct {
	int numero;
	int fila;
	int columna;
	bool siendoRobado;
	int turnoFinal;
} Tesoro;

typedef Tesoro Tesoros[4];

typedef struct {
	Tesoros tesoros;
	int vidas;
	int id;
} Jugador;


Jugador inicializarJugador(int id);



/*
 * Una funcion que chequea si hay un tesoro en esas coordenadas y si es asi, devuelve la posicion del array en la que se
 * encuentra ese tesoro.
 */
int hayTesoro(Tesoros tesoros, int fila, int columna);



/*
 * Devuelve true o false dependiendo de si hay un espia del jugador contrario en esa casilla.
 * El id pasado por parametro tiene que corresponder al jugador contrario
 */
bool hayEspia(Tablero * tablero, Tesoro tesoro, int idEnemigo);



#endif /* JUGADOR_H_ */
