#include "laberinto.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;


//Para dar un formato adecuado a la salida
#include <windows.h>    
#include <cstdio>       
#pragma execution_character_set( "utf-8" )

int main (int numArg, char* args[]) {
    //ignorar (salida datos)
    SetConsoleOutputCP( 65001 );
    //ignorar
    Laberinto lab;
    bool encontrado;
    if(numArg == 2) {
        string ruta = args[1];
        cargarLaberinto(ruta, lab);
        mostrarLaberintoR(lab);        
        buscarCamino(lab, encontrado);
        if(encontrado) {
            mostrarLaberintoR(lab);
        }
        else {
            cout << "Solución no encontrada" << endl;
        }
        cout << endl << "Pulse cualquier letra y enter después para finalizar" << endl;
        char a;
        cin >> a;
        return 0;
    }
    //Opción generación laberinto, parametros ordenados: alto ancho densidad
    else if (numArg == 4) {
        time_t semilla = time(nullptr);  // tiempo actual como semilla
        srand (semilla);                  // Inicializa el generador de nums . pseudoaleatorios 
        lab.alto  = atoi(args[1]);
        lab.ancho = atoi(args[2]);
        float densidad = atof(args[3]);
        generarLaberinto(lab,densidad,0,0);
        mostrarLaberintoR(lab);
        buscarCamino(lab, encontrado);
        if(encontrado) {
            mostrarLaberintoR(lab);
        }
        else {
            cout << "Solución no encontrada" << endl;
        }
        cout << endl << "Pulse cualquier letra y enter después para finalizar" << endl;
        char a;
        cin >> a;
        return 0;
    }
    else {
        cout << "Error" << endl;
        return 1;
    }
}