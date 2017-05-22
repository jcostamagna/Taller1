/*
 * TortugaVerde.cpp
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */
#include "TortugaVerde.h"
const int puntosPorMorirTortugaVerde = 50;
const int cantidadVidasTortugaVerde = 2;
const int velocidadInicialTortugaVerde = 10;

TortugaVerde::TortugaVerde()
{
	this->tipoElemento = TORTUGAVERDE;
	this->cantidadDeVidas = cantidadVidasTortugaVerde;
	this->velocidad = velocidadInicialTortugaVerde;
}

std::string TortugaVerde::obtenerClaveImagen()
{
	return (this->tipoElemento + GUIONBAJO +
			this->obtenerDireccionDeUnMovimiento());
}

const int TortugaVerde::obtenerPuntosPorMorir()
{
	return puntosPorMorirTortugaVerde;
}

TortugaVerde::~TortugaVerde()
{

}

