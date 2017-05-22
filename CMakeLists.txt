cmake_minimum_required (VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE ON)

#Configuracion de rutas
IF(NOT DEFINED RUTA)

    set(RUTA ${CMAKE_BINARY_DIR})

ENDIF(NOT DEFINED RUTA)


set(INSTALACION_SERVER_EDITOR "${RUTA}/Instalacion/ServerEditor")
set(INSTALACION_CLIENTE "${RUTA}/Instalacion/Cliente")
configure_file( Common/src/constantes.h.in Common/src/constantes.h )

#Flags
set(CMAKE_CXX_FLAGS "-std=gnu++98 -Wall -Werror -Wno-long-long -pedantic -pedantic-errors -g -O3 -DNDEBUG -ggdb -DDEBUG -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -ggdb -DDEBUG -fno-inline")
SET(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -Wno-long-long -pedantic -pedantic-errors") 

#Testeo de librerias auxiliares
ENABLE_LANGUAGE(CXX)
try_compile(LIBRARIES_TEST_COMPILED ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libraries_test.cpp
	LINK_LIBRARIES glog pthread
        OUTPUT_VARIABLE LOG)

if(LIBRARIES_TEST_COMPILED)
  message(STATUS "Libraries test. Compiled successfully.")
else()
  message(FATAL_ERROR "There was an error trying to compile a basic test code:\n ${LOG} \n Please execute 'sudo apt-get install build-essential libgoogle-glog-dev' and try again.")
endif()

message(STATUS "Resuming the configuration process....")

#Archivos
project("Blues JackRabbit")
file(GLOB Common_SRC
    "Common/src/*.cpp"
)
file(GLOB Editor_SRC
    "Editor/src/*.cpp"
)
file(GLOB Editor_Elementos
    "Editor/src/elementos/*.cpp"
)
file(GLOB Server_SRC
    "Servidor/src/*.cpp"
)
file(GLOB Client_SRC
    "Cliente/src/*.cpp"
)
file(GLOB Images_SRC
    "Editor/src/Imagenes/*"
)
file(GLOB ClientImages_SRC
    "Cliente/src/Imagenes/*"
)
#-------------------------------EDITOR------------------------------------------
INCLUDE(FindPkgConfig)
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Editor/src")
include_directories("${PROJECT_SOURCE_DIR}/Editor/src")
include_directories("${PROJECT_SOURCE_DIR}/Editor/src/elementos")
INCLUDE(FindPkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})  
include_directories(${GTKMM_INCLUDE_DIRS} ${GSTMM_INCLUDE_DIRS})
PKG_SEARCH_MODULE(TINYXML REQUIRED tinyxml)
INCLUDE_DIRECTORIES(${TINYXML_INCLUDE_DIRS})
#~ PKG_SEARCH_MODULE(PTHREAD REQUIRED pthread)
#~ INCLUDE_DIRECTORIES(${PTHREAD_INCLUDE_DIRS})
#~ PKG_SEARCH_MODULE(X11 REQUIRED X11)
#~ INCLUDE_DIRECTORIES(${X11_INCLUDE_DIRS})
add_executable(Editor_
			${Editor_SRC}
			${Editor_Elementos}
			${Common_SRC}
		)
TARGET_LINK_LIBRARIES(Editor_ pthread)
TARGET_LINK_LIBRARIES(Editor_ tinyxml)
link_directories(${GTKMM_LIBRARY_DIRS})  
target_link_libraries(Editor_ ${GTKMM_LIBRARIES}) 
TARGET_LINK_LIBRARIES(Editor_ X11)
INSTALL(FILES Editor_ DESTINATION ${RUTA}/Instalacion/ServerEditor     
PERMISSIONS
        OWNER_READ OWNER_WRITE
        GROUP_READ
        WORLD_READ OWNER_EXECUTE GROUP_EXECUTE
        WORLD_EXECUTE)
#-------------------------------CLIENTE--------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Cliente/src")
include_directories("${PROJECT_SOURCE_DIR}/Cliente/src")
INCLUDE(FindPkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})  
include_directories(${GTKMM_INCLUDE_DIRS} ${GSTMM_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})  
include_directories(${GTKMM_INCLUDE_DIRS} ${GSTMM_INCLUDE_DIRS}) 
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_image REQUIRED SDL2_image>=2.0.0)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})
PKG_SEARCH_MODULE(TINYXML REQUIRED tinyxml)
INCLUDE_DIRECTORIES(${TINYXML_INCLUDE_DIRS})
#~ PKG_SEARCH_MODULE(PTHREAD REQUIRED pthread)
#~ INCLUDE_DIRECTORIES(${PTHREAD_INCLUDE_DIRS})
#~ PKG_SEARCH_MODULE(X11 REQUIRED X11)
#~ INCLUDE_DIRECTORIES(${X11_INCLUDE_DIRS})
add_executable(Client
			${Client_SRC}
			${Common_SRC}
		)
TARGET_LINK_LIBRARIES(Client pthread)
TARGET_LINK_LIBRARIES(Client tinyxml)
TARGET_LINK_LIBRARIES(Client SDL2)
TARGET_LINK_LIBRARIES(Client SDL2_image)
TARGET_LINK_LIBRARIES(Client X11)
link_directories(${GTKMM_LIBRARY_DIRS})  
target_link_libraries(Client ${GTKMM_LIBRARIES})
INSTALL(FILES Client DESTINATION ${RUTA}/Instalacion/Cliente     
PERMISSIONS
        OWNER_READ OWNER_WRITE
        GROUP_READ
        WORLD_READ OWNER_EXECUTE GROUP_EXECUTE
        WORLD_EXECUTE)
#-------------------------------SERVIDOR------------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Servidor/src")
include_directories("${PROJECT_SOURCE_DIR}/Servidor/src")
find_package(PkgConfig REQUIRED)
PKG_SEARCH_MODULE(TINYXML REQUIRED tinyxml)
INCLUDE_DIRECTORIES(${TINYXML_INCLUDE_DIRS})
#~ PKG_SEARCH_MODULE(GLOG REQUIRED glog)
#~ INCLUDE_DIRECTORIES(${GLOG_INCLUDE_DIRS})
#~ PKG_SEARCH_MODULE(PTHREAD REQUIRED pthread)
#~ INCLUDE_DIRECTORIES(${PTHREAD_INCLUDE_DIRS})
add_executable(Server
			${Server_SRC}
			${Common_SRC}
			)			
TARGET_LINK_LIBRARIES(Server tinyxml)
TARGET_LINK_LIBRARIES(Server pthread)
TARGET_LINK_LIBRARIES(Server glog)
#~ target_link_libraries(Server ${GLOG_LIBRARIES})
#~ target_include_directories(Server PUBLIC ${GLOG_INCLUDE_DIRS})
#~ target_compile_options(Server PUBLIC ${GLOG_CFLAGS_OTHER})

INSTALL(FILES Server DESTINATION ${RUTA}/Instalacion/ServerEditor
PERMISSIONS
        OWNER_READ OWNER_WRITE
        GROUP_READ
        WORLD_READ OWNER_EXECUTE GROUP_EXECUTE
        WORLD_EXECUTE)
#-------------------------------------------------------------------------------

#Creacion de directorios necesarios y copias de imagenes y glades
file(COPY "Cliente.glade" DESTINATION ${INSTALACION_CLIENTE})
file(COPY "Editor.glade" DESTINATION ${INSTALACION_SERVER_EDITOR})

file(MAKE_DIRECTORY ${INSTALACION_SERVER_EDITOR}/Niveles)
file(MAKE_DIRECTORY ${INSTALACION_SERVER_EDITOR}/log)
file(MAKE_DIRECTORY ${INSTALACION_SERVER_EDITOR}/Imagenes)
file(MAKE_DIRECTORY ${INSTALACION_CLIENTE}/Imagenes)
file(COPY ${Images_SRC} DESTINATION ${INSTALACION_SERVER_EDITOR}/Imagenes)
file(COPY ${ClientImages_SRC} DESTINATION ${INSTALACION_CLIENTE}/Imagenes)
