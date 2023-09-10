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
	Posicion ultimoMovimiento;

	while((jugador1->vidas > 0) && (jugador2->vidas > 0)) {
		cout << "- TURNO " << turno << " -" << endl;

		// Despues del primer turno los jugadores deberian poder mover sus tesoros.
		cout << " - JUGADOR 1 - " << endl;
		if (turno > 1){
			tesorosSuperpuestos(jugador1, ultimoMovimiento.fila, ultimoMovimiento.fila);
			pedirMoverTesoro(jugador1, &ultimoMovimiento);
			cout << "columna: " << ultimoMovimiento.columna << " fila: " << ultimoMovimiento.fila << endl;
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

		tesorosSuperpuestos(jugador2, ultimoMovimiento.fila, ultimoMovimiento.fila);

		if (turno > 1 && jugador2->vidas >0){
			pedirMoverTesoro(jugador2, &ultimoMovimiento);
			cout << "columna: " << ultimoMovimiento.columna << " fila: " << ultimoMovimiento.fila << endl;
		}


		cout << "Jugador 2 - Coloque sus espias ---" << endl;
		pedirEspia(tablero, jugador2->id);
		imprimirTablero(tablero, jugador2);

		chequearTesorosRobados(tablero, jugador1, 2, turno);


		hayTesoro(jugador1->tesoros, 2, 2);


		cout << "-INGRESE UN NUMERO PARA TERMINAR EL TURNO: ";
		cin >> aux;





		//Este loop se encarga de cambiar el estado de los tesoros una vez que ya fueron robados.
		for(int i = 0; i < 4 ; i++){
			if(jugador1->tesoros[i].turnoFinal < turno-1){
				jugador1->tesoros[i].siendoRobado = false;
				//Esto hace que los tesoros dejen de ocupar esas casillas una vez que han sido robados
				jugador1->tesoros[i].columna = 20;
				jugador1->tesoros[i].fila = 20;
			}
			if(jugador2->tesoros[i].turnoFinal < turno-1){
				jugador2->tesoros[i].siendoRobado = false;
				jugador2->tesoros[i].columna = 20;
				jugador2->tesoros[i].fila = 20;
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
