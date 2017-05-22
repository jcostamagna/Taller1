#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_
#include <string>

class Socket {
private:
	struct sockaddr_in* server;
	int fd;
	Socket (const Socket& object);
	Socket& operator=(const Socket& object);
	Socket(int fd);
 	bool leerSize(long *value);
 	bool enviarSize(long value);
 	bool recibirData(void *buf, int buflen);
 	bool enviarData(void *buf, int buflen);

public:
	Socket();
	int conectar(const std::string& ip, int puerto);
	bool enlazar(int puerto);
	bool escucharConexiones(int cantDeConexiones);
	Socket* aceptarConexiones();
	int enviarMensaje(const std::string& mensaje);
	int recibirMensaje(std::string& buffer);

	int cerrarSocket();
	~Socket();
};


#endif /* COMMON_SOCKET_H_ */
