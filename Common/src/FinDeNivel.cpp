/*
 * FinDeNivel.cpp
 *
 *  Created on: 21/11/2015
 *      Author: nicolasdubiansky
 */

#include "FinDeNivel.h"

FinDeNivel::FinDeNivel()
{
	this->tipoDeElemento = FINDENIVEL;
}

void FinDeNivel::persistir(TiXmlElement* root){
	TiXmlElement * element = new TiXmlElement( FINDENIVEL );
	root->LinkEndChild( element );
	element->SetAttribute(ATRIBUTO_NOMBRE, this->claveImagenTransparente);
	element->SetAttribute(ATRIBUTO_PUNTO_X, this->verticeSupIzqX);
	element->SetAttribute(ATRIBUTO_PUNTO_Y, this->verticeSupIzqY);
}

void FinDeNivel::hidratar(TiXmlElement* element){
	element->QueryStringAttribute(ATRIBUTO_NOMBRE, &this->claveImagenTransparente);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_X, &this->verticeSupIzqX);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_Y, &this->verticeSupIzqY);
}

Elemento* FinDeNivel::obtenerCopia(){
	FinDeNivel* elemento = new FinDeNivel();
	elemento->setearClaveImagenTransparente(this->claveImagenTransparente);
	elemento->setearVerticeSupIzqAreaImagen(this->verticeSupIzqX, this->verticeSupIzqY);
	return elemento;
}

std::string FinDeNivel::obtenerInformacion()
{
	std::string informacion("");
	informacion += this->pasarIntAString(this->id) + CARACTER_VACIO + this->tipoDeElemento +
				   CARACTER_VACIO + this->pasarIntAString(this->verticeSupIzqX) + CARACTER_VACIO +
				   this->pasarIntAString(this->verticeSupIzqY);
	return informacion;
}

