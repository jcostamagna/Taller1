/*
 * Arma.h
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_ARMA_H_
#define COMMON_SRC_ARMA_H_

class Arma {
private:
	int frecuenciaDisparo, contador;
public:
	Arma();
	bool disparar();
	void clear();
	~Arma();
};

#endif /* COMMON_SRC_ARMA_H_ */
