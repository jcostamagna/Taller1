/*
 * server_Monitor.cpp
 *
 *  Created on: 21 Sep 2015
 *      Author: osboxes
 */
#include "server_Monitor.h"

Monitor::Monitor(AdministradorDeNiveles& admin): admin(admin){}

std::vector<std::string> Monitor::obtenerNiveles()
{
	return this->admin.nombreNiveles();
}

const std::vector<Partida*>& Monitor::obtenerPartidas()
{
	Lock lock(this->mutex);
	return this->bd.obtenerPartidas();
}

bool Monitor::agregarJugador(Partida* partida,Observador* clientHandler)
{
	Lock lock(this->mutex);
	return partida->agregarJugador(clientHandler);
}

Partida* Monitor::obtenerPartida(const std::string &nombrePartida)
{
	return this->bd.obtenerPartida(nombrePartida);
}

std::vector<std::string> Monitor::obtenerInformacionDelNivel(const std::string &nombreNivel)
{
	std::vector<std::string> vector;
	Nivel* nivel = this->admin.obtenerPunteroANivel(nombreNivel);
	nivel->obtenerInformacion(vector);
	return vector;
}

Nivel* Monitor::obtenerNivel(const std::string &nombreNivel)
{
	return this->admin.obtenerPunteroANivel(nombreNivel);
}

bool Monitor::crearPartida(const std::vector<std::string>& vector,const unsigned int cantidadJugadores,
						   const std::string &nombrePartida)
{
	Partida* partida = new Partida(vector,cantidadJugadores,nombrePartida, this->admin);
	return this->bd.agregarPartida(partida);
}

