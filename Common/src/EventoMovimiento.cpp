#include "EventoMovimiento.h"
#include <sstream>

const std::string EventoMovimiento::eventoAsString() const{
	std::stringstream ss;
	ss << this->tipoDeEvento << SEPARADOR_CAMPOS << id << SEPARADOR_CAMPOS <<
				this->posX<<SEPARADOR_CAMPOS<<this->posY;
	return ss.str();
}

const std::string& EventoMovimiento::tipoEvento(){
	return this->tipoDeEvento;
}
