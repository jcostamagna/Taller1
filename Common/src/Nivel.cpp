#include "Nivel.h"
#include "tinyxml.h"
#include "PersistidorFunctor.h"
#include "CopiadorFunctor.h"

Nivel::Nivel(const std::string& nombre, const int& ancho, const int& alto):nombre(nombre),
	alto(alto),ancho(ancho)
{
	this->idElemento = 0;
	this->colores.push_back(COLOR_ROJO);
	this->colores.push_back(COLOR_CELESTE);
	this->colores.push_back(COLOR_AMARILLO);
	this->colores.push_back(COLOR_VERDE);
	this->colores.push_back(COLOR_VIOLETA);
	this->posicionColorASetear = 0;
}

GeneradorConejo* Nivel::obtenerGeneradorConejo()
{
	GeneradorConejo* generador = NULL;
	bool hayGeneradorDisponible = false;
	std::vector<GeneradorConejo*>::iterator it;
	for (it = this->conejos.begin(); it != this->conejos.end(); ++it)
	{
		if((*it)->estaDisponible())
		{
			generador = (*it);
			(*it)->ponerNoDisponible();
			hayGeneradorDisponible = true;
		}
	}
	if(hayGeneradorDisponible)
	{
		return generador;
	}else{
		this->ponerEnDisponibleTodosLosGeneradores();
		return this->obtenerGeneradorConejo();
	}
}

void Nivel::ponerEnDisponibleTodosLosGeneradores()
{
	std::vector<GeneradorConejo*>::iterator it;
	for (it = this->conejos.begin(); it != this->conejos.end(); ++it)
	{
		(*it)->ponerComoDisponible();
	}
}

int Nivel::obtenerAnchoNivel() const
{
	return this->ancho;
}

const int Nivel::obtenerPosicionColor()const
{
	return this->posicionColorASetear;
}

void Nivel::aumentarPosicionColor()
{
	if(this->posicionColorASetear < (int)this->colores.size()-1)
	{
		++this->posicionColorASetear;
	}else{
		this->posicionColorASetear = 0;
	}
}

int Nivel::obtenerAltoNivel() const
{
	return this->alto;
}

Nivel::Nivel (const Nivel& object){
	this->nombre = object.nombre;
	this->alto = object.alto;
	this->ancho = object.ancho;
	this->idElemento = 0;
	CopiadorFunctor copiador(*this);
	std::for_each(object.elementos.begin(), object.elementos.end(), copiador);
	std::for_each(object.generadoresTortugas.begin(), object.generadoresTortugas.end(), copiador);
	std::for_each(object.conejos.begin(), object.conejos.end(), copiador);
	this->colores.push_back(COLOR_ROJO);
	this->colores.push_back(COLOR_CELESTE);
	this->colores.push_back(COLOR_AMARILLO);
	this->posicionColorASetear = 0;
}

const std::vector<std::string>& Nivel::obtenerColores() const
{
	return this->colores;
}

const std::string Nivel::obtenerNombre()const
{
	return this->nombre;
}

void Nivel::agregarElemento(Elemento* elemento)
{
	elemento->setearId(this->idElemento);
	++this->idElemento;
	this->elementos.push_back(elemento);
}

void Nivel::agregarGenerador(GeneradorTortuga* generador){
	generador->setearId(this->idElemento);
	++this->idElemento;
	this->generadoresTortugas.push_back(generador);
}

void Nivel::agregarGenerador(GeneradorConejo* conejo){
	conejo->setearId(this->idElemento);
	++this->idElemento;
	this->conejos.push_back(conejo);
}

void eliminarElemento(Elemento* elemento){
	delete elemento;
}

void Nivel::obtenerInformacion(std::vector<std::string> &vector)
{
	std::vector<Elemento*>::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it)
	{
		vector.push_back((*it)->obtenerInformacion());
	}

	std::vector<GeneradorConejo*>::iterator itConejo;
	for (itConejo = this->conejos.begin(); itConejo != this->conejos.end(); ++itConejo)
	{
		vector.push_back((*itConejo)->obtenerInformacion());
	}

	std::vector<GeneradorTortuga*>::iterator itTortuga;
	for (itTortuga = this->generadoresTortugas.begin(); itTortuga != this->generadoresTortugas.end(); ++itTortuga)
	{
		vector.push_back((*itTortuga)->obtenerInformacion());
	}
}

const std::vector<Elemento*>& Nivel::obtenerElementos() const
{
	return this->elementos;
}

const std::vector<GeneradorTortuga*>& Nivel::obtenerTortugas() const
{
	return this->generadoresTortugas;
}

const std::vector<GeneradorConejo*>& Nivel::obtenerConejos() const
{
	return this->conejos;
}

const std::string Nivel::pasarIntAString(const int entero)
{
	std::stringstream ss;
	ss << entero;
	return (ss.str());
}


Nivel::~Nivel(){
	std::for_each(this->elementos.begin(), this->elementos.end(), eliminarElemento);
	std::for_each(this->generadoresTortugas.begin(), this->generadoresTortugas.end(), eliminarElemento);
	std::for_each(this->conejos.begin(), this->conejos.end(), eliminarElemento);
}


