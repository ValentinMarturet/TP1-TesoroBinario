/*
 * principal.cpp
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */
#include "Tablero.h"
#include "TesoroBinario.h"

int main() {

	int alto, ancho;
	alto = 20;
	ancho = 20;

	Tablero tablero = inicializarTablero(alto, ancho);
	Jugador jugador1 = inicializarJugador(1);
	Jugador jugador2 = inicializarJugador(2);

	iniciarJuego(&tablero, &jugador1, &jugador2);

	borrarTablero(&tablero);
	return 0;
}
