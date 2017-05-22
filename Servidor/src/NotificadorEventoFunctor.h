#ifndef NOTIFICADOREVENTOFUNCTOR_H_
#define NOTIFICADOREVENTOFUNCTOR_H_

#include "../../Common/src/Evento.h"
#include "Observador.h"

class NotificadorEventoFunctor {
	const Evento* evento;
public:
	NotificadorEventoFunctor(const Evento* evento): evento(evento){}
	void operator()(Observador* observador);
};

#endif /* NOTIFICADOREVENTOFUNCTOR_H_ */
