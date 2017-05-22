/*
 * TortugaRoja.cpp
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */
#include "TortugaRoja.h"
const int puntosPorMorirTortugaRoja = 50;
const int velocidadTortugaRoja = 15;
const int cantidadDeVidasTortugaRoja = 1;

TortugaRoja::TortugaRoja()
{
	this->tipoElemento = TORTUGAROJA;
	this->cantidadDeVidas = cantidadDeVidasTortugaRoja;
	this->velocidad = velocidadTortugaRoja;
}

std::string TortugaRoja::obtenerClaveImagen()
{
	return (this->tipoElemento + GUIONBAJO +
			this->obtenerDireccionDeUnMovimiento());
}

const int TortugaRoja::obtenerPuntosPorMorir()
{
	return puntosPorMorirTortugaRoja;
}

TortugaRoja::~TortugaRoja(){}
