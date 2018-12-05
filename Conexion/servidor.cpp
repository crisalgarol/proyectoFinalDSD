#include "Respuesta.h"
#include <iostream>
#include <cstring>
#include <string>
#include "Solicitud.h"

using namespace std;

int main(int argc, char** argv){
  int pto = atoi(argv[1]);
  Respuesta r(pto);
  struct mensaje m = r.getRequest();
  /*int i = 0; //contador
  int j = 0; // contador de oracion
  int k = 0; //contador de palindromos
  char id_server;
  char * oracion;
  char * palindromos;
  int encontre_id = 0;
  palindromos = new char[strlen(m.arguments)];
  oracion = new char[strlen(m.arguments)];
  cout << m.arguments << endl;
  while( m.arguments[i] != '\0'){
    if(m.arguments[i] == '!'){
      id_server = m.arguments[i-1];
      palindromos[k] = id_server;
      k++;
      palindromos[k] = '!';
      k++;
      encontre_id = 1;
    }
    else{
      if(m.arguments[i] == '|'){
        //verificar si es palindromo
        oracion[j+1] = '\0';
        cout << oracion << endl;
        bzero(oracion, strlen(m.arguments));
        j = 0;
        //copiar a la cadena a mandar
      }else if(encontre_id){
        oracion[j] = m.arguments[i];
        j++;
      }
    }
    i++;
  }
  cout << palindromos << endl;*/

  cout << m.arguments << endl;
  //Solicitud solicitud;
  /*char * ip = (char*)"10.100.74.35";
  int puerto = 1234;
  int id = 1;
  char* cadena = (char*)"puto";
  char * respuesta = solicitud.doOperation(ip, puerto, 1, cadena, id);*/
  return 0;
}
