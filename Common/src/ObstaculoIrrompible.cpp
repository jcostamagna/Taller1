/*
 * ObstaculoIrrompible.cpp
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#include "ObstaculoIrrompible.h"

ObstaculoIrrompible::ObstaculoIrrompible()
{
	this->tipoDeElemento = OBSTACULO_IRROMP;
}

void ObstaculoIrrompible::persistir(TiXmlElement* root){
	TiXmlElement * element = new TiXmlElement( OBSTACULO_IRROMP );
	root->LinkEndChild( element );
	element->SetAttribute(ATRIBUTO_NOMBRE, this->claveImagenTransparente);
	element->SetAttribute(ATRIBUTO_PUNTO_X, this->verticeSupIzqX);
	element->SetAttribute(ATRIBUTO_PUNTO_Y, this->verticeSupIzqY);
}

void ObstaculoIrrompible::hidratar(TiXmlElement* element){
	element->QueryStringAttribute(ATRIBUTO_NOMBRE, &this->claveImagenTransparente);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_X, &this->verticeSupIzqX);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_Y, &this->verticeSupIzqY);
}

Elemento* ObstaculoIrrompible::obtenerCopia(){
	ObstaculoIrrompible* elemento = new ObstaculoIrrompible;
	elemento->setearClaveImagenTransparente(this->claveImagenTransparente);
	elemento->setearVerticeSupIzqAreaImagen(this->verticeSupIzqX, this->verticeSupIzqY);
	return elemento;
}
