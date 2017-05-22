#include "AdministradorDeNiveles.h"
#include "dirent.h"
#include "constantes.h"
#include "common_XMLHandler.h"

bool AdministradorDeNiveles::levantarNiveles(){
	XMLHandler handler;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (RUTA_SERVER_EDITOR_NIVELES)) == NULL) return false;
	/* print all the files and directories within directory */
	while ((ent = readdir (dir)) != NULL) {
		std::string nombreNivel(ent->d_name);
		//Error del metodo que siempre imprime eso, ver dsp
	    if (nombreNivel == std::string("..") || nombreNivel == std::string(".")) continue;
	    Nivel nivel = handler.levantarNivel(RUTA_SERVER_EDITOR_NIVELES SEPARADOR_DIRECTORIOS + nombreNivel);
		niveles.insert(std::make_pair(nombreNivel, nivel));
	 }
	 closedir (dir);
	 return !niveles.empty();
}


void AdministradorDeNiveles::agregarNivel(Nivel& nivel)
{
	this->niveles.insert(std::make_pair(nivel.obtenerNombre(), nivel));
}

void AdministradorDeNiveles::guardarNivel(const Nivel& nivel){
	XMLHandler handler;
	handler.guardarNivel(nivel);
}

void guardarNivelMap(std::pair<const std::string, Nivel>& pair){
	XMLHandler handler;
	handler.guardarNivel(pair.second);
}

void AdministradorDeNiveles::guardarNiveles(){
	std::for_each(niveles.begin(), niveles.end(), guardarNivelMap);
}


void AdministradorDeNiveles::agregarNivelCopia(Nivel nivel)
{
	this->eliminarNivel(nivel.obtenerNombre());
	this->niveles.insert(std::make_pair(nivel.obtenerNombre(), nivel));
}

Nivel* AdministradorDeNiveles::obtenerPunteroANivel(const std::string& nombreNivel)
{
	return &this->niveles.at(nombreNivel);
}

Nivel AdministradorDeNiveles::getNivel(const std::string& nombreNivel)
{
	return this->niveles.at(nombreNivel);
}

std::vector<std::string> AdministradorDeNiveles::nombreNiveles()
{
	std::vector<std::string> vector;
	for(std::map<std::string, Nivel>::iterator it = this->niveles.begin(); it != this->niveles.end(); ++it)
	{
		vector.push_back(it->first);
	}
	return vector;
}

bool AdministradorDeNiveles::eliminarNivel(const std::string &nombreNivel)
{
	 std::map<std::string, Nivel>::iterator it;
	 it = this->niveles.find(nombreNivel);
	  if (it != this->niveles.end())
	  {
		  this->niveles.erase (it);
		  return true;
	  }
	  return false;
}

bool AdministradorDeNiveles::eliminarNivelDelMapYDelXML(const std::string &nombreNivel)
{
	if(this->eliminarNivel(nombreNivel))
	{
		  remove((std::string(RUTA_SERVER_EDITOR_NIVELES) +
				  SEPARADOR_DIRECTORIOS + nombreNivel).c_str());
		  return true;
	}
	return false;
}

