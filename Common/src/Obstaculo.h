#ifndef OBSTACULO_H_
#define OBSTACULO_H_
#include "Elemento.h"

class Obstaculo: public Elemento {
	/*
	 * Clase abstracta o interfaz Obstaculo, el obstaculo puede ser rompible e irrompible
	 */
public:
	std::string obtenerInformacion();
	virtual ~Obstaculo(){}
};

#endif /* OBSTACULO_H_ */
