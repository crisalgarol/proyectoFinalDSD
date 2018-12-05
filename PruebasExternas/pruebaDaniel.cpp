#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ctype.h>
#include <stdio.h>
 
using namespace std;

bool esPalindromo(char *, int);
string conversionAPlano(string);
string conversionAPlano(string texto);
vector<string> separarPalabras(string texto, int n);
string serializar(vector<string> vectorus);

int main () {
	
    int n = 5;
    int longitud;

    vector <string> palabrasObtenidas;
    vector <string> palindromos;

  	string cad_s;
	
	ifstream ifs("prueba.txt");
    string content( (std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()) );

    int contadorDeNVueltas = n;

    while(contadorDeNVueltas >= 2){

            cout << "Iteracion para: " << contadorDeNVueltas << endl;
            cout << "_________________________________________________-" << endl;

            string listaDePalabras = serializar(palabrasObtenidas = separarPalabras(content, contadorDeNVueltas));
            separarPalabras(content, contadorDeNVueltas);
            cout << "Despues de lista" << endl;
            cout << listaDePalabras << endl;
            cout << listaDePalabras << endl;
            for(int i=0; i<palabrasObtenidas.size(); i++){

                cout << palabrasObtenidas.at(i) << endl; 

                string limpio = conversionAPlano(palabrasObtenidas.at(i));//lo 
                longitud = strlen(limpio.c_str());

                char cadenalimpia[sizeof(limpio)];//declaro cadena limpia
                strcpy(cadenalimpia, limpio.c_str());//copio ahi lo leido	

                if(esPalindromo(cadenalimpia, longitud))
                    palindromos.push_back(palabrasObtenidas.at(i));
                
            }


            cout << "Palindromos encontrados " << endl;
            for(int i=0; i<palindromos.size(); i++){
                //Buscar
                cout << palindromos.at(i) << endl;
            }

            contadorDeNVueltas--;
            cout << "_________________FIN________________________________\n\n" << endl << endl;
        }

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

int contadorEspacios(string cadena){

    int counter = 0;

    for(char &c: cadena){
        if(c == ' ')
            counter++;
    }

    return counter;

}

string conversionAPlano(string texto){
    
    int tam = texto.length();
    int counter = 0;

    string textoLimpio = "";

    for (char& letra: texto){

        if(letra != ' ')
            textoLimpio+=letra;
        
    } 
    return textoLimpio;
}

vector<string> separarPalabras(string texto, int n){

    vector<string> palabras;
    vector <string> palabrasEnConjuntos;

    int valorAnterior = 0;

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
                case -77: palabraLeida+="["; break;
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
                case -109: palabraLeida+="["; break;
                case -102: palabraLeida+="*"; break;
                default: break;
            }  
        }

        else if( (int)letra < 0)
            continue;

        
        else if(((int)letra>=65 && (int)letra<= 90) || ((int)letra>=97 && (int)letra<= 122))
            palabraLeida+= letra;
        
    }
    palabras.push_back(palabraLeida); 
    /**********************/


    int tamanoOriginalArregloPalabras = palabras.size();
        
    while(palabras.size() >= n){
        
            conjunto = "";

            for(int i=0; i<palabras.size(); i++){

                if(n==1 && i==0){
                    palabrasEnConjuntos.push_back(palabras.at(0));
                    continue;
                }

                else if( i!= 0 && ( ( (i+1)%n)==0) ){

                    if(n!=1)
                        conjunto += " ";

                    conjunto +=palabras.at(i);
                    
                    if(contadorEspacios(conjunto) == (n-1)){
                        palabrasEnConjuntos.push_back(conjunto);
                    }
                    
                    conjunto = "";
                    //cout << palabrasEnConjuntos.at(palabrasEnConjuntos.size()-1) << endl;
                }else{
                    conjunto += palabras.at(i);
                    if((i+2) % n != 0)
                        conjunto += " ";
                }   
            }
        
            if(n==1)
                break;

        if(valorAnterior != 0 && valorAnterior!=palabras.size()){
            cout << "Error, disminuyo" << endl;
            int bbbb;
            cin >> bbbb;
        }

        cout << "PS1: " << palabras.size() << endl;
        palabras.erase(palabras.begin());
        //cout << "Pase a la segunda etapa" << endl;
        valorAnterior = palabras.size();
    }

    return palabrasEnConjuntos;

}

string serializar(vector<string> vectorus){

    string devuelto = "";

    for(int i=0; i<vectorus.size(); i++){
        devuelto += vectorus.at(i) + "|";
    }

    cout<<"Salida de serializar" << endl;
    return devuelto;

}
