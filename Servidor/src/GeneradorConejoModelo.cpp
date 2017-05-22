/*
 * GeneradorConejoModelo.cpp
 *
 *  Created on: 24/11/2015
 *      Author: matiaskamien
 */
#include "GeneradorConejoModelo.h"

GeneradorConejoModelo::GeneradorConejoModelo(const int verticeX, const int verticeY
		,const int idParaConejo)
{
	this->verticeX = verticeX;
	this->verticeY = verticeY;
	this->idParaConejo = idParaConejo;
	this->disponible = true;
}

const bool GeneradorConejoModelo::estaDisponible()
{
	return this->disponible;
}

void GeneradorConejoModelo::ponerNoDisponible()
{
	this->disponible = false;
}

void GeneradorConejoModelo::ponerComoDisponible()
{
	this->disponible = true;
}

const int GeneradorConejoModelo::obtenerVerticeX()
{
	return this->verticeX;
}

const int GeneradorConejoModelo::obtenerIdParaConejo()
{
	return this->idParaConejo;
}

const int GeneradorConejoModelo::obtenerVerticeY()
{
	return this->verticeY;
}

GeneradorConejoModelo::~GeneradorConejoModelo() {}

