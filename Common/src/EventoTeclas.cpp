#include "EventoTeclas.h"
#include "constantes.h"
#include <iostream>

EventoTeclas::EventoTeclas(int id, const std::vector<char> teclas): id(id) {
	arriba = teclas.at(POSICION_ARRIBA);
	abajo = teclas.at(POSICION_ABAJO);
	derecha = teclas.at(POSICION_DERECHA);
	izquierda = teclas.at(POSICION_IZQUIERDA);
	barra = teclas.at(POSICION_BARRA);
}

bool EventoTeclas::teclaArriba() const{
	return this->arriba;
}

bool EventoTeclas::teclaAbajo() const{
	return this->abajo;
}

bool EventoTeclas::teclaDerecha() const{
	return this->derecha;
}

bool EventoTeclas::teclaIzquierda() const{
	return this->izquierda;
}

bool EventoTeclas::teclaBarra() const{
	return this->barra;
}

int EventoTeclas::getId() const{
	return this->id;
}


