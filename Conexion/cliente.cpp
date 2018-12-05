#include "Solicitud.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv){
    Solicitud solicitud;
    char * ip = (char*)"127.0.0.1";
    int pto = 7200;
    int id = 1;
    char  * cadena = (char*)"1!anitalavalatina|holamundo|simonlamona|";
    char * respuesta = solicitud.doOperation(ip, pto, 1, cadena, id);

    return 0;
}
