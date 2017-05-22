/*
 * client_Modelo.cpp
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */

#include "Modelo.h"
#include "MoverElementoFunctor.h"
#include "ColectorDeEventosFunctor.h"
#include "EventoTeclas.h"
#include "DuetFunctor.h"
#include <algorithm>
#include <iostream>
const int posicionIdElemento = 0;
const int posicionTipoDeElementoEnElVector = 1;
const int posicionVerticeSuperiorIzqX = 2;
const int posicionVerticeSuperiorIzqY = 3;
const int posicionColor = 4;
const int posicionFrecuenciaDeGeneracion = 4;
const int posicionCantidadMaxima = 5;

Modelo::Modelo()
{
	this->mapDeFunciones.insert(std::make_pair(CONEJO, &Modelo::generarInstanciaConejo));
	this->mapDeFunciones.insert(std::make_pair(TORTUGAROJA, &Modelo::generarInstanciaTortugaRoja));
	this->mapDeFunciones.insert(std::make_pair(TORTUGAVERDE, &Modelo::generarInstanciaTortugaVerde));
	this->mapDeFunciones.insert(std::make_pair(OBSTACULOROMP, &Modelo::generarInstanciaObstaculoRompible));
	this->mapDeFunciones.insert(std::make_pair(OBSTACULO_IRROMP, &Modelo::generarInstanciaObstaculoIrrompible));
	this->mapDeFunciones.insert(std::make_pair(FINDENIVEL, &Modelo::generarInstanciaFinDeNivel));
	this->cantidadJugadores = 0;//Ver si se necesita esto!
	this->idElementos=1;
	this->altoDeNivel = 0;
	this->anchoDeNivel = 0;
	this->yaFueCreadoMapDePuntajes = false;
}

void Modelo::setearAnchoNivel(const int anchoNivel)
{
	this->anchoDeNivel = anchoNivel;
}

void Modelo::setearAltoNivel(const int altoNivel)
{
	this->altoDeNivel = altoNivel;
}

ElementoGraficable* Modelo::obtenerElemento(const int id)
{
	std::vector<ElementoGraficable*>::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it)
	{
		if((*it)->obtenerId() == id)
		{
			return (*it);
		}
	}
	return NULL;
}

ElementoGraficable* Modelo::generarInstanciaConejo()
{
	return (new Conejo());
}
ElementoGraficable* Modelo::generarInstanciaTortugaRoja()
{
	return (new TortugaRoja());
}
ElementoGraficable* Modelo::generarInstanciaTortugaVerde()
{
	return (new TortugaVerde());
}

ElementoGraficable* Modelo::generarInstanciaObstaculoRompible()
{
	return (new ObstaculoRompibleGraficable());
}
ElementoGraficable* Modelo::generarInstanciaObstaculoIrrompible()
{
	return (new ObstaculoIrrompibleGraficable());
}
ElementoGraficable* Modelo::generarInstanciaFinDeNivel()
{
	return (new FinDeNivelGraficable());
}

const int Modelo::pasarStringAInt(const std::string &string)
{
	std::stringstream ss;
	int entero = 0;
	ss << string;
	ss >> entero;
	return entero;
}

const std::string Modelo::pasarIntAString(const int entero)
{
	std::stringstream ss;
	ss << entero;
	return ss.str();
}

int Modelo::agregarElementoGraficable(ElementoGraficable* elemento)
{
	int idElemento = this->idElementos;
	elemento->setearId(idElemento);
	++this->idElementos;
	this->elementos.push_back(elemento);
	return idElemento;
}

void Modelo::eliminarElemento(const int idElemento)
{
	std::vector<ElementoGraficable*>::iterator it;
	std::vector<ElementoGraficable*>::iterator elementoAEliminar;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it)
	{
		if((*it)->obtenerId() == idElemento)
		{
			elementoAEliminar = it;
			break;
		}
	}
	delete (*it);
	this->elementos.erase(elementoAEliminar);
}

void Modelo::setearCantidadJugadores(const int cantidadJugadores)
{
	this->cantidadJugadores = cantidadJugadores;
}

const std::vector<std::string> Modelo::obtenerInformacion()
{
	std::vector<ElementoGraficable*>::iterator it;
	std::vector<std::string> vector;
	vector.push_back(INICIAR_NIVEL);
	vector.push_back(this->pasarIntAString(this->altoDeNivel));
	vector.push_back(this->pasarIntAString(this->anchoDeNivel));
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it)
	{
		vector.push_back((*it)->obtenerInformacion());
	}
	return vector;
}

void Modelo::agregarElemento(const std::string &informacionElemento)
{
	std::vector<std::string> vector = this->parser.split(informacionElemento,'*');
	std::cout << "Info elem: " << informacionElemento << std::endl;
	std::string tipoElemento = vector.at(posicionTipoDeElementoEnElVector);
	ElementoGraficable* elemento=(this->*mapDeFunciones[tipoElemento])();
	this->agregarElementoAlModelo(elemento,vector);
}

void Modelo::agregarElementoAlModelo(ElementoGraficable* elemento,
		const std::vector<std::string>& vector)
{
	elemento->setearId(this->pasarStringAInt(vector.at(posicionIdElemento)));
	elemento->setearTipoElemento(vector.at(posicionTipoDeElementoEnElVector));
	elemento->setearVerticeSuperiorIzqX(this->pasarStringAInt(vector.at(posicionVerticeSuperiorIzqX)));
	elemento->setearVerticeSuperiorIzqY(this->pasarStringAInt(vector.at(posicionVerticeSuperiorIzqY)));
	elemento->setearVerticeSuperiorIzqXAnterior(elemento->obtenerVerticeSuperiorIzqX());
	elemento->setearVerticeSuperiorIzqYAnterior(elemento->obtenerVerticeSuperiorIzqY());
	if(elemento->obtenerTipoElemento() == CONEJO)
	{
		Conejo* conejo = (Conejo*)elemento;
		conejo->setearColor(vector.at(posicionColor));
	}
	++this->idElementos;
	this->elementos.push_back(elemento);
}

std::vector<ElementoGraficable*>& Modelo::obtenerElementosParaModificacion()
{
	return this->elementos;
}

const std::vector<ElementoGraficable*>& Modelo::obtenerElementos()const
{
	return this->elementos;
}

void Modelo::setearMatcheos(const std::map<int,int> matcheos){
	this->macheoClientes = matcheos;
	if(!this->yaFueCreadoMapDePuntajes)
	{
		this->crearMapDePuntajes();
	}
}

void Modelo::crearMapDePuntajes()
{
	std::map<int,int>::iterator it;
	for (it = this->macheoClientes.begin(); it != this->macheoClientes.end(); ++it)
	{
		this->macheoPuntajes.insert(std::make_pair((*it).first,0));//Matcheo los ids.
	}
	this->yaFueCreadoMapDePuntajes = true;
}

void Modelo::actualizarPuntajes()
{
	std::map<int,int>::iterator it;
	for (it = this->macheoPuntajes.begin(); it != this->macheoPuntajes.end(); ++it)
	{
		int idConejo = this->macheoClientes[(*it).first];
		Conejo* conejo = (Conejo*)this->obtenerElemento(idConejo);
		if(conejo)//Si entra quiere decir que el conejo no murió en el nivel.
		{
			this->macheoPuntajes[(*it).first] += conejo->obtenerPuntaje();
		}
	}
}

void Modelo::moverElemento(const EventoTeclas& evento){
	int idElemento = this->macheoClientes.at(evento.getId());
	MoverElementoFunctor moverElemento(idElemento, evento);
	std::for_each(this->elementos.begin(), this->elementos.end(), moverElemento);
}

void Modelo::chequearColisiones(std::vector<Evento*>& eventos){
	DuetFunctor functor(this->elementos, eventos);
	std::for_each(this->elementos.begin(), this->elementos.end(), functor);
}

void Modelo::eventosParticulares(std::vector<Evento*>& eventos){
	ColectorEventosParticulares colector(eventos);
	std::for_each(this->elementos.begin(), this->elementos.end(), colector);
}

const int Modelo::obtenerIdGanador()
{
	int puntajeMasAlto = 0;
	int idGanador = -1;
	std::map<int,int>::iterator it;
	for (it = this->macheoPuntajes.begin(); it != this->macheoPuntajes.end(); ++it)
	{
		if((*it).second > puntajeMasAlto)
		{
			puntajeMasAlto = (*it).second;
			idGanador = (*it).first;
		}
	}
	return idGanador;
}

const int Modelo::obtenerPuntajeGanador()
{
	int puntajeMasAlto = 0;
	std::map<int,int>::iterator it;
	for (it = this->macheoPuntajes.begin(); it != this->macheoPuntajes.end(); ++it)
	{
		if((*it).second > puntajeMasAlto)//En caso de empate muestra solo el primero.
		{
			puntajeMasAlto = (*it).second;
		}
	}
	return puntajeMasAlto;
}

void moverElementos(ElementoGraficable* elemento){
	elemento->mover();
}

void Modelo::eventosMover(){
	std::for_each(this->elementos.begin(), this->elementos.end(), moverElementos);
}

bool Modelo::conejoVivo(int idConejo){
	Conejo* conejo = (Conejo*)this->obtenerElemento(idConejo);
	return conejo->estaVivo();
}

bool Modelo::chequearConejosVivos(){
	std::vector<ElementoGraficable*>::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it)
	{
		if((*it)->obtenerTipoElemento() == CONEJO)
		{
			Conejo* conejo = (Conejo*)(*it);
			if (conejo->estaVivo()){return true;}
		}
	}
	return false;
}

const std::map<int,int>& Modelo::obtenerMatcheos(){
	return this->macheoClientes;
}

std::vector<Evento*> Modelo::colectarEventosMover(){
	std::vector<Evento*> eventos;
	ColectorDeEventosFunctor colector(eventos, this->macheoClientes);
	std::for_each(this->elementos.begin(), this->elementos.end(), colector);
	return eventos;
}

const int Modelo::obtenerIdActual(){
	return this->idElementos;
}

void limpiarElemento(ElementoGraficable* elemento){
	delete elemento;
}

void Modelo::limpiar(){
	std::for_each(this->elementos.begin(), this->elementos.end(), limpiarElemento);
	this->elementos.clear();
	this->macheoClientes.clear();
	this->idElementos = 1;
}

Modelo::~Modelo()
{
	std::for_each(this->elementos.begin(), this->elementos.end(), limpiarElemento);
}

