#include "Observable.h"
#include "NotificadorFunctor.h"
#include "NotificadorEventosFunctor.h"
#include "NotificadorEventoFunctor.h"

#include <algorithm>

void Observable::agregarObservador(Observador* observador){
	observadores.push_back(observador);
}

void Observable::eliminarObservador(const Observador* jugador){
	std::vector<Observador*>::iterator it;
	std::vector<Observador*>::iterator jugadorAEliminar;
	it = this->observadores.begin();
	bool encontrado = false;
	while(!encontrado && it != this->observadores.end())
	{
		if((*it) == jugador)
		{
			encontrado = true;
			jugadorAEliminar = it;
		}
		++it;
	}
	if(encontrado)
	{
		this->observadores.erase(jugadorAEliminar);
	}
}

const std::vector<Observador*>& Observable::obtenerObservadores()
{
	return this->observadores;
}

void Observable::notificar(const std::string& evento){
	NotificadorFunctor notificador(evento);
	std::for_each(this->observadores.begin(), this->observadores.end(), notificador);
}

void Observable::notificar(const std::vector<std::string>& eventos){
	NotificadorEventosFunctor notificador(eventos);
	std::for_each(this->observadores.begin(), this->observadores.end(), notificador);
}

void Observable::notificar(const Evento* evento){
	NotificadorEventoFunctor notificador(evento);
	std::for_each(this->observadores.begin(), this->observadores.end(), notificador);
}


