//3CV15
//Alumnos: Gómez Martínez José Luis
//          Sánchez Torres Kevin Alexander
#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

char cadena_aux [50];     //cadena auxiliar GLOBAL TOKEN
char cadena_num[20];
char cadena_id[20];
char doble[3];

bool bandoble = false;
bool bandoble2 = false;

int num1 = 0;   //incrementador para cadena auxiliar
int num2 = 0;
int num3 = 0;
int y = 0;


char Reservadas[9][20] = {"if", "switch", "while", "case", "break", "for",
                        "else", "do", "default"};

char noTerminales[16][5] = {"(", ")", "[", "]", ";", "+", "-", "/", "*",
                        "<", ">", ".", ",", "=", "#", "!"};

string nombrenoTer[17] = {"parentesis_abierto", "parentesis_cerrado", "corchete_abierto",
                            "corchete_cerrado", "punto_y_coma", "mas", "menos", "diagonal",
                            "producto", "menor_que", "mayor_que", "punto", "coma", "igualdad",
                            "gato", "admiracion"};

char noTerminalesdobles[4][5] = {"==", "!=", "<=", ">="};

string nombrenoTd[4] = {"igual", "diferente", "menor_igual", "mayor_igual"};

void comprobardoble(char c1, char c2){
    doble[0] = c1;
    doble[1] = c2;

    for(int i = 0; i < sizeof(noTerminalesdobles) / 5; i++){
        if(strcmp(doble,noTerminalesdobles[i]) == 0){
            y = i;
            bandoble = true;
            bandoble2 = true;
        }
    }
}

bool VerificarNumero(char c){
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

bool VerificarPalabra(char c){
    if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'){
        return true;
    }
    return false;
}

void leercadena(char c){
    char letra[2];
    cadena_aux[num1] = c;
    num1++;

    if(cadena_aux[0] == ' '){
        num1--;
    }
    if(VerificarPalabra(c) || (VerificarNumero(c) && num3 > 0)){
        cadena_id[num3] = c;
        num3++;
    }
    if(VerificarNumero(c) && num3 == 0){
        cadena_num[num2] = c;
        num2++;
    }
    if(!VerificarNumero(cadena_aux[num1-1]) && cadena_num[0] != '\0'){
        cout<<"<num, "<<cadena_num<<">"<<endl;
        num2 = 0;
        memset(cadena_num, 0, 20);
        num1 = 0;
        memset(cadena_aux, 0, 50);
        cadena_aux[0] = c;
    }
    for(int i = 0; i < sizeof(Reservadas) / 20; i++){
        if(strcmp(cadena_aux,Reservadas[i]) == 0){
            cout<<"<id, "<<Reservadas[i]<<">"<<endl;
            num1 = 0;
            memset(cadena_aux, 0, 50);
        }
        if(strcmp(cadena_id,Reservadas[i]) == 0 || strcmp(cadena_id,noTerminales[i]) == 0){
            num3 = 0;
            memset(cadena_id, 0, 20);
        }
        if(strcmp(cadena_id,Reservadas[i]) != 0 && (cadena_aux[num1-1] == ' ' || !VerificarPalabra(cadena_aux[num1-1])) && cadena_id[0] != '\0'){
            cout<<"<id, "<<cadena_id<<">"<<endl;
            num3 = 0;
            memset(cadena_id, 0, 20);
            num1 = 0;
            memset(cadena_aux, 0, 50);
            cadena_aux[0] = c;
        }
    }
    letra[0] = c;
    for(int i = 0; i < sizeof(noTerminales)/5; i++){
        if(strcmp(cadena_aux,noTerminales[i]) == 0){
            if(bandoble == false && bandoble2 == false){
                cout<<"<"<<nombrenoTer[i]<<", "<<noTerminales[i]<<">"<<endl;
                num1 = 0;
                memset(cadena_aux, 0, 50);
            }
            if(bandoble == false && bandoble2 == true){
                bandoble2 = false;
            }
            if(bandoble == true){
                bandoble = false;
                cout<<"<"<<nombrenoTd[y]<<", "<<doble<<">"<<endl;
                num1 = 0;
                memset(cadena_aux, 0, 50);
            }
        }
    }
}

void recorrercadena(string cadena){
    for(int i=0; i<cadena.size(); i++){
        comprobardoble(cadena[i], cadena[i+1]);
        leercadena(cadena[i]);
    }
}

main(){
    string cadena;
    cout<<"Introduce una cadena: ";
    getline(cin, cadena);
    cout<<endl;
    recorrercadena(cadena);
}
