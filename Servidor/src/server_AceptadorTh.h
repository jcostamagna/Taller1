
#ifndef SERVER_ACEPTADORTH_H_
#define SERVER_ACEPTADORTH_H_

#include <list>
#include <vector>

#include "../../Common/src/common_Socket.h"
#include "../../Common/src/Thread.h"
#include "Client.h"
#include "server_Monitor.h"
#include "server_Partida.h"

class AceptadorTh: public Thread {
private:
	Socket aceptadorClientes;
	Monitor &monitor;
	bool keepAlive;
	std::list<Client*> clientes;
	int idCliente;

	void cerrarClientes();
	AceptadorTh(const AceptadorTh& object);
	AceptadorTh& operator=(const AceptadorTh& object);
public:
	explicit AceptadorTh(int puerto,Monitor &monitor);
	/* Operacion de aceptar clientes utilizando la funcion bloqueante
	 * accept. Limpia los clientes a medida que acepta */
	void run();

	//Devuelve si el cliente sigue vivo. En caso de no ser así, llama al join y libera la memoria.
	bool hiloMurio(Client* cliente) const;
	void terminarProceso();
};

#endif /* SERVER_ACEPTADORTH_H_ */
