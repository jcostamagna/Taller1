#ifndef OBSTACULOROMPIBLE_H_
#define OBSTACULOROMPIBLE_H_
#include "Obstaculo.h"

class ObstaculoRompible: public Obstaculo {
private:

public:
	ObstaculoRompible();
	void persistir(TiXmlElement* element);
	void hidratar(TiXmlElement* element);
	Elemento* obtenerCopia();
	virtual ~ObstaculoRompible(){}
};

#endif /* OBSTACULOROMPIBLE_H_ */
