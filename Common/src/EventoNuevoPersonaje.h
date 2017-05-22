#ifndef EVENTONUEVOPERSONAJE_H_
#define EVENTONUEVOPERSONAJE_H_

#include "Evento.h"

class EventoNuevoPersonaje: public Evento {
private:
	std::string tipoDeElemento;
	int id, posX, posY, direccion;
public:
	EventoNuevoPersonaje(const std::string& tipoElemento, int id, int posX, int posY, int direccion);

	//Devuelve el evento como string: NEW|tipoElemento|id|posX|posY
	const std::string eventoAsString() const;

	int obtenerId();
	int obtenerPosX();
	int obtenerPosY();
	int obtenerDireccion();
	std::string& obtenerTipoDeElemento();

	virtual ~EventoNuevoPersonaje(){}
};

#endif /* EVENTONUEVOPERSONAJE_H_ */
