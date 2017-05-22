/*
 * client_Vista.cpp
 *
 *  Created on: 7/11/2015
 *      Author: nicolasdubiansky
 */
#include "client_Vista.h"

Vista::Vista()
{
	this->ventanaInicial = NULL;
	this->imagenInicialCliente = NULL;
	this->botonSalir = NULL;
	this->botonCrearPartida = NULL;
	this->botonUnirseAPartida = NULL;
	this->ventanaCrearPartida = NULL;
	this->botonVolverPrincipal = NULL;
	this->botonEmpezarAJugar = NULL;
	this->entradaCantidadJugadores = NULL;
	this->treeViewNiveles = NULL;
	this->treeViewNivelesAgregados = NULL;
	this->ventanaUnirseAPartida = NULL;
	this->botonUnirseAPartidaPrincipal = NULL;
	this->botonVolverPrincipalUnirPartida = NULL;
	this->treeViewPartidas = NULL;
	this->entradaNombrePartida = NULL;
	this->ventanaDeEspera = NULL;
}

void Vista::iniciarInterfaz(const char* rutaDelArchivoGlade)
{
	this->builderCliente = Gtk::Builder::create_from_file(rutaDelArchivoGlade);
	this->conectarBotones();
	this->setearImagenesDeBotones(100,100);
}

void Vista::conectarBotones()
{
	this->builderCliente->get_widget("ventanaInicial",this->ventanaInicial);
	this->builderCliente->get_widget("imagenInicial",this->imagenInicialCliente);
	this->builderCliente->get_widget("botonCrearPartida",this->botonCrearPartida);
	this->builderCliente->get_widget("botonUnirseAPartida",this->botonUnirseAPartida);
	this->builderCliente->get_widget("botonSalir",this->botonSalir);

	this->builderCliente->get_widget("ventanaCrearPartida",this->ventanaCrearPartida);
	this->builderCliente->get_widget("botonVolverPrincipal",this->botonVolverPrincipal);
	this->builderCliente->get_widget("botonEmpezarAJugar",this->botonEmpezarAJugar);
	this->builderCliente->get_widget("entradaCantidadJugadores",this->entradaCantidadJugadores);
	this->builderCliente->get_widget("entradaNombrePartida",this->entradaNombrePartida);
	this->builderCliente->get_widget("twNiveles",this->treeViewNiveles);
	this->builderCliente->get_widget("twNivelesAgregados",this->treeViewNivelesAgregados);

	this->builderCliente->get_widget("ventanaUnirseAPartda",this->ventanaUnirseAPartida);
	this->builderCliente->get_widget("botonUnirseAPartidaPrincipal",this->botonUnirseAPartidaPrincipal);
	this->builderCliente->get_widget("botonVolverUnirse",this->botonVolverPrincipalUnirPartida);
	this->builderCliente->get_widget("twPartidas",this->treeViewPartidas);

	this->builderCliente->get_widget("ventanaDeEspera",this->ventanaDeEspera);

}

void Vista::setearImagenesDeBotones(const int alto,const int ancho)
{
	this->imagenInicialCliente->set(RUTA_SERVER_EDITOR_IMAGENES SEPARADOR_DIRECTORIOS "jazzRabitEditor.png");
	this->imagenInicialCliente->set_size_request(alto,ancho);
}

Gtk::Button* Vista::obtenerBotonCrearPartida()
{
	return this->botonCrearPartida;
}

Gtk::Button* Vista::obtenerBotonUnirseAPartida()
{
	return this->botonUnirseAPartida;
}

Gtk::Button* Vista::obtenerBotonVolver()
{
	return this->botonVolverPrincipal;
}

Gtk::Window* Vista::obtenerVentanaInicial()
{
	return this->ventanaInicial;
}

Gtk::Window* Vista::obtenerVentanaDeEspera()
{
	return this->ventanaDeEspera;
}

Gtk::Window* Vista::obtenerVentanaCrearPartida()
{
	return this->ventanaCrearPartida;
}

Gtk::Button* Vista::obtenerBotonSalir()
{
	return this->botonSalir;
}

Gtk::Button* Vista::obtenerBotonEmpezarAJugar()
{
	return this->botonEmpezarAJugar;
}

Gtk::Entry* Vista::obtenerEntradaCantidadJugadores()
{
	return this->entradaCantidadJugadores;
}

Gtk::Entry* Vista::obtenerEntradaNombrePartida()
{
	return this->entradaNombrePartida;
}

Gtk::TreeView* Vista::obtenerTreeviewNiveles()
{
	return this->treeViewNiveles;
}

Gtk::TreeView* Vista::obtenerTreeviewNivelesAgregados()
{
	return this->treeViewNivelesAgregados;
}

Glib::RefPtr<Gtk::TreeStore>& Vista::obtenerTreeModelNiveles()
{
	return this->treeModelNiveles;
}

Glib::RefPtr<Gtk::TreeStore>& Vista::obtenerTreeModelNivelesAgregados()
{
	return this->treeModelNivelesAgregados;
}

Gtk::Window* Vista::obtenerVentanaUnirseAPartida()
{
	return this->ventanaUnirseAPartida;
}

Gtk::Button* Vista::obtenerBotonUnirseAPartidaPrincipal()
{
	return this->botonUnirseAPartidaPrincipal;
}

Gtk::Button* Vista::obtenerBotonVolverDeUnirseAPartida()
{
	return this->botonVolverPrincipalUnirPartida;
}

Gtk::TreeView* Vista::obtenerTreeviewPartidas()
{
	return this->treeViewPartidas;
}

Glib::RefPtr<Gtk::TreeStore>& Vista::obtenerTreeModelPartidas()
{
	return this->treeModelPartidas;
}
