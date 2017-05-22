#include "LevantadorDeNivelesFunctor.h"
#include "ConversorDeNivelAModelo.h"
#include "../../Common/src/constantes.h"
#include "EventoMatcheo.h"

void LevantadorDeNivelesFunctor::operator()(const std::string& nombreNivel)
{
	ConversorDeNivelAModelo conversor;
	Nivel* nivel = this->partida.admin.obtenerPunteroANivel(nombreNivel);
	conversor.pasarInformacionAModelo(nivel,&this->partida);
	this->partida.notificar(this->partida.modelo.obtenerInformacion());
	this->enviarMatcheos(this->partida.modelo.obtenerMatcheos());
	this->partida.empezarNivel();
	this->partida.limpiar();
}


void LevantadorDeNivelesFunctor::enviarMatcheos(const std::map<int, int>& matcheo){
	std::map<int,int>::const_iterator it;
	for (it = matcheo.begin(); it != matcheo.end(); ++it ){
		Evento* evento = new EventoMatcheo((*it).first, (*it).second);
		this->partida.notificar(evento);
		delete evento;
	}

}
