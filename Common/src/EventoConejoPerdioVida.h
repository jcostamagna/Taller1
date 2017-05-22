/*
 * EventoConejoPerdioVida.h
 *
 *  Created on: 29/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_EVENTOCONEJOPERDIOVIDA_H_
#define COMMON_SRC_EVENTOCONEJOPERDIOVIDA_H_
#include "Evento.h"
#include <sstream>

class EventoConejoPerdioVida:public Evento {
private:
	int id;
public:
	EventoConejoPerdioVida(const int id);

	//Devuelve el evento como string: ECPV|id
	const std::string eventoAsString() const;

	const std::string& tipoEvento();

	int obtenerId();

	virtual ~EventoConejoPerdioVida(){}
};

#endif /* COMMON_SRC_EVENTOCONEJOPERDIOVIDA_H_ */
