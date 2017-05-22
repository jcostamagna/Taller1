#include "NotificadorEventosFunctor.h"


void NotificadorEventosFunctor::operator()(Observador* observador){
	observador->actualizar(eventos);
}
