#include "Client.h"
#define ESTADO_VALIDO 1
#define ERROR_ 0
#include <string>
#include <glog/logging.h>

Client::Client(int idCliente, Socket* client, Monitor& monitor): handler(monitor,idCliente),
recibidor(client, this->handler),enviador(client, this->handler)
{
	this->idCliente = idCliente;
	this->client = client;
}

void Client::start(){
	this->recibidor.start();
	this->enviador.start();
}

void Client::join(){
	this->recibidor.join();
	this->enviador.join();
}


bool Client::sigueVivo(){
	return enviador.sigueVivo() and recibidor.sigueVivo();
}

int Client::getId(){
	return this->idCliente;
}

void Client::terminarProceso(){
	this->client->cerrarSocket();
	LOG(INFO)<<"Desconectado cliente numero "<<idCliente;
}


Client::~Client() {
	delete this->client;
}
