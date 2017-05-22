/*
 * TortugaVerde.h
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef COMMON_SRC_GENERADORTORTUGAVERDE_H_
#define COMMON_SRC_GENERADORTORTUGAVERDE_H_
#include "GeneradorTortuga.h"

class GeneradorTortugaVerde: public GeneradorTortuga {
public:
	GeneradorTortugaVerde();
	void persistir(TiXmlElement* element);
	void hidratar(TiXmlElement* element);
	GeneradorTortugaVerde* obtenerCopia();
	virtual ~GeneradorTortugaVerde(){}

};

#endif /* COMMON_SRC_TORTUGAVERDE_H_ */
