/*
 * EventoConejoPerdioVida.cpp
 *
 *  Created on: 29/11/2015
 *      Author: matiaskamien
 */

#include "EventoConejoPerdioVida.h"

EventoConejoPerdioVida::EventoConejoPerdioVida(const int id):Evento(EVENTO_CONEJO_PERDIO_VIDA),
	id(id){}

const std::string EventoConejoPerdioVida::eventoAsString() const
{
	std::stringstream ss;
	ss << this->tipoDeEvento << SEPARADOR_CAMPOS << this->id;
	return ss.str();
}

const std::string& EventoConejoPerdioVida::tipoEvento(){
	return this->tipoDeEvento;
}

int EventoConejoPerdioVida::obtenerId(){
	return this->id;
}
