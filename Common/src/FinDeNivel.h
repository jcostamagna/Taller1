/*
 * FinDeNivel.h
 *
 *  Created on: 21/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef COMMON_SRC_FINDENIVEL_H_
#define COMMON_SRC_FINDENIVEL_H_
#include "Elemento.h"

class FinDeNivel: public Elemento {
public:
	FinDeNivel();
	void persistir(TiXmlElement* element);
	Elemento* obtenerCopia();
	void hidratar(TiXmlElement* element);
	std::string obtenerInformacion();
	virtual ~FinDeNivel(){}
};

#endif /* COMMON_SRC_FINDENIVEL_H_ */
