#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Solicitud.h"
#include <string>
#include <cstring>

using namespace std;

int puerto= 7200;

int main(void) {
  char *info;
  int s, res;
  unsigned int clilen;
  struct sockaddr_in server_addr, msg_to_client_addr;
  unsigned int from_len;        /* Longitd dirección fuente */
  s = socket(AF_INET, SOCK_DGRAM, 0);
  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);;
  server_addr.sin_port = htons(puerto);

  bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
  clilen = sizeof(msg_to_client_addr);
  info = (char*)malloc(4000);
  bzero(info, 4000);
  //while (1) {
    recvfrom(s, info, 4000, 0, (struct sockaddr *)&msg_to_client_addr, &clilen);
    printf("\nCliente conectado desde %s:%d\n",inet_ntoa(msg_to_client_addr.sin_addr),ntohs(msg_to_client_addr.sin_port));
    printf("%s\n", info);
    sendto(s, info, 4000, 0, (struct sockaddr *)&msg_to_client_addr, clilen);
  //}

  /*vector<char*> ip;
  ip.push_back((char*)"10.100.68.88"); //daniel
  ip.push_back((char*)"10.100.74.5");  //otrocarnal
  ip.push_back((char*)"10.100.74.35"); //danyparc
  ip.push_back((char*)"127.0.0.1");*/


  char** ip= (char**)malloc(4*sizeof(char*));
  for(int i = 0; i < 4; i++){
    ip[i] = (char*)malloc((16)*sizeof(char));
  }

  ip[0] = (char*)"10.100.68.88";
  ip[1] = (char*)"10.100.74.5";
  ip[2] = (char*)"10.100.74.35";
  ip[3] = (char*)"127.0.0.1";
  for(int j = 0; j < 4; j++){
    cout << ip[j] << endl;
  }

  Solicitud solicitud;
  vector<char*> resultados;
  char  * cadena = (char*)"1!anitalavalatina|holamundo|simonlamona|";
  for(int i = 0; i < 4; i++){
    char * r = solicitud.doOperation(ip[i], 9999, 1, cadena, 1);
    resultados.push_back(r);
  }
  for(int j = 0; j < resultados.size(); j++){
    cout << resultados[j];
  }
  return 0;

}
