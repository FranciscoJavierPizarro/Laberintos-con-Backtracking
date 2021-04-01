/***********************************************************************\
 * Módulo principal del programa laberinto
 * Autores:
 *         Franciso Javier Pizarro Martínez
 *         Javier Salafranca Pradilla
 * Última revisión del código:01/04/2021
 * Funcionamiento:El programa puede funcionar de dos formas distinas, en
 * ambas debemos añadir en el proceso de apertura del programa por
 * terminal, datos en la primera la ruta a un fichero .txt en el cual debe
 * existir un laberinto ya prediseñado.En la segunda, debemos introducir
 * los siguientes datos ancho alto y densidad deseadas para el laberinto
 * que vamos a generar
 \***********************************************************************/ 
#include <iostream>
#include <stdlib.h>
#include "laberinto.hpp"
using namespace std;

//Para dar un formato adecuado a la salida
#include <windows.h>    
#include <cstdio>       
#pragma execution_character_set( "utf-8" )

int main(int numArg, char* args[]) {
    //ignorar (salida datos)
    SetConsoleOutputCP( 65001 );
    //ignorar
    bool sol;
    Laberinto lab;
    lab.alto = MAX_DIM;
    lab.ancho = MAX_DIM;
    //Opción lectura fichero
    if(numArg == 2) {
        string ruta = args[1];
        cargarLaberinto(ruta, lab);
        mostrarLaberintoR(lab);        
        buscarCamino(lab, sol);
        if(sol) {
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
        time_t semilla = time ( nullptr );  // tiempo actual como semilla
        srand (semilla);                  // Inicializa el generador de nums . pseudoaleatorios 
        lab.alto  = atoi(args[1]);
        lab.ancho = atoi(args[2]);
        float densidad = atof(args[3]);
        generarLaberinto(lab,densidad,0,0);
        mostrarLaberintoR(lab);
        buscarCamino(lab, sol);
        if(sol) {
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