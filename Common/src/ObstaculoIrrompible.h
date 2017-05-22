/*
 * ObstaculoIrrompible.h
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef COMMON_SRC_OBSTACULOIRROMPIBLE_H_
#define COMMON_SRC_OBSTACULOIRROMPIBLE_H_
#include "Obstaculo.h"

class ObstaculoIrrompible:public Obstaculo {
public:
	ObstaculoIrrompible();
	void persistir(TiXmlElement* element);
	void hidratar(TiXmlElement* element);
	Elemento* obtenerCopia();
	virtual ~ObstaculoIrrompible(){}

};

#endif /* COMMON_SRC_OBSTACULOIRROMPIBLE_H_ */
