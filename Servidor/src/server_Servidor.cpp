
#include "server_Servidor.h"

#include <iostream>
#include <string>
#include <glog/logging.h>
#define SALIR "q"

Servidor::Servidor(int puerto, AdministradorDeNiveles& admin): monitor(admin), aceptador(puerto,monitor){}

bool Servidor::comenzar(){
	this->aceptador.start();
	std::string mensaje;
	std::getline(std::cin,mensaje);
	while (mensaje != SALIR){
		std::getline(std::cin,mensaje);
	}
	this->aceptador.terminarProceso();
	this->aceptador.join();
	return true;
}

