#ifndef COLECTOREVENTOSPARTICULARES_H_
#define COLECTOREVENTOSPARTICULARES_H_

#include <vector>
#include "Evento.h"
#include "ElementoGraficable.h"

class ColectorEventosParticulares {
private:
	std::vector<Evento*>& eventos;
public:
	ColectorEventosParticulares(std::vector<Evento*>& eventos): eventos(eventos){}
	void operator()(ElementoGraficable* elemento);
};

#endif /* COLECTOREVENTOSPARTICULARES_H_ */
