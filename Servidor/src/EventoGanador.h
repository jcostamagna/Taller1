#ifndef EVENTOGANADOR_H_
#define EVENTOGANADOR_H_

#include "../../Common/src/Evento.h"

class EventoGanador: public Evento {
private:
	int id, score;
public:
	EventoGanador(int id, int score): Evento(EVENTO_GANADOR), id(id), score(score){}

	//Devuelve el evento como string: WIN|id|score
	const std::string eventoAsString() const;


	~EventoGanador(){}
};

#endif /* EVENTOGANADOR_H_ */
