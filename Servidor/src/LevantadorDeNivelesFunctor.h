#ifndef LEVANTADORDENIVELESFUNCTOR_H_
#define LEVANTADORDENIVELESFUNCTOR_H_


#include "server_Partida.h"
#include <map>

class LevantadorDeNivelesFunctor {
private:
	Partida& partida;
public:
	LevantadorDeNivelesFunctor(Partida& partida): partida(partida){}
	void operator()(const std::string& nivel);
	void enviarMatcheos(const std::map<int, int>& matcheo);
};

#endif /* LEVANTADORDENIVELESFUNCTOR_H_ */
