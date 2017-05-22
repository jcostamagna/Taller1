#ifndef NOTIFICADORFUNCTOR_H_
#define NOTIFICADORFUNCTOR_H_

#include <string>
#include "Observador.h"

class NotificadorFunctor {

private:
	const std::string& evento;
public:
	NotificadorFunctor(const std::string& evento): evento(evento){}
	void operator()(Observador* observador);
};

#endif /* NOTIFICADORFUNCTOR_H_ */
