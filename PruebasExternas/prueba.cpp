#include <iostream>
#include <string>
//á: 160 é: 130 í: 161 ó: 162 ú: 163 Á: 181 É: 144 Í: 214 Ó: 224 Ú: 23 ñ: 164 Ñ: 165

using namespace std;

string pa = "conservaráéíóú";


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
    string loco = "Ñandú";

    for (char& letra: loco){
        cout << (int)letra << endl;
    }



    cout << conversionAPlano(loco) << endl;
    

}