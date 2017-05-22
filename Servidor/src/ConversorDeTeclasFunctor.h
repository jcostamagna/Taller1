#ifndef CONVERSORDETECLASFUNCTOR_H_
#define CONVERSORDETECLASFUNCTOR_H_

#include <vector>
#include <string>

class ConversorDeTeclasFunctor {
private:
	std::vector<char> teclas;
public:
	ConversorDeTeclasFunctor();
	void operator()(const std::string& tecla);
	std::vector<char>& mapaDeTeclas();
};

#endif /* CONVERSORDETECLASFUNCTOR_H_ */
