/*
 * client_CopiadorTextura.h
 *
 *  Created on: 30/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef CLIENTE_SRC_CLIENT_COPIADORTEXTURA_H_
#define CLIENTE_SRC_CLIENT_COPIADORTEXTURA_H_
#include "client_TexturaSDL.h"
#include <iostream>

class CopiadorTextura {
private:
	int x;
	int y;
	TexturaSDL* textura;
public:
	CopiadorTextura(int x,int y,TexturaSDL* textura);
	void setarX(int x);
	void setearY(int y);
	void renderizar(int& cameraX,int& cameraY);
	void setearTextura(TexturaSDL* textura);

};

#endif /* CLIENTE_SRC_CLIENT_COPIADORTEXTURA_H_ */
