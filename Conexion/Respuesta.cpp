#include "Respuesta.h"
#include "PaqueteDatagrama.h"
#include <cstring>
#include <iostream>

using namespace std;

Respuesta::Respuesta(int pl){
    socketlocal = new SocketDatagrama(pl);
}

struct mensaje Respuesta::getRequest(){
    mensaje peticion, *ptr;
    //Se limpia la estructura
    bzero(&peticion, sizeof(peticion));
    //ptr = &peticion;
    PaqueteDatagrama request(sizeof(mensaje));
    socketlocal->recibe(request);
    /*cout << request.obtieneDatos() << endl;
    cout << request.obtieneDireccion() << endl;
    cout << request.obtienePuerto() << endl;*/
    memcpy(&peticion, request.obtieneDatos(), sizeof(mensaje));
    memcpy(peticion.IP, request.obtieneDireccion(), strlen(request.obtieneDireccion()));
    peticion.puerto = request.obtienePuerto();
    //cout << peticion.operationId << endl;
    return peticion;
}

void Respuesta::sendReply(char*r, char*ipCliente, int puertoCliente, int requestId){
    //cout << "Simon " << r << endl;
    //cout << ipCliente << endl;
    mensaje respuesta;
    bzero(&respuesta, sizeof(respuesta));
    memcpy(respuesta.IP, ipCliente, strlen(ipCliente));
    memcpy(respuesta.arguments, r, strlen(r));
    respuesta.messageType = 1;
    respuesta.puerto = puertoCliente;
    respuesta.requestId = requestId;
    /*cout << "Si" << respuesta.arguments << endl;
    cout << respuesta.IP << endl;
    cout << respuesta.puerto << endl;*/
    PaqueteDatagrama response((char*)&respuesta, sizeof(mensaje), respuesta.IP, respuesta.puerto);
    socketlocal->envia(response);
}
