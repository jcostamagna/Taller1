/*
 * server_XMLHandler.cpp
 *
 *  Created on: 29/10/2015
 *      Author: matiaskamien
 */
#include "common_XMLHandler.h"
#include "constantes.h"
#include "tinyxml.h"
#include "Nivel.h"
#include "PersistidorFunctor.h"

typedef void (XMLHandler::*Funciones)(Nivel,TiXmlElement*);

XMLHandler::XMLHandler(){
	elementosNivel.insert(std::make_pair(CONEJO, &XMLHandler::agregarGeneradorConejo));
	elementosNivel.insert(std::make_pair(OBSTACULOROMP, &XMLHandler::agregarObstaculoRompible));
	elementosNivel.insert(std::make_pair(OBSTACULO_IRROMP, &XMLHandler::agregarObstaculoIrrompible));
	elementosNivel.insert(std::make_pair(TORTUGAROJA, &XMLHandler::agregarGeneradorTortugaRoja));
	elementosNivel.insert(std::make_pair(TORTUGAVERDE, &XMLHandler::agregarGeneradorTortugaVerde));
	elementosNivel.insert(std::make_pair(FINDENIVEL, &XMLHandler::agregarFinDeNivel));
}

Nivel XMLHandler::levantarNivel(const std::string& rutaNivel)
{
	TiXmlDocument doc( rutaNivel );
	if (!doc.LoadFile()) std::cout<<"ERROR Al levantar nivel";
	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem=hDoc.FirstChildElement().Element();
	if (!pElem) std::cout<<"ERROR Al levantar nivel";
	std::string nombreNivel(pElem->Value());
	int ancho, alto;
	pElem->QueryIntAttribute(ATRIBUTO_ANCHO, &ancho);
	pElem->QueryIntAttribute(ATRIBUTO_ALTO, &alto);
	Nivel nivel(nombreNivel, ancho, alto);
	hRoot=TiXmlHandle(pElem);
	pElem=hRoot.FirstChildElement().Element();
	while(pElem){
		std::string tipoDeElemento(pElem->Value());
		(this->*elementosNivel[tipoDeElemento])(nivel, pElem);//Agrega el elemento al nivel
		pElem=pElem->NextSiblingElement();
	}
	return nivel;
}

void XMLHandler::agregarGeneradorConejo(Nivel& nivel,TiXmlElement* elemento){
	GeneradorConejo* generadorConejo = new GeneradorConejo();
	generadorConejo->hidratar(elemento);
	nivel.agregarGenerador(generadorConejo);
}

void XMLHandler::agregarObstaculoRompible(Nivel& nivel,TiXmlElement* elemento){
	Elemento* obstaculoRompible = new ObstaculoRompible();
	obstaculoRompible->hidratar(elemento);
	nivel.agregarElemento(obstaculoRompible);
}
void XMLHandler::agregarObstaculoIrrompible(Nivel& nivel,TiXmlElement* elemento){
	Elemento* obstaculoIrrompible = new ObstaculoIrrompible();
	obstaculoIrrompible->hidratar(elemento);
	nivel.agregarElemento(obstaculoIrrompible);
}

void XMLHandler::agregarGeneradorTortugaRoja(Nivel& nivel,TiXmlElement* elemento){
	GeneradorTortuga* genTortugaRoja = new GeneradorTortugaRoja();
	genTortugaRoja->hidratar(elemento);
	nivel.agregarGenerador(genTortugaRoja);
}

void XMLHandler::agregarGeneradorTortugaVerde(Nivel& nivel,TiXmlElement* elemento){
	GeneradorTortuga* genTortugaVerde = new GeneradorTortugaVerde();
	genTortugaVerde->hidratar(elemento);
	nivel.agregarGenerador(genTortugaVerde);
}

void XMLHandler::agregarFinDeNivel(Nivel& nivel,TiXmlElement* elemento){
	FinDeNivel* finDeNivel = new FinDeNivel();
	finDeNivel->hidratar(elemento);
	nivel.agregarElemento(finDeNivel);
}

void XMLHandler::guardarNivel(const Nivel& nivel){
	std::string nombreNivel	 = nivel.obtenerNombre();
	int alto = nivel.obtenerAltoNivel();
	int ancho = nivel.obtenerAnchoNivel();
	std::vector<Elemento*> elementos = nivel.obtenerElementos();
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	TiXmlElement * root = new TiXmlElement(nombreNivel);
	root->SetAttribute(ATRIBUTO_ANCHO, ancho);
	root->SetAttribute(ATRIBUTO_ALTO, alto);
	doc.LinkEndChild( root );
	PersistidorFunctor functor(root);
	std::for_each(elementos.begin(), elementos.end(), functor);

	doc.SaveFile(std::string(RUTA_SERVER_EDITOR_NIVELES) + SEPARADOR_DIRECTORIOS + nombreNivel);
}


