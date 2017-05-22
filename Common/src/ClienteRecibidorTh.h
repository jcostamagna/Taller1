#ifndef CLIENTERECIBIDORTH_H_
#define CLIENTERECIBIDORTH_H_
#include "ClienteTh.h"

class ClienteRecibidorTh: public ClienteTh {
public:
	ClienteRecibidorTh(Socket* client, Handler& handler): ClienteTh(client, handler){}

	//Se encarga de recibir los mensajes.
	void run();
	~ClienteRecibidorTh(){}
};

#endif /* CLIENTERECIBIDORTH_H_ */
