#include "Respuesta.h"
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Solicitud.h"

using namespace std;

bool esPalindromo(char *cadena, int longitud);
string serializar(vector<string> vectorus);

int main(int argc, char** argv){
  int pto = atoi(argv[1]);
  Respuesta r(pto);

  struct mensaje m = r.getRequest();
  
  /*Hacer un split*/
  vector <string> palindromosLista;
  vector <string> listaFrases;

  string p = "";
  char l = ' ';
  int itera = 0;

  while(l != '\0'){
    l = m.arguments[itera];

    if(l == '|'){
        listaFrases.push_back(p);
        p = "";
    }else{
      p+=l;
    }

    itera++;

  }

  /****VERIFICAR SI LAS PALABRAS RECIBIDAS SON PALINDROMOS***/
  for(int i=0; i<listaFrases.size(); i++){
    
    string pal = listaFrases.at(i);

    char cadenalimpia[ sizeof(pal)];
    strcpy(cadenalimpia, pal.c_str());

    bool resultado = esPalindromo(cadenalimpia, pal.length());

    if(resultado)
      palindromosLista.push_back(pal);


  }

  string datoAEnviar = serializar(palindromosLista);

  



  


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

  char arrayEnviar[datoAEnviar.size()+1];

  int iterador = 0;
  for(char &c:datoAEnviar){
      arrayEnviar[iterador] = c;
      iterador++;
  }

  arrayEnviar[iterador] = '\0';


  cout << m.arguments << endl;
  r.sendReply(arrayEnviar, m.IP, m.puerto, 1);
  //char*r, char*ipCliente, int puertoCliente, int requestId
  //Solicitud solicitud;s
  /*char * ip = (char*)"10.100.74.35";
  int puerto = 1234;
  int id = 1;
  char* cadena = (char*)"puto";
  char * respuesta = solicitud.doOperation(ip, puerto, 1, cadena, id);*/
  return 0;
}

bool esPalindromo(char *cadena, int longitud) {
    //if (longitud <= 1) return true; 
    int inicio = 0, fin = longitud - 1; 
    // Mientras el primer y último carácter sean iguales
    for(int i=0; cadena[i]; i++){
        cadena[i] = tolower(cadena[i]);
    }

    while (cadena[inicio] == cadena[fin]){
        // Aquí sólo resta un carácter por comparar, eso indica que SÍ es palíndroma
        if (inicio >= fin) return true;
        // Vamos acortando la cadena
        inicio++;
        fin--;
    }

    // Si termina el ciclo y no se rompió, entonces no es palíndroma
    return false;
}

string serializar(vector<string> vectorus){

    string devuelto = "";

    for(int i=0; i<vectorus.size(); i++){
        devuelto += vectorus.at(i) + "|";
    }

    cout<<"Salida de serializar" << endl;
    return devuelto;

}