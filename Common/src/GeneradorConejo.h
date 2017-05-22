/*
 * Conejo.h
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef COMMON_SRC_GENERADORCONEJO_H_
#define COMMON_SRC_GENERADORCONEJO_H_
#include "Elemento.h"

class GeneradorConejo: public Elemento{
private:
	std::string color;
	bool disponible;
public:
	GeneradorConejo();
	void persistir(TiXmlElement* element);
	GeneradorConejo* obtenerCopia();
	void hidratar(TiXmlElement* element);
	const bool estaDisponible();
	void ponerNoDisponible();
	void ponerComoDisponible();
	void setearColor(const std::string &color);
	const std::string& obtenerColor();
	std::string obtenerInformacion();
	virtual ~GeneradorConejo(){}

};
#endif /* COMMON_SRC_CONEJO_H_ */

