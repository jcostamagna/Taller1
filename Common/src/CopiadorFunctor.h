#ifndef COPIADORFUNCTOR_H_
#define COPIADORFUNCTOR_H_
#include "Nivel.h"

class CopiadorFunctor {
	Nivel& nivel;
public:
	CopiadorFunctor(Nivel& nivel): nivel(nivel) {}
	void operator()(Elemento* elemento);
	void operator()(GeneradorTortuga* generadorTortuga);
	void operator()(GeneradorConejo* generadorTortuga);
};

#endif /* COPIADORFUNCTOR_H_ */
