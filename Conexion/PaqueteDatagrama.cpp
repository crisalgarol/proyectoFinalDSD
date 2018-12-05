#include "PaqueteDatagrama.h"
#include <string> //memcpy

//Crea un paquete de envío tipo datagrama
PaqueteDatagrama::PaqueteDatagrama(char * d, unsigned int lon, char * protocol_internet, int pto){
  longitud = lon;
  datos = new char[longitud];
  bzero(datos, longitud);
  memcpy(datos, d, longitud);
  memcpy(ip, protocol_internet, strlen(protocol_internet) + 1);
  puerto = pto;
}

//Crea un mensaje vacío de una longitud determinada para la recepción
PaqueteDatagrama::PaqueteDatagrama(unsigned int lon){
  longitud = lon;
  datos = new char[longitud];
}

PaqueteDatagrama::~PaqueteDatagrama(){
  delete[] datos;
}

//Regresa la dirección IP de la maquina a la cual se está enviando el datagrama
// o desde la cual el datagrama se ha recibido
char* PaqueteDatagrama::obtieneDireccion(){
  return ip;
}

//Regresa la longitud de los datos que serán enviados o la longitud de los datos recibidos.
unsigned int PaqueteDatagrama::obtieneLongitud(){
  return longitud;
}

//Regresa el número de puerto en el host remoto al cual se envía el datagrama
//o desde el cual el datagrama se ha recibido
int PaqueteDatagrama::obtienePuerto(){
  return puerto;
}

//Regresa los datos almacenados en el miembro datos.
char* PaqueteDatagrama::obtieneDatos(){
  return datos;
}

//Inicializa el puerto en los datos privados de la clase
void PaqueteDatagrama::inicializaPuerto(int pto){
  puerto = pto;
  return;
}

//Inicializa la IP en los datos privados de la clase
void PaqueteDatagrama::inicializaIp(char* protocol_internet){
  memcpy(ip, protocol_internet, strlen(protocol_internet)+1);
  return;
}

//Inicializa los datos que se almacenan en el miembro datos
void PaqueteDatagrama::inicializaDatos(char* d){
  bzero(datos, longitud);
  memcpy(datos, d, longitud);
  return;
}
