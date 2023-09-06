/*
 * TesoroBinario.cpp
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#include "TesoroBinario.h"




using namespace std;

TesoroBinario inicializarTesoroBinario(int alto, int ancho){
	TesoroBinario tesoroBinario;

	Jugador jugador1 = inicializarJugador(1);
	Jugador jugador2 = inicializarJugador(2);

	tesoroBinario.jugador1 = &jugador1;
	tesoroBinario.jugador2 = &jugador2;
	Tablero tablero = inicializarTablero(alto, ancho);

	tesoroBinario.tablero = &tablero;

	return tesoroBinario;
}


void iniciarJuego(Tablero * tablero, Jugador * jugador1, Jugador * jugador2){
	cout << "-  T E S O R O   B I N A R I O  -" << endl;
	cout << "-- EMPIEZA EL JUEGO --" << endl;


	int turno = 1;
	int aux;

	while((jugador1->vidas > 0) && (jugador2->vidas > 0)) {
		cout << "- TURNO " << turno << " -" << endl;

		cout << "Jugador 1 - Coloque sus espias ---" << endl;
		pedirEspia(tablero, jugador1->id);
		imprimirTablero(tablero, jugador1);

		// Tengo que iterar sobre los tesoros del contrincante. Si alguno tiene un espia encima, ese tesoro se empiza a recoger
		// y la casilla se bloquea por 5 turnos.
		for(int i = 0; i<4; i++){
			if(hayEspia(tablero, jugador2->tesoros[i], 2)){
				jugador2->tesoros[i].siendoRobado = true;
				jugador2->tesoros[i].turnoFinal = turno+5;
			}
		}




		cout << "-INGRESE UN NUMERO PARA PASARLE EL TURNO AL JUGADOR 2: ";
		cin >> aux;


		cout << "Jugador 2 - Coloque sus espias ---" << endl;
		pedirEspia(tablero, jugador2->id);
		imprimirTablero(tablero, jugador2);
		// Tengo que iterar sobre los tesoros del contrincante. Si alguno tiene un espia encima, ese tesoro se empiza a recoger
		// y la casilla se bloquea por 5 turnos.

		cout << "-INGRESE UN NUMERO PARA TERMINAR EL TURNO: ";
		cin >> aux;




		turno++;
	}




}
