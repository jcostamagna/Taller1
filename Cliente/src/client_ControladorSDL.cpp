/*
 * client_ControladorSDL.cpp
 *
 *  Created on: 17/11/2015
 *      Author: matiaskamien
 */
#include "client_Controlador.h"
#include "client_ControladorSDL.h"
const std::string ARRIBA = "Arriba";
const std::string IZQUIERDA = "Izquierda";
const std::string ABAJO = "Abajo";
const std::string DERECHA = "Derecha";
const std::string BARRA = "Barra";
const std::string tituloVentana = "BluesJazzRabbit";
ControladorSDL::ControladorSDL(bool &hiloCorriendoAtributo,	ProtocoloClientes &protocolo)
: hiloCorriendo(hiloCorriendoAtributo),protocolo(protocolo)
{
	this->ventana = NULL;
	this->renderizadorDeVentana = NULL;
	Display* d = XOpenDisplay(NULL);
	Screen*  s = DefaultScreenOfDisplay(d);
	this->altoPantalla = s->height;
	this->anchoPantalla = s->width;

	this->mapaTeclas.insert(std::make_pair(ARRIBA,false));
	this->mapaTeclas.insert(std::make_pair(ABAJO,false));
	this->mapaTeclas.insert(std::make_pair(DERECHA,false));
	this->mapaTeclas.insert(std::make_pair(IZQUIERDA,false));
	this->mapaTeclas.insert(std::make_pair(BARRA,false));
	this->altoNivel = 0;
	this->anchoNivel = 0;
}

void ControladorSDL::setearAltoYAnchoDeNivel(const int alto, const int ancho)
{
	this->altoNivel = alto;
	this->anchoNivel = ancho;
	this->manejadorEventos.setearAnchoYAltoNivel(ancho,alto);
}

void ControladorSDL::mostrarGanador(const std::string &resultado)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"RESULTADO PARTIDA",resultado.c_str(),this->ventana);

}

void ControladorSDL::cargarTextura(const std::string &rutaImagen,int x,int y)
{
	TexturaSDL* texturaACrear = new TexturaSDL();
	texturaACrear->setearRender(this->renderizadorDeVentana);
	if(!texturaACrear->cargarTextura(rutaImagen))
	{
		delete texturaACrear;
	}else{
		texturaACrear->setearVerticeSupIzqX(x);
		texturaACrear->setearVerticeSupIzqY(y);
	//	this->texturas.push_back(texturaACrear);
	}
}

void ControladorSDL::correrHiloSdl(Modelo* modelo,BlockingQueue<std::string>* colaParaEnviar)
{
	this->hiloCorriendo = true;
	if( !this->inicializarSDL() )
	{
		std::cout << "Error al inicializar SDL" << std::endl;
	}else{
		//this->cargarModeloEnVectorTexturas(modelo);
		SDL_RenderClear( this->renderizadorDeVentana );
		SDL_RenderPresent( this->renderizadorDeVentana );
		this->manejadorEventos.iniciarManejadorEventos(this->anchoPantalla,this->altoPantalla,
				modelo,this->renderizadorDeVentana);
		this->manejadorEventos.setearAnchoYAltoNivel(this->anchoNivel,this->altoNivel);
		bool salir = false;
		SDL_Event evento;
		while(!salir && this->hiloCorriendo)
		{
			while(SDL_PollEvent(&evento))
			{

				if( evento.type == SDL_QUIT )
				{
					salir = true;
				}
				if(evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP)
				{
					std::string stringTeclasAEnviar = this->capturarTeclasPresionadas(evento);
					if(!stringTeclasAEnviar.empty())
					{
						colaParaEnviar->put(stringTeclasAEnviar);
					}else{
					}
				}
			}
			//SDL_Delay(50);
			manejadorEventos.renderizarImagenes();
		}
	}
	this->finalizarSDL(colaParaEnviar);
}

void ControladorSDL::finalizarSDL(BlockingQueue<std::string>* colaParaEnviar)
{
	this->liberarMemoriaControlador();
	this->hiloCorriendo = false;
	this->mutex.signal();
	colaParaEnviar->put(SALIR);
}

const bool ControladorSDL::tipoDeEventoValido(SDL_Event &evento)
{
	if((evento.type != SDL_MOUSEBUTTONUP) &&
			   (evento.type != SDL_MOUSEBUTTONDOWN) &&
			   (evento.type != SDL_MOUSEMOTION) &&
			   (evento.type != SDL_MOUSEWHEEL))
	{
		return true;
	}else{
		return false;
	}
}

void ControladorSDL::esperarHilo()
{
	this->mutex.wait();
}

const std::string ControladorSDL::capturarTeclasPresionadas(SDL_Event &evento)
{
	SDL_PumpEvents();

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	std::map<std::string,bool> mapaAux = this->mapaTeclas;

	this->mapaTeclas[ARRIBA] = keystate[SDL_SCANCODE_UP];
	this->mapaTeclas[ABAJO] = keystate[SDL_SCANCODE_DOWN];
	this->mapaTeclas[DERECHA] = keystate[SDL_SCANCODE_RIGHT];
	this->mapaTeclas[IZQUIERDA] = keystate[SDL_SCANCODE_LEFT];
	this->mapaTeclas[BARRA] = keystate[SDL_SCANCODE_SPACE];

	if(!this->mapaDeTeclasIguales(this->mapaTeclas,mapaAux))
	{
		std::vector<bool> teclas;
		teclas.push_back(this->mapaTeclas[ARRIBA]);
		teclas.push_back(this->mapaTeclas[IZQUIERDA]);
		teclas.push_back(this->mapaTeclas[ABAJO]);
		teclas.push_back(this->mapaTeclas[DERECHA]);
		teclas.push_back(this->mapaTeclas[BARRA]);
		return this->protocolo.generarMensajeTeclasPresionadas(teclas);
	}else{
		return "";
	}
}


bool ControladorSDL::mapaDeTeclasIguales(const std::map<std::string,bool>& mapaTeclas,
		const std::map<std::string,bool>& mapaTeclasAux)const
{
	if((mapaTeclas.find(ARRIBA)->second == mapaTeclasAux.find(ARRIBA)->second) && (mapaTeclas.find(IZQUIERDA)->second
			== mapaTeclasAux.find(IZQUIERDA)->second)&& (mapaTeclas.find(ABAJO)->second
				== mapaTeclasAux.find(ABAJO)->second) && (mapaTeclas.find(DERECHA)->second
					== mapaTeclasAux.find(DERECHA)->second)&& (mapaTeclas.find(BARRA)->second
							== mapaTeclasAux.find(BARRA)->second)){
		return true;
	}
	return false;
}

std::vector<bool> ControladorSDL::seteoTeclas(std::map<std::string,bool> map)
{

	bool teclaArribaPresionada = map["Arriba"];
	bool teclaAbajoPresionada = map["Abajo"];
	bool teclaIzquierdaPresionada = map["Izquierda"];
	bool teclaDerechaPresionada = map["Derecha"];
	bool teclaDisparoPresionada = map["Barra"];
	std::vector<bool> teclas;
	teclas.push_back(teclaArribaPresionada);
	teclas.push_back(teclaIzquierdaPresionada);
	teclas.push_back(teclaAbajoPresionada);
	teclas.push_back(teclaDerechaPresionada);
	teclas.push_back(teclaDisparoPresionada);
	return teclas;
}

void ControladorSDL::setearIdConejoDelCliente(const int id)
{
	this->manejadorEventos.setarIdDelConejo(id);
}

void ControladorSDL::liberarMemoriaControlador()
{
	SDL_DestroyRenderer( this->renderizadorDeVentana );
	SDL_DestroyWindow( this->ventana );
	this->ventana = NULL;
	this->renderizadorDeVentana = NULL;
	IMG_Quit();
	SDL_Quit();
}

bool ControladorSDL::inicializarSDL()
{
	bool estadoInicializacion = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "No se pudo inicializar SDL. Error: " << SDL_GetError() << std::endl;
		estadoInicializacion = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			std::cout << "Error con SLD_SetHint" << std::endl;
		}
		this->ventana = SDL_CreateWindow( tituloVentana.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				this->anchoPantalla, this->altoPantalla, SDL_WINDOW_RESIZABLE );
		if( this->ventana == NULL )
		{
			std::cout << "No se pudo crear la ventana. Error: " << SDL_GetError() << std::endl;
			estadoInicializacion = false;
		}
		else
		{
			this->renderizadorDeVentana = SDL_CreateRenderer( this->ventana, -1, SDL_RENDERER_ACCELERATED );
			if( this->renderizadorDeVentana == NULL )
			{
				std::cout << "No se pudo crear el render. Error: " << SDL_GetError() << std::endl;
				estadoInicializacion = false;
			}
			else
			{
				SDL_SetRenderDrawColor( this->renderizadorDeVentana, 0xFF, 0xFF, 0xFF, 0xFF );
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					std::cout << "No se pudo inicializasr SDL_image. Error: " << IMG_GetError() << std::endl;
					estadoInicializacion = false;
				}
			}
		}
	}
	return estadoInicializacion;
}
