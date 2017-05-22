/*
 * EventoFinDeNivel.h
 *
 *  Created on: 29/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_EVENTOFINDENIVEL_H_
#define COMMON_SRC_EVENTOFINDENIVEL_H_
#include "Evento.h"
#include <sstream>

class EventoFinDeNivel : public Evento{
private:
	int id;
public:
	EventoFinDeNivel(int id);

	//Devuelve el evento como string: FDN|id
	const std::string eventoAsString() const;

	const std::string& tipoEvento();

	virtual ~EventoFinDeNivel(){}
};

#endif /* COMMON_SRC_EVENTOFINDENIVEL_H_ */
