#ifndef NOTIFICADOREVENTOSFUNCTOR_H_
#define NOTIFICADOREVENTOSFUNCTOR_H_

#include "Observador.h"

class NotificadorEventosFunctor {
	const std::vector<std::string>& eventos;
public:
	NotificadorEventosFunctor(const std::vector<std::string>& eventos): eventos(eventos){}
	void operator()(Observador* observador);
};

#endif /* NOTIFICADOREVENTOSFUNCTOR_H_ */
