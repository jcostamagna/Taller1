#include "EventoNuevoPersonaje.h"
#include <sstream>

EventoNuevoPersonaje::EventoNuevoPersonaje(const std::string& tipoElemento, int id, int posX,
					int posY, int direccion) : Evento(EVENTO_NUEVO_PERSONAJE),
					tipoDeElemento(tipoElemento), id(id), posX(posX), posY(posY),
					direccion(direccion){}

const std::string EventoNuevoPersonaje::eventoAsString() const{
	std::stringstream ss;
	ss << this->tipoDeEvento<<SEPARADOR_CAMPOS<<tipoDeElemento<<SEPARADOR_CAMPOS<<id<<SEPARADOR_CAMPOS<<this->posX<<SEPARADOR_CAMPOS<<this->posY;
	return ss.str();
}

int EventoNuevoPersonaje::obtenerId(){
	return this->id;
}

int EventoNuevoPersonaje::obtenerPosX(){
	return this->posX;
}

int EventoNuevoPersonaje::obtenerPosY(){
	return this->posY;
}

int EventoNuevoPersonaje::obtenerDireccion(){
	return this->direccion;
}

std::string& EventoNuevoPersonaje::obtenerTipoDeElemento(){
	return this->tipoDeElemento;
}
