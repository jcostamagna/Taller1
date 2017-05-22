/*
 * ConversorDeNivelAModelo.cpp
 *
 *  Created on: 24/11/2015
 *      Author: matiaskamien
 */

#include "ConversorDeNivelAModelo.h"

ConversorDeNivelAModelo::ConversorDeNivelAModelo() {
	this->mapDeFunciones.insert(std::make_pair(CONEJO, &ConversorDeNivelAModelo::agregarConejoGraficable));
	this->mapDeFunciones.insert(std::make_pair(TORTUGAROJA, &ConversorDeNivelAModelo::agregarGeneradorTortugaRoja));
	this->mapDeFunciones.insert(std::make_pair(TORTUGAVERDE, &ConversorDeNivelAModelo::agregarGeneradorTortugaVerde));
	this->mapDeFunciones.insert(std::make_pair(OBSTACULOROMP, &ConversorDeNivelAModelo::agregarObstaculoRompibleGraficable));
	this->mapDeFunciones.insert(std::make_pair(OBSTACULO_IRROMP, &ConversorDeNivelAModelo::agregarObstaculoIrrompibleGraficable));
	this->mapDeFunciones.insert(std::make_pair(FINDENIVEL, &ConversorDeNivelAModelo::agregarFinDeNivelGraficable));
}

void ConversorDeNivelAModelo::pasarInformacionAModelo(Nivel* nivel,Partida* partida)
{
	int idElemento = 1;
	partida->obtenerModelo().setearAltoNivel(nivel->obtenerAltoNivel());
	partida->obtenerModelo().setearAnchoNivel(nivel->obtenerAnchoNivel());
	std::vector<Elemento*>::const_iterator it;
	for (it = nivel->obtenerElementos().begin(); it != nivel->obtenerElementos().end(); ++it)
	{
		(this->*mapDeFunciones[(*it)->obtenerTipoElemento()])((*it),partida,idElemento);
		++idElemento;
	}
	int cantJugadoresPartida = partida->obtenerCantidadJugadores();
	for (int i = 0; i < cantJugadoresPartida; ++i)
	{
		int posicionEnElVector = (i % cantJugadoresPartida);
		GeneradorConejo* generadorConejo = nivel->obtenerGeneradorConejo();
		std::string colorASetear = nivel->obtenerColores().at(nivel->obtenerPosicionColor());
		nivel->aumentarPosicionColor();
		generadorConejo->setearColor(colorASetear);
		(this->*mapDeFunciones[generadorConejo->obtenerTipoElemento()])(generadorConejo,partida,idElemento);
		++idElemento;
	}
	std::vector<GeneradorTortuga*>::const_iterator itGenTortugas;
	for (itGenTortugas = nivel->obtenerTortugas().begin();
			itGenTortugas != nivel->obtenerTortugas().end(); ++itGenTortugas)
	{
		(this->*mapDeFunciones[(*itGenTortugas)->obtenerTipoElemento()])((*itGenTortugas),partida,idElemento);
		++idElemento;
	}
	partida->obtenerModelo().setearMatcheos(this->mapDeMatcheo);
}

void ConversorDeNivelAModelo::agregarConejoGraficable(const Elemento* elemento,Partida* partida,const int idConejo)
{
	int verticeX = elemento->obtenerVerticeX();
	int verticeY = elemento->obtenerVerticeY();
	GeneradorConejoModelo* generadorConejo = new GeneradorConejoModelo(verticeX,verticeY,idConejo);
	partida->agregarGeneradorConejo(generadorConejo);
	Conejo* conejo = new Conejo();
	GeneradorConejo* generadorConejoColor = (GeneradorConejo*)elemento;
	conejo->setearColor(generadorConejoColor->obtenerColor());
	ClientHandler* cliente = (ClientHandler*)partida->obtenerObservadorAMatchear();
	int idClient = cliente->obtenerId();
	this->mapDeMatcheo.insert(std::make_pair(idClient,idConejo));//Matcheo los ids.
	conejo->setearId(idConejo);
	conejo->setearVerticeSuperiorIzqX(verticeX);
	conejo->setearVerticeSuperiorIzqY(verticeY);
	partida->obtenerModelo().agregarElementoGraficable(conejo);
}

void ConversorDeNivelAModelo::agregarGeneradorTortugaRoja(const Elemento* elemento,Partida* partida,const int id)
{
	TortugaRoja* tortugaRoja = new TortugaRoja();
	tortugaRoja->setearVerticeSuperiorIzqX(elemento->obtenerVerticeX());
	tortugaRoja->setearVerticeSuperiorIzqXAnterior(elemento->obtenerVerticeX());
	tortugaRoja->setearVerticeSuperiorIzqY(elemento->obtenerVerticeY());
	tortugaRoja->setearVerticeSuperiorIzqYAnterior(elemento->obtenerVerticeY());
	tortugaRoja->setearId(id);
	partida->obtenerModelo().agregarElementoGraficable(tortugaRoja);
	GeneradorTortuga* generadorTortugaElemento=(GeneradorTortuga*)elemento;
	GeneradorTortugaRojaModelo* generadorTortuga = new GeneradorTortugaRojaModelo
			(elemento->obtenerVerticeX(),elemento->obtenerVerticeY(),
					generadorTortugaElemento->obtenerFrecuenciaGeneracion(),
					generadorTortugaElemento->obtenerCantidadMaxima());
	partida->agregarGeneradorTortuga(generadorTortuga);
}

void ConversorDeNivelAModelo::agregarGeneradorTortugaVerde(const Elemento* elemento,Partida* partida,const int id)
{
	TortugaVerde* tortugaVerde = new TortugaVerde();
	tortugaVerde->setearVerticeSuperiorIzqX(elemento->obtenerVerticeX());
	tortugaVerde->setearVerticeSuperiorIzqXAnterior(elemento->obtenerVerticeX());
	tortugaVerde->setearVerticeSuperiorIzqY(elemento->obtenerVerticeY());
	tortugaVerde->setearVerticeSuperiorIzqYAnterior(elemento->obtenerVerticeY());
	tortugaVerde->setearId(id);
	partida->obtenerModelo().agregarElementoGraficable(tortugaVerde);
	GeneradorTortuga* generadorTortugaElemento=(GeneradorTortuga*)elemento;
	GeneradorTortugaVerdeModelo* generadorTortuga = new GeneradorTortugaVerdeModelo
			(elemento->obtenerVerticeX(),elemento->obtenerVerticeY(),
					generadorTortugaElemento->obtenerFrecuenciaGeneracion(),
					generadorTortugaElemento->obtenerCantidadMaxima());
	partida->agregarGeneradorTortuga(generadorTortuga);

}

void ConversorDeNivelAModelo::agregarObstaculoRompibleGraficable(const Elemento* elemento,Partida* partida,const int id)
{
	ObstaculoRompibleGraficable* obstaculoRompibleGraficable = new ObstaculoRompibleGraficable();
	obstaculoRompibleGraficable->setearVerticeSuperiorIzqX(elemento->obtenerVerticeX());
	obstaculoRompibleGraficable->setearVerticeSuperiorIzqXAnterior(elemento->obtenerVerticeX());
	obstaculoRompibleGraficable->setearVerticeSuperiorIzqY(elemento->obtenerVerticeY());
	obstaculoRompibleGraficable->setearVerticeSuperiorIzqYAnterior(elemento->obtenerVerticeY());
	obstaculoRompibleGraficable->setearId(id);
	partida->obtenerModelo().agregarElementoGraficable(obstaculoRompibleGraficable);
}

void ConversorDeNivelAModelo::agregarObstaculoIrrompibleGraficable(const Elemento* elemento,Partida* partida,const int id)
{
	ObstaculoIrrompibleGraficable* obstaculoIrrompible = new ObstaculoIrrompibleGraficable();
	obstaculoIrrompible->setearVerticeSuperiorIzqX(elemento->obtenerVerticeX());
	obstaculoIrrompible->setearVerticeSuperiorIzqXAnterior(elemento->obtenerVerticeX());
	obstaculoIrrompible->setearVerticeSuperiorIzqY(elemento->obtenerVerticeY());
	obstaculoIrrompible->setearVerticeSuperiorIzqYAnterior(elemento->obtenerVerticeY());
	obstaculoIrrompible->setearId(id);
	partida->obtenerModelo().agregarElementoGraficable(obstaculoIrrompible);
}

void ConversorDeNivelAModelo::agregarFinDeNivelGraficable(const Elemento* elemento,Partida* partida,const int id)
{
	FinDeNivelGraficable* finDeNivel = new FinDeNivelGraficable();
	finDeNivel->setearVerticeSuperiorIzqX(elemento->obtenerVerticeX());
	finDeNivel->setearVerticeSuperiorIzqXAnterior(elemento->obtenerVerticeX());
	finDeNivel->setearVerticeSuperiorIzqY(elemento->obtenerVerticeY());
	finDeNivel->setearVerticeSuperiorIzqYAnterior(elemento->obtenerVerticeY());
	finDeNivel->setearId(id);
	partida->obtenerModelo().agregarElementoGraficable(finDeNivel);
}

const int ConversorDeNivelAModelo::pasarStringAInt(const std::string &string)
{
	std::stringstream ss;
	int entero = 0;
	ss << string;
	ss >> entero;
	return entero;
}

ConversorDeNivelAModelo::~ConversorDeNivelAModelo() {}

