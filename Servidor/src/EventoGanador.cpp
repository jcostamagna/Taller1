#include "EventoGanador.h"
#include <sstream>

const std::string EventoGanador::eventoAsString() const{
	std::stringstream ss;
	ss << this->tipoDeEvento<<SEPARADOR_CAMPOS<<id<<SEPARADOR_CAMPOS<<this->score;
	return ss.str();
}


