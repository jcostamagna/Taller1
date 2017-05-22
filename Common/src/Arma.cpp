/*
 * Arma.cpp
 *
 *  Created on: 23/11/2015
 *      Author: matiaskamien
 */

#include "../../Common/src/Arma.h"
#define FREC_DISPARO 500

Arma::Arma() {
	frecuenciaDisparo = FREC_DISPARO;
	contador = 0;

}

bool Arma::disparar(){
	return contador % this->frecuenciaDisparo == 0;
}

void Arma::clear(){
	contador= 0;
}

Arma::~Arma() {
	// TODO Auto-generated destructor stub
}

