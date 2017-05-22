/*
 * Conejo.h
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_CONEJO_H_
#define COMMON_SRC_CONEJO_H_
#include "ElementoGraficable.h"
#include "EventoConejoPerdioVida.h"
#include "EventoFinDeNivel.h"
#include "Arma.h"

class Conejo : public ElementoGraficable{
private:
	int cantidadDeVidas;
	std::string color;
	float aceleracionX, velocidadX, velocidadY;
	bool disparo, saltando;
	int puntaje;
	bool estaCayendo;
	Arma arma;
	void setearEjeHorizontal(const bool izquierda,const bool derecha);
	void setearEjeVertical(const bool arriba,const bool abajo);
	void actualizarEstadoDeLastimado();
	std::string ultimaDireccionDerechaOIzquierda;
	//Deja al conejo en un estado válido luego de la colisión.
	void actualizarEstadoLuegoDeColision();
	bool fueLastimado;
	int cantidadCiclosSinSerAtacado;
	void setearSiEstaCayendo(bool cayendo);
	const bool obtenerSiEstaCayendo();

public:
	//Setea la cantidad de vidas y el arma inicial.
	Conejo();

	//Pierde una vida el conejo.
	void perderVida();

	const int xSupIzq();

	const int ySupIzq();

	const int anchoDeColision();

	const int altoDeColision();

	//Setea el atributo color.
	void setearColor(const std::string &color);

	//Aumenta el puntaje del conejo.
	void aumentarPuntaje(const int puntajeAAumentar);

	const int obtenerPuntaje();

	//Redefine el método de ElementoGraficable ya que devuelve su color también.
	const std::string obtenerInformacion();

	//Actualiza la posición del conejo.
	void mover();

	//Actualiza la posición del conejo.
	void procesarEvento(const EventoTeclas& evento);

	//Colisiona con el elemento recibido por parámetro. Agrega eventos en caso de que
	//haya en el vector.
	void resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector);

	//Resta una vida, vuelven los dos a la posición anterior y agrega un evento indicando
	//que perdió una vida.
	void colisionar(Tortuga* tortuga,std::vector<Evento*>& vector);

	//No hace nada ya que los conejos no chocan entre si.
	void colisionar(Conejo* conejo,std::vector<Evento*>& vector);

	//Vuelve a la posición anterior.
	void colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector);

	//Vuelve a la posición anterior.
	void colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector);

	//Agrega un evento de fin de nivel en el vector.
	void colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector);

	//Resta una vida y agrega un evento indicando que perdió una vida y otro indicando que
	//se debe destruir a la bala.
	void colisionar(Bala* bala,std::vector<Evento*>& vector);


	//Agrega el evento de disparo
	void eventoParticulares(std::vector<Evento*>& eventos);

	const std::string obtenerRutaImagen();

	bool estaVivo();

	//Devuelve el color del conejo.
	const std::string& obtenerColor()const;

	std::string obtenerClaveImagen();

	const int obtenerCantidadVidas();

	//pone el booleano fueLastimado en false
	void puedeVolverASerLastimado();

	~Conejo();
};

#endif /* COMMON_SRC_CONEJO_H_ */
