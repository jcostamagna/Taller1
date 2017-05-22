#ifndef COMMON_SRC_EVENTOELEMENTODESTRUIDO_H_
#define COMMON_SRC_EVENTOELEMENTODESTRUIDO_H_

#include "Evento.h"

class EventoElementoDestruido: public Evento {
private:
	int id;
public:
	EventoElementoDestruido(int id): Evento(EVENTO_DESTRUIR_PERSONAJE), id(id){}

	//Devuelve el evento como string: DEL|id
	const std::string eventoAsString() const;

	const std::string& tipoEvento();

	const int obenerId();

	virtual ~EventoElementoDestruido(){}
};

#endif /* COMMON_SRC_EVENTOELEMENTODESTRUIDO_H_ */
