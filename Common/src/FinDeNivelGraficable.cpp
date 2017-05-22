/*
 * FinDeNivelGraficable.cpp
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */
#include "FinDeNivelGraficable.h"
#include "Bala.h"
#include "Conejo.h"
#include "ObstaculoIrrompibleGraficable.h"
#include "ObstaculoRompibleGraficable.h"
#include "Tortuga.h"
#include <iostream>
const int deltaVerticeXColision = 3;
const int deltaVerticeYColision = 5;
const int anchoRectanguloColision = 55;
const int altoRectanguloColision = 45;

FinDeNivelGraficable::FinDeNivelGraficable()
{
	this->tipoElemento = FINDENIVEL;
}

const bool FinDeNivelGraficable::obtenerSiEstaCayendo()
{
	return false;
}

const int FinDeNivelGraficable::xSupIzq()
{
	return this->verticeSuperiorIzqX+deltaVerticeXColision;
}

const int FinDeNivelGraficable::ySupIzq()
{
	return this->verticeSuperiorIzqY+deltaVerticeYColision;
}

const int FinDeNivelGraficable::anchoDeColision()
{
	return anchoRectanguloColision;
}

const int FinDeNivelGraficable::altoDeColision()
{
	return altoRectanguloColision;
}

std::string FinDeNivelGraficable::obtenerClaveImagen()
{
	return (this->tipoElemento);
}

void FinDeNivelGraficable::mover(){}

void FinDeNivelGraficable::resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector)
{
	elemento->colisionar(this,vector);
}

void FinDeNivelGraficable::colisionar(Tortuga* tortuga,std::vector<Evento*>& vector){}

void FinDeNivelGraficable::colisionar(Conejo* conejo,std::vector<Evento*>& vector){}

void FinDeNivelGraficable::colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector){}

void FinDeNivelGraficable::colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector){}

void FinDeNivelGraficable::colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector){}

void FinDeNivelGraficable::colisionar(Bala* bala,std::vector<Evento*>& vector){}

const std::string FinDeNivelGraficable::obtenerRutaImagen()
{
	std::string ruta(RUTA_SERVER_EDITOR_IMAGENES SEPARADOR_DIRECTORIOS NOMBRE_IMAGEN_FIN_DE_NIVEL);
	return ruta;
}

FinDeNivelGraficable::~FinDeNivelGraficable() {}
