/*
 * GeneradorTortugaModelo.cpp
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#include "GeneradorTortugaModelo.h"
const int defaultFrecuencia = 10;
GeneradorTortugaModelo::GeneradorTortugaModelo(const int verticeX,const int verticeY,
		const int frecuencia,const int cantidadMaxima)
{
	this->verticeX=verticeX;
	this->verticeY=verticeY;
	if(frecuencia<=0)
	{
		this->frecuenciaGeneracion = defaultFrecuencia*1000;
	}else{
		this->frecuenciaGeneracion=frecuencia*1000;//Conversion
	}
	//se le resta 1 porque al crear un generador, ya genera la primer tortuga
	this->cantidadMaxima=cantidadMaxima-1;
	this->contador = 1;
}

bool GeneradorTortugaModelo::chequearGeneracion(){
	++this->contador;
	return ((this->contador%this->frecuenciaGeneracion) == 0);
}
