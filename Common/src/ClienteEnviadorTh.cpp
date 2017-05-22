#include "ClienteEnviadorTh.h"


void ClienteEnviadorTh::run(){
	std::string mensaje;
	int numBytes = ESTADO_VALIDO;
	while (numBytes > ERROR_SOCKET)
	{
		mensaje = this->handler.obtenerRespuesta();
		numBytes = this->client->enviarMensaje(mensaje);
		if (numBytes <= ERROR_SOCKET or mensaje == SALIR) break;
		mensaje.clear();
	}
	keepAlive = false;
}


