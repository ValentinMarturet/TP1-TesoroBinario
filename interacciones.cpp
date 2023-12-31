/*
 * interacciones.cpp
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#include <iostream>
#include <string>

#include "interacciones.h"
#include "Jugador.h"
#include "Casillero.h"

using namespace std;

void imprimirTablero(Tablero *tablero, Jugador *jugador) {

	for (int i = 0; i < tablero->alto; i++) {
		// printea las coordenadas horizontales
		if (i == 0) {

			for (int j = 0; j < tablero->ancho; j++) {
				if (j == 0) {
					cout << "--- ";
				}
				if (j < 10) {
					cout << "|---" << j << "--";
				} else {
					cout << "|--" << j << "--";
				}
				if (j == (tablero->ancho - 1)) {
					cout << "|" << endl;
				}
			}
		}

		// printea los bordes superiores de las casillas.
		for (int j = 0; j < tablero->ancho; j++) {
			//printea el espaciado de las coordenadas
			if (j == 0 && i + 1 < 10) {
				cout << "--- ";
			} else if (j == 0) {
				cout << "----";
			}
			cout << "_______";
			if (j == (tablero->ancho - 1)) {
				cout << endl;
			}
		}
		// printea el primer borde lateral de la casilla.

		for (int j = 0; j < tablero->ancho; j++) {
			// printea las coordenadas verticales
			if (j == 0 && i < 10) {
				cout << "-" << i << "- ";
			} else if (j == 0) {
				cout << "-" << i << "-";
			}

			int posicion = hayTesoro(jugador->tesoros, i, j);
			if (posicion < 4 && !(jugador->tesoros[posicion].siendoRobado)
					&& (jugador->tesoros[posicion].turnoFinal == 0)) {
				cout << "|" << "T" << posicion + 1;
			} else if (posicion < 4
					&& jugador->tesoros[posicion].siendoRobado) {
				cout << "|" << "X ";
			} else {
				cout << "|" << "  ";
			}

			// Muestra los espias en el trablero
			int id = 1;
			if (tablero->matriz[i][j].espia == jugador->id) {
				cout << " " << "E" << id << " ";
			} else {
				cout << "    ";
			}

			if (j == (tablero->ancho - 1)) {
				cout << "|" << endl;
			}
		}

		if (i == (tablero->ancho - 1)) {
			// printea el espaciado de las coordenadas.
			for (int j = 0; j < tablero->ancho; j++) {
				if (j == 0) {
					cout << "----";
				}
				cout << "_______";
				if (j == (tablero->ancho - 1)) {
					cout << endl;
				}
			}
		}
	}
}

void pedirTesoros(Tesoros tesoros) {

	for (int i = 0; i < 4; i++) {
		Tesoro tesoro;
		tesoro.numero = i + 1;
		tesoro.siendoRobado = false;
		tesoro.turnoFinal = 0;
		cout << "Indique la fila en la que quieres colocar el tesoro Nº"
				<< i + 1 << ":";
		cin >> tesoro.fila;

		cout << "Indique la columna en la que quieres colocar el tesoro Nº"
				<< i + 1 << ":";
		cin >> tesoro.columna;

		tesoros[i] = tesoro;

	}

}

void pedirEspia(Tablero *tablero, int id) {
	Coordenada espia;
	bool condicion;
	do {

		cout << "Ingrese la fila en la que quiere colocar el espia: ";
		cin >> espia.fila;
		cout << "Ingrese la columna en la que quiere colocar el espia: ";
		cin >> espia.columna;

		if (tablero->matriz[espia.fila][espia.columna].espia == id) {
			cout
					<< "Ya tienes un espia en esa casilla, por favor coloquelo en otra."
					<< endl;
			condicion = true;
		} else
			condicion = false;
	} while (condicion);

	if (tablero->matriz[espia.fila][espia.columna].espia == 0) {
		// caso de que la casilla no tenga ningun espia
		tablero->matriz[espia.fila][espia.columna].espia = id;
	} else {
		// caso de que la casilla tenga algun espia enemigo
		cout
				<< "Tu espia se ha encontrado con un espia enemigo - Ambos han sido eliminados."
				<< endl;
		tablero->matriz[espia.fila][espia.columna].espia = 0;
	}

}

void pedirMoverTesoro(Jugador *jugador, Posicion *ultimoMovimiento) {
	cout << "DEBES MOVER UN TESORO..." << endl;
	int numeroTesoro;
	cout << "Indique que tesoro quiere mover (1, 2, 3, 4):";
	cin >> numeroTesoro;
	while (numeroTesoro > 5 && numeroTesoro < 1) {
		cout << "Numero de tesoro invalido!" << endl;
		cout << "Indique que tesoro quiere mover (1, 2, 3, 4):";
		cin >> numeroTesoro;
	}
	while (jugador->tesoros[numeroTesoro - 1].turnoFinal != 0) {
		cout << "Este tesoro ya fue robado!" << endl;
		cout << "Indique que tesoro quiere mover (1, 2, 3, 4):";
		cin >> numeroTesoro;
	}

	int movimiento;
	do {

		cout << "Indique como quiere mover el tesoro:" << endl << "- Arriba (1)"
				<< "              " << "- Abajo (2)" << endl
				<< "- Izquierda (3)" << "           " << "- Derecha(4)" << endl
				<< "- Arriba-Izquierda (5)" << "    " << "- Abajo-Izquierda (6)"
				<< endl << "- Arriba-Derecha (7)" << "      "
				<< "- Abajo-Derecha (8)" << endl;
		cin >> movimiento;
	} while (movimiento < 0 || movimiento > 8);

	moverTesoro(movimiento, jugador->tesoros, numeroTesoro, ultimoMovimiento);

}

void moverTesoro(int movimiento, Tesoros tesoros, int numeroTesoro,
		Posicion *ultimoMovimiento) {
	int cantidadCasillas = 0;
	int coincidencias = 0;
	numeroTesoro--;

	switch (movimiento) {
	case 1:
		cout << "MOVIENDO TESORO HACIA ARRIBA" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].fila - cantidadCasillas >= 0) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].fila - cantidadCasillas)
							&& tesoros[i].columna
									== tesoros[numeroTesoro].columna
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}

			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].fila - cantidadCasillas >= 0)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}
		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].fila - cantidadCasillas >= 0));
		tesoros[numeroTesoro].fila -= cantidadCasillas;
		break;

	case 2:
		cout << "MOVIENDO TESORO HACIA ABAJO" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].fila + cantidadCasillas < 20) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].fila + cantidadCasillas)
							&& tesoros[i].columna
									== tesoros[numeroTesoro].columna
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}
			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].fila + cantidadCasillas < 20)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}
		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].fila + cantidadCasillas < 20));
		tesoros[numeroTesoro].fila += cantidadCasillas;
		break;

	case 3:
		cout << "MOVIENDO TESORO HACIA IZQUIERDA" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].columna - cantidadCasillas >= 0) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].columna - cantidadCasillas)
							&& tesoros[i].fila == tesoros[numeroTesoro].fila
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}

			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].columna - cantidadCasillas >= 0)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}
		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].columna - cantidadCasillas >= 0));
		tesoros[numeroTesoro].columna -= cantidadCasillas;
		break;

	case 4:
		cout << "MOVIENDO TESORO HACIA DERECHA" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].columna + cantidadCasillas < 20) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].columna + cantidadCasillas)
							&& tesoros[i].fila == tesoros[numeroTesoro].fila
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}

			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].columna + cantidadCasillas < 20)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}
		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].columna + cantidadCasillas < 20));
		tesoros[numeroTesoro].columna += cantidadCasillas;
		break;

	case 5:
		cout << "MOVIENDO TESORO HACIA ARRIBA-IZQUIERDA" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].columna - cantidadCasillas >= 0
					&& tesoros[numeroTesoro].fila - cantidadCasillas >= 0) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].columna - cantidadCasillas)
							&& tesoros[i].fila
									== (tesoros[numeroTesoro].fila
											- cantidadCasillas)
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}

			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].columna - cantidadCasillas >= 0
							&& tesoros[numeroTesoro].fila - cantidadCasillas
									>= 0)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}
		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].columna - cantidadCasillas >= 0
						&& tesoros[numeroTesoro].fila - cantidadCasillas >= 0));
		tesoros[numeroTesoro].columna -= cantidadCasillas;
		tesoros[numeroTesoro].fila -= cantidadCasillas;
		break;

	case 6:
		cout << "MOVIENDO TESORO HACIA ABAJO-IZQUIERDA" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].columna - cantidadCasillas >= 0
					&& tesoros[numeroTesoro].fila + cantidadCasillas < 20) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].columna - cantidadCasillas)
							&& tesoros[i].fila
									== (tesoros[numeroTesoro].fila
											+ cantidadCasillas)
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}

			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].columna - cantidadCasillas >= 0
							&& tesoros[numeroTesoro].fila + cantidadCasillas
									< 20)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}
		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].columna - cantidadCasillas >= 0
						&& tesoros[numeroTesoro].fila + cantidadCasillas < 20));
		tesoros[numeroTesoro].columna -= cantidadCasillas;
		tesoros[numeroTesoro].fila += cantidadCasillas;
		break;

	case 7:
		cout << "MOVIENDO TESORO HACIA ARRIBA-DERECHA" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].columna + cantidadCasillas < 20
					&& tesoros[numeroTesoro].fila - cantidadCasillas >= 0) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].columna + cantidadCasillas)
							&& tesoros[i].fila
									== (tesoros[numeroTesoro].fila
											- cantidadCasillas)
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}

			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].columna + cantidadCasillas < 20
							&& tesoros[numeroTesoro].fila - cantidadCasillas
									>= 0)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}
		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].columna + cantidadCasillas < 20
						&& tesoros[numeroTesoro].fila - cantidadCasillas >= 0));
		tesoros[numeroTesoro].columna += cantidadCasillas;
		tesoros[numeroTesoro].fila -= cantidadCasillas;
		break;

	case 8:
		cout << "MOVIENDO TESORO HACIA ABAJO-DERECHA" << endl;
		do {
			cout << "Indique cuantas casillas quieres mover el tesoro: ";
			cin >> cantidadCasillas;
			if (tesoros[numeroTesoro].columna + cantidadCasillas < 20
					&& tesoros[numeroTesoro].fila + cantidadCasillas < 20) {
				coincidencias = 0;
				for (int i = 0; i < 4; i++) {
					if (tesoros[i].fila
							== (tesoros[numeroTesoro].columna + cantidadCasillas)
							&& tesoros[i].fila
									== (tesoros[numeroTesoro].fila
											+ cantidadCasillas)
							&& i != numeroTesoro) {
						coincidencias++;
					}
				}

			}
			if (coincidencias > 0
					|| !(tesoros[numeroTesoro].columna + cantidadCasillas < 20
							&& tesoros[numeroTesoro].fila + cantidadCasillas
									< 20)) {
				cout
						<< "La casilla a la que intentas mover el tesoro ya esta ocupada por uno de tus tesoros o te saliste del tablero."
						<< endl << "Por favor, elije otra." << endl;
			}

		} while (coincidencias > 0
				|| !(tesoros[numeroTesoro].columna + cantidadCasillas < 20
						&& tesoros[numeroTesoro].fila + cantidadCasillas < 20));
		tesoros[numeroTesoro].columna += cantidadCasillas;
		tesoros[numeroTesoro].fila += cantidadCasillas;
		break;
	}
	ultimoMovimiento->columna = tesoros[numeroTesoro].columna;
	ultimoMovimiento->fila = tesoros[numeroTesoro].fila;
}

void guardarTablero(Tablero *tablero, Jugador *jugador, ofstream * salida, int turno) {

	*salida << " - TURNO " << turno << "- " << endl;

	for (int i = 0; i < tablero->alto; i++) {
		// printea las coordenadas horizontales
		if (i == 0) {

			for (int j = 0; j < tablero->ancho; j++) {
				if (j == 0) {
					*salida << "--- ";
				}
				if (j < 10) {
					*salida << "|---" << j << "--";
				} else {
					*salida << "|--" << j << "--";
				}
				if (j == (tablero->ancho - 1)) {
					*salida << "|" << endl;
				}
			}
		}

		// printea los bordes superiores de las casillas.
		for (int j = 0; j < tablero->ancho; j++) {
			//printea el espaciado de las coordenadas
			if (j == 0 && i + 1 < 10) {
				*salida << "--- ";
			} else if (j == 0) {
				*salida << "----";
			}
			*salida << "_______";
			if (j == (tablero->ancho - 1)) {
				*salida << endl;
			}
		}
		// printea el primer borde lateral de la casilla.

		for (int j = 0; j < tablero->ancho; j++) {
			// printea las coordenadas verticales
			if (j == 0 && i < 10) {
				*salida << "-" << i << "- ";
			} else if (j == 0) {
				*salida << "-" << i << "-";
			}

			// Printea los tesoros en las posiciones adecuadas
			int posicion = hayTesoro(jugador->tesoros, i, j);
			if (posicion < 4 && !(jugador->tesoros[posicion].siendoRobado)
					&& (jugador->tesoros[posicion].turnoFinal == 0)) {
				*salida << "|" << "T" << posicion + 1;
			} else if (posicion < 4
					&& jugador->tesoros[posicion].siendoRobado) {
				*salida << "|" << "X ";
			} else {
				*salida << "|" << "  ";
			}

			// Muestra los espias en el trablero
			int id = 1;
			if (tablero->matriz[i][j].espia == jugador->id) {
				*salida << " " << "E" << id << " ";
			} else {
				*salida << "    ";
			}

			if (j == (tablero->ancho - 1)) {
				*salida << "|" << endl;
			}
		}

		if (i == (tablero->ancho - 1)) {
			// printea el espaciado de las coordenadas.
			for (int j = 0; j < tablero->ancho; j++) {
				if (j == 0) {
					*salida << "----";
				}
				*salida << "_______";
				if (j == (tablero->ancho - 1)) {
					*salida << endl;
				}
			}
		}
	}
	*salida << endl;
}
