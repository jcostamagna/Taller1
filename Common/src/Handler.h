#ifndef HANDLER_H_
#define HANDLER_H_

#include <string>

class Handler {
public:
	Handler();
	virtual void realizarConsulta(const std::string& buffer){}
	virtual std::string obtenerRespuesta(){return std::string("");}
	virtual ~Handler();
};

#endif /* HANDLER_H_ */
