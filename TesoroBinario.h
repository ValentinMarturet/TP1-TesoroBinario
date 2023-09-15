/*
 * TesoroBinario.h
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#ifndef TESOROBINARIO_H_
#define TESOROBINARIO_H_


#include "Jugador.h"


void iniciarJuego(Tablero * tablero, Jugador * jugador1, Jugador * jugador2);

/*
 * Tengo que iterar sobre los tesoros del contrincante. Si alguno tiene un espia encima, ese tesoro se empiza a recoger
 * y la casilla se bloquea por 5 turnos.
 */

void chequearTesorosRobados(Tablero * tablero, Jugador * jugadorEnemigo, int id, int turno);


#endif /* TESOROBINARIO_H_ */
