#include "Juego.h"
#include "Tablero.h"
#include <iostream>
#include <fstream>
#include <ctime>

Juego::Juego(const std::string& nombre1, const std::string& nombre2)
    : nombreJugador1(nombre1), nombreJugador2(nombre2), jugador1('*'), jugador2('-') {
}

void Juego::jugar() {
    int turno = 0;
    while (true) {
        if (turno == 0) {
            cout << "\n" << nombreJugador1 << ", es tu turno (*)." << endl;
        } else {
            cout << "\n" << nombreJugador2 << ", es tu turno (-)." << endl;
        }

        tablero.marcarMovimientosPosibles((turno == 0) ? '*' : '-');
        tablero.mostrar();

        int fila, columna;
        bool movimientoValido = false;
        do {

            cout << "Ingresa la fila y columna (ejemplo: 2 3), o escribe la coordenado 0,0 para pasar el turno: ";
            cin >> fila;
            if (cin.peek() == ' ' || cin.peek() == '\t') {
                cin.ignore();
                cin >> columna;
            } else {
                cout << "Entrada no valida. Debes ingresar dos numeros separados por espacio. Ejemplo: (2 3)." << endl;
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (cin.fail()) {
                cin.clear();
                cout << "Entrada no valida. Debes ingresar dos numeros separados por espacio. Intentalo de nuevo." << endl;
            }else if ( fila == 0 && columna == 0 ) { //Condición para pasar el turno
                break;
            } else if (fila < 1 || fila > Tablero::TAMANO || columna < 1 || columna > Tablero::TAMANO) {
                cout << "Movimiento fuera de rango. Introduce numeros entre 1 y " << Tablero::TAMANO << ". Intentalo de nuevo." << endl;
            } else if (!tablero.movimientosPosibles[fila - 1][columna - 1]) {
                cout << "Movimiento invalido. Intentalo de nuevo." << endl;
            } else if (!tablero.movimientosPosibles[fila - 1][columna - 1]) {
                cout << "Movimiento invalido. Intentalo de nuevo." << endl;
            }
            else {
                movimientoValido = true;
            }
        } while (!movimientoValido);

        tablero.realizarMovimiento(fila - 1, columna - 1, (turno == 0) ? '*' : '-');

        turno = 1 - turno;

        if (tablero.tableroCompleto() || fila == 0 && columna == 0) {
            break;
        }
    }

    int contadorNegras = tablero.contarFichas('*');
    int contadorBlancas = tablero.contarFichas('-');
    string ganador = "Empate";
    if (contadorNegras > contadorBlancas) {
        ganador = nombreJugador1;
    } else if (contadorBlancas > contadorNegras) {
        ganador = nombreJugador2;
    }

    cout << "El juego ha terminado. Ganador: " << ganador << endl;
    cout << "Puntuacion: " << nombreJugador1 << " (*): " << contadorNegras << ", " << nombreJugador2 << " (-): " << contadorBlancas << endl;

    guardarResultado(ganador, contadorNegras, contadorBlancas);
}

void Juego::mostrarResultados() {
    ifstream archivo("resultados.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    }
}

void Juego::guardarResultado(const std::string& ganador, int contadorNegras, int contadorBlancas) {
    std::ofstream archivo("resultados.txt", std::ios::app);
    if (archivo.is_open()) {
        time_t ahora = time(0);
        tm* infoTiempo = localtime(&ahora);
        archivo << "Fecha: " << (infoTiempo->tm_year + 1900) << '/' << (infoTiempo->tm_mon + 1) << '/'
                << infoTiempo->tm_mday << " Hora: " << infoTiempo->tm_hour << ':' << infoTiempo->tm_min << std::endl;
        archivo << "Jugador 1: " << nombreJugador1 << ", Jugador 2: " << nombreJugador2 << std::endl;
        archivo << "Ganador: " << ganador << " (*): " << contadorNegras << ", (-): " << contadorBlancas << std::endl;
        archivo.close();
    }
}
