#ifndef EVENTOTECLAS_H_
#define EVENTOTECLAS_H_

#include <vector>

class EventoTeclas {
private:
	bool arriba, abajo, derecha, izquierda, barra;
	int id;
public:
	EventoTeclas(int id, const std::vector<char> teclas);
	bool teclaArriba() const;
	bool teclaAbajo() const;
	bool teclaDerecha() const;
	bool teclaIzquierda() const;
	bool teclaBarra() const;
	int getId() const;

};

#endif /* EVENTOTECLAS_H_ */
