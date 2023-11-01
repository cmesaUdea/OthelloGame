#include <iostream>
#include <fstream>
#include <ctime>
//#include <vector>
#include <limits>
#include <windows.h>

using namespace std;

class Tablero {
public:
    static const int TAMANO = 8;
    char celdas[TAMANO][TAMANO];
    bool movimientosPosibles[TAMANO][TAMANO];

    Tablero() {
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                celdas[i][j] = ' ';
            }
        }
        celdas[3][3] = celdas[4][4] = '-';
        celdas[3][4] = celdas[4][3] = '*';
    }

    void mostrar() const {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        cout << endl;
        cout << "   1   2   3   4   5   6   7   8" << endl;
        for (int i = 0; i < TAMANO; i++) {
            cout << "  +---+---+---+---+---+---+---+---+" << endl;
            cout << i + 1 << " ";
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == '*') {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo para '*'
                } else if (celdas[i][j] == '-') {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Verde para '-'
                } else if (movimientosPosibles[i][j]) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // Azul para puntos de movimiento
                    cout << "| . ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    continue;
                }
                cout << "| " << celdas[i][j] << " ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            cout << "|" << endl;
        }
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }

    bool movimientoValido(int fila, int columna, char jugador) const {
        if (fila < 0 || fila >= TAMANO || columna < 0 || columna >= TAMANO || celdas[fila][columna] != ' ') {
            return false;
        }

        char rival = (jugador == '*') ? '-' : '*';

        bool valido = false;

        for (int df = -1; df <= 1; df++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (df == 0 && dc == 0) {
                    continue;
                }

                int f = fila + df;
                int c = columna + dc;

                if (f >= 0 && f < TAMANO && c >= 0 && c < TAMANO && celdas[f][c] == rival) {
                    f += df;
                    c += dc;
                    while (f >= 0 && f < TAMANO && c >= 0 && c < TAMANO) {
                        if (celdas[f][c] == ' ') {
                            break;
                        }
                        if (celdas[f][c] == jugador) {
                            valido = true;
                            break;
                        }
                        f += df;
                        c += dc;
                    }
                    if (valido) {
                        break;
                    }
                }
            }
            if (valido) {
                break;
            }
        }

        return valido;
    }

    void marcarMovimientosPosibles(char jugador) {
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                movimientosPosibles[i][j] = false;
            }
        }

        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == ' ') {
                    if (movimientoValido(i, j, jugador)) {
                        movimientosPosibles[i][j] = true;
                    }
                }
            }
        }
    }

    void realizarMovimiento(int fila, int columna, char jugador) {
        celdas[fila][columna] = jugador;
        char rival = (jugador == '*') ? '-' : '*';

        for (int df = -1; df <= 1; df++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (df == 0 && dc == 0) {
                    continue;
                }

                int f = fila + df;
                int c = columna + dc;
                bool fichasCapturadas = false;

                while (f >= 0 && f < TAMANO && c >= 0 && c < TAMANO) {
                    if (celdas[f][c] == rival) {
                        f += df;
                        c += dc;
                        fichasCapturadas = true;
                    } else if (celdas[f][c] == jugador) {
                        if (fichasCapturadas) {
                            f -= df;
                            c -= dc;
                            while (f != fila || c != columna) {
                                celdas[f][c] = jugador;
                                f -= df;
                                c -= dc;
                            }
                            break;
                        } else {
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    bool tableroCompleto() const {
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    int contarFichas(char jugador) const {
        int contador = 0;
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == jugador) {
                    contador++;
                }
            }
        }
        return contador;
    }
};

class Jugador {
public:
    char color;
    Jugador(char c) : color(c) {}
};

class Juego {
public:
    Jugador jugador1, jugador2;
    Tablero tablero;

    Juego(const string& nombre1, const string& nombre2)
        : jugador1('*'), jugador2('-'), nombreJugador1(nombre1), nombreJugador2(nombre2) {}

    void jugar() {
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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    void mostrarResultados() {
        ifstream archivo("resultados.txt");
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                cout << linea << endl;
            }
            archivo.close();
        }
    }

private:
    string nombreJugador1;
    string nombreJugador2;

    void guardarResultado(const string& ganador, int contadorNegras, int contadorBlancas) {
        ofstream archivo("resultados.txt", ios::app);
        if (archivo.is_open()) {
            time_t ahora = time(0);
            tm* infoTiempo = localtime(&ahora);
            archivo << "Fecha: " << (infoTiempo->tm_year + 1900) << '/' << (infoTiempo->tm_mon + 1) << '/'
                    << infoTiempo->tm_mday << " Hora: " << infoTiempo->tm_hour << ':' << infoTiempo->tm_min << endl;
            archivo << "Jugador 1: " << nombreJugador1 << ", Jugador 2: " << nombreJugador2 << endl;
            archivo << "Ganador: " << ganador << " (*): " << contadorNegras << ", (-): " << contadorBlancas << endl;
            archivo.close();
        }
    }
};

int main() {
    string nombreJugador1, nombreJugador2;
    cout << "Nombre del Jugador 1: ";
    cin >> nombreJugador1;
    cout << "Nombre del Jugador 2: ";
    cin >> nombreJugador2;

    Juego juego(nombreJugador1, nombreJugador2);
    juego.jugar();
    juego.mostrarResultados();

    return 0;
}
