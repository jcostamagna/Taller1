#include "NotificadorFunctor.h"

void NotificadorFunctor::operator()(Observador* observador){
	observador->actualizar(evento);
}



