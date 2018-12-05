#include "SocketDatagrama.h"
#include <sys/types.h> //socket
#include <sys/socket.h> //socket
#include <strings.h>//bzero
#include <arpa/inet.h>//htons
#include <cstring>
#include <unistd.h>
#include <string>
#include <iostream>
#include <errno.h> //EWOULDBLOCK

using namespace std;

//Crea un socket tipo datagrama y su parámetro es el puerto local
SocketDatagrama::SocketDatagrama(int pto){
  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //Crea el socket UDP de datagrama
  bzero((char *)&direccionLocal, sizeof(direccionLocal));
  direccionLocal.sin_family = AF_INET;
  direccionLocal.sin_port = htons(pto);
  direccionLocal.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal)); //Se enlaza a la dirección local
}

SocketDatagrama::~SocketDatagrama(){
  close(s);
}

/*struct mensaje* SocketDatagrama::recibe(){
  mensaje * m = new mensaje;
  unsigned int addr_len = sizeof(direccionForanea);
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
  int recibido = recvfrom(s, m, sizeof(mensaje), 0, (struct sockaddr *)&direccionForanea, &addr_len);
  memcpy(m->IP, inet_ntoa(direccionForanea.sin_addr), strlen(inet_ntoa(direccionForanea.sin_addr))+1);
  m->puerto = ntohs(direccionForanea.sin_port);
  return m;
}

//Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(mensaje*m){
  direccionForanea.sin_family = AF_INET;
  direccionForanea.sin_addr.s_addr = inet_addr(m->IP);
  direccionForanea.sin_port = htons(m->puerto);
  int enviado = sendto(s, m, sizeof(*m), 0, (struct sockaddr *)&direccionForanea, sizeof(direccionForanea));
  cout << enviado << endl;
  return enviado;
}*/

//Recibe un paquete tipo datagrama proveniente de este socket
int SocketDatagrama::recibe(PaqueteDatagrama &p){
  //char * msj;
  //msj = new char[p.obtieneLongitud()];
  //bzero(msj, p.obtieneLongitud());
  unsigned int addr_len = sizeof(direccionForanea);
  int recibido = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &addr_len);
  //p.inicializaDatos(msj);
  //delete[] msj;
  p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
  p.inicializaPuerto(ntohs(direccionForanea.sin_port));
  return recibido;
}

//Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(PaqueteDatagrama &p){
  direccionForanea.sin_family = AF_INET;
  direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
  direccionForanea.sin_port = htons(p.obtienePuerto());
  int enviado = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
  return enviado;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos){
  //char * msj;
  //msj = new char[p.obtieneLongitud()];
  //bzero(msj, p.obtieneLongitud());
  unsigned int addr_len = sizeof(direccionForanea);
  timeout.tv_sec = segundos;
  timeout.tv_usec = microsegundos;
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
  int recibido = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &addr_len);
  if (recibido < 0) {
    if (errno == EWOULDBLOCK)
      fprintf(stderr, "Tiempo para recepción transcurrido\n");
    else
      fprintf(stderr, "Error en recvfrom\n");
  }
  //p.inicializaDatos(msj);
  //delete[] msj;
  p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
  p.inicializaPuerto(ntohs(direccionForanea.sin_port));
  return recibido;
}
