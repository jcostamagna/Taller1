/*
 * GeneradorTortugaRojaModelo.cpp
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#include "GeneradorTortugaRojaModelo.h"

	GeneradorTortugaRojaModelo::GeneradorTortugaRojaModelo(const int verticeX,const int verticeY,
			const int frecuencia,const int cantidadMaxima):GeneradorTortugaModelo(verticeX,
					verticeY,frecuencia,cantidadMaxima){}


GeneradorTortugaRojaModelo::~GeneradorTortugaRojaModelo(){}


Tortuga* GeneradorTortugaRojaModelo::generarTortuga()
{
	Tortuga* tortugaACrear = new TortugaRoja();
	tortugaACrear->setearVerticeSuperiorIzqX(this->verticeX);
	tortugaACrear->setearVerticeSuperiorIzqY(this->verticeY);
	--this->cantidadMaxima;
	return tortugaACrear;
}
