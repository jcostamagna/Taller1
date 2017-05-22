#ifndef CLIENT_H_
#define CLIENT_H_

#include "../../Common/src/common_Socket.h"
#include "../../Common/src/common_ProtocoloClientes.h"
#include "server_Monitor.h"
#include "server_ClientHandler.h"
#include <vector>
#include "../../Common/src/ClienteEnviadorTh.h"
#include "../../Common/src/ClienteRecibidorTh.h"

class Client {
private:
	Socket* client;
	int idCliente;
	ClientHandler handler;
	ClienteRecibidorTh recibidor;
	ClienteEnviadorTh enviador;
	Client(const Client& object);
	Client& operator=(const Client& object);
public:
	//Inicializa los atributos de la clase.
	Client(int idCliente, Socket* client, Monitor& monitor);

	//Lanza los dos hilos que tiene como atributo.
	void start();

	//Llama al join de los dos hilos.
	void join();

	//Cierra el socket del cliente y loguea.
	void terminarProceso();

	//Devuelve si los dos hilos que tiene como atributos siguen vivos
	bool sigueVivo();

	int getId();

	//Libera los recursos alocados por la clase.
	~Client();
};

#endif /* CLIENT_H_ */
