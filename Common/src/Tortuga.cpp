/*
 * Tortuga.cpp
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */
#include "Tortuga.h"
#include "Bala.h"
#include "Conejo.h"
#include "ObstaculoIrrompibleGraficable.h"
#include "ObstaculoRompibleGraficable.h"
#include "FinDeNivelGraficable.h"
#include <iostream>
const int direccionInversa = -1;
const int anchoYAltoTortugaColision = 60;
const int deltaVerticeXYColision = 20;

void Tortuga::mover()
{
	this->verticeSuperiorIzqXAnterior = this->verticeSuperiorIzqX;
	this->verticeSuperiorIzqYAnterior = this->verticeSuperiorIzqY;
	this->verticeSuperiorIzqX += this->velocidad;
	this->verticeSuperiorIzqY += GRAVEDAD;
}

void Tortuga::resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector)
{
	elemento->colisionar(this,vector);
}

const int Tortuga::xSupIzq()
{
	return this->verticeSuperiorIzqX+deltaVerticeXYColision;
}

const int Tortuga::ySupIzq()
{
	return this->verticeSuperiorIzqY+deltaVerticeXYColision;
}

const int Tortuga::anchoDeColision()
{
	return anchoYAltoTortugaColision;
}

const int Tortuga::altoDeColision()
{
	return anchoYAltoTortugaColision;
}

void Tortuga::colisionar(Tortuga* tortuga,std::vector<Evento*>& vector)
{
	this->volverAPosicionAnteriorTortuga();
}

void Tortuga::colisionar(Conejo* conejo,std::vector<Evento*>& vector){}

void Tortuga::colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector)
{
	this->volverAPosicionAnteriorTortuga();
}

void Tortuga::colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector)
{
	this->volverAPosicionAnteriorTortuga();
}

void Tortuga::volverAPosicionAnteriorTortuga()
{
	//Si entra al if, la colisión es en el eje horizontal.
	if(this->verticeSuperiorIzqY == this->verticeSuperiorIzqYAnterior)
	{
		//this->verticeSuperiorIzqX = this->verticeSuperiorIzqXAnterior;
		this->velocidad *= direccionInversa;
	}else{
		this->verticeSuperiorIzqY = this->verticeSuperiorIzqYAnterior;
	}
}

void Tortuga::setearSiEstaCayendo(bool cayendo)
{
	this->estaCayendo = cayendo;
}

const bool Tortuga::obtenerSiEstaCayendo()
{
	return this->estaCayendo;
}

void Tortuga::colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector){}

void Tortuga::colisionar(Bala* bala,std::vector<Evento*>& vector)
{
	--cantidadDeVidas;
	if(cantidadDeVidas == 0)
	{
		vector.push_back(new EventoElementoDestruido(this->idElemento));
	}
}
