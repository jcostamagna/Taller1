#include "ConversorDeTeclasFunctor.h"
#include "../../Common/src/constantes.h"
#include <iostream>
const char verdadero = 0;
const char falso = 1;

ConversorDeTeclasFunctor::ConversorDeTeclasFunctor() {}

void ConversorDeTeclasFunctor::operator()(const std::string& tecla)
{
	if (tecla == TECLA_PRESIONADA)
	{
		this->teclas.push_back(verdadero);
	}else{
		this->teclas.push_back(falso);
	}
}

std::vector<char>& ConversorDeTeclasFunctor::mapaDeTeclas()
{
	return this->teclas;
}
