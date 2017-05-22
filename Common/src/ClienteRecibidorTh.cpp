#include "ClienteRecibidorTh.h"


void ClienteRecibidorTh::run(){
	std::string buffer;
	int numBytes = ESTADO_VALIDO;
	while (numBytes > ERROR_SOCKET)
	{
		numBytes = this->client->recibirMensaje(buffer);
		if (numBytes <= ERROR_SOCKET)
		{
			this->handler.realizarConsulta(SALIR);
			break;
		}
		this->handler.realizarConsulta(buffer);
		buffer.clear();
	}
	this->keepAlive = false;
}


