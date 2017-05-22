/*
 * common_ProtocoloClientes.h
 *
 *  Created on: 29/10/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_COMMON_PROTOCOLOCLIENTES_H_
#define COMMON_COMMON_PROTOCOLOCLIENTES_H_
#include "../../Common/src/common_Parser.h"
#include "../../Common/src/constantes.h"
#include <sstream>
#include <vector>
#include <string>

//Esta clase va a encapsular el protocolo para comunicarse entre cliente y servidor.
class ProtocoloClientes{
	private:
		char separador;
		char separadorAuxiliar;
		Parser parser;

	public:
		//Setea el separador.
		ProtocoloClientes();

		//Splitea el texto según el separador y lo devuelve.
		std::vector<std::string> split(const std::string& texto,const char separador);

		//Devuelve el separador.
		const char obtenerSeparador();

		//Devuelve el separador en string.
		const std::string obtenerSeparadorEnString();

		//Devuelve el separador de auxiliar.
		const char obtenerSeparadorAuxiliar();

		//Devuelve en string del separador auxiliar
		const std::string obtenerSeparadorAuxiliarEnString();

		//Devuelve el entero pasado por parámetro en string.
		const std::string pasarIntAString(const int entero);

		//Recibe la información de una partida y genera el string para enviar al cliente.
		const std::string generarMensajeProtocolarPartida(const std::string &nombrePartida,
										const unsigned int cantidadJugadoresRestantes);

		//Recibe el nombre de una partida y genera el string para preguntar cuantos jugadores faltan.
		const std::string generarPreguntaCantidadJugadores(const std::string &nombrePartida);

		//Recibe el nombre de un nivel y genera el string para enviar al cliente.
		const std::string generarMensajeProtocolarNivel(const std::string &nombreNivel);

		//Recibe los nombres de los niveles de la partida en un vector y genera el string para enviar
		//al servidor.
		const std::string generarMensajeDeInicioDePartida(const std::vector<std::string> &niveles,
							const std::string &cantidadJugadores,const std::string &nombrePartida);

		//Parsea la información recibida desde el server para luego crear el modelo del nivel.
		const std::vector<std::string> parsearInformacionDeNivel(const std::string &informacionDelNivel);

		//Recibe la información de un nivel por parámetro y genera el string para enviar al cliente.
		const std::string generarMensajeInformacionNivel(const std::vector<std::string> &vector/*,
																const int idCliente*/);

		//Recibe el nombre de partida y genera el mensaje a enviar al server.
		const std::string generarMensajeDeUnionAPartida(const std::string &nombrePartida);

		//Recibe la informacion de las teclas UP-LEFT-DOWN-RIGHT-SPACE en ese orden y genera el mensaje
		//A enviar al server de las teclas que fueron presionadas por el jugador.
		const std::string generarMensajeTeclasPresionadas(const std::vector<bool>& teclas);
};

#endif /* COMMON_COMMON_PROTOCOLOCLIENTES_H_ */
