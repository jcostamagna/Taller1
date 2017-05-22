
#define PARAMETROS 2
#define ERROR_ -1
#define SALIDA_EXITOSA 0
#include <stdio.h>
#include "../../Common/src/constantes.h"
#include <stdlib.h>
#include "server_Servidor.h"
#include <glog/logging.h>
#define LOG_INFO "/log.INFO"
#include "../../Common/src/AdministradorDeNiveles.h"
#include "../../Common/src/Nivel.h"
#include "../../Common/src/ObstaculoRompible.h"

int main(int argc, char** argv){
	if (argc != PARAMETROS) return ERROR_;
	google::InitGoogleLogging(argv[0]);
	google::SetLogDestination(google::INFO, RUTA_SERVER_EDITOR_LOG LOG_INFO);
	LOG(INFO) << "Inicia el servidor";
	LOG(INFO)<<"LA RUTA ES   :"<<RUTA;
	int puerto = atoi(argv[1]);
	
	AdministradorDeNiveles admin;
	if (!admin.levantarNiveles()) return ERROR_;
	
	Servidor server(puerto,admin);	
	server.comenzar();
	return SALIDA_EXITOSA;
}

