/*
 * server_XMLHandler.h
 *
 *  Created on: 29/10/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_COMMON_XMLHANDLER_H_
#define COMMON_COMMON_XMLHANDLER_H_

#include <string>
#include <vector>
#include <map>
#include "Nivel.h"
#include "GeneradorConejo.h"
#include "FinDeNivel.h"
#include "ObstaculoIrrompible.h"
#include "ObstaculoRompible.h"
#include "GeneradorTortugaRoja.h"
#include "GeneradorTortugaVerde.h"
#include "Elemento.h"

//Esta clase se encarga de leer el XLM y pasar a objetos la información.
class XMLHandler{
private:
	typedef void (XMLHandler::*Funciones)(Nivel&,TiXmlElement*);
	std::map<std::string,Funciones> elementosNivel;
	XMLHandler (const XMLHandler& object);
	XMLHandler& operator=(const XMLHandler& object);
	void agregarGeneradorConejo(Nivel& nivel,TiXmlElement* elemento);
	void agregarObstaculoRompible(Nivel& nivel,TiXmlElement* elemento);
	void agregarObstaculoIrrompible(Nivel& nivel,TiXmlElement* elemento);
	void agregarGeneradorTortugaRoja(Nivel& nivel,TiXmlElement* elemento);
	void agregarGeneradorTortugaVerde(Nivel& nivel,TiXmlElement* elemento);
	void agregarFinDeNivel(Nivel& nivel,TiXmlElement* elemento);

public:
	XMLHandler();
	Nivel levantarNivel(const std::string& rutaNivel);
	void guardarNivel(const Nivel& nivel);

};

#endif /* COMMON_COMMON_XMLHANDLER_H_ */
