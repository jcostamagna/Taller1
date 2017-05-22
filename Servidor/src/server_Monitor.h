/*
 * server_Monitor.h
 *
 *  Created on: 21 Sep 2015
 *      Author: osboxes
 */

#ifndef SERVER_MONITOR_H_
#define SERVER_MONITOR_H_

#include <string>
#include "server_BaseDeDatos.h"
#include "../../Common/src/Lock.h"
#include "Observador.h"
#include "../../Common/src/AdministradorDeNiveles.h"

class Monitor {
private:
	Mutex mutex;
	BaseDeDatos bd;
	AdministradorDeNiveles& admin;

	Monitor(const Monitor& object);
	Monitor& operator=(const Monitor& object);
public:
	/* Clase protectora de la base de datos para la concurrencia */
	Monitor(AdministradorDeNiveles& admin);

	//Devuelve los niveles.
	std::vector<std::string> obtenerNiveles();

	//Devuelve las partidas y la cantidad de jugadores que faltan para que empiece.
	const std::vector<Partida*>& obtenerPartidas();

	//Devuelve un puntero a la partida recibida por parámetro.
	Partida* obtenerPartida(const std::string &nombrePartida);

	//Devuelve un puntero al nivel recibido por parámetro.
	Nivel* obtenerNivel(const std::string &nombreNivel);

	//Devuelve un vector de string con la informacion del nivel.
	std::vector<std::string> obtenerInformacionDelNivel(const std::string &nombreNivel);

	//Devuelve true si pudo agregar al jugador. False si no lo agrego.
	bool agregarJugador(Partida* partida,Observador* clientHandler);

	//Crea una nueva partida.
	bool crearPartida(const std::vector<std::string>& vector,const unsigned int cantidadJugadores,
					  const std::string &nombrePartida);
};

#endif /* SERVER_MONITOR_H_ */
