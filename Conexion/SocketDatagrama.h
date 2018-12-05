#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_
#include <netinet/in.h>//Familia AF_INET
#include <sys/time.h> //timeval
#include "PaqueteDatagrama.h"
#include "mensaje.h"

class SocketDatagrama{
  private:
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    int s; //ID socket
    struct timeval timeout;
  public:
    SocketDatagrama(int);
    ~SocketDatagrama();
    /*//Recibe un paquete tipo datagrama proveniente de este socket
    struct mensaje* recibe();
    //Envía un paquete tipo datagrama desde este socket
    int envia(mensaje*);*/
    //Recibe un paquete tipo datagrama proveniente de este socket
    int recibe(PaqueteDatagrama &p);
    //Envía un paquete tipo datagrama desde este socket
    int envia(PaqueteDatagrama &p);
    int recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos);
};

#endif
