
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "../../Common/src/common_Socket.h"
#include <../../../usr/include/SDL2/SDL_image.h>
#define PARAMETROS 3
#define ERROR 1
#include "client_Cliente.h"

int main(int argc,char** argv){
	if (argc != PARAMETROS) return ERROR;
	std::string ip = std::string(argv[1]);
	int puerto =  atoi(argv[2]);

	Cliente cliente;
	Gtk::Main kit(argc, argv);
	cliente.iniciarCliente(puerto,ip);
}

