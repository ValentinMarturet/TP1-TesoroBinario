/*
 * Jugador.cpp
 *
 *  Created on: 3 sep. 2023
 *      Author: Valentin
 */


#include "Jugador.h"
#include "interacciones.h"




Jugador inicializarJugador(int id){
	Jugador jugador;


	std::cout << "El jugador numero " << id << " debe indicar donde quiere colocar sus tesoros. " << std::endl;
	jugador.id = id;
	jugador.vidas = 4;

	pedirTesoros(jugador.tesoros);

	return jugador;
}



int hayTesoro(Tesoros tesoro, int fila, int columna){
	int posicion = 5;
	for(int i=0; i<4 ;i++){
		if(tesoro[i].fila == fila && tesoro[i].columna== columna){
			posicion = i;
		}
	}

	return posicion;
}


bool hayEspia(Tablero * tablero, Tesoro * tesoro, int idEnemigo){
	bool resultado;

	if(tablero->matriz[tesoro->fila][tesoro->columna].espia == idEnemigo){
		resultado = true;
	} else resultado = false;

	return resultado;
}


