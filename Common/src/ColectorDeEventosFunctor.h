#ifndef COLECTORDEEVENTOSFUNCTOR_H_
#define COLECTORDEEVENTOSFUNCTOR_H_

#include <map>
#include <vector>
#include "Evento.h"
#include "ElementoGraficable.h"

class ColectorDeEventosFunctor {
private:
	std::map<int,int>& matcheo;
	std::vector<Evento*>& eventos;
public:
	ColectorDeEventosFunctor(std::vector<Evento*>& eventos, std::map<int,int>& matcheo): matcheo(matcheo), eventos(eventos){}
	void operator()(ElementoGraficable* elemento);
};

#endif /* COLECTORDEEVENTOSFUNCTOR_H_ */
