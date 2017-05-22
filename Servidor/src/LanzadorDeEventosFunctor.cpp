#include "LanzadorDeEventosFunctor.h"
#include "../../Common/src/constantes.h"
#include <iostream>
#include "../../Common/src/EventoElementoDestruido.h"
#include "../../Common/src/EventoNuevoPersonaje.h"
#include "../../Common/src/EventoConejoPerdioVida.h"
#include "../../Common/src/Bala.h"

typedef void (LanzadorDeEventosFunctor::*Funciones)(Evento* evento);

LanzadorDeEventosFunctor::LanzadorDeEventosFunctor(Partida& partida): partida(partida){
	this->tipoDeEventos.insert(std::make_pair(EVENTO_FIN_DE_NIVEL, &LanzadorDeEventosFunctor::finDeNivel));
	this->tipoDeEventos.insert(std::make_pair(EVENTO_DESTRUIR_PERSONAJE, &LanzadorDeEventosFunctor::destruirElemento));
	this->tipoDeEventos.insert(std::make_pair(EVENTO_NUEVO_PERSONAJE, &LanzadorDeEventosFunctor::nuevoElemento));
	this->tipoDeEventos.insert(std::make_pair(EVENTO_CONEJO_PERDIO_VIDA, &LanzadorDeEventosFunctor::limpiarConejos));
}

void LanzadorDeEventosFunctor::operator()(Evento* evento)
{
	if (this->tipoDeEventos[evento->tipoEvento()] != 0)
	{
		(this->*tipoDeEventos[evento->tipoEvento()])(evento);
	}
	this->partida.notificar(evento);
	delete evento;
}


void LanzadorDeEventosFunctor::finDeNivel(Evento* evento){
	partida.terminarNivel();
}

void LanzadorDeEventosFunctor::destruirElemento(Evento* evento){
	EventoElementoDestruido* eventoDestruir = (EventoElementoDestruido*)evento;
	this->partida.obtenerModelo().eliminarElemento(eventoDestruir->obenerId());
}

void LanzadorDeEventosFunctor::nuevoElemento(Evento* evento){
	EventoNuevoPersonaje* eventoNuevo = (EventoNuevoPersonaje*)evento;
	ElementoGraficable* elemento;
	std::string tipoDeElemento = eventoNuevo->obtenerTipoDeElemento();
	if (tipoDeElemento == TORTUGAVERDE || tipoDeElemento == TORTUGAROJA)
	{
		return;
	}
	if (tipoDeElemento == BALA)
	{
		elemento = new Bala();
	}
	int posX = eventoNuevo->obtenerPosX();
	int posY = eventoNuevo->obtenerPosY();
	int direccion = eventoNuevo->obtenerDireccion();
	elemento->setearVerticeSuperiorIzqX(posX);
	elemento->setearVerticeSuperiorIzqY(posY);
	Bala* bala = (Bala*) elemento;
	ElementoGraficable* elem = this->partida.obtenerModelo().obtenerElemento(eventoNuevo->obtenerId());
	Conejo* conejo = (Conejo*)elem;
	bala->setearConejoQueLaDisparo(conejo);
	bala->setearDireccion(direccion);
	int idElemento = 0;
	if(elemento)
	{
		idElemento = this->partida.obtenerModelo().agregarElementoGraficable(elemento);
	}
	delete evento;
	evento = new EventoNuevoPersonaje(tipoDeElemento, idElemento, posX, posY, direccion);
}

void LanzadorDeEventosFunctor::limpiarConejos(Evento* evento){
	EventoConejoPerdioVida* eventoVida = (EventoConejoPerdioVida*)evento;
	int id = eventoVida->obtenerId();
	if (this->partida.obtenerModelo().conejoVivo(id)) return;
	this->partida.notificar(evento);
	delete evento;
	this->partida.obtenerModelo().eliminarElemento(id);
	evento = new EventoElementoDestruido(id);
	if (!this->partida.obtenerModelo().chequearConejosVivos()){
		this->partida.terminarNivel();
	}
}
