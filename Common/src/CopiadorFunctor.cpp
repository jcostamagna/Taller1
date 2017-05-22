#include "CopiadorFunctor.h"

void CopiadorFunctor::operator()(Elemento* elemento){
	Elemento* elementoNuevo = elemento->obtenerCopia();
	nivel.agregarElemento(elementoNuevo);
}

void CopiadorFunctor::operator()(GeneradorTortuga* generadorTortuga){
	GeneradorTortuga* generador = generadorTortuga->obtenerCopia();
	nivel.agregarGenerador(generador);
}

void CopiadorFunctor::operator()(GeneradorConejo* generadorConejo){
	GeneradorConejo* generador = generadorConejo->obtenerCopia();
	nivel.agregarGenerador(generador);
}
