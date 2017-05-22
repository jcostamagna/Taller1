#include "../../Common/src/constantes.h"
#include "ElementoGraficable.h"
#include <iostream>
const std::string DERECHA = "derecha";
const std::string IZQUIERDA = "izquierda";
const std::string SALTO_SUBIENDO = "salto_subiendo";
const std::string SALTO_CAYENDO = "salto_cayendo";
const std::string SALTO_CAIDA = "salto_caida";
const std::string ARRIBA = "arriba";
const std::string ABAJO = "abajo";
const std::string PARADO = "parado";
const int cantidadImagenes = 4;

ElementoGraficable::ElementoGraficable()
{
	this->idElemento = 0;
	this->verticeSuperiorIzqX = 0;
	this->verticeSuperiorIzqY = 0;
	this->verticeSuperiorIzqXAnterior = this->verticeSuperiorIzqX;
	this->verticeSuperiorIzqYAnterior = this->verticeSuperiorIzqY;
	this->indiceImagen=0;
}

void ElementoGraficable::mover(const int posX,const int posY)
{
	this->verticeSuperiorIzqXAnterior = this->verticeSuperiorIzqX;
	this->verticeSuperiorIzqYAnterior = this->verticeSuperiorIzqY;
	this->verticeSuperiorIzqX = posX;
	this->verticeSuperiorIzqY = posY;
}

void ElementoGraficable::setearId(const int id)
{
	this->idElemento = id;
}

void ElementoGraficable::setearTipoElemento(const std::string &tipoElemento)
{
	this->tipoElemento = tipoElemento;
}

void ElementoGraficable::setearVerticeSuperiorIzqX(const int verticeSuperiorIzqX)
{
	this->verticeSuperiorIzqX = verticeSuperiorIzqX;
}

void ElementoGraficable::setearVerticeSuperiorIzqY(const int verticeSuperiorIzqY)
{
	this->verticeSuperiorIzqY = verticeSuperiorIzqY;
}


int ElementoGraficable::obtenerVerticeSuperiorIzqX()const
{
	return this->verticeSuperiorIzqX;
}

const std::string ElementoGraficable::pasarIntAString(const int entero)
{
	std::stringstream ss;
	ss << entero;
	return (ss.str());
}

const int ElementoGraficable::obtenerId()const
{
	return this->idElemento;
}

void mover(const EventoTeclas& evento){
}

const std::string ElementoGraficable::obtenerInformacion()
{
	std::string informacion("");
	informacion += this->pasarIntAString(this->idElemento) + CARACTER_VACIO + this->tipoElemento
				   + CARACTER_VACIO + this->pasarIntAString(this->verticeSuperiorIzqX) +
				   CARACTER_VACIO + this->pasarIntAString(this->verticeSuperiorIzqY);
	return informacion;
}

int ElementoGraficable::obtenerVerticeSuperiorIzqY()const
{
	return this->verticeSuperiorIzqY;
}

int ElementoGraficable::obtenerVerticeSuperiorIzqXAnterior()const
{
	return this->verticeSuperiorIzqXAnterior;
}

int ElementoGraficable::obtenerVerticeSuperiorIzqYAnterior()const
{
	return this->verticeSuperiorIzqYAnterior;
}

void ElementoGraficable::setearVerticeSuperiorIzqXAnterior(const int x)
{
	this->verticeSuperiorIzqXAnterior = x;
}

void ElementoGraficable::setearVerticeSuperiorIzqYAnterior(const int y)
{
	this->verticeSuperiorIzqYAnterior = y;
}

const bool ElementoGraficable::validarColision(ElementoGraficable* elemento)
{
	int xElemIzq = elemento->xSupIzq();
	int xElemDer = elemento->xSupIzq()+elemento->anchoDeColision();
	int yElemSup = elemento->ySupIzq();
	int yElemInf = elemento->ySupIzq()+elemento->altoDeColision();
	int xIzq = this->xSupIzq();
	int xDer = this->xSupIzq()+this->anchoDeColision();
	int ySup = this->ySupIzq();
	int yInf = this->ySupIzq()+this->altoDeColision();

	if(yElemSup >= yInf || yElemInf <= ySup)
	{
		return false;
	}
	if(xElemIzq >= xDer || xElemDer <= xIzq)
	{
		return false;
	}
	return true;
}

const bool ElementoGraficable::volverAPosicionAnterior()
{
	//Si entra al if, la colisión es en el eje horizontal.
	if(this->verticeSuperiorIzqY == this->verticeSuperiorIzqYAnterior)
	{
		this->verticeSuperiorIzqX = this->verticeSuperiorIzqXAnterior;
		return true;
	}else{
		this->verticeSuperiorIzqY = this->verticeSuperiorIzqYAnterior;
		return false;
	}
}

const bool ElementoGraficable::seMovio()
{
	if(this->verticeSuperiorIzqX == this->verticeSuperiorIzqXAnterior &&
	   this->verticeSuperiorIzqY == this->verticeSuperiorIzqYAnterior)
	{
		return false;
	}else{
		return true;
	}
}


const std::string ElementoGraficable::obtenerDireccionDeUnMovimiento()
{
	if(this->verticeSuperiorIzqXAnterior < this->verticeSuperiorIzqX)
	{
		return DERECHA;
	}
	if(this->verticeSuperiorIzqX < this->verticeSuperiorIzqXAnterior)
	{
		return IZQUIERDA;
	}
	if(this->verticeSuperiorIzqYAnterior > this->verticeSuperiorIzqY )
	{
		return SALTO_SUBIENDO;
	}
	if(this->verticeSuperiorIzqYAnterior < this->verticeSuperiorIzqY )
	{
		this->setearSiEstaCayendo(true);
		return SALTO_CAYENDO;
	}
	if(this->verticeSuperiorIzqX == this->verticeSuperiorIzqXAnterior &&
			this->obtenerSiEstaCayendo())
	{
		this->setearSiEstaCayendo(false);
		return SALTO_CAIDA;
	}
	this->setearSiEstaCayendo(false);
	return PARADO;
}

std::string ElementoGraficable::obtenerTipoElemento()
{
	return this->tipoElemento;
}

const int ElementoGraficable::obtenerIndiceImagen()
{
	int indiceActual = this->indiceImagen;
	++this->indiceImagen;
	if(this->indiceImagen==cantidadImagenes)
	{
		this->indiceImagen=0;
	}
	return indiceActual;
}


ElementoGraficable::~ElementoGraficable()
{

}

