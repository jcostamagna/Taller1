#include "ColectorDeEventosFunctor.h"
#include "EventoMovimiento.h"
#include <iostream>

void ColectorDeEventosFunctor::operator()(ElementoGraficable* elemento){
	if (elemento->seMovio()){
		this->eventos.push_back(new EventoMovimiento(elemento->obtenerId(), elemento->obtenerVerticeSuperiorIzqX(), elemento->obtenerVerticeSuperiorIzqY()));
	}
}
