/*
 * GeneradorTortugaVerdeModelo.cpp
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#include "GeneradorTortugaVerdeModelo.h"

GeneradorTortugaVerdeModelo::GeneradorTortugaVerdeModelo(const int verticeX,const int verticeY,
		const int frecuencia,const int cantidadMaxima):GeneradorTortugaModelo(verticeX,
				verticeY,frecuencia,cantidadMaxima){}

GeneradorTortugaVerdeModelo::~GeneradorTortugaVerdeModelo() {}

Tortuga* GeneradorTortugaVerdeModelo::generarTortuga()
{
	Tortuga* tortugaACrear = new TortugaVerde();
	tortugaACrear->setearVerticeSuperiorIzqX(this->verticeX);
	tortugaACrear->setearVerticeSuperiorIzqY(this->verticeY);
	--this->cantidadMaxima;
	return tortugaACrear;
}
