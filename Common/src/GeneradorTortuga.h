/*
 * Tortuga.h
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */
#ifndef COMMON_SRC_GENERADORTORTUGA_H_
#define COMMON_SRC_GENERADORTORTUGA_H_
#include "Elemento.h"

class GeneradorTortuga:public Elemento {
protected:
	int frecuenciaGeneracion;
	int cantidadMaxima;
public:
	int obtenerFrecuenciaGeneracion();
	int obtenerCantidadMaxima();
	void setFrecuenciaGeneracion(int frecuenciaGeneracion);
	void setCantidadMaxima(int cantidadMaxima);
	virtual GeneradorTortuga* obtenerCopia()=0;
	std::string obtenerInformacion();
	virtual ~GeneradorTortuga(){}
};

#endif /* COMMON_SRC_TORTUGA_H_ */
