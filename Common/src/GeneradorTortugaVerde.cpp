/*
 * TortugaVerde.cpp
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#include "GeneradorTortugaVerde.h"

GeneradorTortugaVerde::GeneradorTortugaVerde()
{
	this->cantidadMaxima = 0;
	this->frecuenciaGeneracion = 0;
	this->tipoDeElemento = TORTUGAVERDE;
}

void GeneradorTortugaVerde::persistir(TiXmlElement* root){
	TiXmlElement * element = new TiXmlElement( TORTUGAVERDE );
	root->LinkEndChild( element );
	element->SetAttribute(ATRIBUTO_NOMBRE, this->claveImagenTransparente);
	element->SetAttribute(ATRIBUTO_PUNTO_X, this->verticeSupIzqX);
	element->SetAttribute(ATRIBUTO_PUNTO_Y, this->verticeSupIzqY);
	element->SetAttribute(ATRIBUTO_CANTIDAD_MAX, this->cantidadMaxima);
	element->SetAttribute(ATRIBUTO_FRECUENCIA_GENERACION, this->frecuenciaGeneracion);
}


void GeneradorTortugaVerde::hidratar(TiXmlElement* element){
	element->QueryStringAttribute(ATRIBUTO_NOMBRE, &this->claveImagenTransparente);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_X, &this->verticeSupIzqX);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_Y, &this->verticeSupIzqY);
	element->QueryIntAttribute(ATRIBUTO_CANTIDAD_MAX, &this->cantidadMaxima);
	element->QueryIntAttribute(ATRIBUTO_FRECUENCIA_GENERACION, &this->frecuenciaGeneracion);
}

GeneradorTortugaVerde* GeneradorTortugaVerde::obtenerCopia(){
	GeneradorTortugaVerde* elemento = new GeneradorTortugaVerde;
	elemento->setearClaveImagenTransparente(this->claveImagenTransparente);
	elemento->setearVerticeSupIzqAreaImagen(this->verticeSupIzqX, this->verticeSupIzqY);
	elemento->setCantidadMaxima(this->cantidadMaxima);
	elemento->setFrecuenciaGeneracion(frecuenciaGeneracion);
	return elemento;
}
