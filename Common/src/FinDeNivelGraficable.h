/*
 * FinDeNivelGraficable.h
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_FINDENIVELGRAFICABLE_H_
#define COMMON_SRC_FINDENIVELGRAFICABLE_H_
#include "ElementoGraficable.h"

class FinDeNivelGraficable : public ElementoGraficable{
public:
	FinDeNivelGraficable();
	std::string obtenerClaveImagen();
	const std::string obtenerRutaImagen();

	const int xSupIzq();

	const int ySupIzq();

	const int anchoDeColision();

	const int altoDeColision();

	//heredado de ElementoGraficable, no hace nada en esta entidad
	void setearSiEstaCayendo(bool cayendo){};
	//retorna siempre false
	const bool obtenerSiEstaCayendo();
	//No hace nada ya que un Fin de nivel no se mueve.
	void mover();

	//Colisiona con el elemento recibido por parámetro. Agrega eventos en caso de que
	//haya en el vector.
	void resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector);

	//No hace nada ya que la lógica ya la tiene la tortuga.
	void colisionar(Tortuga* tortuga,std::vector<Evento*>& vector);

	//No hace nada ya que la lógica ya la tiene el conejo.
	void colisionar(Conejo* conejo,std::vector<Evento*>& vector);

	//No hace nada ya que no pueden chocar.
	void colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector);

	//No hace nada ya que no pueden chocar.
	void colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector);

	//No hace nada ya que no pueden chocar.
	void colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector);

	//No hace nada.
	void colisionar(Bala* bala,std::vector<Evento*>& vector);

	void eventoParticulares(std::vector<Evento*>& eventos){}

	~FinDeNivelGraficable();
};

#endif /* COMMON_SRC_FINDENIVELGRAFICABLE_H_ */
