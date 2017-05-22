/*
 * server_ClientHandler.cpp
 *
 *  Created on: 21 Sep 2015
 *      Author: osboxes
 */

#include "server_ClientHandler.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "../../Common/src/common_Parser.h"
#include "../../Common/src/constantes.h"
#include "ConversorDeTeclasFunctor.h"
#include "../../Common/src/EventoTeclas.h"
const int posicionNombrePartida = 1;
const int posicionCantidadJugadoresPartida = 2;
const int posicionPrimerNivelPartida = 3;
const int posicionTeclas = 1;

typedef void (ClientHandler::*Funciones)(std::vector<std::string>&);

ClientHandler::ClientHandler(Monitor& monitor,const int id): monitor(monitor)
{
	this->partidaEnJuego = NULL;
	this->id = id;
}

void ClientHandler::identificarComandos(std::map<std::string,
		Funciones> map, std::vector<std::string> comandos){
	std::string error(RESPUESTA_ERROR);
	if (comandos.empty()) {
		this->queue.put(error);
		return;
	}
	if (map[comandos.at(0)]!= 0) (this->*map[comandos.at(0)])(comandos);
	else this->queue.put(error);
}

void ClientHandler::obtenerNiveles(std::vector<std::string> &comandos)
{
	std::string nivelesConSeparador = this->procesarNiveles(this->monitor.obtenerNiveles());
	if (nivelesConSeparador.empty()) this->queue.put(std::string(RESPUESTA_ERROR));
	else this->queue.put(nivelesConSeparador);
}

void ClientHandler::obtenerCantidadJugadoresFaltantes(std::vector<std::string> &comandos)
{
	unsigned int cantidadJugadoresFaltantes = this->partidaEnJuego->obtenerCantidadJugadoresFaltantes();
	std::string cantidadJugadoresFaltantesString = this->pasarIntAString(cantidadJugadoresFaltantes);
	this->queue.put(cantidadJugadoresFaltantesString);
}

void ClientHandler::iniciarPartida(std::vector<std::string> &comandos)
{
	std::string nombrePartida = comandos.at(posicionNombrePartida);
	unsigned int cantidadJugadores = this->pasarStringAInt(comandos.at(posicionCantidadJugadoresPartida));
	std::vector<std::string> vectorDeNiveles;
	std::vector<std::string>::iterator it;
	for (unsigned int var = posicionPrimerNivelPartida; var < comandos.size(); ++var)
	{
		vectorDeNiveles.push_back(comandos.at(var));
	}
	std::string respuesta;
	if(this->monitor.crearPartida(vectorDeNiveles,cantidadJugadores,nombrePartida))
	{
		this->partidaEnJuego = this->monitor.obtenerPartida(nombrePartida);
		if((this->monitor.agregarJugador(this->partidaEnJuego,this)) &&
			(this->partidaEnJuego->estaLlena()))
		{
			this->partidaEnJuego->start();
		}
		this->queue.put(RESPUESTA_OK);
		//Si no agrega jugador la respuesta es OK. Ver eso
	}else{
		this->queue.put(RESPUESTA_ERROR);
	}
}

const int ClientHandler::obtenerId()const
{
	return this->id;
}

void ClientHandler::verificarUnirseAPartida(std::vector<std::string> &comandos)
{
	std::string respuesta;
	std::string nombrePartida = comandos.at(posicionNombrePartida);
	Partida* partida = this->monitor.obtenerPartida(nombrePartida);
	if(this->monitor.agregarJugador(partida,this))
	{
		this->partidaEnJuego = partida;
		if(this->partidaEnJuego->estaLlena())
		{
			this->partidaEnJuego->start();
		}
		this->queue.put(RESPUESTA_OK);
	}else{
		this->queue.put(RESPUESTA_ERROR);
	}
}

void ClientHandler::salir(std::vector<std::string> &comandos)
{
	//Este mensaje no llega al cliente, termina al enviador
	this->queue.put(SALIR);
	if(this->partidaEnJuego != NULL)
	{
		this->partidaEnJuego->eliminarObservador(this);
	}
}

const int ClientHandler::pasarStringAInt(const std::string &cadena)
{
	int cantidadJugadores;
	std::stringstream ss;
	ss << cadena;
	ss >> cantidadJugadores;
	return cantidadJugadores;
}

const std::string ClientHandler::pasarIntAString(const int entero)
{
	std::stringstream ss;
	ss << entero;
	return (ss.str());
}

void ClientHandler::obtenerPartidas(std::vector<std::string> &comandos)
{
	std::string partidasConSeparador = this->procesarPartidas(this->monitor.obtenerPartidas());
	if (partidasConSeparador.empty()) this->queue.put(std::string(RESPUESTA_ERROR));
	else this->queue.put(partidasConSeparador);
}

void ClientHandler::entradaDeTeclas(std::vector<std::string> &comandos)
{
	std::vector<std::string> teclas(this->protocolo.split(comandos.at(posicionTeclas),
												this->protocolo.obtenerSeparadorAuxiliar()));
	std::vector<char> vector = this->llenarVector(teclas);
	this->partidaEnJuego->encolarEvento(EventoTeclas(this->id,vector));
}

const std::vector<char> ClientHandler::llenarVector(const std::vector<std::string> &vectorDeTeclas)
{
	std::vector<char> vectorADevolver;
	for (int i = 0; i < (int)vectorDeTeclas.size(); ++i)
	{
		if(vectorDeTeclas.at(i) == VERDADERO)
		{
			vectorADevolver.push_back(1);
		}else{
			vectorADevolver.push_back(0);
		}
	}
	return vectorADevolver;
}

void ClientHandler::realizarConsulta(const std::string& mensaje)
{
	std::vector<std::string> comandos = this->protocolo.split(mensaje,
														this->protocolo.obtenerSeparador());
	std::map<std::string, Funciones> map = setearMap();
	identificarComandos(map, comandos);
}

std::string ClientHandler::obtenerRespuesta(){
	return this->queue.pull();
}

std::map<std::string, Funciones> ClientHandler::setearMap()
{
	std::map<std::string, Funciones> map;
	map.insert(std::make_pair(OBTENER_NIVELES, &ClientHandler::obtenerNiveles));
	map.insert(std::make_pair(OBTENER_PARTIDAS, &ClientHandler::obtenerPartidas));
	map.insert(std::make_pair(INICIAR_PARTIDA, &ClientHandler::iniciarPartida));
	map.insert(std::make_pair(UNIRSE_A_PARTIDA, &ClientHandler::verificarUnirseAPartida));
	map.insert(std::make_pair(OBTENER_CANTIDAD_JUGADORES_FALTANTES, &ClientHandler::obtenerCantidadJugadoresFaltantes));
	map.insert(std::make_pair(ESTADO_TECLAS, &ClientHandler::entradaDeTeclas));//Falta updatear Constante
	map.insert(std::make_pair(OBTENER_ID, &ClientHandler::asignarID));
	map.insert(std::make_pair(SALIR, &ClientHandler::salir));
	return map;
}

void ClientHandler::asignarID(std::vector<std::string> &comandos)
{
	this->queue.put(this->pasarIntAString(this->id));
}

const std::string ClientHandler::procesarNiveles
								(const std::vector<std::string> &vectorDeNiveles)
{
	std::string respuesta;
	std::vector<std::string>::const_iterator it;
	for (it = vectorDeNiveles.begin(); it != vectorDeNiveles.end(); ++it)
	{
		respuesta += this->protocolo.generarMensajeProtocolarNivel((*it));
	}
	respuesta = respuesta.substr(0,respuesta.size()-1);//Borra "|" final
	return respuesta;
}

const std::string ClientHandler::procesarPartidas
								(const std::vector<Partida*> &vectorDePartidas)
{
	std::string respuesta;
	std::vector<Partida*>::const_iterator it;
	for (it = vectorDePartidas.begin(); it != vectorDePartidas.end(); ++it)
	{
		if((*it)->obtenerCantidadJugadoresFaltantes() > 0)
		{
			respuesta += this->protocolo.generarMensajeProtocolarPartida
					((*it)->obtenerNombre(),(*it)->obtenerCantidadJugadoresFaltantes());
		}
	}
	respuesta = respuesta.substr(0,respuesta.size()-1);//Borra "|" final
	return respuesta;
}

void ClientHandler::actualizar(const std::string& evento)
{
	this->queue.put(evento);
}

void ClientHandler::actualizar(const std::vector<std::string>& eventos)
{
	std::string nivel = protocolo.generarMensajeInformacionNivel(eventos);
	queue.put(nivel);
}

void ClientHandler::actualizar(const Evento* evento)
{
	queue.put(evento->eventoAsString());
}


