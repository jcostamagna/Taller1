/*
 * ElementoGraficable.h
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */
#ifndef COMMON_SRC_ELEMENTOGRAFICABLE_H_
#define COMMON_SRC_ELEMENTOGRAFICABLE_H_
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <cmath>
#include "constantes.h"
#include "EventoTeclas.h"
#include "EventoElementoDestruido.h"

class Bala;
class ObstaculoIrrompibleGraficable;
class ObstaculoRompibleGraficable;
class Conejo;
class Tortuga;
class FinDeNivelGraficable;

class ElementoGraficable {
protected:
	int idElemento;
	std::string tipoElemento;
	int verticeSuperiorIzqX;
	int verticeSuperiorIzqY;
	int verticeSuperiorIzqXAnterior;
	int verticeSuperiorIzqYAnterior;
	int indiceImagen;
	ElementoGraficable(const ElementoGraficable& object);
	ElementoGraficable& operator=(const ElementoGraficable& object);

	//Devuelve en string el entero recibido por parametro.
	const std::string pasarIntAString(const int entero);

	virtual void setearSiEstaCayendo(bool cayendo)=0;
	virtual const bool obtenerSiEstaCayendo()=0;
public:
	ElementoGraficable();
	void setearId(const int id);
	void setearTipoElemento(const std::string &tipoElemento);
	void setearVerticeSuperiorIzqX(const int verticeSuperiorIzqX);
	void setearVerticeSuperiorIzqY(const int verticeSuperiorIzqY);
	int obtenerVerticeSuperiorIzqX()const;
	virtual const std::string obtenerInformacion();
	int obtenerVerticeSuperiorIzqY()const;
	std::string obtenerTipoElemento();
	//Mueve el elemento a las nuevas posiciones.
	void mover(const int posX,const int posY);

	//Devuelve el id del elemento.
	const int obtenerId()const;

	//Mueve el elemento con un evento.
	virtual void mover()=0;

	//Chequea si las coordenadas anterior son iguales a las actuales. De ser así, devuelve false.
	const bool seMovio();

	//Devuelve la coordenada x del vértice superior izquierdo que va a ser utilizado para verificar
	//colisiones.
	virtual const int xSupIzq()=0;

	//Devuelve la coordenada y del vértice superior izquierdo que va a ser utilizado para verificar
	//colisiones.
	virtual const int ySupIzq()=0;

	//Devuelve el ancho del elemento que va a ser tomado en cuenta para verificar colisiones.
	virtual const int anchoDeColision()=0;

	//Devuelve el alto del elemento que va a ser tomado en cuenta para verificar colisiones.
	virtual const int altoDeColision()=0;

	//Devuelve si el elemento colisionó con el elemento recibido por parámetro.
	const bool validarColision(ElementoGraficable* elemento);

	//Colisiona con el elemento recibido por parámetro. Agrega eventos en caso de que
	//haya en el vector.
	virtual void resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector)=0;

	//Acá va a estar la lógica sobre que hacer en caso de que haya colisión con un conejo.
	virtual void colisionar(Conejo* elemento,std::vector<Evento*>& vector)=0;

	//Acá va a estar la lógica sobre que hacer en caso de que haya colisión con un conejo.
	virtual void colisionar(FinDeNivelGraficable* elemento,std::vector<Evento*>& vector)=0;

	//Acá va a estar la lógica sobre que hacer en caso de que haya colisión con un conejo.
	virtual void colisionar(ObstaculoIrrompibleGraficable* elemento,std::vector<Evento*>& vector)=0;

	//Acá va a estar la lógica sobre que hacer en caso de que haya colisión con un conejo.
	virtual void colisionar(ObstaculoRompibleGraficable* elemento,std::vector<Evento*>& vector)=0;

	//Acá va a estar la lógica sobre que hacer en caso de que haya colisión con un conejo.
	virtual void colisionar(Tortuga* elemento,std::vector<Evento*>& vector)=0;

	//Acá va a estar la lógica sobre que hacer en caso de que haya colisión con un conejo.
	virtual void colisionar(Bala* elemento,std::vector<Evento*>& vector)=0;

	//El elemento vuelve a la posición anterior. Devuelve true si colisionó en el eje horizontal.
	//Devuelve false si colisionó en el eje vertical.
	const bool volverAPosicionAnterior();

	virtual void eventoParticulares(std::vector<Evento*>& eventos) = 0;

	int obtenerVerticeSuperiorIzqXAnterior()const;
	int obtenerVerticeSuperiorIzqYAnterior()const;
	void setearVerticeSuperiorIzqXAnterior(const int x);
	void setearVerticeSuperiorIzqYAnterior(const int y);
	const std::string obtenerDireccionDeUnMovimiento();
	virtual std::string obtenerClaveImagen()=0;
	//Devuelve el indice de la imagen a graficar e incrementa el indice.
	const int obtenerIndiceImagen();

	virtual ~ElementoGraficable();
};

#endif /* COMMON_SRC_ELEMENTOGRAFICABLE_H_ */
