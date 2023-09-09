/*
 * TesoroBinario.cpp
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#include "TesoroBinario.h"
#include "interacciones.h"
#include <iostream>




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

		// Despues del primer turno los jugadores deberian poder mover sus tesoros.
		cout << " - JUGADOR 1 - " << endl;
		if (turno > 1){
			pedirMoverTesoro(jugador1);
		}


		cout << "Jugador 1 - Coloque sus espias ---" << endl;
		pedirEspia(tablero, jugador1->id);
		imprimirTablero(tablero, jugador1);

		// Tengo que iterar sobre los tesoros del contrincante. Si alguno tiene un espia encima, ese tesoro se empiza a recoger
		// y la casilla se bloquea por 5 turnos.
		chequearTesorosRobados(tablero, jugador2, 1, turno);





		cout << "-INGRESE UN NUMERO PARA PASARLE EL TURNO AL JUGADOR 2: ";
		cin >> aux;

		cout << " - JUGADOR 2 - " << endl;
		if (turno > 1 && jugador2->vidas >0){
			pedirMoverTesoro(jugador2);
		}


		cout << "Jugador 2 - Coloque sus espias ---" << endl;
		pedirEspia(tablero, jugador2->id);
		imprimirTablero(tablero, jugador2);

		chequearTesorosRobados(tablero, jugador1, 2, turno);

//		for(int i = 0; i<4; i++){
//			if(hayEspia(tablero, &jugador1->tesoros[i], 2) && (jugador1->tesoros[i].turnoFinal == 0)){
//				cout << "¡¡LE ESTAS ROBANDO UN TESORO A TU CONTRINCANTE!!" << endl;
//				jugador1->tesoros[i].siendoRobado = true;
//				jugador1->tesoros[i].turnoFinal = turno+5;
//				jugador1->vidas--;
//			}
//		}

		hayTesoro(jugador1->tesoros, 2, 2);


		cout << "-INGRESE UN NUMERO PARA TERMINAR EL TURNO: ";
		cin >> aux;





		//Este loop se encarga de cambiar el estado de los tesoros una vez que ya fueron robados.
		for(int i = 0; i < 4 ; i++){
			if(jugador1->tesoros[i].turnoFinal < turno-1){
				jugador1->tesoros[i].siendoRobado = false;
			}
			if(jugador2->tesoros[i].turnoFinal < turno-1){
				jugador2->tesoros[i].siendoRobado = false;
			}
		}
		turno++;
	}
	if (jugador1->vidas == 0){
		cout << "EL JUGADOR 1 SE HA QUEDADO SIN TESOROS..." << endl;
	} else if (jugador2->vidas == 0){
		cout << "EL JUGADOR 2 SE HA QUEDADO SIN TESOROS..." << endl;
	} else {
		cout << "HA OCURRIDO UN ERROR Y LA PARTIDA HA TERMINADO." << endl;
	}


}

void chequearTesorosRobados(Tablero * tablero, Jugador * jugadorEnemigo, int id, int turno){
	for(int i = 0; i<4; i++){
		if(hayEspia(tablero, &jugadorEnemigo->tesoros[i], id) && (jugadorEnemigo->tesoros[i].turnoFinal == 0)){
			cout << "¡¡LE ESTAS ROBANDO UN TESORO A TU CONTRINCANTE!!" << endl;
			jugadorEnemigo->tesoros[i].siendoRobado = true;
			jugadorEnemigo->tesoros[i].turnoFinal = turno+5;
			jugadorEnemigo->vidas--;
		}
	}
}
