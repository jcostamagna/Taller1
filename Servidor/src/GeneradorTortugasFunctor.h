#ifndef GENERADORTORTUGASFUNCTOR_H_
#define GENERADORTORTUGASFUNCTOR_H_
#include "server_Partida.h"
#include "../../Common/src/GeneradorTortugaModelo.h"

class GeneradorTortugasFunctor {
private:
	Partida& partida;
public:
	GeneradorTortugasFunctor(Partida& partida): partida(partida){}
	void operator()(GeneradorTortugaModelo* generador);
};

#endif /* GENERADORTORTUGASFUNCTOR_H_ */
