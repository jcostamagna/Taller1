#ifndef CLIENTEENVIADORTH_H_
#define CLIENTEENVIADORTH_H_

#include "ClienteTh.h"


class ClienteEnviadorTh: public ClienteTh {
public:
	ClienteEnviadorTh(Socket* client, Handler& handler): ClienteTh(client, handler){}

	//Se encarga de enviar los mensajes.
	void run();
	~ClienteEnviadorTh(){}
};

#endif /* CLIENTEENVIADORTH_H_ */
