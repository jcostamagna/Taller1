/*
 * ObstaculoRompibleGraficable.cpp
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */
#include "ObstaculoRompibleGraficable.h"
#include "Bala.h"
#include "Conejo.h"
#include "ObstaculoIrrompibleGraficable.h"
#include "Tortuga.h"
#include "FinDeNivelGraficable.h"
const int anchoObstaculoRompible = 60;
const int altoObstaculoRompible = 55;

ObstaculoRompibleGraficable::ObstaculoRompibleGraficable()
{
	this->tipoElemento = OBSTACULOROMP;
}

const bool ObstaculoRompibleGraficable::obtenerSiEstaCayendo()
{
	return false;
}

std::string ObstaculoRompibleGraficable::obtenerClaveImagen()
{
	return (this->tipoElemento);
}

void ObstaculoRompibleGraficable::mover()
{}

const int ObstaculoRompibleGraficable::xSupIzq()
{
	return this->verticeSuperiorIzqX;
}

const int ObstaculoRompibleGraficable::ySupIzq()
{
	return this->verticeSuperiorIzqY;
}

const int ObstaculoRompibleGraficable::anchoDeColision()
{
	return anchoObstaculoRompible;
}

const int ObstaculoRompibleGraficable::altoDeColision()
{
	return altoObstaculoRompible;
}

void ObstaculoRompibleGraficable::resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector)
{
	elemento->colisionar(this,vector);
}

void ObstaculoRompibleGraficable::colisionar(Tortuga* tortuga,std::vector<Evento*>& vector){}

void ObstaculoRompibleGraficable::colisionar(Conejo* conejo,std::vector<Evento*>& vector){}

void ObstaculoRompibleGraficable::colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector){}

void ObstaculoRompibleGraficable::colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector){}

void ObstaculoRompibleGraficable::colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector){}

void ObstaculoRompibleGraficable::colisionar(Bala* bala,std::vector<Evento*>& vector){}

const std::string ObstaculoRompibleGraficable::obtenerRutaImagen()
{
	std::string ruta(RUTA_SERVER_EDITOR_IMAGENES SEPARADOR_DIRECTORIOS NOMBRE_IMAGEN_OBSTACULO_ROMPIBLE);
	return ruta;
}
ObstaculoRompibleGraficable::~ObstaculoRompibleGraficable(){}
