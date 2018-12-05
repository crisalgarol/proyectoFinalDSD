#ifndef RESPUESTA_H_
#define RESPUESTA_H_

#include "SocketDatagrama.h"


class Respuesta{

    public:
        Respuesta(int);
        struct mensaje getRequest(void);
        void sendReply(char * r, char *ipCliente, int puertoCliente, int requestId);
    private:
        SocketDatagrama *socketlocal;
};

#endif
