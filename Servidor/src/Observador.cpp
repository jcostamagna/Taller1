#include "Observador.h"

Observador::Observador()
{
	this->yaFueMatcheado = false;
}

const bool Observador::fueMatcheado()
{
	return this->yaFueMatcheado;
}

void Observador::desasignarMatcheo()
{
	this->yaFueMatcheado = false;
}

void Observador::asignarMatcheo()
{
	this->yaFueMatcheado = true;
}
