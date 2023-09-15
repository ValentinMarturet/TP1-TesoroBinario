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




void iniciarJuego(Tablero * tablero, Jugador * jugador1, Jugador * jugador2){
	cout << "-  T E S O R O   B I N A R I O  -" << endl;
	cout << "-- EMPIEZA EL JUEGO --" << endl;


	int turno = 1;
	int aux;
	Posicion ultimoMovimiento;


	string ruta1 = "jugador1.txt";
	string ruta2 = "jugador2.txt";

	ofstream archivo1;
	ofstream archivo2;
	archivo1.open(ruta1.c_str());
	archivo2.open(ruta2.c_str());


	while((jugador1->vidas > 0) && (jugador2->vidas > 0)) {
		cout << "- TURNO " << turno << " -" << endl;

		// Despues del primer turno los jugadores deberian poder mover sus tesoros.
		cout << " - JUGADOR 1 - " << endl;
		if (turno > 1){
			tesorosSuperpuestos(jugador1, ultimoMovimiento.fila, ultimoMovimiento.columna);
			pedirMoverTesoro(jugador1, &ultimoMovimiento);
		}


		cout << "Jugador 1 - Coloque sus espias ---" << endl;
		pedirEspia(tablero, jugador1->id);
		imprimirTablero(tablero, jugador1);
		guardarTablero(tablero, jugador1, &archivo1, turno);

		// Tengo que iterar sobre los tesoros del contrincante. Si alguno tiene un espia encima, ese tesoro se empiza a recoger
		// y la casilla se bloquea por 5 turnos.
		chequearTesorosRobados(tablero, jugador2, 1, turno);





		cout << "-INGRESE UN NUMERO PARA PASARLE EL TURNO AL JUGADOR 2: ";
		cin >> aux;

		cout << " - JUGADOR 2 - " << endl;

		tesorosSuperpuestos(jugador2, ultimoMovimiento.fila, ultimoMovimiento.columna);

		if (turno > 1 && jugador2->vidas >0){
			pedirMoverTesoro(jugador2, &ultimoMovimiento);
			cout << "columna: " << ultimoMovimiento.columna << " fila: " << ultimoMovimiento.fila << endl;
		}


		cout << "Jugador 2 - Coloque sus espias ---" << endl;
		pedirEspia(tablero, jugador2->id);
		imprimirTablero(tablero, jugador2);
		guardarTablero(tablero, jugador2, &archivo2, turno);

		chequearTesorosRobados(tablero, jugador1, 2, turno);



		cout << "-INGRESE UN NUMERO PARA TERMINAR EL TURNO: ";
		cin >> aux;





		//Este loop se encarga de cambiar el estado de los tesoros una vez que ya fueron robados.
		for(int i = 0; i < 4 ; i++){
			if(jugador1->tesoros[i].turnoFinal < turno-1 && jugador1->tesoros[i].turnoFinal != 0){
				jugador1->tesoros[i].siendoRobado = false;
				//Esto hace que los tesoros dejen de ocupar esas casillas una vez que han sido robados
				jugador1->tesoros[i].columna = 20;
				jugador1->tesoros[i].fila = 20;
			}
			if(jugador2->tesoros[i].turnoFinal < turno-1 && jugador2->tesoros[i].turnoFinal != 0){
				jugador2->tesoros[i].siendoRobado = false;
				jugador2->tesoros[i].columna = 20;
				jugador2->tesoros[i].fila = 20;
			}
		}
		turno++;
	}
	if(jugador1->vidas == 0 && jugador2->vidas == 0){
		cout << "LA APRTIDA HA TERMINADO EN EMPATE..." << endl;
	} else if (jugador1->vidas == 0){
		cout << "EL JUGADOR 1 SE HA QUEDADO SIN TESOROS..." << endl;
	} else if (jugador2->vidas == 0){
		cout << "EL JUGADOR 2 SE HA QUEDADO SIN TESOROS..." << endl;
	} else {
		cout << "HA OCURRIDO UN ERROR Y LA PARTIDA HA TERMINADO." << endl;
	}

	archivo1.close();
	archivo2.close();


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
