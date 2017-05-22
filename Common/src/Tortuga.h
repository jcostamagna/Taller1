/*
 * Tortuga.h
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_TORTUGA_H_
#define COMMON_SRC_TORTUGA_H_
#include "ElementoGraficable.h"

class Tortuga : public ElementoGraficable {
protected:
	int cantidadDeVidas;
	int velocidad;
	bool estaCayendo;

	void setearSiEstaCayendo(bool cayendo);
	const bool obtenerSiEstaCayendo();

	//Actualiza la posición de la tortuga.
	void mover();

	const int xSupIzq();

	const int ySupIzq();

	const int anchoDeColision();

	const int altoDeColision();

	//Colisiona con el elemento recibido por parámetro. Agrega eventos en caso de que
	//haya en el vector.
	void resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector);

	//Cambia de dirección.
	void colisionar(Tortuga* tortuga,std::vector<Evento*>& vector);

	//No hace nada ya que la lógica ya la tiene el conejo.
	void colisionar(Conejo* conejo,std::vector<Evento*>& vector);

	//Vuelve a la posición anterior.
	void colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector);

	//Vuelve a la posición anterior.
	void colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector);

	//No hace nada.
	void colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector);

	//Agrega un evento evento indicando que hay que destruir a la tortuga y otro indicando
	//que hay que destruir la bala.
	void colisionar(Bala* bala,std::vector<Evento*>& vector);
	void eventoParticulares(std::vector<Evento*>& eventos){}

public:
	void volverAPosicionAnteriorTortuga();

	//Devuelve la cantidad de puntos que ganará el conejo que la mate.
	virtual const int obtenerPuntosPorMorir()=0;
};

#endif /* COMMON_SRC_TORTUGA_H_ */
