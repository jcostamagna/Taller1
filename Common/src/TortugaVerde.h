/*
 * TortugaVerde.h
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_TORTUGAVERDE_H_
#define COMMON_SRC_TORTUGAVERDE_H_
#include "Tortuga.h"

class TortugaVerde : public Tortuga{
public:
	TortugaVerde();
	std::string obtenerClaveImagen();

	//Devuelve la cantidad de puntos que otorga al conejo al morir.
	const int obtenerPuntosPorMorir();

	~TortugaVerde();
};

#endif /* COMMON_SRC_TORTUGAVERDE_H_ */
