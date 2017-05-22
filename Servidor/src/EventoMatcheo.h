#ifndef EVENTOMATCHEO_H_
#define EVENTOMATCHEO_H_
#include "../../Common/src/constantes.h"
#include "../../Common/src/Evento.h"

class EventoMatcheo: public Evento {
private:
	int idCliente, idElemento;
public:
	EventoMatcheo(int idCliente, int idElemento): Evento(EVENTO_MATCHEO), idCliente(idCliente), idElemento(idElemento){}

	//Devuelve el evento como string: MAT|idCliente|idElemento
	const std::string eventoAsString() const;

};

#endif /* EVENTOMATCHEO_H_ */
