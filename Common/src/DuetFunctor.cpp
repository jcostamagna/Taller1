#include "DuetFunctor.h"
#include "ChequeadorColisionesFunctor.h"
#include <algorithm>

void DuetFunctor::operator()(ElementoGraficable* elemento){
	ChequeadorColisionesFunctor colisiones(elemento, eventos);
	std::for_each(this->elementos.begin(), this->elementos.end(), colisiones);
}
