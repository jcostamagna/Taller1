/*
 * editor_AreaImagen.h
 *
 *  Created on: 8/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef EDITOR_SRC_EDITOR_AREAIMAGEN_H_
#define EDITOR_SRC_EDITOR_AREAIMAGEN_H_
#include <iostream>
#include <vector>
#include <sstream>
#include "constantes.h"
#include "tinyxml.h"

//Representa la region rectangular que ocupa una imagen en una ventana
class Elemento {
protected:
	int verticeSupIzqX;
	int verticeSupIzqY;
	int id;
	std::string claveImagenTransparente;
	std::string tipoDeElemento;

	//Devuelve el entero pasado por parámetro en string.
	const std::string pasarIntAString(const int entero);
public:
	void setearVerticeSupIzqAreaImagen(int verticeSupIzqX,int verticeSupIzqY);
	void setearClaveImagenTransparente(const std::string& claveImagen);
	void setearId(int id);
	std::string obtenerClaveImagenTransparente()const;
	std::string obtenerTipoElemento()const;
	int obtenerVerticeX()const;
	int obtenerVerticeY()const;
	int obtenerId()const;

	//Persiste el elemento en XML.
	virtual void persistir(TiXmlElement* element);

	//Carga el elemento desde el XML.
	virtual void hidratar(TiXmlElement* element) = 0;
	virtual Elemento* obtenerCopia() = 0;

	//Devuelve la información del elemento  en un string.
	virtual std::string obtenerInformacion() = 0;
	virtual~Elemento();
};

#endif /* EDITOR_SRC_EDITOR_AREAIMAGEN_H_ */
