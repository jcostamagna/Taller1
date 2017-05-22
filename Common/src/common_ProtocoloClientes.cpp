/*
 * common_ProtocoloClientes.cpp
 *
 *  Created on: 29/10/2015
 *      Author: matiaskamien
 */
#include "common_ProtocoloClientes.h"
#include <iostream>
const char separadorPrincipal = '|';
const char separadorSecundario = '*';

ProtocoloClientes::ProtocoloClientes()
{
	this->separador = separadorPrincipal;
	this->separadorAuxiliar = separadorSecundario;
}

const char ProtocoloClientes::obtenerSeparador()
{
	return this->separador;
}

std::vector<std::string> ProtocoloClientes::split(const std::string& texto,const char separador)
{
	return this->parser.split(texto,separador);
}

const std::string ProtocoloClientes::obtenerSeparadorEnString()
{
	std::stringstream ss;
	ss << this->separador;
	return (ss.str());
}

const std::string ProtocoloClientes::pasarIntAString(const int entero)
{
	std::stringstream ss;
	ss << entero;
	return (ss.str());
}

const char ProtocoloClientes::obtenerSeparadorAuxiliar()
{
	return this->separadorAuxiliar;
}

const std::string ProtocoloClientes::obtenerSeparadorAuxiliarEnString()
{
	std::stringstream ss;
	ss << this->separadorAuxiliar;
	return (ss.str());
}

const std::string ProtocoloClientes::generarMensajeProtocolarPartida
				(const std::string &nombrePartida,const unsigned int cantidadJugadoresRestantes)
{
	std::string mensaje = nombrePartida + this->obtenerSeparadorAuxiliarEnString() +
						  this->pasarIntAString(cantidadJugadoresRestantes) + this->obtenerSeparadorEnString();
	return mensaje;
}

const std::string ProtocoloClientes::generarMensajeProtocolarNivel(const std::string &nombreNivel)
{
	std::string mensaje = nombreNivel + this->obtenerSeparadorEnString();
	return mensaje;
}

const std::string ProtocoloClientes::generarMensajeDeInicioDePartida(const std::vector<std::string> &niveles,
		const std::string &cantidadJugadores,const std::string &nombrePartida)
{
	std::string mensaje = INICIAR_PARTIDA;
	mensaje += this->obtenerSeparadorEnString() + nombrePartida
			 + this->obtenerSeparadorEnString() + cantidadJugadores + this->obtenerSeparadorEnString();
	for (unsigned int var = 0; var < niveles.size(); ++var)
	{
		mensaje += niveles[var] + this->obtenerSeparadorEnString();
	}
	mensaje = mensaje.substr(0,mensaje.size()-1);//Borra "|" final
	return mensaje;
}


const std::vector<std::string> ProtocoloClientes::parsearInformacionDeNivel(const std::string &informacionDelNivel)
{
	return this->parser.split(informacionDelNivel, this->separador);
}

const std::string ProtocoloClientes::generarMensajeInformacionNivel
									(const std::vector<std::string> &vector/*,const int idCliente*/)
{
	std::string mensaje("");
	//mensaje += this->pasarIntAString(idCliente) + this->obtenerSeparadorEnString();
	for (size_t var = 0; var < vector.size(); ++var)
	{
		std::vector<std::string> infoElemento = this->split(vector.at(var),CARACTER_VACIO_CHAR);
		for (unsigned int var = 0; var < infoElemento.size(); ++var)
		{
			mensaje += infoElemento.at(var) + this->obtenerSeparadorAuxiliarEnString();
		}
		mensaje = mensaje.substr(0,mensaje.size()-1);//Borra "*" final
		mensaje += this->obtenerSeparadorEnString();
	}
	mensaje = mensaje.substr(0,mensaje.size()-1);//Borra "|" final
	return mensaje;
}

const std::string ProtocoloClientes::generarPreguntaCantidadJugadores(const std::string &nombrePartida)
{
	std::string mensaje(OBTENER_CANTIDAD_JUGADORES_FALTANTES);
	mensaje += this->obtenerSeparadorEnString() + nombrePartida;
	return mensaje;
}

const std::string ProtocoloClientes::generarMensajeDeUnionAPartida(const std::string &nombrePartida)
{
	std::string mensaje = UNIRSE_A_PARTIDA + this->obtenerSeparadorEnString() +
						  nombrePartida;
	return mensaje;
}

const std::string ProtocoloClientes::generarMensajeTeclasPresionadas(const std::vector<bool>& teclas)
{
	std::string teclasPresionadas(ESTADO_TECLAS + this->obtenerSeparadorEnString());
	std::vector<bool>::const_iterator it;
	for (it = teclas.begin(); it !=teclas.end(); ++it)
	{
		if((*(it))==true)
		{
			teclasPresionadas+=VERDADERO;
		}else{
			teclasPresionadas+=FALSO;
		}
		teclasPresionadas+=this->obtenerSeparadorAuxiliar();
	}
	teclasPresionadas = teclasPresionadas.substr(0,teclasPresionadas.size()-1);//Borra "*" final
	return teclasPresionadas;
}


