/*
 * GeneradorConejoModelo.h
 *
 *  Created on: 24/11/2015
 *      Author: matiaskamien
 */

#ifndef SERVIDOR_SRC_GENERADORCONEJOMODELO_H_
#define SERVIDOR_SRC_GENERADORCONEJOMODELO_H_

class GeneradorConejoModelo {
private:
	int verticeX;
	int verticeY;
	int idParaConejo;
	bool disponible;
public:
	//Setea los atributos.
	GeneradorConejoModelo(const int verticeX, const int verticeY,const int idParaConejo);

	//Devuelve el vértice X.
	const int obtenerVerticeX();

	const bool estaDisponible();

	//Devuelve el ID para conejo.
	const int obtenerIdParaConejo();

	//Setea el booleano en false.
	void ponerNoDisponible();

	//Setea el booleano en true.
	void ponerComoDisponible();

	//Devuelve el vértice Y.
	const int obtenerVerticeY();

	~GeneradorConejoModelo();
};

#endif /* SERVIDOR_SRC_GENERADORCONEJOMODELO_H_ */

