
#include "common_Parser.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> Parser::split(const std::string& texto,
		const char delimit){
	std::string parsed;
	std::stringstream input_stringstream(texto);
	std::vector<std::string> tokens;

	while (getline(input_stringstream,parsed,delimit))
	{
	    tokens.push_back(parsed);
	}
	return tokens;
}

std::string Parser::join(std::vector<std::string> vector, const char delimit){
	std::stringstream stream;
	std::vector<std::string>::iterator it;
	for (it=vector.begin(); it < vector.end(); it++){
		if(it != vector.begin())
		  stream << delimit;
		stream<<(*it);
	}
	std::string texto = std::string(stream.str());
	return texto;
}


