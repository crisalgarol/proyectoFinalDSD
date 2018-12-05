#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
 
using namespace std;

int esPalindromo(char *, int);
string conversionAPlano(string);
string conversionAPlano(string texto);
vector<string> separarPalabras(string texto, int n);

int main () {
	
    int n = 0;
    int longitud;

    vector <string> palabrasObtenidas;
    vector <string> palindromos;

  	string cad_s;
	
	ifstream ifs("prueba.txt");
    string content( (std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()) );

    palabrasObtenidas = separarPalabras(content, 3);
    
    for(int i=0; i<palabrasObtenidas.size(); i++){
        cout << palabrasObtenidas.at(i) << endl;
    }



/*
    string limpio = conversionAPlano(content);//lo 
    longitud = strlen(limpio.c_str());
    cout<<longitud<<endl;

    char cadenalimpia[sizeof(limpio)];//declaro cadena limpia
	strcpy(cadenalimpia, limpio.c_str());//copio ahi lo leido	

    int resultado = esPalindromo(cadenalimpia, longitud);
    
    if (resultado) {
        cout<< cadenalimpia << " \nes palindroma"<< endl;
    } else {
        cout<< cadenalimpia <<" \nNO es palindroma"<< endl;
    }
    */
}

int esPalindromo(char * cadena, int longitud) {
    if (longitud <= 1) return 1; 
    int inicio = 0, fin = longitud - 1; 
    // Mientras el primer y último carácter sean iguales
    while (cadena[inicio] == cadena[fin]){
        // Aquí sólo resta un carácter por comparar, eso indica que SÍ es palíndroma
        if (inicio >= fin) return 1;
        // Vamos acortando la cadena
        inicio++;
        fin--;
    }
    // Si termina el ciclo y no se rompió, entonces no es palíndroma
    return 0;
}

string conversionAPlano(string texto){
    
    int tam = texto.length();
    int counter = 0;

    string textoLimpio = "";

    for (char& letra: texto){

        //Si hay un acento o la verirguilla de la n
        if(letra == (char)-61)
            continue;
        
        //Si es una enie Mayuscula
        if(letra == (char) -79 )
            textoLimpio += "}";
        
        else if(letra == (char)-111)
            textoLimpio += "{";
        
        
        //Si es una letra acentuada minuscula
        else if(letra == (char)-95 || letra == (char)-87 || letra == (char)-83 || letra == (char)-77 || letra == (char)-70){            
            switch((int)letra){
                case -95: textoLimpio+=")"; break;
                case -87: textoLimpio+="="; break;
                case -83: textoLimpio+="+"; break;
                case -77: textoLimpio+="-"; break;
                case -70: textoLimpio+="*"; break;
                default: break;
            }
        }

        

        //Si es una letra acentuada mayuscula
        else if(letra == (char)-127 || letra == (char)-119 || letra == (char)-115 || letra == (char)-109 || letra == (char)-102){
            switch((int)letra){
                case -127: textoLimpio+=")"; break;
                case -119: textoLimpio+="="; break;
                case -115: textoLimpio+="+"; break;
                case -109: textoLimpio+="-"; break;
                case -102: textoLimpio+="*"; break;
                default: break;
            }  
        }

        
        else if(((int)letra>=65 && (int)letra<= 90) || ((int)letra>=97 && (int)letra<= 122))
            textoLimpio+=letra;
        
    } 
    return textoLimpio;
}

vector<string> separarPalabras(string texto, int n){

    vector<string> palabras;
    vector <string> palabrasEnConjuntos;

    string palabraLeida;        
    string conjunto;


    /***Agrega todas las palabras separadas a palabras***/
    for(char letra: texto){


        if(letra == ' '){
            palabras.push_back(palabraLeida); 
            palabraLeida = "";
        }

        else if(letra == (char)-61) continue;
        
        //Si es una enie Mayuscula
        if(letra == (char) -79 )
            palabraLeida += "}";
        
        else if(letra == (char)-111)
            palabraLeida += "{";
        
        
        //Si es una letra acentuada minuscula
        else if(letra == (char)-95 || letra == (char)-87 || letra == (char)-83 || letra == (char)-77 || letra == (char)-70){            
            switch((int)letra){
                case -95: palabraLeida+=")"; break;
                case -87: palabraLeida+="="; break;
                case -83: palabraLeida+="+"; break;
                case -77: palabraLeida+="-"; break;
                case -70: palabraLeida+="*"; break;
                default: break;
            }
        }

        

        //Si es una letra acentuada mayuscula
        else if(letra == (char)-127 || letra == (char)-119 || letra == (char)-115 || letra == (char)-109 || letra == (char)-102){
            switch((int)letra){
                case -127: palabraLeida+=")"; break;
                case -119: palabraLeida+="="; break;
                case -115: palabraLeida+="+"; break;
                case -109: palabraLeida+="-"; break;
                case -102: palabraLeida+="*"; break;
                default: break;
            }  
        }

        
        else if(((int)letra>=65 && (int)letra<= 90) || ((int)letra>=97 && (int)letra<= 122))
            palabraLeida+=letra;
    }
    palabras.push_back(palabraLeida); 
    /**********************/
        
    while(palabras.size() >= n){

        for(int i=0; i<palabras.size(); i++){

            if(n==1 && i==0){
                palabrasEnConjuntos.push_back(palabras.at(0));
                continue;
            }

            else if( i!= 0 && ( ( (i+1)%n)==0) ){

                if(n!=1)
                    conjunto += " ";

                conjunto +=palabras.at(i);
                palabrasEnConjuntos.push_back(conjunto);
                conjunto = "";
            }else{
                conjunto += palabras.at(i);
                if((i+2) % n != 0)
                    conjunto += " ";
            }   
        }
        palabras.erase(palabras.begin());
        
    
        //cout << "***********" << endl;
    }

    return palabrasEnConjuntos;

}