/*
 * TortugaRoja.h
 *
 *  Created on: 21/11/2015
 *      Author: matiaskamien
 */

#ifndef COMMON_SRC_TORTUGAROJA_H_
#define COMMON_SRC_TORTUGAROJA_H_
#include "Tortuga.h"

class TortugaRoja : public Tortuga {
public:
	TortugaRoja();
	std::string obtenerClaveImagen();

	//Devuelve la cantidad de puntos que otorga al conejo al morir.
	const int obtenerPuntosPorMorir();

	~TortugaRoja();
};

#endif /* COMMON_SRC_TORTUGAROJA_H_ */
