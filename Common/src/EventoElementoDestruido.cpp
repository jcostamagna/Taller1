#include "EventoElementoDestruido.h"
#include "constantes.h"
#include <sstream>


const std::string EventoElementoDestruido::eventoAsString() const{
	std::stringstream ss;
	ss << this->tipoDeEvento<<SEPARADOR_CAMPOS<<id;
	return ss.str();
}

const std::string& EventoElementoDestruido::tipoEvento(){
	return this->tipoDeEvento;
}

const int EventoElementoDestruido::obenerId(){
	return this->id;
}
