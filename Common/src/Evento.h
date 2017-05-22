#ifndef EVENTO_H_
#define EVENTO_H_

#include <string>
#include "constantes.h"

class Evento {
protected:
	std::string tipoDeEvento;
public:

	Evento(const std::string& tipoDeEvento);

	//Devuelve el evento como string: tipoDeElemento
	virtual const std::string eventoAsString() const=0;

	//Devuelve el tipo de evento
	const std::string& tipoEvento();

	virtual ~Evento(){}
};

#endif /* EVENTO_H_ */
