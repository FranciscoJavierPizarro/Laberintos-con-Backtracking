//***************************************************************************
// File:   laberinto.cpp
// Author: Programación II. Universidad de Zaragoza
// Date:   March 26, 2021
// Coms:   Implementación del tipo "Laberinto" para la práctica 3 de la asignatura
//***************************************************************************

#include "laberinto.hpp"
#include <unistd.h> // para "usleep"

//*************************************************************************
// Encontrar un camino en el laberinto
//*************************************************************************
bool mover(Laberinto& lab, int y, int x) {
    //Caso final bueno
    if ((y == lab.alto-2) && (x == lab.ancho-2)) {
        return true;
    }
    //No hemos llegado al final, debemos seguir moviendo
    else {
        if(lab.mapa[y][x] == LIBRE && x >= 1) {
            lab.mapa[y][x] = CAMINO;
            if(mover(lab, y, x + 1)) {
                
                return true;
            }
            if(mover(lab, y + 1, x)) {
                
                return true;
            }
            if(mover(lab, y, x - 1)) {
                
                return true;
            }
            if(mover(lab, y - 1, x)) {
                
                return true;
            }
            lab.mapa[y][x] = IMPOSIBLE;
            return false;
        }
        else {
            return false;
        }
    }
}


void buscarCamino(Laberinto& lab, bool& encontrado) {
    encontrado = mover(lab, 1, 1);
}

//*************************************************************************
// Generar el laberinto
//*************************************************************************

void cargarLaberinto(const string nombFichero, Laberinto& lab) {
    ifstream f(nombFichero);
    char car;
    int nColumnas = 0;
    int colMax = 0;
    int nFilas = 0;
    int contador = 0;
    if(f.is_open()) {
        while (!f.eof()) {
            f.get(car);
            if(car == '\n') {
                nFilas++;
                nColumnas = 0;
            }
            else {
                lab.mapa[nFilas][nColumnas] = car;
                nColumnas++;
                if(nColumnas > colMax) {
                    colMax = nColumnas;
                }
            }
        }
        lab.alto = nFilas;
        lab.ancho = colMax;
    }
    else {
        cout << "Error abriendo el fichero" << endl;
    }
    f.close();
}
int randINT(const int a, const int b) {
    int num;
        // Asigna a num un pseudoaleatorio del intervalo [a,b]
    num = (a + rand () % (b - a + 1));
    return num;
}

void generarLaberinto(Laberinto &lab, double densidad, int fila, int col) {
    //estamos en el final
    if(col == lab.ancho - 1 && fila == lab.alto - 1) {
        lab.mapa[fila][col] = MURO;
        lab.alto++;
        //FIN
    }
    //estamos en la última columna
    else if(col == lab.ancho - 1) {
        lab.mapa[fila][col] = MURO;
        generarLaberinto(lab, densidad, fila + 1, 0);
    }
    //estamos en la primera fila del laberinto o en la primera columna o en la última fila
    else if(fila == 0 || col == 0 || fila == lab.alto - 1) {
        lab.mapa[fila][col] = MURO;
        generarLaberinto(lab, densidad, fila, col + 1);
    }
    //Caso normal
    else {
        //Generación aleatoria en base a la densidad
        float x;
        x = randINT(0,100)/100.0;
        if(x <= densidad) {
            lab.mapa[fila][col] = MURO;
        }
        else {
            lab.mapa[fila][col] = LIBRE;
        }
        //Recursividad
        generarLaberinto(lab, densidad, fila, col + 1);
    }
}

//*************************************************************************
// Visualizar el camino encontrado
//*************************************************************************

// Pre:   "lab" es un laberinto correcto
// Post:  Se ha mostrado el laberinto por la salida estándar
// Coms:  Versión iterativa
void mostrarLaberinto(const Laberinto& lab) {
    for (int i = 0; i < lab.alto; i++) {
        for (int j = 0; j < lab.ancho; j++) {
            cout << lab.mapa[i][j];
        }
        // Al acabar una fila, se cambia de línea
        cout << endl;
    }
}

void mostrar(const Laberinto& Lab, int fil, int col) {
    if(fil < Lab.alto && col < Lab.ancho) {
        if(Lab.mapa[fil][col] == CAMINO) {
            cout << "\033[1;32;42m" << Lab.mapa[fil][col] << "\033[0m";
        }
        else {
            cout << Lab.mapa[fil][col];
        }
        col++;
        mostrar(Lab, fil, col);
    }
    else if(fil < Lab.alto) {
        cout << endl;
        fil++;
        col = 0;
        mostrar(Lab, fil, col);
    }
    else {

    }
}


// Pre:  "lab" es un laberinto correcto
// Post:  Se ha mostrado el laberinto por la salida estándar
// Coms:  Versión recursiva
void mostrarLaberintoR(const Laberinto& lab) {
    mostrar(lab, 0, 0);
}
