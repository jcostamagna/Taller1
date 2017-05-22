#include "ColectorEventosParticulares.h"

void ColectorEventosParticulares::operator()(ElementoGraficable* elemento){
	elemento->eventoParticulares(eventos);
}


