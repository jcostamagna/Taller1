/*
 * GeneradorTortugaRojaModelo.h
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_GENERADORTORTUGAROJAMODELO_H_
#define COMMON_SRC_GENERADORTORTUGAROJAMODELO_H_
#include "GeneradorTortugaModelo.h"
#include <iostream>

class GeneradorTortugaRojaModelo : public GeneradorTortugaModelo{
public:
	GeneradorTortugaRojaModelo(const int verticeX,const int verticeY,const int frecuencia
			,const int cantidadMaxima);
	~GeneradorTortugaRojaModelo();
	Tortuga* generarTortuga();

};

#endif /* COMMON_SRC_GENERADORTORTUGAROJAMODELO_H_ */
