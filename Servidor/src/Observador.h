#ifndef OBSERVADOR_H_
#define OBSERVADOR_H_
#include <string>
#include <vector>
#include "../../Common/src/Evento.h"

class Observador {
private:
	bool yaFueMatcheado;
public:
	//Setea el atributo booleano en false.
	Observador();

	//Devuelve si ya fue matcheado con un conejo o no.
	const bool fueMatcheado();

	//Pone en true al booleano que tiene como atributo.
	void asignarMatcheo();

	//Pone en false al booleano que tiene como atributo.
	void desasignarMatcheo();

	virtual void actualizar(const std::string& evento) = 0;

	virtual void actualizar(const std::vector<std::string>& eventos) = 0;

	virtual void actualizar(const Evento* evento) = 0;

	virtual ~Observador(){}
};

#endif /* OBSERVADOR_H_ */
