/*
 * GeneradorTortugaModelo.h
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_GENERADORTORTUGAMODELO_H_
#define COMMON_SRC_GENERADORTORTUGAMODELO_H_
#include "TortugaRoja.h"
#include "TortugaVerde.h"
class GeneradorTortugaModelo {
protected:
	int cantidadMaxima;
	int frecuenciaGeneracion;
	int verticeX;
	int verticeY;
	int contador;
public:
	virtual Tortuga* generarTortuga()=0;
	GeneradorTortugaModelo(const int verticeX,const int verticeY,
			const int frecuencia,const int cantidadMaxima);
	bool chequearGeneracion();
	virtual ~GeneradorTortugaModelo(){};
};

#endif /* COMMON_SRC_GENERADORTORTUGAMODELO_H_ */
