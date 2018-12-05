#include <iostream>
#include <string>
#include <vector>

using namespace std;

string textobienloco = "Érase una vez una niña que era muy querida por su abuelita, a la que visitaba con frecuencia aunque vivía al otro lado del bosque. Su madre que sabía coser muy bien le había hecha una bonita caperuza roja que la niña nunca se quitaba, por lo que todos la llamaban Caperucita roja.Una tarde la madre la mandó a casa de la abuelita que se encontraba muy enferma, para que le llevara unos pasteles recién horneados, una cesta de pan y mantequilla.";

string conversionAPlano(string texto){
    
    int tam = texto.length();
    int counter = 0;

    string textoLimpio = "";

    for (char& letra: texto){
        
        //Si hay un acento o la verirguilla de la n
        if(letra == (char)-61)
            continue;
        
        //Si es una enie
        if(letra == (char) -79){
            textoLimpio += "}";
        }
        
        
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

int main(){


    //for(int i=0; i<1000; i++)
        cout << conversionAPlano(textobienloco) << endl;;


}