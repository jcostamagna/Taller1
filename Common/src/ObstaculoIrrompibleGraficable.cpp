/*
 * ObstaculoIrrompibleGraficable.cpp
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */
#include "ObstaculoIrrompibleGraficable.h"
#include "Bala.h"
#include "Conejo.h"
#include "ObstaculoRompibleGraficable.h"
#include "Tortuga.h"
#include "FinDeNivelGraficable.h"
#include <iostream>
const int anchoObstaculoIrrompible = 60;
const int altoObstaculoIrrompible = 55;

ObstaculoIrrompibleGraficable::ObstaculoIrrompibleGraficable()
{
	this->tipoElemento = OBSTACULO_IRROMP;
}

const int ObstaculoIrrompibleGraficable::xSupIzq()
{
	return this->verticeSuperiorIzqX;
}

const int ObstaculoIrrompibleGraficable::ySupIzq()
{
	return this->verticeSuperiorIzqY;
}

const int ObstaculoIrrompibleGraficable::anchoDeColision()
{
	return anchoObstaculoIrrompible;
}

const int ObstaculoIrrompibleGraficable::altoDeColision()
{
	return altoObstaculoIrrompible;
}

std::string ObstaculoIrrompibleGraficable::obtenerClaveImagen()
{
	return (this->tipoElemento);
}

const bool ObstaculoIrrompibleGraficable::obtenerSiEstaCayendo()
{
	return false;
}

void ObstaculoIrrompibleGraficable::mover(){}

void ObstaculoIrrompibleGraficable::resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector)
{
	elemento->colisionar(this,vector);
}

void ObstaculoIrrompibleGraficable::colisionar(Tortuga* tortuga,std::vector<Evento*>& vector){}

void ObstaculoIrrompibleGraficable::colisionar(Conejo* conejo,std::vector<Evento*>& vector){}

void ObstaculoIrrompibleGraficable::colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector){}

void ObstaculoIrrompibleGraficable::colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector){}

void ObstaculoIrrompibleGraficable::colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector){}

void ObstaculoIrrompibleGraficable::colisionar(Bala* bala,std::vector<Evento*>& vector){}

const std::string ObstaculoIrrompibleGraficable::obtenerRutaImagen()
{
	std::string ruta(RUTA_SERVER_EDITOR_IMAGENES SEPARADOR_DIRECTORIOS NOMBRE_IMAGEN_OBSTACULO_IRROMPIBLE);
	return ruta;
}


ObstaculoIrrompibleGraficable::~ObstaculoIrrompibleGraficable()
{

}

