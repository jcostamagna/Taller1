/*
 * server_Partida.cpp
 *
 *  Created on: 29/10/2015
 *      Author: matiaskamien
 */
#include "server_Partida.h"
#include "../../Common/src/Lock.h"
#include "../../Common/src/constantes.h"
#include "LevantadorDeNivelesFunctor.h"
#include "../../Common/src/EventoMovimiento.h"
#include "../../Common/src/EventoElementoDestruido.h"
#include "EventoGanador.h"
#include "../../Common/src/EventoNuevoPersonaje.h"
#include "LanzadorDeEventosFunctor.h"
#include "GeneradorTortugasFunctor.h"
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

Partida::Partida(const std::vector<std::string>& niveles,const unsigned int cantidadJugadores,
										const std::string &nombre, AdministradorDeNiveles& admin): niveles(niveles), admin(admin)
{
	this->cantidadJugadores = cantidadJugadores;
	this->cantidadJugadoresParcial = 0;
	this->idPartida = 0;
	this->nombre = nombre;
	this->estaViva = false;
	this->jugandoNivel = false;
}

void Partida::ponerEnDisponibleTodosLosGeneradores()
{
	std::vector<GeneradorConejoModelo*>::iterator it;
	for (it = this->generadoresDeConejos.begin(); it != this->generadoresDeConejos.end(); ++it)
	{
		(*it)->ponerComoDisponible();
	}
}

Modelo& Partida::obtenerModelo()
{
	return this->modelo;
}

void Partida::agregarGeneradorTortuga(GeneradorTortugaModelo* generador)
{
	this->generadorTortugas.push_back(generador);
}

void Partida::agregarGeneradorConejo(GeneradorConejoModelo* generadorConejo)
{
	this->generadoresDeConejos.push_back(generadorConejo);
}


const std::string Partida::obtenerNombre()const
{
	return this->nombre;
}

void Partida::setearId(const int idPartida)
{
	this->idPartida = idPartida;
}

const int Partida::obtenerIdPartida()const{
	return this->idPartida;
}

const unsigned int Partida::obtenerCantidadJugadoresFaltantes() const
{
	return (this->cantidadJugadores-this->cantidadJugadoresParcial);
}

const bool Partida::faltanJugadores() const
{
	return (this->obtenerCantidadJugadoresFaltantes() > 0);
}

bool Partida::agregarJugador(Observador* jugador)
{
	if(!this->faltanJugadores()) return false;
	this->agregarObservador(jugador);
	this->sumarJugador();
	return true;
}

const Observador* Partida::obtenerObservadorAMatchear()const
{
	//Observador* observador = NULL;
	std::vector<Observador*>::const_iterator it;
	for (it = this->observadores.begin(); it != this->observadores.end(); ++it)
	{
		if(!((*it)->fueMatcheado()))
		{
			(*it)->asignarMatcheo();
			break;
		}
	}
	return (*it);
}

const int Partida::obtenerCantidadJugadores()const
{
	return this->cantidadJugadores;
}

const bool Partida::estaLlena()
{
	return (this->obtenerCantidadJugadoresFaltantes() == 0);
}

void Partida::sumarJugador()
{
	++this->cantidadJugadoresParcial;
}


void Partida::encolarEvento(const EventoTeclas& evento){
	this->eventos.push(evento);
}

void Partida::procesarEventos(){
	Lock lock(this->mutex);
	while (!eventos.empty()){
		modelo.moverElemento(eventos.front());
		eventos.pop();
	}
}


void Partida::terminarNivel(){
	this->jugandoNivel = false;
}

void Partida::empezarNivel(){
	//Sale del while una vez que termina el nivel.
	this->jugandoNivel = true;
	clock_t timer;
	LanzadorDeEventosFunctor lanzador(*this);
	GeneradorTortugasFunctor generador(*this);
	std::vector<Evento*> eventosColisiones, eventosMovimiento, eventosParticulares;
	float milisegundosFaltantes;
	while(this->jugandoNivel && this->observadores.size() > 0)
	{
		timer = clock();

		//Generar Tortugas
		std::for_each(this->generadorTortugas.begin(), this->generadorTortugas.end(), generador);

		//Procesar teclas
		this->procesarEventos();

		//Mover elementos
		this->modelo.eventosMover();

		//Chequear colisiones
		std::vector<Evento*> eventosColisiones;
		this->modelo.chequearColisiones(eventosColisiones);
		eventosMovimiento = this->modelo.colectarEventosMover();

		//Envio primero los eventos de movimiento y luego de colisiones
		std::for_each(eventosMovimiento.begin(), eventosMovimiento.end(), lanzador);
		std::for_each(eventosColisiones.begin(), eventosColisiones.end(), lanzador);
		eventosMovimiento.clear();
		eventosColisiones.clear();

		//Eventos particulares (disparos)
		this->modelo.eventosParticulares(eventosParticulares);
		std::for_each(eventosParticulares.begin(), eventosParticulares.end(), lanzador);
		eventosParticulares.clear();
		//Loop de 100 milisegundos
		timer = clock() - timer;
		milisegundosFaltantes = 100 - ((((float)timer)/CLOCKS_PER_SEC)*1000);
		usleep(1000*milisegundosFaltantes);
	}
	this->modelo.actualizarPuntajes();
}

const int Partida::obtenerIdGanadorPartida()
{
	return this->modelo.obtenerIdGanador();
}

void Partida::run()
{
	this->estaViva = true;
	LevantadorDeNivelesFunctor levantador(*this);
	std::for_each(this->niveles.begin(), this->niveles.end(), levantador);
	int idGanador = this->obtenerIdGanadorPartida();
	int puntaje = this->obtenerPuntajeGanador();
	Evento* eventoGanador = new EventoGanador(idGanador, puntaje);
	this->notificar(eventoGanador);
	delete eventoGanador;
}

const int Partida::obtenerPuntajeGanador()
{
	return this->modelo.obtenerPuntajeGanador();
}

void limpiarTortugas(GeneradorTortugaModelo* generador){
	delete generador;
}

void limpiarConejos(GeneradorConejoModelo* generador){
	delete generador;
}

void Partida::limpiar(){
	std::for_each(this->generadorTortugas.begin(), this->generadorTortugas.end(), limpiarTortugas);
	std::for_each(this->generadoresDeConejos.begin(), this->generadoresDeConejos.end(), limpiarConejos);
	this->generadorTortugas.clear();
	this->generadoresDeConejos.clear();
	this->desactivarMatcheoObservadores();
	this->modelo.limpiar();
}

const bool Partida::vive()
{
	return this->estaViva;
}

void Partida::desactivarMatcheoObservadores()
{
	std::vector<Observador*>::iterator it;
	for (it = this->observadores.begin(); it != this->observadores.end(); ++it)
	{
		(*it)->desasignarMatcheo();
	}
}

Partida::~Partida()
{
	std::for_each(this->generadorTortugas.begin(), this->generadorTortugas.end(), limpiarTortugas);
	std::for_each(this->generadoresDeConejos.begin(), this->generadoresDeConejos.end(), limpiarConejos);
}



