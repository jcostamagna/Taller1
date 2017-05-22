#ifndef EVENTOMOVIMIENTO_H_
#define EVENTOMOVIMIENTO_H_

#include "Evento.h"


class EventoMovimiento: public Evento {
private:
	int id, posX, posY;
public:
	EventoMovimiento(int id, int posX, int posY): Evento(EVENTO_MOVIMIENTO), id(id), posX(posX), posY(posY){}

	//Devuelve el evento como string: MOVE|id|posX|posY
	const std::string eventoAsString() const;

	const std::string& tipoEvento();

	virtual ~EventoMovimiento(){}
};

#endif /* EVENTOMOVIMIENTO_H_ */
