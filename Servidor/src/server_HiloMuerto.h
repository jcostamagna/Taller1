
#ifndef HILOMUERTO_H_
#define HILOMUERTO_H_

#include "server_AceptadorTh.h"

class HiloMuerto {
private:
	const AceptadorTh& acept;
	HiloMuerto& operator=(const HiloMuerto& object);
public:
	/* Clase functor utilizada para filtrar clientes(hilos) muertos */
	explicit HiloMuerto(const AceptadorTh& aceptador);
	bool operator()(Client* cliente);
};

#endif /* HILOMUERTO_H_ */
