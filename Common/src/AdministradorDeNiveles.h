#ifndef ADMINISTRADORDENIVELES_H_
#define ADMINISTRADORDENIVELES_H_

#include <map>
#include <string>
#include <iostream>
#include "Nivel.h"

class AdministradorDeNiveles {
	/*
	 * Clase encarga de contener a los niveles, devuelve las copias de los mismos para que cada uno avance de manera distinta
	 */
private:
	std::map<std::string, Nivel> niveles;
	AdministradorDeNiveles (const AdministradorDeNiveles& object);
	AdministradorDeNiveles& operator=(const AdministradorDeNiveles& object);
public:
	AdministradorDeNiveles() {}
	//Levanta los archivos XML de niveles y los carga en memoria.
	bool levantarNiveles();

	//Devuelve una copia del objeto Nivel cuyo nombre recibe por parámetro.
	Nivel getNivel(const std::string& nombreNivel);

	//Devuelve un puntero del objeto Nivel cuyo nombre recibe por parámetro.
	Nivel* obtenerPunteroANivel(const std::string& nombreNivel);

	//Devuelve un vector de string con los nombres de los niveles.
	std::vector<std::string> nombreNiveles();

	//Agrega el nivel al map.
	void agregarNivel(Nivel& nivel);

	//Llama al guardar nivel de XML handler.
	void guardarNivel(const Nivel& nivel);

	void guardarNiveles();

	//Agrega una copia de nivel al map.
	void agregarNivelCopia(Nivel nivel);
	//Elimina el nivel del map y devuelve true en caso de ser exitoso el borrado
	bool eliminarNivel(const std::string &nombreNivel);
	//Elimina el nivel del map y del disco duro, es decir borra el xml
	//y devuelve true en caso de ser exitoso el borrado
	bool eliminarNivelDelMapYDelXML(const std::string &nombreNivel);
};

#endif /* ADMINISTRADORDENIVELES_H_ */
