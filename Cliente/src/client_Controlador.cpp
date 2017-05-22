/*
 * client_Controlador.cpp
 *
 *  Created on: 7/11/2015
 *      Author: nicolasdubiansky
 */
#include "client_Controlador.h"
#include "../../Common/src/constantes.h"
#include "../../Common/src/TortugaRoja.h"
#include "../../Common/src/TortugaVerde.h"
#include "../../Common/src/Bala.h"
const int nadieGanoPartida = -1;
const std::string mensajeDeCierreVentanaInicial("Cerrando juego..");
const std::string stringVacio("");
const std::string stringCero("0");
const std::string noHayNivelesAgregados("Como mínimo debe agregar un nivel!");
const std::string entradaJugadoresVacia("Debe ingresar cantidad de jugadores!");
const std::string entradaNombreVacia("Debe ingresar nombre de partida!");
const std::string minimoUnJugador("Como mínimo debe haber un jugador!");
const std::string debeSeleccionarAlgunaPartida("Debe seleccionar alguna partida!");
const std::string yaExistePartidaConMismoNombre("Ya existe una partida con ese nombre.\nPor favor elija otro.");
const std::string partidaLlena("La partida ya está llena!");
const std::string columnaNiveles("Niveles");
const std::string columnaNivelesAgregados("Niveles agregados");
const std::string columnaPartidas("Partidas");
const std::string columnaCantidadJugadores("Cantidad de jugadores que faltan para empezar");
const std::string tooltipTreeviewNiveles("Haga doble click para agregar el nivel a la partida..");
const std::string tooltipTreeviewNivelesAgregados("Haga doble click para sacar el nivel de la partida..");
const std::string tooltipTreeviewPartidas("Haga doble click para unirse a la partida..");
const std::string noHayPartidas("No hay ninguna partida!");
const std::string noHayNivelesCreados("No hay niveles creados");
const std::string eligioPartida("Ha elegido la partida: ");
const std::string partidaEnJuegoEjecutandose("Ya hay una partida ejecutandose. No puede crear otra");
const std::string mensajeGanador("FELICITACIONES!! HA GANADO LA PARTIDA");
const std::string mensajePerdedor("HA PERDIDO LA PARTIDA. LO SENTIMOS!");
const std::string ningunGanador("LO SENTIMOS! NADIE HA GANADO ESTA PARTIDA");
const std::string ninguno("NINGUNO");
const std::string idGanadorMensaje("ID GANADOR: ");
const std::string mensajePuntaje("PUNTAJE: ");
const int posicionTipoDeEvento = 0;
const int posicionIdElemento = 1;
const int posicionTipoElemento = 1;
const int posicionPuntaje = 2;
const int posicionIdNuevoElemento = 2;
const int posicionCoordX = 2;
const int posicionCoordY = 3;
const int posicionCoordXNuevoElemento = 3;
const int posicionCoordYNuevoElemento = 4;
const int posicionIdClienteMatcheo = 1;
const int posicionIdElementoMatcheo = 2;
const int posicionAltoNivel = 1;
const int posicionAnchoNivel = 2;


Controlador::Controlador(ProtocoloClientes &protocolo) : protocolo(protocolo),
		hiloSDL(NULL),controladorSDL(hiloCorriendo,protocolo)
{
	this->hiloCorriendo = false;
	this->fueLlamadoQuit = false;
	this->empezoLoop = false;
	this->mapProcesoDeEventos.insert(std::make_pair(EVENTO_DESTRUIR_PERSONAJE, &Controlador::destruirPersonaje));
	this->mapProcesoDeEventos.insert(std::make_pair(EVENTO_GANADOR, &Controlador::finalizarPartida));
	this->mapProcesoDeEventos.insert(std::make_pair(EVENTO_MOVIMIENTO, &Controlador::moverPersonaje));
	this->mapProcesoDeEventos.insert(std::make_pair(EVENTO_NUEVO_PERSONAJE, &Controlador::crearNuevoPersonaje));
	this->mapProcesoDeEventos.insert(std::make_pair(INICIAR_NIVEL, &Controlador::iniciarNuevoNivel));
	this->mapProcesoDeEventos.insert(std::make_pair(EVENTO_FIN_DE_NIVEL, &Controlador::terminarNivel));
	this->mapProcesoDeEventos.insert(std::make_pair(EVENTO_MATCHEO, &Controlador::matchearId));
	this->mapProcesoDeEventos.insert(std::make_pair(EVENTO_CONEJO_PERDIO_VIDA, &Controlador::restarVidaConejo));

	this->mapCreacionElemento.insert(std::make_pair(TORTUGAROJA, &Controlador::agregarNuevaTortugaRoja));
	this->mapCreacionElemento.insert(std::make_pair(TORTUGAVERDE, &Controlador::agregarNuevaTortugaVerde));
	this->mapCreacionElemento.insert(std::make_pair(BALA, &Controlador::agregarNuevaBala));
	this->mapCreacionElemento.insert(std::make_pair(PREMIO, &Controlador::agregarNuevoPremio));
	this->id = -1;
	this->idConejo = -1;
}

void Controlador::setearInformacionElemento(ElementoGraficable* elemento,
											const std::vector<std::string>& vector)
{
	elemento->setearTipoElemento(vector.at(posicionTipoElemento));
	elemento->setearId(this->pasarStringAInt(vector.at(posicionIdNuevoElemento)));
	elemento->setearVerticeSuperiorIzqX(this->pasarStringAInt(vector.at(posicionCoordXNuevoElemento)));
	elemento->setearVerticeSuperiorIzqXAnterior(this->pasarStringAInt(vector.at(posicionCoordXNuevoElemento)));
	elemento->setearVerticeSuperiorIzqY(this->pasarStringAInt(vector.at(posicionCoordYNuevoElemento)));
	elemento->setearVerticeSuperiorIzqYAnterior(this->pasarStringAInt(vector.at(posicionCoordYNuevoElemento)));
}

void Controlador::agregarNuevaTortugaRoja(const std::vector<std::string>& vector)
{
	ElementoGraficable* tortugaRoja = new TortugaRoja();
	this->setearInformacionElemento(tortugaRoja,vector);
	this->modelo.agregarElementoGraficable(tortugaRoja);
}

void Controlador::agregarNuevaTortugaVerde(const std::vector<std::string>& vector)
{
	ElementoGraficable* tortugaVerde = new TortugaVerde();
	this->setearInformacionElemento(tortugaVerde,vector);
	this->modelo.agregarElementoGraficable(tortugaVerde);
}

void Controlador::agregarNuevaBala(const std::vector<std::string>& vector)
{
	ElementoGraficable* bala = new Bala();
	this->setearInformacionElemento(bala,vector);
	this->modelo.agregarElementoGraficable(bala);
}

void Controlador::agregarNuevoPremio(const std::vector<std::string>& vector)
{
	/*ElementoGraficable* premio = new Premio();
	this->setearInformacionElemento(premio,vector);*/
	//HIDRATAR CLASE PREMIO.
}

void Controlador::destruirPersonaje(const std::vector<std::string>& vector)
{
	std::string idElemento = vector.at(posicionIdElemento);
	int id = this->pasarStringAInt(idElemento);
	this->modelo.eliminarElemento(id);
}

void Controlador::restarVidaConejo(const std::vector<std::string>& vector)
{
	std::string idConejo = vector.at(posicionIdElemento);
	ElementoGraficable* conejo = this->modelo.obtenerElemento(this->pasarStringAInt(idConejo));
	Conejo* conejoCasteado = (Conejo*)conejo;
	conejoCasteado->perderVida();
}


void Controlador::terminarNivel(const std::vector<std::string>& vector)
{
	std::string idConejo = vector.at(posicionIdElemento);
	int id = this->pasarStringAInt(idConejo);
	ElementoGraficable* elemento = this->modelo.obtenerElemento(id);
	Conejo* conejo = (Conejo*)elemento;
	conejo->aumentarPuntaje(PUNTOS_POR_GANAR_NIVEL);
	this->modelo.limpiar();
}

void Controlador::iniciarNuevoNivel(const std::vector<std::string>& vector)
{
	std::vector<std::string> vectorDeInformacion = vector;
	std::string altoNivel = vector.at(posicionAltoNivel);
	std::string anchoNivel = vector.at(posicionAnchoNivel);
	int alto = this->pasarStringAInt(altoNivel);
	int ancho = this->pasarStringAInt(anchoNivel);
	this->controladorSDL.setearAltoYAnchoDeNivel(alto,ancho);
	vectorDeInformacion.erase(vectorDeInformacion.begin());
	vectorDeInformacion.erase(vectorDeInformacion.begin());
	vectorDeInformacion.erase(vectorDeInformacion.begin());
	this->cargarModelo(vectorDeInformacion);
}

void Controlador::finalizarPartida(const std::vector<std::string>& vector)
{
	std::string idGanador = vector.at(posicionIdElemento);
	std::string puntaje = vector.at(posicionPuntaje);
	int id = this->pasarStringAInt(idGanador);
	this->mostrarGanador(id,puntaje,idGanador);
}

void Controlador::mostrarGanador(const int id, const std::string &puntaje,const std::string& idString)
{
	std::string haGanado;
	std::string idGanador = idString;
	if(id == this->id)
	{
		haGanado = mensajeGanador;
	}else{
		if(id == nadieGanoPartida)
		{
			haGanado = ningunGanador;
			idGanador = ninguno;
		}else{
			haGanado = mensajePerdedor;
		}
	}
	std::cout<<haGanado<<std::endl;
	std::string resultado = haGanado+SALTO_DE_LINEA+idGanadorMensaje +idGanador+PUNTO+
								SALTO_DE_LINEA+mensajePuntaje+puntaje+PUNTO;
	this->controladorSDL.mostrarGanador(resultado);
	this->hiloCorriendo = false;
}

void Controlador::moverPersonaje(const std::vector<std::string>& vector)
{
	 std::string idElemento = vector.at(posicionIdElemento);
	 std::string posX = vector.at(posicionCoordX);
	 std::string posY = vector.at(posicionCoordY);
	 ElementoGraficable* elementoAMover = this->modelo.obtenerElemento(this->pasarStringAInt(idElemento));
	 if(elementoAMover)
	 {
		 elementoAMover->mover(this->pasarStringAInt(posX),this->pasarStringAInt(posY));
	 }
}

void Controlador::crearNuevoPersonaje(const std::vector<std::string>& vector)
{
	std::string tipoElemento = vector.at(posicionTipoElemento);
	(this->*mapCreacionElemento[tipoElemento])(vector);
}

void Controlador::matchearId(const std::vector<std::string>& vector)
{
	std::string idCliente = vector.at(posicionIdClienteMatcheo);
	int idClienteInt = this->pasarStringAInt(idCliente);
	if(this->id == idClienteInt)
	{
		std::string idElemento = vector.at(posicionIdElementoMatcheo);
		this->idConejo = this->pasarStringAInt(idElemento);
		this->controladorSDL.setearIdConejoDelCliente(this->idConejo);
	}
}

void Controlador::esperarHilo()
{
	this->controladorSDL.esperarHilo();
}

void Controlador::iniciarInterfaz(const char* rutaDelArchivoGlade)
{
	this->obtenerId();
	this->vista.iniciarInterfaz(rutaDelArchivoGlade);
	this->asignarAccionesABotones();
	this->setearConfiguracionTreeViews();
	this->vista.obtenerVentanaInicial()->show_all();
	Gtk::Main::run(*this->vista.obtenerVentanaInicial());
	if(this->empezoLoop)
	{
		this->iniciarLoopProcesarEventos();
	}
}

void Controlador::obtenerId()
{
	this->mensajesServidor.put(OBTENER_ID);
	std::string id = this->eventos.pull();
	this->id = this->pasarStringAInt(id);
}

bool Controlador::hiloEstaCorriendo()
{
	return this->hiloCorriendo;
}

void Controlador::realizarConsulta(const std::string& buffer){
	if(buffer == SALIR)
	{
		this->mensajesServidor.put(SALIR);
		if(!this->empezoLoop)
		{
			this->quitGtkmm();
		}
	}
	this->eventos.put(buffer);
}

void Controlador::quitGtkmm()
{
	if(!this->fueLlamadoQuit)
	{
		this->fueLlamadoQuit = true;
		Gtk::Main::quit();
	}
}


std::string Controlador::obtenerRespuesta()
{
	std::string buffer = this->mensajesServidor.pull();
	return buffer;
}

void Controlador::cargarModelo(const std::vector<std::string> &vector)
{
	for (unsigned int var = 0; var < vector.size(); ++var)
	{
		this->modelo.agregarElemento(vector[var]);
	}
}

void Controlador::mostrarVentanaPreviaInicioPartida()
{
	if (hiloSDL)
	{
		Gtk::MessageDialog msj(partidaEnJuegoEjecutandose);
		msj.run();
	}else{
		//Lanzo un nuevo hilo para SDL.
		this->hiloCorriendo = true;
		hiloSDL = Glib::Threads::Thread::create(sigc::bind(sigc::mem_fun
					(controladorSDL, &ControladorSDL::correrHiloSdl), &this->modelo,
										&this->mensajesServidor));
	}
}

void Controlador::iniciarLoopProcesarEventos()
{
	std::string evento = this->eventos.pull();
	std::vector<std::string> vector = this->protocolo.split(evento,this->protocolo.obtenerSeparador());
	std::string tipoDeEvento = vector.at(posicionTipoDeEvento);
	while((tipoDeEvento != EVENTO_GANADOR)&&(tipoDeEvento!=SALIR))
	{
		(this->*mapProcesoDeEventos[tipoDeEvento])(vector);
		evento = this->eventos.pull();
		vector = this->protocolo.split(evento,this->protocolo.obtenerSeparador());
		tipoDeEvento = vector.at(posicionTipoDeEvento);
	}
	if(tipoDeEvento!=SALIR){
		this->finalizarPartida(vector);
	}else{
		this->hiloCorriendo = false;
	}
}

void Controlador::asignarAccionesABotones()
{
	this->vista.obtenerBotonSalir()->signal_clicked().connect(sigc::mem_fun(*this,&Controlador::clickBotonSalir));
	this->vista.obtenerBotonCrearPartida()->signal_clicked().connect(sigc::mem_fun(*this,&Controlador::clickBotonCrearPartida));
	this->vista.obtenerBotonUnirseAPartida()->signal_clicked().connect(sigc::mem_fun(*this,&Controlador::clickBotonUnirseAPartida));
	this->vista.obtenerBotonVolver()->signal_clicked().connect(sigc::mem_fun(*this,&Controlador::clickBotonVolverPrincipal));
	this->vista.obtenerBotonVolverDeUnirseAPartida()->signal_clicked().connect(sigc::mem_fun(*this,&Controlador::clickBotonVolverPrincipalDesdeUnirse));
	this->vista.obtenerBotonEmpezarAJugar()->signal_clicked().connect(sigc::mem_fun(*this,&Controlador::clickBotonEmpezarAJugar));
	this->vista.obtenerBotonUnirseAPartidaPrincipal()->signal_clicked().connect(sigc::mem_fun(*this,&Controlador::clickUnirseAPartidaPrincipal));
	this->vista.obtenerTreeviewNiveles()->signal_row_activated().connect(sigc::mem_fun(*this,&Controlador::clickNivelTreeView));
	this->vista.obtenerTreeviewNivelesAgregados()->signal_row_activated().connect(sigc::mem_fun(*this,&Controlador::clickNivelTreeViewAgregados));
	this->vista.obtenerTreeviewPartidas()->signal_row_activated().connect(sigc::mem_fun(*this,&Controlador::clickPartidaTreeView));
}

void Controlador::setearConfiguracionTreeViews()
{
	this->vista.obtenerTreeModelNiveles() = Gtk::TreeStore::create(this->modeloColumnasNiveles);
	this->vista.obtenerTreeModelNivelesAgregados() = Gtk::TreeStore::create(this->modeloColumnasNiveles);
	this->vista.obtenerTreeModelPartidas() = Gtk::TreeStore::create(this->modeloColumnasPartidas);
	this->vista.obtenerTreeviewNiveles()->append_column(columnaNiveles, this->modeloColumnasNiveles.nombreNivel);
	this->vista.obtenerTreeviewNivelesAgregados()->append_column(columnaNivelesAgregados, this->modeloColumnasNiveles.nombreNivel);
	this->vista.obtenerTreeviewPartidas()->append_column(columnaPartidas, this->modeloColumnasPartidas.nombrePartida);
	this->vista.obtenerTreeviewPartidas()->append_column(columnaCantidadJugadores, this->modeloColumnasPartidas.cantidadJugadoresFaltantes);
	this->vista.obtenerTreeviewNiveles()->set_reorderable();
	this->vista.obtenerTreeviewNivelesAgregados()->set_reorderable();
	this->vista.obtenerTreeviewNiveles()->set_tooltip_text(tooltipTreeviewNiveles);
	this->vista.obtenerTreeviewNivelesAgregados()->set_tooltip_text(tooltipTreeviewNivelesAgregados);
	this->vista.obtenerTreeviewPartidas()->set_tooltip_text(tooltipTreeviewPartidas);
}

void Controlador::setearCantidadJugadores(const int cantidadJugadores)
{
	this->modelo.setearCantidadJugadores(cantidadJugadores);
}

void Controlador::clickBotonEmpezarAJugar()
{
	std::string cantidadJugadores = this->vista.obtenerEntradaCantidadJugadores()->get_text();
	std::string nombrePartida = this->vista.obtenerEntradaNombrePartida()->get_text();
	if(cantidadJugadores.length() == 0)
	{
		Gtk::MessageDialog msj(entradaJugadoresVacia);
		msj.run();
	}else{
		if(nombrePartida.length() == 0)
		{
			Gtk::MessageDialog msj(entradaNombreVacia);
			msj.run();
		}else{
			if(cantidadJugadores == stringCero)
			{
				Gtk::MessageDialog msj(minimoUnJugador);
				msj.run();
			}else{
				std::vector<std::string> nivelesAgregados;
				this->agregarNivelesAgregados(nivelesAgregados);
				if(nivelesAgregados.size() > 0)
				{
					this->iniciarPartida(nivelesAgregados);
					//this->iniciarLoopProcesarEventos();
					this->empezoLoop = true;
				}else{
					Gtk::MessageDialog msj(noHayNivelesAgregados);
					msj.run();
				}
			}
		}

	}
}

void Controlador::iniciarPartida(const std::vector<std::string> &nivelesDePartida)
{
	Glib::ustring cantidadJugadoresUstring = this->vista.obtenerEntradaCantidadJugadores()->get_text();
	std::string cantidadJugadores = cantidadJugadoresUstring;
	std::string nombrePartida = this->vista.obtenerEntradaNombrePartida()->get_text();
	std::string mensajeAEnviar = this->protocolo.generarMensajeDeInicioDePartida(this->nivelesAgregados,cantidadJugadores,nombrePartida);
	this->mensajesServidor.put(mensajeAEnviar);
	std::string respuesta;
	respuesta = this->eventos.pull();
	if(respuesta == RESPUESTA_ERROR)
	{
		Gtk::MessageDialog msj(yaExistePartidaConMismoNombre);
		msj.run();
	}else{
		this->vista.obtenerVentanaCrearPartida()->hide();
		this->setearCantidadJugadores(this->pasarStringAInt(cantidadJugadores));
		this->nombrePartida = nombrePartida;
		this->mostrarVentanaPreviaInicioPartida();
	}
}

const int Controlador::pasarStringAInt(const std::string &string)
{
	int entero;
	std::stringstream ss;
	ss << string;
	ss >> entero;
	return entero;
}

void Controlador::clickUnirseAPartidaPrincipal()
{
	Glib::RefPtr<Gtk::TreeSelection> selection = this->vista.obtenerTreeviewPartidas()->get_selection();
	Gtk::TreeModel::iterator iter = selection->get_selected();
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring nombrePartidaUstring = row[this->modeloColumnasPartidas.nombrePartida];
		std::string nombrePartida = nombrePartidaUstring;
		this->unirseAPartida(nombrePartida);
	}else{
		Gtk::MessageDialog msjError(debeSeleccionarAlgunaPartida);
		msjError.run();
	}
}

void Controlador::unirseAPartida(const std::string &nombrePartida)
{
	std::string mensaje = this->protocolo.generarMensajeDeUnionAPartida(nombrePartida);
	this->mensajesServidor.put(mensaje);
	std::string respuesta;
	respuesta = this->eventos.pull();
	if(respuesta == RESPUESTA_ERROR)
	{
		Gtk::MessageDialog msjError(partidaLlena);
		msjError.run();
	}else{
		this->empezoLoop = true;
		this->nombrePartida = nombrePartida;
		this->vista.obtenerVentanaUnirseAPartida()->hide();
		this->mostrarVentanaPreviaInicioPartida();//Ventana para esperar que se llene la partida.
	}
}

void Controlador::agregarNivelesAgregados(std::vector<std::string> &nivelesAgregados)
{
	typedef Gtk::TreeModel::Children type_children;
	type_children children = this->vista.obtenerTreeModelNivelesAgregados()->children();
	for(type_children::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring nombreNivel = row[modeloColumnasNiveles.nombreNivel];
		nivelesAgregados.push_back(nombreNivel);
	}
}



void Controlador::clickNivelTreeView(const Gtk::TreeModel::Path& path,
        Gtk::TreeViewColumn*)
{
	Gtk::TreeModel::iterator iter = this->vista.obtenerTreeModelNiveles()->get_iter(path);
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring nombreNivel = row[this->modeloColumnasNiveles.nombreNivel];
		this->sacarNivelDeTreeView(this->niveles,nombreNivel);
		this->nivelesAgregados.push_back(nombreNivel);
		this->actualizarTreeView(this->vista.obtenerTreeModelNiveles(),this->vista.obtenerTreeviewNiveles(),this->niveles);
		this->actualizarTreeView(this->vista.obtenerTreeModelNivelesAgregados(),this->vista.obtenerTreeviewNivelesAgregados(),this->nivelesAgregados);
	}
}

void Controlador::clickPartidaTreeView(const Gtk::TreeModel::Path& path,
			        Gtk::TreeViewColumn*)
{
	//Unirse a la partida!
	Gtk::TreeModel::iterator iter = this->vista.obtenerTreeModelPartidas()->get_iter(path);
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring nombrePartida = row[this->modeloColumnasPartidas.nombrePartida];
		std::string mensajeAMostrar = eligioPartida + nombrePartida;
		Gtk::MessageDialog msj(mensajeAMostrar);
		msj.run();
	}
}

void Controlador::clickNivelTreeViewAgregados(const Gtk::TreeModel::Path& path,
		        Gtk::TreeViewColumn*)
{
	Gtk::TreeModel::iterator iter = this->vista.obtenerTreeModelNivelesAgregados()->get_iter(path);
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring nombreNivel = row[this->modeloColumnasNiveles.nombreNivel];
		this->sacarNivelDeTreeView(this->nivelesAgregados,nombreNivel);
		this->niveles.push_back(nombreNivel);
		this->actualizarTreeView(this->vista.obtenerTreeModelNiveles(),this->vista.obtenerTreeviewNiveles(),this->niveles);
		this->actualizarTreeView(this->vista.obtenerTreeModelNivelesAgregados(),this->vista.obtenerTreeviewNivelesAgregados(),this->nivelesAgregados);
	}
}

void Controlador::cargarTreeView(Glib::RefPtr<Gtk::TreeStore>& treeModel,Gtk::TreeView* treeView,std::vector<std::string> &vector)
{
	if(vector.size() > 0)
	{
		std::vector<std::string>::iterator it;
		for (it = vector.begin(); it != vector.end(); ++it)
		{
			Gtk::TreeModel::Row row = *(treeModel->append());
			row[this->modeloColumnasNiveles.nombreNivel] = (*it);
		}
	}
	treeView->set_model(treeModel);
}

void Controlador::actualizarTreeView(Glib::RefPtr<Gtk::TreeStore>& treeModel,Gtk::TreeView* treeView,
		std::vector<std::string> &vector)
{
	treeModel.clear();
	treeModel = Gtk::TreeStore::create(this->modeloColumnasNiveles);
	this->cargarTreeView(treeModel,treeView,vector);
}

void Controlador::actualizarTreeViewPartida()
{
	this->vista.obtenerTreeModelPartidas().clear();
	this->vista.obtenerTreeModelPartidas() = Gtk::TreeStore::create(this->modeloColumnasPartidas);
	this->cargarTreeViewPartidas();
}

void Controlador::cargarTreeViewPartidas()
{
	std::vector<std::string>::iterator it;
	for (it = this->partidas.begin(); it != this->partidas.end(); ++it)
	{
		std::vector<std::string> datosPartida = this->protocolo.split((*it),this->protocolo.obtenerSeparadorAuxiliar());
		Gtk::TreeModel::Row row = *(this->vista.obtenerTreeModelPartidas()->append());
		row[this->modeloColumnasPartidas.nombrePartida] = datosPartida.at(0);
		row[this->modeloColumnasPartidas.cantidadJugadoresFaltantes] = datosPartida.at(1);
	}
	this->vista.obtenerTreeviewPartidas()->set_model(this->vista.obtenerTreeModelPartidas());
}

void Controlador::sacarNivelDeTreeView(std::vector<std::string> &vector,
								const std::string &nombreNivel)
{
	std::vector<std::string>::iterator it;
	std::vector<std::string>::iterator nivelAEliminar;
	bool encontrado = false;
	it = vector.begin();
	while(!encontrado && it != vector.end())
	{
		if( (*it) == nombreNivel)
		{
			nivelAEliminar = it;
			encontrado = true;
		}
		++it;
	}
	if(encontrado)
	{
		vector.erase(nivelAEliminar);
	}
}

std::vector<std::string> Controlador::obtenerNiveles()
{
	std::vector<std::string> niveles;
	this->mensajesServidor.put(OBTENER_NIVELES);
	std::string listaDeNiveles;
	listaDeNiveles = this->eventos.pull();
	return this->protocolo.split(listaDeNiveles,this->protocolo.obtenerSeparador());
}

std::vector<std::string> Controlador::obtenerPartidas()
{
	std::vector<std::string> partidas;
	this->mensajesServidor.put(OBTENER_PARTIDAS);
	std::string listaDePartidas;
	//this->socket.recibirMensaje(listaDePartidas);
	listaDePartidas = this->eventos.pull();
	this->protocolo.split(listaDePartidas,this->protocolo.obtenerSeparador());
	return this->protocolo.split(listaDePartidas,this->protocolo.obtenerSeparador());
}

void Controlador::mostrarVentanaCrearPartida()
{
	this->vista.obtenerVentanaInicial()->hide();
	this->vista.obtenerEntradaCantidadJugadores()->set_text(stringVacio);
	this->vista.obtenerEntradaNombrePartida()->set_text(stringVacio);
	this->actualizarTreeView(this->vista.obtenerTreeModelNiveles(),this->vista.obtenerTreeviewNiveles(),this->niveles);
	this->actualizarTreeView(this->vista.obtenerTreeModelNivelesAgregados(),this->vista.obtenerTreeviewNivelesAgregados(),this->nivelesAgregados);
	this->vista.obtenerVentanaCrearPartida()->show_all();
	Gtk::Main::run(*this->vista.obtenerVentanaCrearPartida());
}

void Controlador::mostrarVentanaUnirseAPartida()
{
	this->vista.obtenerVentanaInicial()->hide();
	this->actualizarTreeViewPartida();
	this->vista.obtenerVentanaUnirseAPartida()->show_all();
	Gtk::Main::run(*this->vista.obtenerVentanaUnirseAPartida());
}

void Controlador::clickBotonCrearPartida()
{
	this->nivelesAgregados.clear();
	this->niveles.clear();
	this->niveles = this->obtenerNiveles();
	if(this->niveles.at(0) == RESPUESTA_ERROR)
	{
		Gtk::MessageDialog message2(noHayNivelesCreados);
		message2.run();
	}else{
		this->mostrarVentanaCrearPartida();
	}
}

void Controlador::clickBotonUnirseAPartida()
{
	this->partidas.clear();
	this->partidas = this->obtenerPartidas();
	if(this->partidas[0] != RESPUESTA_ERROR)
	{
		this->mostrarVentanaUnirseAPartida();
	}else{
		Gtk::MessageDialog message2(noHayPartidas);
		message2.run();
	}
}

void Controlador::clickBotonSalir()
{
	Gtk::MessageDialog message2(mensajeDeCierreVentanaInicial);
	message2.run();
	this->mensajesServidor.put(SALIR);
	this->vista.obtenerVentanaInicial()->hide();
	this->fueLlamadoQuit = true;
	Gtk::Main::quit();
}

void Controlador::clickBotonVolverPrincipal()
{
	this->vista.obtenerVentanaCrearPartida()->hide();
	this->vista.obtenerVentanaInicial()->show_all();
	Gtk::Main::run(*this->vista.obtenerVentanaInicial());
}

void Controlador::clickBotonVolverPrincipalDesdeUnirse()
{
	this->vista.obtenerVentanaUnirseAPartida()->hide();
	this->vista.obtenerVentanaInicial()->show_all();
	Gtk::Main::run(*this->vista.obtenerVentanaInicial());
}

Controlador::~Controlador()
{
	if (hiloSDL)
	{
	    hiloSDL->join();
	}
}

