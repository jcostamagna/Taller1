/*
 * server_AceptadorTh.cpp
 *
 *  Created on: 21 Sep 2015
 *      Author: osboxes
 */

#include "server_AceptadorTh.h"
#include <list>
#include <algorithm>
#include "server_HiloMuerto.h"
#include <glog/logging.h>

typedef bool (AceptadorTh::*Funciones)(Client* cliente);

AceptadorTh::AceptadorTh(int puerto,Monitor &monitor) : monitor(monitor)
{
	if (!this->aceptadorClientes.enlazar(puerto)) LOG(INFO)<<"Ocurrio un problema al enlazar";
	this->keepAlive = true;
	this->idCliente = 0;
}

bool AceptadorTh::hiloMurio(Client* cliente) const{
	if (cliente->sigueVivo()) return false;
	cliente->terminarProceso();
	cliente->join();
	delete cliente;
	return true;
}

void AceptadorTh::run(){
	HiloMuerto hilo(*this);
	aceptadorClientes.escucharConexiones(1);
	while (this->keepAlive)
	{
		Socket* client = this->aceptadorClientes.aceptarConexiones();
		if (client == NULL)
		{
			LOG(INFO)<<"El servidor deja de aceptar clientes";
			break;
		}
		LOG(INFO) << "Conectado cliente numero " << idCliente;
		this->clientes.push_back(new Client(idCliente, client, this->monitor));
		this->clientes.back()->start();
		clientes.remove_if(hilo);
		++idCliente;
	}
}


void AceptadorTh::cerrarClientes(){
	std::list<Client*>::iterator it;
	for (it = clientes.begin(); it != clientes.end(); ++it)
	{
		(*it)->terminarProceso();
		(*it)->join();
		delete (*it);
	}
}

void AceptadorTh::terminarProceso(){
	this->keepAlive = false;
	this->cerrarClientes();
	this->aceptadorClientes.cerrarSocket();
}

