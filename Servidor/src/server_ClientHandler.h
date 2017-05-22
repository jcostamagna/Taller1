
#ifndef SERVER_CLIENTHANDLER_H_
#define SERVER_CLIENTHANDLER_H_
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <sstream>
#include "server_Monitor.h"
#include "../../Common/src/common_ProtocoloClientes.h"
#include "Observador.h"
#include "Observable.h"
#include "../../Common/src/BlockingQueue.h"
#include "../../Common/src/Handler.h"

class ClientHandler: public Observador, public Handler {
public:
	/* Tipo de punteros a funciones usados para llamar a los distintos metodos*/
	typedef void (ClientHandler::*Funciones)(std::vector<std::string>&);
private:
	Monitor& monitor;
	Partida* partidaEnJuego;
	std::string respuesta;
	ProtocoloClientes protocolo;
	BlockingQueue<std::string> queue;
	int id;
	//Setea el map con las funciones.
	std::map<std::string, Funciones> setearMap();


	void identificarComandos(std::map<std::string, Funciones> map,
			std::vector<std::string> comandos);
	ClientHandler(const ClientHandler& object);
	ClientHandler& operator=(const ClientHandler& object);

	//Acola una "q".
	void salir(std::vector<std::string> &comandos);

	//Acola un string con los niveles.
	void obtenerNiveles(std::vector<std::string>& comandos);

	//Acola un string con el numero de jugadores que faltan para que empiece la partida.
	void obtenerCantidadJugadoresFaltantes(std::vector<std::string> &comandos);

	//Llena el vector de char con 0(verdadero) o 1(falso) según las teclas recibidas y lo devuelve.
	const std::vector<char> llenarVector(const std::vector<std::string> &vectorDeTeclas);

	//Manda el id al cliente.
	void asignarID(std::vector<std::string> &comandos);

	//Acola un string con las partidas.
	void obtenerPartidas(std::vector<std::string>& comandos);

	//Acola un string con la información del primer nivel de la partida.
	void iniciarPartida(std::vector<std::string> &comandos);

	//Devuelve los niveles separados por el separador del protocolo.
	const std::string procesarNiveles(const std::vector<std::string> &vectorDeNiveles);

	//Devuelve las partidas separadas por el separador del protocolo.
	const std::string procesarPartidas(const std::vector<Partida*> &vectorDePartidas);

	//Verifica si hay lugar para unirse a la partida y acola una respuesta.
	void verificarUnirseAPartida(std::vector<std::string> &comandos);

	//Devuelve el string recibido por parámetro en int.
	const int pasarStringAInt(const std::string &cadena);

	void entradaDeTeclas(std::vector<std::string> &comandos);

	//Devuelve el entero recibido por parámetro en string.
	const std::string pasarIntAString(const int entero);

public:
	//Setea en NULL el atributo partidaEnJuego.
	ClientHandler(Monitor& monitor,const int id);

	//Recibe el eveto de la partida
	void actualizar(const std::string& evento);

	//Devuelve el id.
	const int obtenerId()const;

	//Recibe eventos de la partida
	void actualizar(const std::vector<std::string>& eventos);

	void actualizar(const Evento* evento);

	//Procesa el mensaje recibido
	void realizarConsulta(const std::string& consulta);

	//devuelve la respuesta.
	std::string obtenerRespuesta();
};

#endif /* SERVER_CLIENTHANDLER_H_ */

