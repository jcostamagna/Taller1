#ifndef CLIENTETH_H_
#define CLIENTETH_H_

#include "common_Socket.h"
#include "Handler.h"
#include "Thread.h"
#include <iostream> //Not necesary
#define ESTADO_VALIDO 1
#define ERROR_SOCKET 0
#define SALIR "q"

class ClienteTh: public Thread {
private:
	ClienteTh(const ClienteTh& object);
	ClienteTh& operator=(const ClienteTh& object);
protected:
	Socket* client;
	Handler& handler;
	bool keepAlive;

public:
	ClienteTh(Socket* client, Handler& handler);
	void run(){}
	bool sigueVivo();
	~ClienteTh(){}
};

#endif /* CLIENTETH_H_ */
