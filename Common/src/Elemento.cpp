/*
 * editor_AreaImagen.cpp
 *
 *  Created on: 8/11/2015
 *      Author: nicolasdubiansky
 */
#include "Elemento.h"

void Elemento::setearVerticeSupIzqAreaImagen(int verticeSupIzqX,
			int verticeSupIzqY)
{
	this->verticeSupIzqX=verticeSupIzqX;
	this->verticeSupIzqY=verticeSupIzqY;
}

std::string Elemento::obtenerTipoElemento()const
{
	return this->tipoDeElemento;
}

void Elemento::setearId(int id){
	this->id = id;
}

const std::string Elemento::pasarIntAString(const int entero)
{
	std::stringstream ss;
	ss << entero;
	return (ss.str());
}

int Elemento::obtenerVerticeX()const
{
	return this->verticeSupIzqX;
}

int Elemento::obtenerVerticeY()const
{
	return this->verticeSupIzqY;
}

int Elemento::obtenerId()const{
	return id;
}

std::string Elemento::obtenerClaveImagenTransparente()const
{
	return this->claveImagenTransparente;
}
void Elemento::setearClaveImagenTransparente(const std::string& claveImagen)
{
	this->claveImagenTransparente=claveImagen;
}

void Elemento::persistir(TiXmlElement* root){
	TiXmlElement * element = new TiXmlElement( this->tipoDeElemento );
	root->LinkEndChild( element );
	element->SetAttribute(ATRIBUTO_NOMBRE, this->claveImagenTransparente);
	element->SetAttribute(ATRIBUTO_PUNTO_X, this->verticeSupIzqX);
	element->SetAttribute(ATRIBUTO_PUNTO_Y, this->verticeSupIzqY);
}

Elemento::~Elemento()
{}

