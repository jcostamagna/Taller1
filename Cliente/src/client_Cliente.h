/*
 * client_Cliente.h
 *
 *  Created on: 7/11/2015
 *      Author: nicolasdubiansky
 */
#ifndef CLIENTE_SRC_CLIENT_CLIENTE_H_
#define CLIENTE_SRC_CLIENT_CLIENTE_H_
#define SALIDA_EXITOSA 0
#define ERROR 1
#include "../../Common/src/common_Socket.h"
#include "../../Common/src/common_ProtocoloClientes.h"
#include "../../Common/src/ClienteEnviadorTh.h"
#include "../../Common/src/ClienteRecibidorTh.h"
#include "client_Controlador.h"

class Cliente {
private:
	Socket socket;
	ProtocoloClientes protocolo;
	Controlador controlador;
	ClienteEnviadorTh enviador;
	ClienteRecibidorTh recibidor;
	void start();
	void join();
	bool conectarConServidor(int puerto,const std::string& ip);
public:
	Cliente();

	bool iniciarCliente(int puerto,const std::string& ip);

	~Cliente();
};

#endif /* CLIENTE_SRC_CLIENT_CLIENTE_H_ */
