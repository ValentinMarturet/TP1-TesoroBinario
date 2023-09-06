/*
 * TesoroBinario.h
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#ifndef TESOROBINARIO_H_
#define TESOROBINARIO_H_

#include <iostream>
#include "Jugador.h"
#include "Tablero.h"
#include "interacciones.h"

typedef struct {
	Tablero * tablero;
	Jugador * jugador1;
	Jugador * jugador2;

} TesoroBinario;

TesoroBinario inicializarTesoroBinario(int alto, int ancho);


void iniciarJuego(Tablero * tablero, Jugador * jugador1, Jugador * jugador2);


#endif /* TESOROBINARIO_H_ */
