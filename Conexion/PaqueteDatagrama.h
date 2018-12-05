#ifndef PAQUETEDATAGRAMA_H
#define PAQUETEDATAGRAMA_H

class PaqueteDatagrama {
  private:
    char *datos; //Almacena los datos
    char ip[16]; //Almacena la IP
    unsigned int longitud; //Almacena la longitud de la cadena de datos
    int puerto; //Almacena el puerto
  public:
    PaqueteDatagrama(char *, unsigned int, char *, int );
    PaqueteDatagrama(unsigned int );
    ~PaqueteDatagrama();
    char *obtieneDireccion();
    unsigned int obtieneLongitud();
    int obtienePuerto();
    char *obtieneDatos();
    void inicializaPuerto(int);
    void inicializaIp(char *);
    void inicializaDatos(char *);
};

#endif
