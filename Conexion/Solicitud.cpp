#include "Solicitud.h"
#include "PaqueteDatagrama.h"
#include <cstring>
#include <iostream>
#include <string.h>

#define INTENTOS 7
#define SEGUNDOS 2
#define USEGUNDOS 100000

using namespace std;

Solicitud::Solicitud(){
    socketlocal = new SocketDatagrama(0);
}

char * Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments, int requestId){
    mensaje peticion;
    //Se limpia la estructura
    bzero(&peticion, sizeof(peticion));
    //Se copian datos a copia en mensaje
    memcpy(peticion.IP, IP, strlen(IP)+1);
    peticion.messageType = 0;
    peticion.puerto = puerto;
    peticion.operationId = operationId;
    memcpy(peticion.arguments, arguments, strlen(arguments)+1);
    peticion.requestId = requestId;
    PaqueteDatagrama request((char*)&peticion, sizeof(mensaje), peticion.IP, peticion.puerto);
    PaqueteDatagrama response(sizeof(mensaje));
    int r = -1;
    int i = 0;
    /*cout << peticion.operationId << endl;
    cout << request.obtieneDatos() << endl;
    cout << request.obtieneDireccion() << endl;
    cout << request.obtienePuerto() << endl;*/
    while (r == -1 && i < INTENTOS) {
      socketlocal->envia(request);
      r = socketlocal->recibeTimeout(response, SEGUNDOS, USEGUNDOS);
      i++;
    }
    if(r == -1 && i == 7){
      cout << "Servidor no disponible. Intente más tarde" << endl;
    }
    mensaje respuesta;
    memcpy(&respuesta, response.obtieneDatos(), sizeof(mensaje));
    cout << endl;
    cout << '\t'<< "requestIdCliente " << requestId <<endl;
    cout << '\t'<< "requestIdServidor" << respuesta.requestId << endl;
    if(requestId == respuesta.requestId){
      return respuesta.arguments;
    }
    else
      return (char*)"-1";
    //cout << respuesta.arguments << endl;
    //char aux[TAM_MAX_DATA];
    //memcpy(aux, respuesta.arguments, strlen(respuesta.arguments));

}
