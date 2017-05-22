/*
 * EventoFinDeNivel.cpp
 *
 *  Created on: 29/11/2015
 *      Author: matiaskamien
 */

#include "EventoFinDeNivel.h"

EventoFinDeNivel::EventoFinDeNivel(int id) : Evento(EVENTO_FIN_DE_NIVEL), id(id){}

const std::string EventoFinDeNivel::eventoAsString() const
{
	std::stringstream ss;
	ss << this->tipoDeEvento << SEPARADOR_CAMPOS << this->id;
	return ss.str();
}
