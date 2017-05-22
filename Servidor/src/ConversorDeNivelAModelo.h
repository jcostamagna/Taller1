/*
 * ConversorDeNivelApartida.h
 *
 *  Created on: 24/11/2015
 *      Author: matiaskamien
 */

#ifndef SERVIDOR_SRC_CONVERSORDENIVELAMODELO_H_
#define SERVIDOR_SRC_CONVERSORDENIVELAMODELO_H_
#include "../../Common/src/Nivel.h"
#include "server_Partida.h"
#include "server_ClientHandler.h"
#include <map>
#include "../../Common/src/Conejo.h"
#include "../../Common/src/TortugaRoja.h"
#include "../../Common/src/TortugaVerde.h"
#include "../../Common/src/GeneradorTortugaRojaModelo.h"
#include "../../Common/src/GeneradorTortugaVerdeModelo.h"
#include "GeneradorConejoModelo.h"
#include "../../Common/src/GeneradorTortuga.h"
#include "../../Common/src/ObstaculoIrrompibleGraficable.h"
#include "../../Common/src/ObstaculoRompibleGraficable.h"
#include "../../Common/src/FinDeNivelGraficable.h"

class ConversorDeNivelAModelo {
public:
	/* Tipo de punteros a funciones usados para llamar a los distintos metodos*/
	typedef void (ConversorDeNivelAModelo::*Funciones)(const Elemento*,Partida*,const int);
	ConversorDeNivelAModelo();
	~ConversorDeNivelAModelo();

	//Recibe un nivel y pasa su información a la partida recibida por parámetro.
	void pasarInformacionAModelo(Nivel* nivel,Partida* partida);
private:
	std::map<std::string,Funciones> mapDeFunciones;
	std::map<int,int> mapDeMatcheo;

	//Agrega un conejo al modelo.
	void agregarConejoGraficable(const Elemento* elemento,Partida* partida,const int id);
	void agregarGeneradorTortugaRoja(const Elemento* elemento,Partida* partida,const int id);
	void agregarGeneradorTortugaVerde(const Elemento* elemento,Partida* partida,const int id);
	void agregarObstaculoRompibleGraficable(const Elemento* elemento,Partida* partida,const int id);
	void agregarObstaculoIrrompibleGraficable(const Elemento* elemento,Partida* partida,const int id);
	void agregarFinDeNivelGraficable(const Elemento* elemento,Partida* partida,const int id);
	const int pasarStringAInt(const std::string &string);
};

#endif /* SERVIDOR_SRC_CONVERSORDENIVELAMODELO_H_ */
