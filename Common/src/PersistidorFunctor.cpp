#include "PersistidorFunctor.h"
#include "constantes.h"

PersistidorFunctor::PersistidorFunctor(TiXmlElement * root)
{
	this->root = root;
}

void PersistidorFunctor::operator()(Elemento* elemento){

	elemento->persistir(this->root);
}
