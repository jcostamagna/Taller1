#include "EventoMatcheo.h"
#include <sstream>

const std::string EventoMatcheo::eventoAsString() const{
	std::stringstream ss;
	ss << this->tipoDeEvento << SEPARADOR_CAMPOS << idCliente << SEPARADOR_CAMPOS <<
				this->idElemento;
	return ss.str();
}
