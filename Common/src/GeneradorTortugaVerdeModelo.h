/*
 * GeneradorTortugaVerdeModelo.h
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_GENERADORTORTUGAVERDEMODELO_H_
#define COMMON_SRC_GENERADORTORTUGAVERDEMODELO_H_
#include "GeneradorTortugaModelo.h"
#include <iostream>

class GeneradorTortugaVerdeModelo : public GeneradorTortugaModelo {
public:
	GeneradorTortugaVerdeModelo(const int verticeX,const int verticeY,const int frecuencia
			,const int cantidadMaxima);
	~GeneradorTortugaVerdeModelo();
	Tortuga* generarTortuga();

};

#endif /* COMMON_SRC_GENERADORTORTUGAVERDEMODELO_H_ */
