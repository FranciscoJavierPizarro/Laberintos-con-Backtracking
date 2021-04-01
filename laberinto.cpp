//***************************************************************************
// File:   laberinto.cpp
// Author: Programación II. Universidad de Zaragoza
//         Francisco Javier Pizarro Martínez
//         Javier Salafranca Pradilla
// Date:   March 26, 2021
// Coms:   Implementación del tipo "Laberinto" para la práctica 3 de la asignatura
//***************************************************************************

#include "laberinto.hpp"
#include <unistd.h> // para "usleep"



//*************************************************************************
// Encontrar un camino en el laberinto
//*************************************************************************
bool mover(Laberinto& lab, int x, int y) {
    //Caso final bueno
    if ((y == lab.alto-2) && (x == lab.ancho-2)) {
        lab.mapa[x][y] = CAMINO;
        return true;
    }
    //No hemos llegado al final, debemos seguir moviendo
    else {
        //La casilla que nos han pasado esta vacia y en el tablero
        if ((y >= 1) && (x >= 1) && (y <= lab.alto-2) && (x <= lab.ancho-2) && (lab.mapa[x][y] == LIBRE)) {
            lab.mapa[x][y] = CAMINO;
            //Los cuatro posibles movimientos
            if(mover(lab, x + 1, y)) {
                return true;
            }
            if(mover(lab, x, y + 1)) {
                return true;
            }
            if(mover(lab, x - 1, y)) {
                return true;
            }
            if(mover(lab, x, y - 1)) {
                return true;
            }            
            //backtracking
            lab.mapa[x][y] = IMPOSIBLE;
            return false;
        }
        else {
            return false;
        }
        return false;
    }
}


void buscarCamino(Laberinto& lab, bool& encontrado) {
    encontrado = mover(lab, 1, 1);
}

//*************************************************************************
// Generar el laberinto
//*************************************************************************

void cargarLaberinto(const string nombFichero, Laberinto& lab) {
    ifstream f;
    string linea;
    int nColumnas = 0;
    int nFilas = 0;
    int contador = 0;
    bool actualizado = false;
    f.open(nombFichero);
    if(f.is_open()) {
        while (!f.eof()){
            getline(f,linea);
            nFilas++;
            for(int i = 0; i < linea.length(); i ++) {
                lab.mapa[i][contador] = linea[i];
                if(!actualizado) {
                    nColumnas++;
                }
            }
            contador++;
            actualizado = true;
        }
        lab.alto = nFilas;
        lab.ancho = nColumnas;
        f.close();
    }
    else {
        cout << "Error abriendo el fichero del laberinto de " << nombFichero << endl;
    }
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
        lab.mapa[col][fila] = MURO;
        //FIN
    }
    //estamos en la última columna
    else if(col == lab.ancho - 1) {
        lab.mapa[col][fila] = MURO;
        generarLaberinto(lab, densidad, fila + 1, 0);
    }
    //estamos en la primera fila del laberinto o en la primera columna o en la última fila
    else if(fila == 0 || col == 0 || fila == lab.alto - 1) {
        lab.mapa[col][fila] = MURO;
        generarLaberinto(lab, densidad, fila, col + 1);
    }
    //Caso normal
    else {
        //Generación aleatoria en base a la densidad
        float x;
        x = randINT(0,100)/100.0;
        if(x <= densidad) {
            lab.mapa[col][fila] = MURO;
        }
        else {
            lab.mapa[col][fila] = LIBRE;
        }
        //Recursividad
        generarLaberinto(lab, densidad, fila, col + 1);
    }
}


//*************************************************************************
// Visualizar el camino encontrado
//*************************************************************************


void mostrarAux(const Laberinto& lab, int x, int y) {
//estamos en el final
    if(x == lab.ancho - 1 && y == lab.alto - 1) {
        cout << "\033[1;36;41m" << lab.mapa[x][y] << "\033[0m";
        //FIN
    }
    //estamos en la última columna, así que hay que saltar y volver a la primera columna de la siguiente fila
    else if(x == lab.ancho - 1) {
        cout << "\033[1;36;41m" << lab.mapa[x][y] << "\033[0m" << endl;
        mostrarAux(lab, 0, y + 1);
    }
    //Caso normal
    else {
        //Recursividad
        if(lab.mapa[x][y] == MURO) {
            cout << "\033[1;36;41m" << lab.mapa[x][y] << "\033[0m";
        }
        else if(lab.mapa[x][y] == CAMINO){
            cout << "\033[1;36;46m" << lab.mapa[x][y] << "\033[0m";
        }
        else {
        cout << lab.mapa[x][y];
        }
        mostrarAux(lab, x + 1, y);
    }
}

// Pre:  "lab" es un laberinto correcto, según la especificación en el enunciado
// Post:  Se ha mostrado el laberinto por la salida estándar
// Coms:  Versión recursiva
void mostrarLaberintoR(const Laberinto& lab) {
    mostrarAux(lab, 0 ,0);
    cout << endl << endl;
}



// Pre:   "lab" es un laberinto correcto, según la especificación dada para el tipo
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
    cout << endl << endl << endl;
}
