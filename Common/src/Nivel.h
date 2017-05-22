#ifndef NIVEL_H_
#define NIVEL_H_

#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "Elemento.h"
#include "GeneradorTortuga.h"
#include "GeneradorConejo.h"

class Nivel {
	/*Clase Nivel contiene la informacion del nivel, debe ser
	 * copiable porque para cada partida tendra un estado diferente, pero el mismo inicio*/
private:
	std::vector<Elemento*> elementos;
	std::vector<GeneradorTortuga*> generadoresTortugas;
	std::vector<GeneradorConejo*> conejos;
	std::string nombre;
	int idElemento;
	Nivel& operator=(const Nivel& object);
	const std::string pasarIntAString(const int entero);
	void agregarInformacionAlVector(std::vector<std::string> &vector,std::vector<Elemento*>::iterator &it);
	int alto, ancho;
	std::vector<std::string> colores;
	int posicionColorASetear;

	//Setea en true el booleano de los generadores de conejo.
	void ponerEnDisponibleTodosLosGeneradores();
public:
	Nivel (const Nivel& object);
	Nivel(const std::string& nombre, const int& ancho, const int& alto);
	int obtenerAnchoNivel() const;
	int obtenerAltoNivel() const;
	void agregarElemento(Elemento* elemento);
	void agregarGenerador(GeneradorTortuga* elemento);
	void agregarGenerador(GeneradorConejo* elemento);
	const std::string obtenerNombre()const;
	void obtenerInformacion(std::vector<std::string> &vector);
	const std::vector<Elemento*>& obtenerElementos() const;

	//Devuelve el primer generador de conejo disponible.
	GeneradorConejo* obtenerGeneradorConejo();

	//Devuelve una referencia constante del vector de generadores de tortugas.
	const std::vector<GeneradorTortuga*>& obtenerTortugas() const;

	//Devuelve una referencia constante del vector de generadores de conejos.
	const std::vector<GeneradorConejo*>& obtenerConejos() const;

	//Devuelve una referencia constante del vector de colores.
	const std::vector<std::string>& obtenerColores() const;

	//Devuelve la posición en el vector del color disponible para setear a un conejo.
	const int obtenerPosicionColor()const;
	
	//Aumenta la posición del color a setear en uno.
	void aumentarPosicionColor();

	~Nivel();
};

#endif /* NIVEL_H_ */
