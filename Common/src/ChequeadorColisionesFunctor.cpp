#include "ChequeadorColisionesFunctor.h"
#include <iostream>

void ChequeadorColisionesFunctor::operator()(ElementoGraficable* elemento){
	if (elemento->obtenerId() == this->elemento->obtenerId()) return;
	if (this->elemento->validarColision(elemento))
	{
		this->elemento->resolverColision(elemento, eventos);
	}
}


