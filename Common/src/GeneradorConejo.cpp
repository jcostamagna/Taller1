/*
 * Conejo.cpp
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#include "GeneradorConejo.h"

GeneradorConejo::GeneradorConejo()
{
	this->tipoDeElemento = CONEJO;
	this->disponible = true;
}

void GeneradorConejo::persistir(TiXmlElement* root){
	TiXmlElement * element = new TiXmlElement( CONEJO );
	root->LinkEndChild( element );
	element->SetAttribute(ATRIBUTO_NOMBRE, this->claveImagenTransparente);
	element->SetAttribute(ATRIBUTO_PUNTO_X, this->verticeSupIzqX);
	element->SetAttribute(ATRIBUTO_PUNTO_Y, this->verticeSupIzqY);
}

void GeneradorConejo::ponerNoDisponible()
{
	this->disponible = false;
}

void GeneradorConejo::ponerComoDisponible()
{
	this->disponible = true;
}

const bool GeneradorConejo::estaDisponible()
{
	return this->disponible;
}

void GeneradorConejo::setearColor(const std::string &color)
{
	this->color = color;
}

const std::string& GeneradorConejo::obtenerColor()
{
	return this->color;
}

std::string GeneradorConejo::obtenerInformacion()
{
	std::string informacion("");
	informacion += this->pasarIntAString(this->id) + CARACTER_VACIO + this->tipoDeElemento +
				   CARACTER_VACIO + this->pasarIntAString(this->verticeSupIzqX) + CARACTER_VACIO +
				   this->pasarIntAString(this->verticeSupIzqY);
	return informacion;
}

GeneradorConejo* GeneradorConejo::obtenerCopia(){
	GeneradorConejo* elemento = new GeneradorConejo;
	elemento->setearClaveImagenTransparente(this->claveImagenTransparente);
	elemento->setearVerticeSupIzqAreaImagen(this->verticeSupIzqX, this->verticeSupIzqY);
	return elemento;
}

void GeneradorConejo::hidratar(TiXmlElement* element){
	element->QueryStringAttribute(ATRIBUTO_NOMBRE, &this->claveImagenTransparente);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_X, &this->verticeSupIzqX);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_Y, &this->verticeSupIzqY);
}
