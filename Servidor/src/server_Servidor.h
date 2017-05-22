
#ifndef SERVER_SERVIDOR_H_
#define SERVER_SERVIDOR_H_
#include <vector>
#include "../../Common/src/common_XMLHandler.h"
#include "server_AceptadorTh.h"
#include "server_Partida.h"
#include "../../Common/src/common_Socket.h"

class Servidor {
	private:
		Servidor(const Servidor& object);
		Servidor& operator=(const Servidor& object);
		Monitor monitor;
		AceptadorTh aceptador;

		/*
		 * Lo creamos direca tamente en el aceptador porque si lo creamos aca, para luego
		 * pasarle una referencia, no sabemos como hacer.
		 */
	public:
		Servidor(int puerto, AdministradorDeNiveles& admin);
		bool comenzar();
};

#endif /* SERVER_SERVIDOR_H_ */
