#include "Evento.h"

Evento::Evento(const std::string& tipoDeEvento): tipoDeEvento(tipoDeEvento){}

const std::string& Evento::tipoEvento(){
	return this->tipoDeEvento;
}
