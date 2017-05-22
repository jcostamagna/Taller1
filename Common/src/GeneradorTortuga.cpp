#include "GeneradorTortuga.h"

void GeneradorTortuga::setFrecuenciaGeneracion(int frecuenciaGeneracion)
{
	this->frecuenciaGeneracion=frecuenciaGeneracion;
}

int GeneradorTortuga::obtenerFrecuenciaGeneracion()
{
	return this->frecuenciaGeneracion;
}

std::string GeneradorTortuga::obtenerInformacion()
{
	std::string informacion("");
	informacion += this->pasarIntAString(this->id) + CARACTER_VACIO + this->tipoDeElemento +
				   CARACTER_VACIO + this->pasarIntAString(this->verticeSupIzqX) + CARACTER_VACIO +
				   this->pasarIntAString(this->verticeSupIzqY) + CARACTER_VACIO +
				   this->pasarIntAString(this->frecuenciaGeneracion) + CARACTER_VACIO + this->pasarIntAString(this->cantidadMaxima);
	return informacion;
}

int GeneradorTortuga::obtenerCantidadMaxima()
{
	return this->cantidadMaxima;
}

void GeneradorTortuga::setCantidadMaxima(int cantidadMaxima)
{
	this->cantidadMaxima=cantidadMaxima;
}

