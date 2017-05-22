
#include "server_HiloMuerto.h"

HiloMuerto::HiloMuerto(const AceptadorTh& aceptador): acept(aceptador){}

bool HiloMuerto::operator()(Client* cliente){
	return acept.hiloMurio(cliente);
}
