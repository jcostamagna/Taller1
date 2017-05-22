/*
 * TortugaRoja.cpp
 *
 *  Created on: 14/11/2015
 *      Author: nicolasdubiansky
 */

#include "GeneradorTortugaRoja.h"

GeneradorTortugaRoja::GeneradorTortugaRoja()
{
	this->cantidadMaxima = 0;
	this->frecuenciaGeneracion = 0;
	this->tipoDeElemento = TORTUGAROJA;
}

void GeneradorTortugaRoja::persistir(TiXmlElement* root){
	TiXmlElement * element = new TiXmlElement( TORTUGAROJA );
	root->LinkEndChild( element );
	element->SetAttribute(ATRIBUTO_NOMBRE, this->claveImagenTransparente);
	element->SetAttribute(ATRIBUTO_PUNTO_X, this->verticeSupIzqX);
	element->SetAttribute(ATRIBUTO_PUNTO_Y, this->verticeSupIzqY);
	element->SetAttribute(ATRIBUTO_CANTIDAD_MAX, this->cantidadMaxima);
	element->SetAttribute(ATRIBUTO_FRECUENCIA_GENERACION, this->frecuenciaGeneracion);
}

void GeneradorTortugaRoja::hidratar(TiXmlElement* element){
	element->QueryStringAttribute(ATRIBUTO_NOMBRE, &this->claveImagenTransparente);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_X, &this->verticeSupIzqX);
	element->QueryIntAttribute(ATRIBUTO_PUNTO_Y, &this->verticeSupIzqY);
	element->QueryIntAttribute(ATRIBUTO_CANTIDAD_MAX, &this->cantidadMaxima);
	element->QueryIntAttribute(ATRIBUTO_FRECUENCIA_GENERACION, &this->frecuenciaGeneracion);
}


GeneradorTortugaRoja* GeneradorTortugaRoja::obtenerCopia(){
	GeneradorTortugaRoja* elemento = new GeneradorTortugaRoja;
	elemento->setearClaveImagenTransparente(this->claveImagenTransparente);
	elemento->setearVerticeSupIzqAreaImagen(this->verticeSupIzqX, this->verticeSupIzqY);
	elemento->setCantidadMaxima(this->cantidadMaxima);
	elemento->setFrecuenciaGeneracion(frecuenciaGeneracion);
	return elemento;
}
