#include "GeneradorTortugasFunctor.h"
#include "../../Common/src/EventoNuevoPersonaje.h"
#include "../../Common/src/constantes.h"
#include "../../Common/src/ElementoGraficable.h"

void GeneradorTortugasFunctor::operator()(GeneradorTortugaModelo* generador){
	if(generador->chequearGeneracion()){
		int idElemento = this->partida.obtenerModelo().agregarElementoGraficable(generador->generarTortuga());
		int direccion = 0;
		ElementoGraficable* elemento = this->partida.obtenerModelo().obtenerElemento(idElemento);
		int posX = elemento->obtenerVerticeSuperiorIzqX();
		int posY = elemento->obtenerVerticeSuperiorIzqY();
		Evento* evento = new EventoNuevoPersonaje(elemento->obtenerTipoElemento(), idElemento, posX, posY, direccion);
		this->partida.notificar(evento);
		delete evento;
	}
}
