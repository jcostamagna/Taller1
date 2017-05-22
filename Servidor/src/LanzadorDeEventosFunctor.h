#ifndef LANZADORDEEVENTOSFUNCTOR_H_
#define LANZADORDEEVENTOSFUNCTOR_H_

#include "server_Partida.h"
#include <map>
#include <string>


class LanzadorDeEventosFunctor {
private:
	typedef void (LanzadorDeEventosFunctor::*Funciones)(Evento* evento);
	Partida& partida;
	std::map<std::string, Funciones> tipoDeEventos;
	void finDeNivel(Evento* evento);
	void destruirElemento(Evento* evento);
	void nuevoElemento(Evento* evento);
	void limpiarConejos(Evento* evento);
public:
	LanzadorDeEventosFunctor(Partida& partida);
	void operator()(Evento* evento);
};

#endif /* LANZADORDEEVENTOSFUNCTOR_H_ */
