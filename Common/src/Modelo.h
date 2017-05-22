/*
 * client_Modelo.h
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_MODELO_H_
#define COMMON_SRC_MODELO_H_
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "common_Parser.h"
#include "Conejo.h"
#include "FinDeNivelGraficable.h"
#include "ObstaculoIrrompibleGraficable.h"
#include "ObstaculoRompibleGraficable.h"
#include "TortugaRoja.h"
#include "TortugaVerde.h"
#include "ColectorEventosParticulares.h"

class Modelo {
public:
	/* Tipo de punteros a funciones usados para llamar a los distintos metodos*/
	typedef ElementoGraficable* (Modelo::*Funciones)();

private:
	std::vector<ElementoGraficable*> elementos;
	std::map<std::string,Funciones> mapDeFunciones;
	std::map<int,int> macheoClientes;
	std::map<int,int> macheoPuntajes;
	bool yaFueCreadoMapDePuntajes;
	int altoDeNivel, anchoDeNivel;
	Parser parser;
	int idElementos;
	int cantidadJugadores;
	ElementoGraficable* generarInstanciaConejo();
	ElementoGraficable* generarInstanciaTortugaRoja();
	ElementoGraficable* generarInstanciaTortugaVerde();
	ElementoGraficable* generarInstanciaObstaculoRompible();
	ElementoGraficable* generarInstanciaObstaculoIrrompible();
	ElementoGraficable* generarInstanciaFinDeNivel();
	void agregarElementoAlModelo(ElementoGraficable* elemento,const std::vector<std::string>& vector);
	//ElementoGraficable* agregarFinDeNivel(const std::vector<std::string>& vector);
	const int pasarStringAInt(const std::string &string);

	const std::string pasarIntAString(const int entero);

	//Agrega al map todos los jugadores de la partida.
	void crearMapDePuntajes();

	Modelo(const Modelo& object);
	Modelo& operator=(const Modelo& object);
public:
	Modelo();

	//Actualiza los puntajes de todos los jugadores al finalizar cada nivel.
	void actualizarPuntajes();

	void setearAnchoNivel(const int anchoNivel);

	void setearAltoNivel(const int altoNivel);

	//agregar un elemento graficable al vector elementos
	int agregarElementoGraficable(ElementoGraficable* elemento);

	//Devuelve el Id del ganador de la partida.
	const int obtenerIdGanador();

	//Devuelve los puntos hechos por el ganador de la partida.
	const int obtenerPuntajeGanador();

	//Devuelve el elemento graficable cuyo id es recibido por parámetro.
	ElementoGraficable* obtenerElemento(const int id);

	std::vector<ElementoGraficable*>& obtenerElementosParaModificacion();

	//Setea la cantidad de jugadores.
	void setearCantidadJugadores(const int cantidadJugadores);

	//Devuelve un vector con los elementos del modelo.
	const std::vector<std::string> obtenerInformacion();

	//Elimina del modelo el elemento cuyo id es recibido por parámetro.
	void eliminarElemento(const int idElemento);

	//Agrega un elemento al vector de elementos graficables.
	void agregarElemento(const std::string &informacionElemento);

	//Devuelve una referencia constante del vector de elementos graficables.
	const std::vector<ElementoGraficable*>& obtenerElementos()const;

	//Setea los nuevos matcheos del modelo
	void setearMatcheos(const std::map<int,int> matcheos);

	//Recibe el id del cliente con las teclas presionadas
	void moverElemento(const EventoTeclas& evento);

	//Recorre todos los elementos chequeando colisiones
	void chequearColisiones(std::vector<Evento*>& eventos);

	//Colecciona eventos particulares que queden por recolectar
	void eventosParticulares(std::vector<Evento*>& eventos);

	//Llama a mover a todos los personajes del modelo
	void eventosMover();

	//Devuelve true si el conejo esta vivo
	bool conejoVivo(int idConejo);

	//Chequea si quedan conejos vivos
	bool chequearConejosVivos();

	//Obtener matcheos
	const std::map<int,int>& obtenerMatcheos();

	//Colecciona los eventos de los movimientos de los personajes
	std::vector<Evento*> colectarEventosMover();

	//Devuelve el id actual
	const int obtenerIdActual();

	//Limpia el vector de elementos, liberando la memoria correspondiente.
	void limpiar();

	~Modelo();
};

#endif /* COMMON_SRC_MODELO_H_ */
