#include "server_BaseDeDatos.h"

BaseDeDatos::BaseDeDatos(){
	this->idPartida = 1;
}

const std::vector<Partida*>& BaseDeDatos::obtenerPartidas()
{
	return this->partidas;
}

bool BaseDeDatos::agregarPartida(Partida* partida)
{
	if(this->yaExistePartidaConMismoNombre(partida->obtenerNombre()))
	{
		return false;
	}else{
		partida->setearId(this->idPartida);
		this->partidas.push_back(partida);
		++this->idPartida;
		return true;
	}
}

bool BaseDeDatos::yaExistePartidaConMismoNombre(const std::string &nombre)
{
	bool yaExiste = false;
	for (unsigned int var = 0; var < this->partidas.size(); ++var)
	{
		if(nombre == this->partidas.at(var)->obtenerNombre())
		{
			yaExiste = true;
			break;
		}
	}
	return yaExiste;
}

Partida* BaseDeDatos::obtenerPartida(const std::string &nombrePartida)
{
	Partida* punteroADevolver = NULL;
	std::vector<Partida*>::iterator it;
	for (it = this->partidas.begin(); it != this->partidas.end(); ++it)
	{
		if(nombrePartida == (*it)->obtenerNombre())
		{
			punteroADevolver = (*it);
			break;
		}
	}
	return punteroADevolver;
}

void eliminarPartida(Partida* partida)
{
	if(partida->vive())
	{
		partida->join();
	}
	delete partida;
}

BaseDeDatos::~BaseDeDatos()
{
	std::for_each(this->partidas.begin(), this->partidas.end(), eliminarPartida);
}

