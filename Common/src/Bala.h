/*
 * Bala.h
 *
 *  Created on: 29/11/2015
 *      Author: matiaskamien
 */
#ifndef COMMON_SRC_BALA_H_
#define COMMON_SRC_BALA_H_
#include "ElementoGraficable.h"

class Bala : public ElementoGraficable {
private:
	int direccion;
	Conejo* conejoQueDisparo;
public:
	Bala();

	//Setea el conejo que disparó la bala.
	void setearConejoQueLaDisparo(Conejo* conejo);

	const int xSupIzq();

	const int ySupIzq();

	const int anchoDeColision();

	const int altoDeColision();

	//Colisiona con el elemento recibido por parámetro. Agrega eventos en caso de que
	//haya en el vector.
	void resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector);

	//No hace nada ya que la lógica ya la tiene la tortuga.
	void colisionar(Tortuga* tortuga,std::vector<Evento*>& vector);

	//No hace nada ya que la lógica ya la tiene el conejo.
	void colisionar(Conejo* conejo,std::vector<Evento*>& vector);

	//Se destruye la bala y el obstaculo agregando los eventos correspondientes al vector.
	void colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector);

	//Se destruye la bala agregando el evento correspondiente al vector.
	void colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector);

	//No hace nada.
	void colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector);

	//No hace nada.
	void colisionar(Bala* bala,std::vector<Evento*>& vector);

	//Aumenta la posición de la bala sumandole la velocidad que es constante.
	void mover();

	//Setea la dirección de la bala. 1 para la derecha. -1 para la izquierda.
	void setearDireccion(int direccion);

	void eventoParticulares(std::vector<Evento*>& eventos){}

	//heredado de ElementoGraficable, no hace nada en esta entidad
	void setearSiEstaCayendo(bool cayendo){};
	//retorna siempre false
	const bool obtenerSiEstaCayendo();

	//Devuelve el conejo que disparó la bala.
	Conejo* obtenerConejoQueLaDisparo();

	std::string obtenerClaveImagen();

	~Bala();
};

#endif /* COMMON_SRC_BALA_H_ */
