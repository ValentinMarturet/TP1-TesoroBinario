/*
 * interacciones.cpp
 *
 *  Created on: 2 sep. 2023
 *      Author: Valentin
 */

#include <iostream>
#include "interacciones.h"
#include "Jugador.h"
#include "Casillero.h"

using namespace std;

void imprimirTablero(Tablero * tablero, Jugador * jugador){

	for(int i = 0; i < tablero->alto; i++){
			// printea las coordenadas horizontales
			if(i == 0){

				for(int j = 0; j < tablero->ancho; j++){
					if(j==0){
						cout << "--- ";
					}
					if(j< 10){
						cout << "|---" << j << "--";
					} else {
						cout << "|--" << j << "--";
					}
					if(j==(tablero->ancho-1)){
						cout << "|" << endl;
					}
				}
			}


			// printea los bordes superiores de las casillas.
			for(int j = 0; j< tablero->ancho; j++) {
				//printea el espaciado de las coordenadas
				if(j == 0 && i+1 < 10){
					cout << "--- ";
				} else if(j == 0){
					cout << "----";
				}
				cout << "_______";
				if(j == (tablero->ancho - 1)){
					cout << endl;
				}
			}
			// printea el primer borde lateral de la casilla.

			for(int j = 0; j<tablero->ancho; j++){
				// printea las coordenadas verticales
				if(j == 0 && i < 10){
					cout << "-" << i << "- ";
				} else if(j == 0) {
					cout << "-" << i << "-";
				}
				// cout << "|" << "T1 E1 ";

//				Coordenada t1, t2, t3, t4;
//				t1.columna = 2; t1.fila = 2;
//				t2.columna = 3; t2.fila = 2;
//				t3.columna = 4; t3.fila = 3;
//				t4.columna = 5; t4.fila = 4;
//
//				Tesoros tesorosPrueba;
//				tesorosPrueba[0] = t1;
//				tesorosPrueba[1] = t2;
//				tesorosPrueba[2] = t3;
//				tesorosPrueba[3] = t4;



				// Printea los tesoros en las posiciones adecuadas
				int posicion = hayTesoro(jugador->tesoros, i , j);
				if (posicion<4 && !(jugador->tesoros[posicion].siendoRobado)&& (jugador->tesoros[posicion].turnoFinal == 0)){
					cout << "|" << "T" << posicion+1;
				} else if(posicion<4 && jugador->tesoros[posicion].siendoRobado){
					cout << "|" << "X ";
				} else{
					cout << "|" << "  ";
				}




				// Muestra los espias en el trablero
				int id = 1;
				if (tablero->matriz[i][j].espia == jugador->id){
					cout << " " << "E" << id << " ";
				} else {
					cout << "    ";
				}
				//cout << " E1 ";

				// cout << "|" << tablero->matriz[i][j].coordenada.x << " " << tablero->matriz[i][j].coordenada.y << " ";
				if(j == (tablero->ancho - 1)){
					cout << "|" << endl;
				}
			}

			if(i == (tablero->ancho -1)){
				// printea el espaciado de las coordenadas.
				for(int j = 0; j< tablero->ancho; j++) {
					if(j == 0){
						cout << "----";
					}
					cout << "_______";
					if(j == (tablero->ancho - 1)){
						cout << endl;
					}
				}
			}
		}
}


void pedirTesoros(Tesoros tesoros){

	for(int i = 0; i < 4; i++){
		Tesoro tesoro;
		tesoro.numero = i+1;
		tesoro.siendoRobado = false;
		tesoro.turnoFinal = 0;
		cout << "Indique la fila en la que quieres colocar el tesoro Nº" << i+1 << ":";
		cin >> tesoro.fila;

		cout << "Indique la columna en la que quieres colocar el tesoro Nº" << i+1 << ":";
		cin >> tesoro.columna;

		tesoros[i] = tesoro;

	}

}

void pedirEspia(Tablero * tablero, int id){
	Coordenada espia;
	bool condicion;
	do {

		cout << "Ingrese la fila en la que quiere colocar el espia: ";
		cin >> espia.fila;
		cout << "Ingrese la columna en la que quiere colocar el espia: ";
		cin >> espia.columna;

		if (tablero->matriz[espia.fila][espia.columna].espia == id){
			cout << "Ya tienes un espia en esa casilla, por favor coloquelo en otra." << endl;
			condicion = true;
		} else condicion = false;
	} while(condicion);

	if(tablero->matriz[espia.fila][espia.columna].espia == 0){
		// caso de que la casilla no tenga ningun espia
		tablero->matriz[espia.fila][espia.columna].espia = id;
	} else {
		// caso de que la casilla tenga algun espia enemigo
		cout << "Tu espia se ha encontrado con un espia enemigo - Ambos han sido eliminados." << endl;
		tablero->matriz[espia.fila][espia.columna].espia = 0;
	}



}

