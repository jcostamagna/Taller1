#include "MoverElementoFunctor.h"
#include "Conejo.h"

void MoverElementoFunctor::operator()(ElementoGraficable* elemento){
	if (elemento->obtenerId() == this->elementoAMover){
		Conejo* conejo = (Conejo*) elemento;
		conejo->procesarEvento(evento);
	}
}

