/*
 * Bala.cpp
 *
 *  Created on: 29/11/2015
 *      Author: matiaskamien
 */
#include "Bala.h"
#include "Conejo.h"
#include "ObstaculoIrrompibleGraficable.h"
#include "ObstaculoRompibleGraficable.h"
#include "Tortuga.h"
#include "FinDeNivelGraficable.h"
const int anchoBalaColision = 15;
const int altoBalaColision = 9;
const int deltaVerticeXColision = 3;
const int deltaVerticeYColision = 6;
const int puntosPorRomperObstaculoRompible = 25;

void Bala::setearConejoQueLaDisparo(Conejo* conejo)
{
	this->conejoQueDisparo = conejo;
}

Bala::Bala()
{
	this->tipoElemento = BALA;
	this->direccion = 0;
	this->conejoQueDisparo = NULL;
}

const bool Bala::obtenerSiEstaCayendo()
{
	return false;
}

const int Bala::xSupIzq()
{
	return this->verticeSuperiorIzqX+deltaVerticeXColision;
}

const int Bala::ySupIzq()
{
	return this->verticeSuperiorIzqY+deltaVerticeYColision;
}

const int Bala::anchoDeColision()
{
	return anchoBalaColision;
}

const int Bala::altoDeColision()
{
	return altoBalaColision;
}

void Bala::resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector)
{
	elemento->colisionar(this,vector);
}

void Bala::colisionar(Tortuga* tortuga,std::vector<Evento*>& vector)
{
	this->conejoQueDisparo->aumentarPuntaje(tortuga->obtenerPuntosPorMorir());
	vector.push_back(new EventoElementoDestruido(this->idElemento));
}

Conejo* Bala::obtenerConejoQueLaDisparo()
{
	return this->conejoQueDisparo;
}

void Bala::colisionar(Conejo* conejo,std::vector<Evento*>& vector){}

void Bala::colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector)
{
	this->conejoQueDisparo->aumentarPuntaje(puntosPorRomperObstaculoRompible);
	vector.push_back(new EventoElementoDestruido(this->idElemento));
	vector.push_back(new EventoElementoDestruido(obstaculoRompible->obtenerId()));
}

void Bala::colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector)
{
	vector.push_back(new EventoElementoDestruido(this->idElemento));
}

void Bala::colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector){}

void Bala::colisionar(Bala* bala,std::vector<Evento*>& vector){}

std::string Bala::obtenerClaveImagen()
{
	return this->tipoElemento;
}

void Bala::mover(){
	this->verticeSuperiorIzqX += this->direccion*VELOCIDAD_BALA;
}


void Bala::setearDireccion(int direccion){
	this->direccion = direccion;
}


Bala::~Bala() {}

