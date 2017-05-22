
#ifndef COMMON_PARSER_H_
#define COMMON_PARSER_H_

#include <vector>
#include <string>

class Parser {
private:
	Parser(const Parser& object);
	Parser& operator=(const Parser& object);
public:
	Parser(){}

	//Hace un split del string recibido con respecto al separador recibido.
	//Devuelve un vector.
	std::vector<std::string> split(const std::string& texto,
			const char separador);
	std::string join(std::vector<std::string> vector, const char delimitador);
};

#endif /* COMMON_PARSER_H_ */
