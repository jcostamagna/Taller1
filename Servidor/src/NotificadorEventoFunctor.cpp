#include "NotificadorEventoFunctor.h"

void NotificadorEventoFunctor::operator()(Observador* observador){
	observador->actualizar(evento);
}

