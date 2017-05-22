/*
 * client_ManejadorEventos.h
 *
 *  Created on: 26/11/2015
 *      Author: nicolasdubiansky
 */

#ifndef CLIENTE_SRC_CLIENT_MANEJADOREVENTOS_H_
#define CLIENTE_SRC_CLIENT_MANEJADOREVENTOS_H_
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "../../Common/src/Modelo.h"
#include "client_TexturaSDL.h"
#include "../../Common/src/Mutex.h"
#include <X11/Xlib.h>
#include "client_CopiadorTextura.h"
/*
 *Entidad encargada de rendereizar los eventos que el servidor le manda
 */
class ManejadorEventos {
private:
	//typedef void (ManejadorEventos::*Funciones)(const ElementoGraficable*,const std::vector<TexturaSDL*>&);
	typedef void (ManejadorEventos::*Eventos)(ElementoGraficable*);
	std::map<std::string,Eventos> generadorDeEventos;
	std::map<std::string,TexturaSDL*> coloresJugadores;

	Modelo* modelo;
	SDL_Renderer* renderizadorDeVentana;
	SDL_Rect* camera;
	int anchoNivel;
	int altoNivel;
	int idConejo;
	TexturaSDL background;
	TexturaSDL esperandoJugadoresImagen;
	TexturaSDL corazonImagen;

	std::vector<TexturaSDL*> conejoMovDerRojo;
	std::vector<TexturaSDL*> conejoMovIzqRojo;
	std::vector<TexturaSDL*> conejoDerParadoRojo;
	std::vector<TexturaSDL*> obstaculoRompible;
	std::vector<TexturaSDL*> obstaculoIrrompible;
	std::vector<TexturaSDL*> finDeNivel;
	std::vector<TexturaSDL*> conejoSaltoSubiendo;
	std::vector<TexturaSDL*> conejoSaltoCayendo;
	std::vector<TexturaSDL*> conejoCaida;
	std::vector<TexturaSDL*> tortugaVerdeMovDerecha;
	std::vector<TexturaSDL*> tortugaVerdeMovIzquierda;
	std::vector<TexturaSDL*> tortugaVerdeParada;
	std::vector<TexturaSDL*> tortugaRojaMovDerecha;
	std::vector<TexturaSDL*> tortugaRojaMovIzquierda;
	std::vector<TexturaSDL*> tortugaRojaParada;
	std::vector<TexturaSDL*> bala;
	bool ajustarCamara();
	//carga el map de eventosAGraficar. Debe ser invocado en el iniciadorManejadorEventos
	void cargarEventosAGraficar();
	//carga el map de generadorDeEventos. Debe ser invocado en el iniciadorManejadorEventos
	void cargarGeneradorDeEventos();
	//carga todas las imagenes del cliente en sus respectivos vectores de texturas
	void cargarImagenesEnVectores();
	//carga una textura en el vector correspondiente
	void cargarTexturaEnVector(const std::string& ruta,std::vector<TexturaSDL*>& vector);
	//carga el map de coloresJugadores. Debe ser invocado en el iniciadorManejadorEventos
	void cargarColoresJugadoresMap();
	void crearClaveYTexturaparaColorDeJugador(const std::string& claveColor,const std::string& rutaImagen);
	std::vector<CopiadorTextura> imagenesIndice0;
	std::vector<CopiadorTextura> imagenesIndice1;
	std::vector<CopiadorTextura> imagenesIndice2;
	std::vector<CopiadorTextura> imagenesIndice3;

	//Acola un CopiadorTextura en el vector de ImagenesIndice indice indicado por parametro
	void acolarImagenEnVectorIndice(int indiceVector,TexturaSDL* textura,int x,int y);

	void renderizarCopiadoresTexturas(std::vector<CopiadorTextura>& imagenes);
	/**************************************************
		EVENTOS PARA EL MAP DE EVENTOS A GRAFICAR
	 ************************************************/
	void renderizarVectorTexturaDeElemento(ElementoGraficable* elemento,
			const std::vector<TexturaSDL*>& imagenesARenderizar);


	/************************************************************
	     EVENTOS PARA EL MAP DE GENERADOR DE EVENTOS
	 ************************************************************/
	void generarEventoMovimientoConejoDerecha(ElementoGraficable* elemento);
	void generarEventoMovimientoConejoIzquierda(ElementoGraficable* elemento);
	void generarEventoMovimientoConejoArriba(ElementoGraficable* elemento);
	void generarEventoMovimientoConejoParado(ElementoGraficable* elemento);
	void generarEventoMovimientoConejoSaltoSubiendo(ElementoGraficable* elemento);
	void generarEventoMovimientoConejoSaltoCayendo(ElementoGraficable* elemento);
	void generarEventoMovimientoConejoCaida(ElementoGraficable* elemento);
	void renderizacionObstaculoRompible(ElementoGraficable* elemento);
	void renderizacionObstaculoIrrompible(ElementoGraficable* elemento);
	void renderizacionFinDeNivel(ElementoGraficable* elemento);
	void generarEventoMovimientoTortugaVerdeDerecha(ElementoGraficable* elemento);
	void generarEventoMovimientoTortugaVerdeIzquierda(ElementoGraficable* elemento);
	void generarEventoMovimientoTortugaVerdeParada( ElementoGraficable* elemento);
	void generarEventoMovimientoTortugaRojaDerecha(ElementoGraficable* elemento);
	void generarEventoMovimientoTortugaRojaIzquierda(ElementoGraficable* elemento);
	void generarEventoMovimientoTortugaRojaParada( ElementoGraficable* elemento);
	void generarEventoMovimientoBala( ElementoGraficable* elemento);

	//Recorre un vector de texturas y libera la memoria. Debe ser invocado en el destructor
	void liberadorDeTexturas(std::vector<TexturaSDL*>& vectorALiberar);
	void renderizarVidasConejo();
	void setearAnchoYAltoPantalla(const int ancho,const int alto);
	/***************************************************************/
public:
	ManejadorEventos();
	void iniciarManejadorEventos(const int anchoPantalla, const int altoPantalla
			,Modelo* modelo,SDL_Renderer* renderizador);
	//Recorre el Modelo y genera un string, que es el evento a realizar por el elemento,
	//y lo usa como clave del map para renderizarlo.
	void renderizarImagenes();
	void setarIdDelConejo(const int idConejo);
	void setearAnchoYAltoNivel(const int ancho, const int alto);
	~ManejadorEventos();
};

#endif /* CLIENTE_SRC_CLIENT_MANEJADOREVENTOS_H_ */
