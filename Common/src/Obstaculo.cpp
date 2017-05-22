#include "Obstaculo.h"


std::string Obstaculo::obtenerInformacion()
{
	std::string informacion("");
	informacion += this->pasarIntAString(this->id) + CARACTER_VACIO + this->tipoDeElemento +
				   CARACTER_VACIO + this->pasarIntAString(this->verticeSupIzqX) + CARACTER_VACIO +
				   this->pasarIntAString(this->verticeSupIzqY);
	return informacion;
}

