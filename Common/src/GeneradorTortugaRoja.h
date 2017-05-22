/*
 * TortugaRoja.h
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef COMMON_GENERADORTORTUGAROJA_H_
#define COMMON_GENERADORTORTUGAROJA_H_
#include "GeneradorTortuga.h"

class GeneradorTortugaRoja: public GeneradorTortuga {
public:
	GeneradorTortugaRoja();
	void persistir(TiXmlElement* element);
	void hidratar(TiXmlElement* element);
	GeneradorTortugaRoja* obtenerCopia();
	virtual ~GeneradorTortugaRoja(){}
};

#endif /* COMMON_TORTUGAROJA_H_ */
