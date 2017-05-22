#ifndef COMMON_SRC_CHEQUEADORCOLISIONESFUNCTOR_H_
#define COMMON_SRC_CHEQUEADORCOLISIONESFUNCTOR_H_

#include "ElementoGraficable.h"
#include <vector>
#include "Evento.h"

class ChequeadorColisionesFunctor {
private:
	ElementoGraficable* elemento;
	std::vector<Evento*>& eventos;
public:
	ChequeadorColisionesFunctor(ElementoGraficable* elemento, std::vector<Evento*>& eventos): elemento(elemento), eventos(eventos){}
	void operator()(ElementoGraficable* elemento);
};

#endif /* COMMON_SRC_CHEQUEADORCOLISIONESFUNCTOR_H_ */
