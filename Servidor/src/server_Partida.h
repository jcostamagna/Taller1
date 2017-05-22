/*
 * server_Partida.h
 *
 *  Created on: 29/10/2015
 *      Author: matiaskamien
 */

#ifndef TP_NUEVO_SERVIDOR_SERVER_PARTIDA_H_
#define TP_NUEVO_SERVIDOR_SERVER_PARTIDA_H_
#include <queue>
#include <string>
#include <vector>
#include "../../Common/src/GeneradorTortugaModelo.h"
#include "../../Common/src/Modelo.h"
#include "../../Common/src/Mutex.h"
#include "../../Common/src/Thread.h"
#include "GeneradorConejoModelo.h"
#include "Observable.h"
#include "../../Common/src/EventoTeclas.h"

class AdministradorDeNiveles;

//Esta clase va a encapsular la información de la partida.
class Partida: public Thread, public Observable{
private:
	friend class LevantadorDeNivelesFunctor;
	int idPartida;
	std::string nombre;
	unsigned int cantidadJugadores;
	unsigned int cantidadJugadoresParcial;
	Mutex mutex;
	Modelo modelo;
	bool estaViva, jugandoNivel;
	std::vector<std::string> niveles;
	std::vector<GeneradorTortugaModelo*> generadorTortugas;
	std::vector<GeneradorConejoModelo*> generadoresDeConejos;
	std::queue<EventoTeclas> eventos;
	AdministradorDeNiveles& admin;
	Partida(const Partida& object);
	Partida& operator=(const Partida& object);

	//Devuelve el primer generador de conejo disponible.
	void ponerEnDisponibleTodosLosGeneradores();

	//Devuelve el id del jugador que ganó la partida.
	const int obtenerIdGanadorPartida();

	//Devuelve los puntos hechos por el ganador de la partida.
	const int obtenerPuntajeGanador();
public:
	//Crea la partida y setea los niveles, la cantidad de jugadores y la cantidad de jugadores parcial.
	Partida(const std::vector<std::string>& niveles,const unsigned int cantidadJugadores,
												const std::string &nombre,  AdministradorDeNiveles& admin);

	//Agregar un generador de tortuga al vector de generadores de tortugas.
	void agregarGeneradorTortuga(GeneradorTortugaModelo* generadorTortuga);

	//Agregar un generador de conejo al vector de generadores de conejos.
	void agregarGeneradorConejo(GeneradorConejoModelo* generadorConejo);

	//Devuelve si se ejecutó el run de la partida.
	const bool vive();

	//Desasigna los matcheos de los observadores.
	void desactivarMatcheoObservadores();

	//Devuelve el id.
	const int obtenerIdPartida()const;

	//Devuelve una referencia del modelo.
	Modelo& obtenerModelo();

	//Devuelve el primer observador que no fue matcheado del vector.
	const Observador* obtenerObservadorAMatchear()const;

	//Devuelve el nombre de la partida.
	const std::string obtenerNombre()const;

	//Indica el fin del nivel
	void terminarNivel();

	//Devuelve la cantidad de jugadores que faltan para que empiece la partida.
	const unsigned int obtenerCantidadJugadoresFaltantes() const;

	//Devuelve la cantidad de jugadores de la partida.
	const int obtenerCantidadJugadores()const;

	//Devuelve true si faltan jugadores para que empiece la partida. False si está llena.
	const bool faltanJugadores() const;

	//Devuelve true si tiene todos los jugadores para que empiece la partida.
	const bool estaLlena();

	//Agrega un jugador a la partida, devuelve True si tuvo exito, False de lo contrario
	bool agregarJugador(Observador* jugador);

	//Devuelve una referencia del notificador.
	//Notificador& obtenerNotificador();

	//Setea el id de la partida.
	void setearId(const int idPartida);

	//Aumenta en uno la cantidad de jugadores parcial.
	void sumarJugador();

	//Encola un evento a la partida
	void encolarEvento(const EventoTeclas& evento);

	void procesarEventos();

	//Empieza el ciclo del nivel.
	void empezarNivel();

	//Limpia los vectores de generadores de conejos y tortugas y llama al limpiarModelo().
	void limpiar();

	/* Metodo del hilo que contiene el loop de la partida*/
	void run();

	//Libera la memoria de los vectores de generadores.
	~Partida();
};

#endif /* TP_NUEVO_SERVIDOR_SERVER_PARTIDA_H_ */
