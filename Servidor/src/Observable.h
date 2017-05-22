#ifndef SUJETO_H_
#define SUJETO_H_

#include "Observador.h"
#include "../../Common/src/Evento.h"
#include <vector>
#include <string>

class Observable {
public:
	std::vector<Observador*> observadores;

	const std::vector<Observador*>& obtenerObservadores();

	//Agrega un observador al vector.
	virtual void agregarObservador(Observador* observador);

	//Elimina un observador del vector.
	virtual void eliminarObservador(const Observador* observador);

	virtual void notificar(const std::string& evento);

	virtual void notificar(const std::vector<std::string>& evento);

	virtual void notificar(const Evento* evento);

	virtual ~Observable(){}

};

#endif /* SUJETO_H_ */
