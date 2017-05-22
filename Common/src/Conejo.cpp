/*
 * Conejo.cpp
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */
#include "Conejo.h"
#include "constantes.h"
#include <iostream>
#include "Bala.h"
#include "ObstaculoIrrompibleGraficable.h"
#include "ObstaculoRompibleGraficable.h"
#include "Tortuga.h"
#include "FinDeNivelGraficable.h"
#include "EventoNuevoPersonaje.h"
const int cantidadVidasConejo = 4;
const int velocidadXMaxima = 30;
const int deltaVerticeXColision = 25;
const int deltaVerticeYColision = 10;
const int anchoYAltoRectanguloColision = 60;
const int valorMovimientoBalaDerecha = 1;
const int valorMovimientoBalaIzquierda = -1;
const std::string IZQUIERDA("izquierda");
const std::string DERECHA("derecha");
const long int cantidadMaxCiclosSinSerAtacado=6;

Conejo::Conejo()
{
	this->tipoElemento = CONEJO;
	this->cantidadDeVidas = cantidadVidasConejo;
	this->aceleracionX = 0;
	this->velocidadX = 0;
	this->velocidadY = 0;
	this->puntaje = 0;
	this->disparo = false;
	this->saltando = false;
	this->estaCayendo = false;
	this->ultimaDireccionDerechaOIzquierda=DERECHA;
	this->fueLastimado = false;
	this->cantidadCiclosSinSerAtacado = cantidadMaxCiclosSinSerAtacado;
}

void Conejo::aumentarPuntaje(const int puntajeAAumentar)
{
	this->puntaje += puntajeAAumentar;
}

const int Conejo::obtenerPuntaje()
{
	return this->puntaje;
}

const std::string Conejo::obtenerRutaImagen()
{
	std::string ruta(RUTA_SERVER_EDITOR_IMAGENES SEPARADOR_DIRECTORIOS NOMBRE_IMAGEN_CONEJO);
	return ruta;
}

bool Conejo::estaVivo(){
	return this->cantidadDeVidas > 0;
}

void Conejo::eventoParticulares(std::vector<Evento*>& eventos){
	int direccion = valorMovimientoBalaDerecha;
	if ( !this->disparo)
	{
		return;
	}
	if (this->ultimaDireccionDerechaOIzquierda == IZQUIERDA){
		direccion = valorMovimientoBalaIzquierda;
	}else{
		if(this->ultimaDireccionDerechaOIzquierda == DERECHA)
		{
			direccion = valorMovimientoBalaDerecha;
		}
	}
	int posX = this->verticeSuperiorIzqX + anchoYAltoRectanguloColision/2 + anchoYAltoRectanguloColision*direccion;
	int posY = this->verticeSuperiorIzqY + anchoYAltoRectanguloColision/2;
	eventos.push_back(new EventoNuevoPersonaje(BALA, this->idElemento, posX, posY, direccion));
}

void Conejo::setearEjeHorizontal(const bool izquierda,const bool derecha){
	if ( ((izquierda)&&(derecha)) || ((!izquierda) && (!derecha))){
		this->aceleracionX = 0;
		this->velocidadX = 0;
		return;
	}
	if (izquierda) {
		this->ultimaDireccionDerechaOIzquierda = IZQUIERDA;
		this->aceleracionX = -ACELERACION;
	}
	else{
		this->ultimaDireccionDerechaOIzquierda = DERECHA;
		this->aceleracionX = ACELERACION;
	}
}

const int Conejo::xSupIzq()
{
	return this->verticeSuperiorIzqX+deltaVerticeXColision;
}

const int Conejo::ySupIzq()
{
	return this->verticeSuperiorIzqY+deltaVerticeYColision;
}

const int Conejo::anchoDeColision()
{
	return anchoYAltoRectanguloColision;
}

const int Conejo::altoDeColision()
{
	return anchoYAltoRectanguloColision;
}

void Conejo::setearEjeVertical(const bool arriba,const bool abajo){
	if(arriba && !this->saltando)
	{
		this->velocidadY = -VELOCIDAD_INICIAL_SALTO;
		this->saltando = true;
	}
}

void Conejo::procesarEvento(const EventoTeclas& evento)
{
	this->setearEjeHorizontal(evento.teclaIzquierda(), evento.teclaDerecha());
	this->setearEjeVertical(evento.teclaArriba(), evento.teclaAbajo());
	if(evento.teclaBarra())
	{
		this->disparo = true;
	}else{
		this->disparo = false;
	}
}

void Conejo::mover()
{
	this->velocidadY += GRAVEDAD;
	this->velocidadX += this->aceleracionX;
	if(this->velocidadX < -velocidadXMaxima){
		this->velocidadX = -velocidadXMaxima;
	}else if(this->velocidadX > velocidadXMaxima){
		this->velocidadX = velocidadXMaxima;
	}
	this->verticeSuperiorIzqXAnterior = this->verticeSuperiorIzqX;
	this->verticeSuperiorIzqYAnterior = this->verticeSuperiorIzqY;
	this->verticeSuperiorIzqX += this->velocidadX;
	this->verticeSuperiorIzqY += this->velocidadY;
}

const std::string& Conejo::obtenerColor()const
{
	return this->color;
}

void Conejo::setearColor(const std::string &color)
{
	this->color = color;
}

std::string Conejo::obtenerClaveImagen()
{
	return (this->tipoElemento + GUIONBAJO +
			this->obtenerDireccionDeUnMovimiento());
}

void Conejo::resolverColision(ElementoGraficable* elemento,std::vector<Evento*>& vector)
{
	elemento->colisionar(this,vector);
}

void Conejo::colisionar(Tortuga* tortuga,std::vector<Evento*>& vector)
{
	if(!fueLastimado)
	{
		--this->cantidadDeVidas;
		this->actualizarEstadoLuegoDeColision();
		tortuga->volverAPosicionAnterior();
		vector.push_back(new EventoConejoPerdioVida(this->idElemento));
		this->fueLastimado = true;
	}
	this->actualizarEstadoDeLastimado();
}

void Conejo::actualizarEstadoDeLastimado()
{
	--this->cantidadCiclosSinSerAtacado;
	if(this->cantidadCiclosSinSerAtacado == 0)
	{
		//lo pueden volver a atacar al conejo
		this->fueLastimado = false;
		this->cantidadCiclosSinSerAtacado = cantidadMaxCiclosSinSerAtacado;
	}
}

void Conejo::perderVida()
{
	--this->cantidadDeVidas;
}

void Conejo::puedeVolverASerLastimado()
{
	this->fueLastimado = false;
}

const std::string Conejo::obtenerInformacion()
{
	std::string informacion("");
	informacion += this->pasarIntAString(this->idElemento) + CARACTER_VACIO + this->tipoElemento
				   + CARACTER_VACIO + this->pasarIntAString(this->verticeSuperiorIzqX) +
				   CARACTER_VACIO + this->pasarIntAString(this->verticeSuperiorIzqY)+CARACTER_VACIO
				   + this->color;
	return informacion;
}

void Conejo::actualizarEstadoLuegoDeColision()
{
	if(this->volverAPosicionAnterior())
	{
		this->velocidadX = 0;
	}else{
		this->velocidadY = 0;
	}
	saltando = false;
}

void Conejo::colisionar(Conejo* conejo,std::vector<Evento*>& vector){}

void Conejo::colisionar(ObstaculoRompibleGraficable* obstaculoRompible,std::vector<Evento*>& vector)
{
	this->actualizarEstadoLuegoDeColision();
}

void Conejo::colisionar(ObstaculoIrrompibleGraficable* obstaculoIrrompible,std::vector<Evento*>& vector)
{
	this->actualizarEstadoLuegoDeColision();
}

void Conejo::colisionar(FinDeNivelGraficable* finDeNivel,std::vector<Evento*>& vector)
{
	vector.push_back(new EventoFinDeNivel(this->idElemento));
	this->puntaje += PUNTOS_POR_GANAR_NIVEL;
}

void Conejo::colisionar(Bala* bala,std::vector<Evento*>& vector)
{
	if(bala->obtenerConejoQueLaDisparo() != this)
	{
		--this->cantidadDeVidas;
		vector.push_back(new EventoConejoPerdioVida(this->idElemento));
		vector.push_back(new EventoElementoDestruido(bala->obtenerId()));
	}
}

void Conejo::setearSiEstaCayendo(bool cayendo)
{
	this->estaCayendo = cayendo;
}
const bool Conejo::obtenerSiEstaCayendo()
{
	return this->estaCayendo;
}

const int Conejo::obtenerCantidadVidas()
{
	return this->cantidadDeVidas;
}


Conejo::~Conejo()
{

}

