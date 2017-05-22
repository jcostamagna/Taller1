
#include "common_Socket.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#define MAX_BUFFER 50
#define CAMPO_SIZE 10
#define BUFFER_SIZE 1024
#define PROTOCOLO_SIZE 3


Socket::Socket(){
	this -> fd = socket(AF_INET, SOCK_STREAM, 0);
	this -> server = NULL;
}

Socket::Socket(int fd){
	this->fd = fd;
	this -> server = NULL;
}

int Socket::conectar(const std::string& ip, int puerto){
	struct hostent *he = gethostbyname(ip.c_str());
	if (he == NULL) return -1;

	struct sockaddr_in servidor;

	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(puerto);
	servidor.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(servidor.sin_zero),8);
	int resultado = connect(fd, (struct sockaddr *)&servidor,
			sizeof(struct sockaddr));
	this->server = &servidor;
	return resultado;
}

bool Socket::enlazar(int puerto){
	struct sockaddr_in servidor;
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(puerto);
	servidor.sin_addr.s_addr = INADDR_ANY;
	bzero(&(servidor.sin_zero),8);
	int resultado = bind(this->fd,(const struct sockaddr*)&(servidor),
			sizeof(struct sockaddr));
	this->server = &servidor;
	return resultado == 0;
}

bool Socket::escucharConexiones(int cantDeConexiones){
	return listen(this->fd,cantDeConexiones) != -1;
}

Socket* Socket::aceptarConexiones(){
	struct sockaddr_in client;
	int sin_size=sizeof(struct sockaddr_in);
	int aceptado = accept(fd,(sockaddr *)&client, (socklen_t*)&sin_size);
	if (aceptado < 0) return NULL;
	return new Socket(aceptado);
}

int Socket::enviarMensaje(const std::string& mensaje){
	long msjSize = mensaje.length();
    if (!enviarSize(msjSize))
        return false;
	return send(fd, mensaje.c_str(), mensaje.length(), MSG_NOSIGNAL);
}

int Socket::recibirMensaje(std::string& buffer){
	char bufferMsjRecibidos[MAX_BUFFER];
	int numBytes = 0;
	long msjSize;
	if (!leerSize(&msjSize))
		return false;
	for (long i = 0; i < msjSize; i += numBytes){
		long faltante = msjSize-i;
		if ((numBytes = recv(fd, bufferMsjRecibidos, std::min(faltante,(long)MAX_BUFFER), 0)) == -1)	return numBytes;
		buffer.append(bufferMsjRecibidos, numBytes);
	}
	return msjSize;
}

bool Socket::recibirData(void *buf, int buflen)
{
    unsigned char *pbuf = (unsigned char *) buf;
    while (buflen > 0)
    {
        int num = recv(fd, pbuf, buflen, 0);
        if (num <= 0) return false;

        pbuf += num;
        buflen -= num;
    }
    return true;
}

bool Socket::leerSize(long *value)
{
    if (!recibirData(value, sizeof(value)))
        return false;
    *value = ntohl(*value);
    return true;
}


bool Socket::enviarData(void *buf, int buflen)
{
    unsigned char *pbuf = (unsigned char *) buf;
    while (buflen > 0)
    {
        int num = send(fd, pbuf, buflen, 0);
        if (num == -1) return false;

        pbuf += num;
        buflen -= num;
    }
    return true;
}


bool Socket::enviarSize(long value)
{
    value = htonl(value);
    return enviarData(&value, sizeof(value));
}



int Socket :: cerrarSocket(){
	shutdown(fd, 2);
	return close(fd);
}

Socket::~Socket(){}
