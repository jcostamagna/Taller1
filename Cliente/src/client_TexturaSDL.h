/*
 * client_TexturaSDL.h
 *
 *  Created on: 21/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef CLIENTE_SRC_CLIENT_TEXTURASDL_H_
#define CLIENTE_SRC_CLIENT_TEXTURASDL_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TexturaSDL {
private:
	SDL_Texture* textura;
	SDL_Renderer* renderizador;

	int ancho;
	int alto;
	int verticeSuperiorIzqX;
	int verticeSuperiorIzqY;
public:
	//Inicializa la textura.
	TexturaSDL();

	//Libera la memoria de la textura.
	~TexturaSDL();

	//Setea el renderizador
	void setearRender(SDL_Renderer* renderizador);

	//Loads image at specified path
	bool cargarTextura( const std::string& ruta );

	//Libera el espacio que aloca la textura
	void liberarTextura();

	//Renderiza una textura en el punto x y dados
	void renderizar( int x, int y, SDL_Rect* porcionImagen = NULL);

	//devuelve las dimensiones de la imagen
	int obtenerAncho()const;
	int obtenerAlto()const;
	void setearVerticeSupIzqX(int x);
	void setearVerticeSupIzqY(int y);
	int obtenerVerticeSupIzqX()const;
	int obtenerVerticeSupIzqY()const;
	SDL_Texture* obtenerTextura();
};

#endif /* CLIENTE_SRC_CLIENT_TEXTURASDL_H_ */
