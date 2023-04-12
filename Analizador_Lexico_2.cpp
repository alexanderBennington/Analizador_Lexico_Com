#include<iostream>
#include<string.h>
#include <cstdlib>
#include <fstream>

using namespace std;

char* token;
char* token_num;
char* token_id;
char* token_cadena;

int num1 = 0;
int num2 = 0;
int num3 = 0;
int num4 = 0;
int num5 = 0;
int y = 0;

int bandcomen[] = {0,0};

char doble[3];

bool bandoble = false;
bool bandoble2 = false;
bool bandcadena = false;
bool bandauxcom = false;
bool bandcomlar = false;


char Reservadas[16][20] = {"and", "clase", "else", "false", "for", "fun", "if", "null", "or", "print",
                          "return", "super", "this", "true", "var", "while"};

char noTerminales[15][5] = {"(", ")", "{", "}", ",", ".", ";", "-", "+", "*", "/", "!", "=",
                            "<", ">"};

string nombrenoTer[15] = {"parentesis_abierto", "parentesis_cerrado", "llave_abierta",
                            "llave_cerrada", "coma", "punto", "punto_y_coma", "menos",
                            "mas", "asterisco", "diagonal", "admiracion", "igual", "menor_que",
                            "mayor_que"};

char noTerminalesdobles[4][5] = {"!=", "==", "<=", ">="};

string nombrenoTd[4] = {"difetente", "igual", "menor_igual", "mayor_igual"};

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

void AlmacenarCadena(char c, int tam)
{
    token_cadena[num4] = c;
    num4++;
    if(c == '"'){
        token_cadena[num4-1] = '\0';
        cout<<"<cadena, "<<token_cadena<<">"<<endl;
        bandcadena = false;
        num4 = 0;
        memset(token_cadena, 0, tam+1 * sizeof(char));
    }
}

void LeerCadena(char c, int tam){
    token[num1] = c;
    num1++;
    if(token[0] == ' '){
        num1--;
    }
    if(token[0] == '\n'){
        num1--;
    }
    if(VerificarPalabra(c) || (VerificarNumero(c) && num3 > 0)){
        token_id[num3] = c;
        num3++;
    }
    if(VerificarNumero(c) && num3 == 0){
        token_num[num2] = c;
        num2++;
    }
    if(!VerificarNumero(token[num1-1]) && token_num[0] != '\0'){
        cout<<"<num, "<<token_num<<">"<<endl;
        num2 = 0;
        memset(token_num, 0, tam+1 * sizeof(char));
        num1 = 0;
        memset(token, 0, tam+1 * sizeof(char));
        token[0] = c;
    }
    if(c == '/'){
        bandcomen[num5] = 1;
        num5++;
        if(bandcomen[0] == 1 && bandcomen[1] == 1){
            memset(token, 0, tam+1 * sizeof(char));
            memset(token_id, 0, tam+1 * sizeof(char));
            memset(token_num, 0, tam+1 * sizeof(char));
            num1 = 0;
            num2 = 0;
            num3 = 0;
            num4 = 0;
            bandauxcom = true;
        }
        return;
    }
    if (c == '*' && bandcomen[0] == 1){
        memset(token, 0, tam+1 * sizeof(char));
        memset(token_id, 0, tam+1 * sizeof(char));
        memset(token_num, 0, tam+1 * sizeof(char));
        num1 = 0;
        num2 = 0;
        num3 = 0;
        num4 = 0;
        num5 = 0;
        bandcomen[0] = 0;
        bandcomlar = true;
        return;
    }
    for(int i = 0; i < sizeof(Reservadas) / 20; i++){
        if(strcmp(token,Reservadas[i]) == 0){
            cout<<"<"<<Reservadas[i]<<">"<<endl;
            num1 = 0;
            memset(token, 0, tam+1 * sizeof(char));
        }
        if(strcmp(token_id,Reservadas[i]) == 0 || strcmp(token_id,noTerminales[i]) == 0){
            num3 = 0;
            memset(token_id, 0, tam+1 * sizeof(char));
        }
        if(strcmp(token_id,Reservadas[i]) != 0 &&
           (token[num1-1] == ' ' || !VerificarPalabra(token[num1-1]))
            && token_id[0] != '\0'){
            cout<<"<id, "<<token_id<<">"<<endl;
            num3 = 0;
            memset(token_id, 0, tam+1 * sizeof(char));
            num1 = 0;
            memset(token, 0, tam+1 * sizeof(char));
            token[0] = c;
        }
    }
    for(int i = 0; i < sizeof(noTerminales)/5; i++){
        if(strcmp(token,noTerminales[i]) == 0){
            if(bandoble == false && bandoble2 == false){
                cout<<"<"<<nombrenoTer[i]<<", "<<noTerminales[i]<<">"<<endl;
                num1 = 0;
                memset(token, 0, tam+1 * sizeof(char));
            }
            if(bandoble == false && bandoble2 == true){
                bandoble2 = false;
            }
            if(bandoble == true){
                bandoble = false;
                cout<<"<"<<nombrenoTd[y]<<", "<<doble<<">"<<endl;
                num1 = 0;
                memset(token, 0, tam+1 * sizeof(char));
            }
        }
    }
    if(c == '"' && num4 == 0){
        bandcadena = true;
        memset(token, 0, tam+1 * sizeof(char));
        memset(token_id, 0, tam+1 * sizeof(char));
        memset(token_num, 0, tam+1 * sizeof(char));
        num1 = 0;
        num2 = 0;
        num3 = 0;
    }
}

void RecorrerCadena(string cadena, int tam){
    string cadenaaux = cadena;
    int lon;
    int j = 0;
    int k = 0;
    for(int i=0; i < cadena.size(); i++){
        if(bandcadena){
            AlmacenarCadena(cadena[i], tam);
        }
        if(bandauxcom){
            cadenaaux.erase(0, i-k);
            lon = cadenaaux.find('\n');
            bandauxcom = false;
            k=i;
        }
        if(bandcomen[0] == 1 && bandcomen[1] == 1){
            if(j == lon){
                bandcomen[0] = 0;
                bandcomen[1] = 0;
            }
            j++;
            num5 = 0;
        }
        if(bandcomlar){
            if(cadena[i] == '/' && cadena[i-1] == '*'){
                bandcomlar = false;
                continue;
            }else{
                continue;
            }
        }
        if(!bandcadena && !bandcomlar && bandcomen[1] == 0){
            comprobardoble(cadena[i], cadena[i+1]);
            LeerCadena(cadena[i], tam);
            j=0;
        }
    }
}


int main(void){
    string cadena, contenido;
    int tam;
    int tam_archivo;
    FILE *fp;
    char* archivo;
    streampos tam_archivo_stream;

    while(cadena != "exit"){
        cout<<">>> ";
        getline(cin, cadena);

        tam = cadena.size();
        archivo = (char*)malloc(tam+1 * sizeof(char));
        memset(archivo, 0, tam+1 * sizeof(char));

        for(int i = 0; i < cadena.size(); i++){
            archivo[i] = cadena[i];
        }

        fp=fopen(archivo,"r");
        if(fp){
            fclose(fp);
            string linea;
            int numLinea = 1;
            ifstream doc(archivo, ifstream::ate | ifstream::binary);
            ifstream txt(archivo);
            if (doc.is_open()) {
                tam_archivo_stream = doc.tellg();

                while (getline(txt, linea)) {
                    contenido += linea + '\n';
                }

                txt.close();
                doc.close();
                cout << "El tamano del archivo es: " << tam_archivo_stream << " bytes." << endl;
                tam_archivo = static_cast<int>(tam_archivo_stream);
                cout << "El contenido del archivo es:\n" << contenido <<endl;

            } else {
                cerr << "No se pudo abrir el archivo." <<endl;
            }

            token = (char*)malloc(tam_archivo+1 * sizeof(char));
            token_id = (char*)malloc(tam_archivo+1 * sizeof(char));
            token_num = (char*)malloc(tam_archivo+1 * sizeof(char));
            token_cadena = (char*)malloc(tam_archivo+1 * sizeof(char));
            memset(token, 0, tam_archivo+1 * sizeof(char));
            memset(token_id, 0, tam_archivo+1 * sizeof(char));
            memset(token_num, 0, tam_archivo+1 * sizeof(char));
            memset(token_cadena, 0, tam_archivo+1 * sizeof(char));

            RecorrerCadena(contenido,tam_archivo);

            free(token);
            free(token_id);
            free(token_num);
            free(token_cadena);
            free(archivo);
            contenido = "";

            num1=0;
            num2=0;
            num3=0;
            num4=0;
            num5=0;

            cout<<endl;

        }else{
            token = (char*)malloc(tam+1 * sizeof(char));
            token_id = (char*)malloc(tam+1 * sizeof(char));
            token_num = (char*)malloc(tam+1 * sizeof(char));
            token_cadena = (char*)malloc(tam_archivo+1 * sizeof(char));
            memset(token, 0, tam+1 * sizeof(char));
            memset(token_id, 0, tam+1 * sizeof(char));
            memset(token_num, 0, tam+1 * sizeof(char));
            memset(token_cadena, 0, tam_archivo+1 * sizeof(char));

            RecorrerCadena(cadena, tam);

            free(token);
            free(token_id);
            free(token_num);
            free(token_cadena);
            free(archivo);

            num1=0;
            num2=0;
            num3=0;
            num4=0;
            num5=0;

            cout<<endl;
        }
    }

    return 0;
}
