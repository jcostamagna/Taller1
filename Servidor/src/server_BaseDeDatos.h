
#ifndef SERVER_BASEDEDATOS_H_
#define SERVER_BASEDEDATOS_H_

#include <map>
#include <string>
#include <vector>
#include "server_Partida.h"
#include "../../Common/src/Nivel.h"

class BaseDeDatos {
	private:
		std::vector<Partida*> partidas;
		int idPartida;
		BaseDeDatos(const BaseDeDatos& object);//Ver si hay que sacarlo!
		BaseDeDatos& operator=(const BaseDeDatos& object);//Ver si hay que sacarlo!

		//Devuelve true si ya hay una partida con ese nombre.
		bool yaExistePartidaConMismoNombre(const std::string &nombre);
	public:
		BaseDeDatos();

		//Devuelve un vector con todas las partidas no están llenas.
		const std::vector<Partida*>& obtenerPartidas();

		//Agrega una partida al vector de partidas.
		//Si ya hay una partida con ese nombre, devuelve false.
		bool agregarPartida(Partida* partida);

		//Devuelve un puntero de la partida recibida por parámetro.
		Partida* obtenerPartida(const std::string &nombrePartida);

		//Libera los recursos utilizados.
		~BaseDeDatos();
};

#endif /* SERVER_BASEDEDATOS_H_ */
