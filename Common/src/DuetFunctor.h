#ifndef CHEQUEADORCOLISIONESFUNCTOR_H_
#define CHEQUEADORCOLISIONESFUNCTOR_H_

#include "ElementoGraficable.h"
#include <vector>

class DuetFunctor {
private:
	const std::vector<ElementoGraficable*>& elementos;
	std::vector<Evento*>& eventos;
public:
	DuetFunctor(const std::vector<ElementoGraficable*>& elementos, std::vector<Evento*>& eventos): elementos(elementos), eventos(eventos){}
	void operator()(ElementoGraficable* elemento);
};

#endif /* CHEQUEADORCOLISIONESFUNCTOR_H_ */
